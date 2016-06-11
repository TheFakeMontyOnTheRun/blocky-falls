#include <vector>
#include <tuple>
#include <utility>

#include "Vipper/Vipper.h"
#include <set>
#include "Modules/Gameplay/Entities/CColumn.h"
#include "Modules/Gameplay/Entities/CLevel.h"
#include "Modules/Gameplay/Presenter/CLevelPresenter.h"

namespace BlockyFalls {
    CLevelPresenter::CLevelPresenter() {
    }
    
    void CLevelPresenter::showPullAnimation(){
    }
    
    void CLevelPresenter::showBlocksExplosionAt( std::vector<std::pair<int, int>> positions ) {
    }
    
    void CLevelPresenter::drawBlockAt( std::tuple<int, int, CColumn::EColour> block ) {
    }
    
    void CLevelPresenter::animateBlockFalling( std::tuple<int, int, CColumn::EColour> block, std::pair<int, int> position) {
    }
    
    void CLevelPresenter::drawScoreGain(int gain) {
    }
    
    void CLevelPresenter::playVanishSound() {
    }
    
    void CLevelPresenter::playFallSound() {
    }
    
    void CLevelPresenter::playPullSound() {
    }
}