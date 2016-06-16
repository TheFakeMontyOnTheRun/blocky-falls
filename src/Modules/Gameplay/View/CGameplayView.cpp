#include <iostream>
#include <array>
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

		mBitmapsForColours[ CColumn::EColour::eRed	] = renderer->loadBitmap( "res/red.png" );
		mBitmapsForColours[ CColumn::EColour::eYellow	] = renderer->loadBitmap( "res/yellow.png" );
		mBitmapsForColours[ CColumn::EColour::eGrey	] = renderer->loadBitmap( "res/grey.png" );
		mBitmapsForColours[ CColumn::EColour::eBlue 	] = renderer->loadBitmap( "res/blue.png" );

		mBitmapsForColours[ CColumn::EColour::eSpark1 	] = renderer->loadBitmap( "res/spark1.png" );
		mBitmapsForColours[ CColumn::EColour::eSpark2	] = renderer->loadBitmap( "res/spark2.png" );
		mBitmapsForColours[ CColumn::EColour::eSpark3	] = renderer->loadBitmap( "res/spark3.png" );
		mBitmapsForColours[ CColumn::EColour::eSpark4	] = renderer->loadBitmap( "res/spark4.png" );
		mBitmapsForColours[ CColumn::EColour::eSpark5	] = renderer->loadBitmap( "res/spark5.png" );

		mFallSound = renderer->loadSound( "res/fall.wav" );
		mCollapseSound = renderer->loadSound( "res/collapse.wav" );
    	mBustedSound = renderer->loadSound("res/busted.wav");
    	mPullSound = renderer->loadSound("res/pull.wav");

		mUIFont = renderer->loadFont( "res/albaregular.ttf", 15 );
	}
	
    void CGameplayView::drawTextAt( std::pair<int, int> position, std::string text ) {
		auto renderer = getRenderer();
		renderer->drawTextAt( position.first, position.second, text, {0xFF, 0xFF, 0x00, 0xFF }, mUIFont  );
	}
	
    void CGameplayView::drawGaugeAt( std::pair<int, int> position, int howFilled) {
		auto renderer = getRenderer();
		renderer->drawSquare(position.first, position.second, 100, position.second + 20, {0,0,255,255});
		renderer->drawSquare(position.first, position.second, howFilled, position.second + 20, {255,0,0,255});
	}
	
    std::pair<int, int> CGameplayView::getLastClick() {
		return std::pair<int, int>( 0, 0 );	
	}

    void CGameplayView::show() {
		auto renderer = getRenderer();
		renderer->drawSquare( 0, 0, 640 - 64, 480, {0,0,0,255} );
	
		auto level = mGameSession->getLevel();
		
		std::set<std::pair<int,int>> positions;

		const auto drawBlock = [&](std::pair<float,float> blockPosition, CColumn::EColour piece ) {
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

	void CGameplayView::setClickDelegate(std::function<void(std::pair<int,int>)> delegate) {
		mClickDelegate = delegate;
	}
	
	void CGameplayView::setKeyDelegate(std::function<void(long keyCode)> delegate) {
		mKeyDelegate = delegate;
	}

	void CGameplayView::drawLimitLine() {
		auto renderer = getRenderer();
		renderer->drawSquare( 640 - 64, 0, 640, 480, {255,0,0,255} );
	}

	void CGameplayView::generateExplosions( std::shared_ptr<CLevel> level, std::function<void(std::pair<int,int>)> onExplosionsFinished ) {
		std::vector< CColumn::CCoordinates > positions = mGameSession->getLevel()->breakBlockAt( mLastClick );
		
		int score = 1;

		for ( auto& origin : positions ) {
			exclusionList.insert( origin );
			++score;
		}

		mGameSession->addToScore( score );

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

	bool CGameplayView::hasAllAnimationsCeased() {
		return exclusionList.size() == 0;
	}
	
	void CGameplayView::onPull() {
		getRenderer()->playSound( mPullSound );
	}

	void CGameplayView::onClick( std::pair<int, int> position ) {
		if ( !hasAllAnimationsCeased() ) {
			return;
		}

		if ( mClickDelegate != nullptr ) {
			mClickDelegate( position );
		}

		mLastClick.first = position.first / 64;
		mLastClick.second = CColumn::kColumnHeight - ( position.second / 64 ) - 1;

		const auto onExplosionsFinished = [&]( CColumn::CCoordinates origin ){
			if ( !hasAllAnimationsCeased() ) {
				getRenderer()->playSound( mBustedSound );
			}
			
			exclusionList.erase( origin );

			if ( hasAllAnimationsCeased() ) {
				generateDropAnimations( mGameSession->getLevel(), [&]( CColumn::CCoordinates origin) {
					
					if ( !hasAllAnimationsCeased() ) {
						getRenderer()->playSound( mFallSound );
					}

					exclusionList.erase( origin );
					
					if ( animationFinishedForColumn( origin.first ) ) {
						mGameSession->getLevel()->dropBlocksAboveEmptySpaces( origin.first );
					}
					
					if ( hasAllAnimationsCeased() ) {

						generateColumnCollapseAnimations( mGameSession->getLevel(), [&](CColumn::CCoordinates block){							
	
							if ( !hasAllAnimationsCeased() ) {
								getRenderer()->playSound( mCollapseSound );
							}

							exclusionList.erase( block );

							if ( hasAllAnimationsCeased() ) {
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
		if ( !hasAllAnimationsCeased() ) {
			return;
		}

		if ( mKeyDelegate != nullptr ) {
			mKeyDelegate( keyCode );
		}
	}
}
