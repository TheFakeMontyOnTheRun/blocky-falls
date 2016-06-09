#include "Vipper/Vipper.h"
#include "Vipper/CLerp.h"

#include "Modules/Gameplay/Entities/CColumn.h"

#include "Modules/TitleScreen/View/CRect.h"
#include "Modules/TitleScreen/View/CPlayButton.h"
#include "Modules/TitleScreen/View/CTitleScreenView.h"
#include "Modules/TitleScreen/Presenter/CTitleScreenPresenter.h"

namespace BlockyFalls {
	
	Vipper::CLerp lerp(0 , 200, 2000);
	long ellapsed = 0;
	CTitleScreenView::CTitleScreenView( std::shared_ptr<Vipper::IRenderer> renderer ) : IView( renderer ) {
		mButton.mBounds = CRect( 200, 300, 250, 350 );
	}
	
	void CTitleScreenView::show() {
		auto renderer = getRenderer();
		renderer->drawSquare( 0,0, 640, 480, 0 );
		ellapsed += 33;
		long delta = lerp.getValue( ellapsed );
		renderer->drawSquare( mButton.mBounds.mX0 + delta, mButton.mBounds.mY0, mButton.mBounds.mX1 + delta, mButton.mBounds.mY1, 0xFF0000 );	
	}
	
	void CTitleScreenView::onClick( std::pair<int, int> position ) {
		std::dynamic_pointer_cast<CTitleScreenPresenter>(getPresenter())->onClickOnPlayButton();
	}
}