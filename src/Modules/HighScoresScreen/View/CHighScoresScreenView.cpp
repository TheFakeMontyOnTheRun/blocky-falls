#include <array>
#include <iostream>
#include "Vipper/Vipper.h"
#include "Modules/HighScoresScreen/Presenter/CHighScoresScreenPresenter.h"
#include "Modules/HighScoresScreen/View/CHighScoresScreenView.h"

namespace BlockyFalls {
	CHighScoresScreenView::CHighScoresScreenView(std::shared_ptr<Vipper::IRenderer> renderer):
	IView( renderer ){
		mTitleTextFont = renderer->loadFont( "res/albasuper.ttf", 40 );
	}
	
	void CHighScoresScreenView::show() {
		auto renderer = getRenderer();
		renderer->drawTextAt( 30, 50, "Game Over!", {255,0,255,255}, mTitleTextFont );	
	}
	
	void CHighScoresScreenView::onClick( std::pair<int, int> position ) {
		std::dynamic_pointer_cast<CHighScoresScreenPresenter>(getPresenter())->onClickOnOkButton();
	}
}
