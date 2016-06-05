#include <iostream>
#include <map>
#include <string>
#include "Vipper/Vipper.h"
#include "Modules/Gameplay/Entities/CLevel.h"
#include "Modules/Gameplay/Entities/CGameSession.h"
#include "Modules/Gameplay/View/CGameplayView.h"

namespace BlockyFalls {
	
	std::map<CLevel::EColour, int> coloursForBlocks;
	
	CGameplayView::CGameplayView(std::shared_ptr<CGameSession> session, std::shared_ptr<Vipper::IRenderer> renderer) : IView( renderer ), mGameSession( session ) {

		
		coloursForBlocks[ CLevel::EColour::eRed 	] = 0xFF0000;
		coloursForBlocks[ CLevel::EColour::eYellow 	] = 0xFFFF00;
		coloursForBlocks[ CLevel::EColour::eGrey	] = 0x999999;
		coloursForBlocks[ CLevel::EColour::eBlue 	] = 0x0000FF;
		coloursForBlocks[ CLevel::EColour::eNothing ] = 0x0;
			
		enum class EColour{ eRed, eYellow, eGrey, eBlue, eNothing};
	}

    void CGameplayView::drawSquareAt( std::tuple<int, int, CLevel::EColour> block ) {
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
			for ( int y = 0; y < CLevel::kColumnHeight; ++y ) {
				auto piece = level->colourAt( x, y );
				
				auto colour = coloursForBlocks[ piece ];
				
				renderer->drawSquare( x * 64, y * 64, (x + 1) * 64, (y + 1) * 64, colour );
			}
		}
	}
	
	void CGameplayView::onClick( std::pair<int, int> position ) {
		mLastClick = position;
		
		mGameSession->getLevel()->breakBlockAt( position );
	}
}
