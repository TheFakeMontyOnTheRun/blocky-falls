#include <utility>
#include <vector>
#include <memory>

#include "Vipper/Vipper.h"
#include "Modules/Gameplay/Router/CGameplayRouter.h"
#include "Modules/Gameplay/Interactor/CGameplayInteractor.h"

namespace BlockyFalls {
		CGameplayInteractor::CGameplayInteractor(std::shared_ptr<Vipper::IRouter> router) : mRouter( router ) {	
		}
	
		void CGameplayInteractor::interact() {			
		}
}