#include <iostream>

#include <functional>
#include <map>
#include <set>
#include <string>
#include <functional>
#include <algorithm>
#include "Vipper/Vipper.h"
#include "Vipper/CLerp.h"
#include "Vipper/CAnimation.h"
#include "Modules/Gameplay/Entities/CColumn.h"
#include "Modules/Gameplay/Entities/CLevel.h"
#include "Modules/Gameplay/Entities/CGameSession.h"
#include "Modules/Gameplay/View/CGameplayView.h"
#include "Modules/Gameplay/View/CBlockAnimationHelper.h"

namespace BlockyFalls {
	CBlockAnimationHelper animationHelper;
	std::map<CColumn::EColour, int> coloursForBlocks;
	
	CGameplayView::CGameplayView(std::shared_ptr<CGameSession> session, std::shared_ptr<Vipper::IRenderer> renderer) : IView( renderer ), mGameSession( session ) {

		

		coloursForBlocks[ CColumn::EColour::eRed 	] = 0xFF0000;
		coloursForBlocks[ CColumn::EColour::eYellow ] = 0xFFFF00;
		coloursForBlocks[ CColumn::EColour::eGrey	] = 0x999999;
		coloursForBlocks[ CColumn::EColour::eBlue 	] = 0x0000FF;
		coloursForBlocks[ CColumn::EColour::eNothing] = 0x000000;
		coloursForBlocks[ CColumn::EColour::eSpecial] = 0x00FFFF;
		
			
		enum class EColour{ eRed, eYellow, eGrey, eBlue, eNothing};
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

		for ( int x = 0; x < CLevel::kNumberOfColumns; ++x ) {
			for ( int y = 0; y < CColumn::kColumnHeight; ++y ) {
				positions.insert( std::pair<int,int>(x, CColumn::kColumnHeight - y - 1 ));
			}
		}
		
		if ( exclusionList.size() > 0 ) {
			//std::cout << std::endl << "ignoring: ";
		}
		
		
		for ( auto& position : positions ) {

			if ( exclusionList.find( position ) != exclusionList.end() ) {
				//std::cout << "; " << position.first << ", " << position.second;
				continue;
			}

			int x = position.first;
			int y = position.second;
			auto piece = level->colourAt( x, CColumn::kColumnHeight - y - 1);
				
			auto colour = ( exclusionList.find( position ) != exclusionList.end() ) ?  coloursForBlocks[ CColumn::EColour::eSpecial ] : coloursForBlocks[ piece ];

			auto screenX0 = (x) * 64;
			auto screenY0 = ( (y ) * 64 );
			auto screenX1 = (x + 1) * 64;
			auto screenY1 = ( (y + 1) * 64 );
				
			renderer->drawSquare( screenX0, screenY0, screenX1, screenY1, colour );
		}

		animationHelper.draw( renderer );
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
				std::cout << "pusing " << block.first << ", " << ( CColumn::kColumnHeight - c - 1 ) << std::endl;
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
			exclusionList.erase( origin );

			if ( exclusionList.size() == 0 ) {
				
				generateDropAnimations( mGameSession->getLevel(), [&]( CColumn::CCoordinates origin) {
					
					exclusionList.erase( origin );
					
					if ( animationFinishedForColumn( origin.first ) ) {
						mGameSession->getLevel()->dropBlocksAboveEmptySpaces( origin.first );
					}
					
					if ( exclusionList.size() == 0 ) {
						generateColumnCollapseAnimations( mGameSession->getLevel(), [&](CColumn::CCoordinates block){							
							// block.second = -block.second + CColumn::kColumnHeight - 1;
							// block.first++; //this looks suspicious and smells of logical error
							exclusionList.erase( block );
							// //std::cout << "exclusionList: ";
							// for ( auto& pair : exclusionList ) {
							// 	//std::cout << ";" << pair.first << ", " << pair.second;
							// }
							// //std::cout << std::endl;

							std::cout << "removing " << block.first << ", " << block.second << std::endl;
							if ( exclusionList.size() == 0 ) {
								std::cout << "------\n\n" << std::endl;								
								// //std::cout << "finished column collapse animation" << std::endl;
								
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
			//std::cout << "busy" << std::endl;
			return;
		}
		mGameSession->getLevel()->addRandomColumn();
	}
}
