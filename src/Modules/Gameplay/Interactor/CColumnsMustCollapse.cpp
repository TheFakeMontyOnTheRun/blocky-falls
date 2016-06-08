#include "Vipper/Vipper.h"
#include "Modules/Gameplay/Entities/CColumn.h"
#include "Modules/Gameplay/Entities/CLevel.h"
#include "Modules/Gameplay/Interactor/CColumnsMustCollapse.h"

namespace BlockyFalls {
    
        CColumnsMustCollapse::CColumnsMustCollapse( std::shared_ptr<CLevel> level) : mLevel( level ) {
        }
        
        void CColumnsMustCollapse::collapseColumns() {
                // static const auto predicate = [](std::shared_ptr<CColumn> c) {
                //         return c->isEmpty();
                // };
                
                // mColumns.erase( std::remove_if( mColumns.begin(), mColumns.end(), predicate), mColumns.end() );
        }
}