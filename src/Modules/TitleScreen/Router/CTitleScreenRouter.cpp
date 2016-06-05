#include <iostream>
#include "Vipper/Vipper.h"

#include "Modules/Gameplay/Entities/CLevel.h"
#include "Modules/Gameplay/Entities/CGameSession.h"

#include "Modules/Gameplay/Router/CGameplayRouter.h"

#include "Modules/TitleScreen/Router/CTitleScreenRouter.h"
#include "Modules/TitleScreen/View/CRect.h"
#include "Modules/TitleScreen/View/CPlayButton.h"
#include "Modules/TitleScreen/View/CTitleScreenView.h"
#include "Modules/TitleScreen/Presenter/CTitleScreenPresenter.h"
#include "Modules/TitleScreen/Interactor/CTitleScreenInteractor.h"
#include "Modules/TitleScreen/Router/CTitleScreenRouter.h"

namespace BlockyFalls {

		CTitleScreenRouter::CTitleScreenRouter(std::shared_ptr<Vipper::IRenderer> renderer,std::shared_ptr<CGameplayRouter> gameplayRouter): Vipper::IRouter( renderer,"title" ),
		mGameplayRouter( gameplayRouter ) {	
		}

		void CTitleScreenRouter::goToGameplay() {
			setNextRoute( mGameplayRouter );		
		}
		
		void CTitleScreenRouter::initWithDefaults() {
			auto view = std::make_shared<BlockyFalls::CTitleScreenView>(getRenderer());
			auto interactor = std::make_shared<BlockyFalls::CTitleScreenInteractor>(shared_from_this());
			auto presenter = std::make_shared<BlockyFalls::CTitleScreenPresenter>(view);
				
			setPresenter( presenter );
			setInteractor( interactor );
			presenter->setView( view );
			presenter->setInteractor( interactor );
			view->setPresenter( presenter );
		}
		
		void CTitleScreenRouter::onFocus(){
			getRenderer()->registerClickListener( std::dynamic_pointer_cast<CTitleScreenView>(getPresenter()->getView()) );
		}
		
    	void CTitleScreenRouter::onRelinquishFocus(){
			getRenderer()->unregisterClickListener( std::dynamic_pointer_cast<CTitleScreenView>(getPresenter()->getView()) );
		}		
}
