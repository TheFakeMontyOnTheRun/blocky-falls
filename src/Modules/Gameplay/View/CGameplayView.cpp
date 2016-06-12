#include <iostream>

#include <functional>
#include <map>
#include <set>
#include <string>
#include <functional>
#include <algorithm>
#include "Vipper/Vipper.h"
#include "Vipper/CLerp.h"

#include "Modules/Gameplay/Entities/CColumn.h"
#include "Modules/Gameplay/Entities/CLevel.h"
#include "Modules/Gameplay/Entities/CGameSession.h"
#include "Modules/Gameplay/View/CGameplayView.h"

#include "Vipper/CAnimation.h"

#include "Modules/Gameplay/View/CBlockAnimationHelper.h"



namespace BlockyFalls {
	CBlockAnimationHelper animationHelper;
	
	CGameplayView::CGameplayView(std::shared_ptr<CGameSession> session, std::shared_ptr<Vipper::IRenderer> renderer) : IView( renderer ), mGameSession( session ) {

		mBitmapsForColours[ CColumn::EColour::eRed		] = renderer->loadBitmap( "res/red.png" );
		mBitmapsForColours[ CColumn::EColour::eYellow	] = renderer->loadBitmap( "res/yellow.png" );
		mBitmapsForColours[ CColumn::EColour::eGrey		] = renderer->loadBitmap( "res/grey.png" );
		mBitmapsForColours[ CColumn::EColour::eBlue 	] = renderer->loadBitmap( "res/blue.png" );

		mBitmapsForColours[ CColumn::EColour::eSpark1 	] = renderer->loadBitmap( "res/spark1.png" );
		mBitmapsForColours[ CColumn::EColour::eSpark2	] = renderer->loadBitmap( "res/spark2.png" );
		mBitmapsForColours[ CColumn::EColour::eSpark3	] = renderer->loadBitmap( "res/spark3.png" );
		mBitmapsForColours[ CColumn::EColour::eSpark4	] = renderer->loadBitmap( "res/spark4.png" );
		mBitmapsForColours[ CColumn::EColour::eSpark5	] = renderer->loadBitmap( "res/spark5.png" );

		mFallSound = renderer->loadSound( "res/fall.wav" );
		mCollapseSound = renderer->loadSound( "res/collapse.wav" );
    	mBustedSound = renderer->loadSound("res/busted.wav");
	}

    void CGameplayView::drawSquareAt( std::tuple<int, int, CColumn::EColour> block ) {
	}
	
    void CGameplayView::drawTextAt( std::pair<int, int> position, std::string text ) {
	}
	
    void CGameplayView::drawGaugeAt( std::pair<int, int> position, float howFilled) {
	}
	
    std::pair<int, int> CGameplayView::getLastClick() {
		return std::pair<int, int>( 0, 0 );	
	}
	
    void CGameplayView::show() {
		auto renderer = getRenderer();
		renderer->drawSquare( 0, 0, 640, 480, 0 );
	
		auto level = mGameSession->getLevel();
		
		std::set<std::pair<int,int>> positions;

		static const auto drawBlock = [&](std::pair<float,float> blockPosition, CColumn::EColour piece ) {
			auto x = blockPosition.first;
			auto y = blockPosition.second;			
			auto screenX0 = (x * 64);
			auto screenY0 = ( y  * 64 );
			renderer->drawBitmapAt( screenX0, screenY0, 64, 64, mBitmapsForColours[ piece ]);
		};

		for ( int x = 0; x < CLevel::kNumberOfColumns; ++x ) {
			for ( int y = 0; y < CColumn::kColumnHeight; ++y ) {
				positions.insert( std::pair<int,int>(x, CColumn::kColumnHeight - y - 1 ));
			}
		}
		
		for ( auto& position : positions ) {

			if ( exclusionList.find( position ) != exclusionList.end() ) {
				continue;
			}

			auto piece = level->colourAt( position.first, CColumn::kColumnHeight - position.second - 1);				
			drawBlock( position, piece );
		}

		animationHelper.draw( renderer, drawBlock );
	}
	
	void CGameplayView::generateExplosions( std::shared_ptr<CLevel> level, std::function<void(std::pair<int,int>)> onExplosionsFinished ) {
		std::vector< CColumn::CCoordinates > positions = mGameSession->getLevel()->breakBlockAt( mLastClick );
		
		for ( auto& origin : positions ) {
			exclusionList.insert( origin );
		}

		animationHelper.vanishBlock( positions, onExplosionsFinished );
	}
	
	void CGameplayView::generateDropAnimations( std::shared_ptr<CLevel> level, std::function<void(std::pair<int,int>)> onDropsFinished ) {
		auto positions = mGameSession->getLevel()->getDropList();

		if ( positions.size() > 0 ) {
			for ( auto& path : positions ) {
				exclusionList.insert( std::get<0>(path) );
			}	
			animationHelper.animateFallingBlocks( positions, onDropsFinished );
		} else {
			onDropsFinished( std::pair<int, int>(0,0) );
		}
	}
	
	void CGameplayView::generateColumnCollapseAnimations( std::shared_ptr<CLevel> level, std::function<void(std::pair<int,int>)> onCollapseFinished ) {
		auto columns = mGameSession->getLevel()->getColumnCollapseList();
		
		for ( auto& movement : columns ) {
			std::vector<CColumn::EColour> column;
			
			for ( int c = 0; c < CColumn::kColumnHeight; ++c ) {
				auto block = std::pair<int, int>( movement.first, c );
				auto colour = mGameSession->getLevel()->colourAt( block.first, block.second );

				if ( colour == CColumn::EColour::eNothing ) {
					continue;
				}

				column.push_back( colour  );
				exclusionList.insert( std::pair<int, int>( block.first, CColumn::kColumnHeight - c - 1 ) );
			}
			animationHelper.moveColumn( movement, column, onCollapseFinished );				
		}
	}
	
	bool CGameplayView::animationFinishedForColumn( int x ) {
		
		for( auto& position : exclusionList ) {
			if ( position.first == x ) {
				return false;
			}
		}

		return true;
	} 
	
	void CGameplayView::onClick( std::pair<int, int> position ) {

		if ( exclusionList.size() > 0 ) {
			return;
		}

		mLastClick.first = position.first / 64;
		mLastClick.second = CColumn::kColumnHeight - ( position.second / 64 ) - 1;

		auto onExplosionsFinished = [&]( CColumn::CCoordinates origin ){
			
			if ( exclusionList.size() > 0 ) {
				getRenderer()->playSound( mBustedSound );
			}
			
			exclusionList.erase( origin );

			if ( exclusionList.size() == 0 ) {
				
				generateDropAnimations( mGameSession->getLevel(), [&]( CColumn::CCoordinates origin) {
					
					if ( exclusionList.size() > 0 ) {
						getRenderer()->playSound( mFallSound );
					}

					exclusionList.erase( origin );
					
					if ( animationFinishedForColumn( origin.first ) ) {
						mGameSession->getLevel()->dropBlocksAboveEmptySpaces( origin.first );
					}
					
					if ( exclusionList.size() == 0 ) {
						generateColumnCollapseAnimations( mGameSession->getLevel(), [&](CColumn::CCoordinates block){							

							if ( exclusionList.size() > 0 ) {
								getRenderer()->playSound( mCollapseSound );
							}

							exclusionList.erase( block );

							if ( exclusionList.size() == 0 ) {

								mGameSession->getLevel()->collapseEmptyColumns();
							}	
						});
					}
				});	
			}
		};
				
		generateExplosions( mGameSession->getLevel(), onExplosionsFinished);
	}
	
	void CGameplayView::onKey( long keyCode ) {
		if ( exclusionList.size() > 0 ) {
			return;
		}
		mGameSession->getLevel()->addRandomColumn();
	}
}
