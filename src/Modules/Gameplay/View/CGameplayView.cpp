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

		for ( auto& position : positions ) {

			if ( exclusionList.find( position ) != exclusionList.end() ) {
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

		if (animationHelper.draw( renderer ) ) {
			// return;
		}		
	}
	
	void CGameplayView::generateExplosions( std::shared_ptr<CLevel> level, std::function<void(std::pair<int,int>)> onExplosionsFinished ) {
		std::vector< std::pair< int, int > > positions = mGameSession->getLevel()->breakBlockAt( mLastClick );
		animationHelper.vanishBlock( positions, onExplosionsFinished );
	}
	
	void CGameplayView::generateDropAnimations( std::shared_ptr<CLevel> level, std::function<void(std::pair<int,int>)> onDropsFinished ) {
		auto positions = mGameSession->getLevel()->getDropList();

		for ( auto& path : positions ) {
			auto origin = std::get<0>(path);
			exclusionList.insert( origin );
		}

		animationHelper.animateFallingBlocks( positions, onDropsFinished );
	}
	
	void CGameplayView::generateColumnCollapseAnimations( std::shared_ptr<CLevel> level, std::function<void()> onCollapseFinished ) {
		onCollapseFinished();
	}
	
	
	void CGameplayView::onClick( std::pair<int, int> position ) {
		mLastClick.first = position.first / 64;
		mLastClick.second = CColumn::kColumnHeight - ( position.second / 64 ) - 1;
				
		generateExplosions( mGameSession->getLevel(), [&]( std::pair<int, int> origin ){



			generateDropAnimations( mGameSession->getLevel(), [&]( std::pair<int, int> origin) {

				exclusionList.erase( origin );
				mGameSession->getLevel()->dropBlocksAboveEmptySpaces( origin.first );

				if ( exclusionList.size() == 0 ) {
					generateColumnCollapseAnimations( mGameSession->getLevel(), [&](){
						mGameSession->getLevel()->collapseEmptyColumns();	
					});
				}
			});	
		});
	}
	
	void CGameplayView::onKey( long keyCode ) {
		mGameSession->getLevel()->addRandomColumn();
	}
}
