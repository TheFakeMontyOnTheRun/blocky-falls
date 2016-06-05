#include "Vipper/Vipper.h"
#include "Modules/TitleScreen/View/CRect.h"
#include "Modules/TitleScreen/View/CPlayButton.h"
#include "Modules/TitleScreen/View/CTitleScreenView.h"
#include "Modules/TitleScreen/Presenter/CTitleScreenPresenter.h"

namespace BlockyFalls {
	
	CTitleScreenView::CTitleScreenView( std::shared_ptr<Vipper::IRenderer> renderer ) : IView( renderer ) {
		mButton.mBounds = CRect( 200, 300, 250, 350 );
	}
	
	void CTitleScreenView::show() {
		getRenderer()->drawSquare( mButton.mBounds.mX0, mButton.mBounds.mY0, mButton.mBounds.mX1, mButton.mBounds.mY1, 0xFF0000 );	
	}
	
	void CTitleScreenView::onClick( std::pair<int, int> position ) {
		std::dynamic_pointer_cast<CTitleScreenPresenter>(getPresenter())->onClickOnPlayButton();
	}
}