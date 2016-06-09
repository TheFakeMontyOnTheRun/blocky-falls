#include <iostream>
#include <map>
#include <string>
#include <functional>
#include "Vipper/Vipper.h"
#include "Modules/Gameplay/Entities/CColumn.h"
#include "Modules/Gameplay/Entities/CLevel.h"
#include "Modules/Gameplay/Entities/CGameSession.h"
#include "Modules/Gameplay/View/CGameplayView.h"

namespace BlockyFalls {
	
	std::map<CColumn::EColour, int> coloursForBlocks;
	
	CGameplayView::CGameplayView(std::shared_ptr<CGameSession> session, std::shared_ptr<Vipper::IRenderer> renderer) : IView( renderer ), mGameSession( session ) {

		
		coloursForBlocks[ CColumn::EColour::eRed 	] = 0xFF0000;
		coloursForBlocks[ CColumn::EColour::eYellow ] = 0xFFFF00;
		coloursForBlocks[ CColumn::EColour::eGrey	] = 0x999999;
		coloursForBlocks[ CColumn::EColour::eBlue 	] = 0x0000FF;
		coloursForBlocks[ CColumn::EColour::eNothing] = 0x00FF00;
			
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
		renderer->drawSquare( mLastClick.first, mLastClick.second, mLastClick.first + 50, mLastClick.second + 50, 0x0000FF );
	
		auto level = mGameSession->getLevel();
		
		for ( int x = 0; x < CLevel::kNumberOfColumns; ++x ) {
			for ( int y = 0; y < CColumn::kColumnHeight; ++y ) {
				auto piece = level->colourAt( x, CColumn::kColumnHeight - y - 1);
				
				auto colour = coloursForBlocks[ piece ];
				
				auto screenX0 = (x) * 64;
				auto screenY0 = ( (y ) * 64 );
				auto screenX1 = (x + 1) * 64;
				auto screenY1 = ( (y + 1) * 64 );
				
				renderer->drawSquare( screenX0, screenY0, screenX1, screenY1, colour );
			}
		}
	}
	
	void CGameplayView::generateExplosions( std::shared_ptr<CLevel> level, std::function<void()> onExplosionsFinished ) {
		onExplosionsFinished();
	}
	
	void CGameplayView::generateDropAnimations( std::shared_ptr<CLevel> level, std::function<void()> onDropsFinished ) {
		onDropsFinished();
	}
	
	void CGameplayView::generateColumnCollapseAnimations( std::shared_ptr<CLevel> level, std::function<void()> onCollapseFinished ) {
		onCollapseFinished();
	}
	
	
	void CGameplayView::onClick( std::pair<int, int> position ) {
		mLastClick.first = position.first / 64;
		mLastClick.second = CColumn::kColumnHeight - ( position.second / 64 ) - 1;
		
		mGameSession->getLevel()->breakBlockAt( mLastClick );
		
		generateExplosions( mGameSession->getLevel(), [&](){
			generateDropAnimations( mGameSession->getLevel(), [&] {
				mGameSession->getLevel()->dropBlocksAboveEmptySpaces();
				generateColumnCollapseAnimations( mGameSession->getLevel(), [&](){
					mGameSession->getLevel()->collapseEmptyColumns();			
				});
			});	
		});
	}
	
	void CGameplayView::onKey( long keyCode ) {
		mGameSession->getLevel()->addRandomColumn();
	}
}
