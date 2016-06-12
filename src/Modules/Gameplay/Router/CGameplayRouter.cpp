#include <map>
#include <set>
#include "Vipper/Vipper.h"
#include "Modules/Gameplay/Entities/CColumn.h"
#include "Modules/Gameplay/Entities/CLevel.h"
#include "Modules/Gameplay/Entities/CGameSession.h"
#include "Modules/Gameplay/Router/CGameplayRouter.h"
#include "Modules/Gameplay/View/CGameplayView.h"
#include "Modules/Gameplay/Presenter/CGameplayPresenter.h"
#include "Modules/Gameplay/Interactor/CGameplayInteractor.h"

namespace BlockyFalls {
	
	CGameplayRouter::CGameplayRouter(std::shared_ptr<Vipper::IRenderer> renderer) : Vipper::IRouter( renderer, "game" ) {
	}
	
	void CGameplayRouter::initWithDefaults(){
		auto session = std::make_shared<BlockyFalls::CGameSession>(1000, 1000, 1);
		auto view = std::make_shared<BlockyFalls::CGameplayView>( session, 	getRenderer());
		auto presenter = std::make_shared<BlockyFalls::CGameplayPresenter>( session, view);
		auto interactor = std::make_shared<BlockyFalls::CGameplayInteractor>( shared_from_this());
		
		setPresenter( presenter );
		setInteractor( interactor );
		presenter->setView( view );
		presenter->setInteractor( interactor );
		view->setPresenter( presenter );
	}
	
	void CGameplayRouter::onFocus(){
		getRenderer()->registerClickListener( std::dynamic_pointer_cast<CGameplayView>(getPresenter()->getView()) );
		getRenderer()->registerKeyListener( std::dynamic_pointer_cast<CGameplayView>(getPresenter()->getView()) );
	}
	
	void CGameplayRouter::onRelinquishFocus(){
		getRenderer()->unregisterClickListener( std::dynamic_pointer_cast<CGameplayView>(getPresenter()->getView()) );
		getRenderer()->unregisterKeyListener( std::dynamic_pointer_cast<CGameplayView>(getPresenter()->getView()) );
	}
}