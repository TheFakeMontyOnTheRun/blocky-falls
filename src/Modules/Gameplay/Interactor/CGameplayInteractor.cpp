#include <utility>
#include <vector>
#include <memory>

#include "Vipper/Vipper.h"
#include "Modules/Gameplay/Entities/CColumn.h"
#include "Modules/Gameplay/Entities/CLevel.h"
#include "Modules/Gameplay/Entities/CGameSession.h"
#include "Modules/Gameplay/Router/CGameplayRouter.h"
#include "Modules/Gameplay/Interactor/CGameplayInteractor.h"

namespace BlockyFalls {
		CGameplayInteractor::CGameplayInteractor(std::shared_ptr<CGameSession> session, std::shared_ptr<Vipper::IRouter> router) : mRouter( router ), mSession( session ) {	
		}
	
		void CGameplayInteractor::interact() {
			if ( mSession->isOver() ) {
				std::dynamic_pointer_cast<CGameplayRouter>(mRouter)->goToGameOver();				
			}			
		}
}