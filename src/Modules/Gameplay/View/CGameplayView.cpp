#include <string>
#include "Vipper/Vipper.h"
#include "Modules/Gameplay/Entities/CLevel.h"
#include "Modules/Gameplay/View/CGameplayView.h"

namespace BlockyFalls {
	CGameplayView::CGameplayView(std::shared_ptr<Vipper::IRenderer> renderer) : IView( renderer ) {
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
		getRenderer()->drawSquare( 0, 0, 640, 480, 0 );		
		getRenderer()->drawSquare( mLastClick.first, mLastClick.second, mLastClick.first + 50, mLastClick.second + 50, 0x0000FF );
	}
	
	void CGameplayView::onClick( std::pair<int, int> position ) {
		mLastClick = position;
	}
}
