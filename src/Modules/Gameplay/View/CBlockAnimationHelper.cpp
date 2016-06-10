#include <vector>
#include <memory>
#include <utility>
#include <functional>
#include <iostream>
#include <algorithm>
#include "Vipper/Vipper.h"
#include "Vipper/CLerp.h"
#include "Modules/Gameplay/Entities/CColumn.h"
#include "Modules/Gameplay/View/CBlockAnimationHelper.h"

namespace BlockyFalls {
  CBlockAnimationHelper::VanishingBlockAnimation::VanishingBlockAnimation(std::pair< int, int > position, std::function<void()> onEnded) : mPosition( position ), lerp( 255, 0, 2000 ), ellapsed( 0 ), mOnEnded( onEnded ) {
  }

    
  CBlockAnimationHelper::FallingBlockAnimation::FallingBlockAnimation(std::pair<int, int> from, std::pair<int, int> to, CColumn::EColour colour, std::function<void()> onEnded) : mPosition( from ), lerpX( from.first, to.first, 2000 ), lerpY( from.second, to.second, 2000 ), ellapsed( 0 ), mOnEnded(onEnded ) {
  }
    
    
  void CBlockAnimationHelper::drawBlock( std::pair<int, int> from, std::pair<int, int> to, CColumn::EColour colour ) {
  }
    
  void CBlockAnimationHelper::vanishBlock( std::vector<std::pair< int, int >> position, std::function<void()> onEnded) {
    for ( auto& pair : position ) {
      mVanishingAnimations.push_back( std::make_shared<VanishingBlockAnimation>(pair, onEnded));
    }
  }
    
  bool CBlockAnimationHelper::draw( std::shared_ptr<Vipper::IRenderer> renderer) {

      bool toReturn = false;
      
      for ( auto& fall : mFallingAnimations ) {
        toReturn = true;
      }
      
      for ( auto& vanish : mVanishingAnimations ) {
        toReturn = true;
        int x = vanish->mPosition.first;
        int y = vanish->mPosition.second;
        vanish->ellapsed += 33;
        renderer->drawSquare( x * 64, y * 64, (x + 1) * 64, (y + 1) * 64, 0xFFFFFF );
      }
      
      
      mFallingAnimations.erase( std::remove_if(mFallingAnimations.begin(), mFallingAnimations.end(), [](std::shared_ptr<FallingBlockAnimation> animation ){
        
        bool toReturn = (animation->ellapsed > 2000); 
        
        if ( animation->mOnEnded != nullptr ) {
          animation->mOnEnded();
        }
        
        return toReturn;
      }), mFallingAnimations.end() );
   
      mVanishingAnimations.erase( std::remove_if(mVanishingAnimations.begin(), mVanishingAnimations.end(), [](std::shared_ptr<VanishingBlockAnimation> animation ){
        bool toReturn = (animation->ellapsed > 2000); 
        
        if ( animation->mOnEnded != nullptr ) {
          animation->mOnEnded();
        }
        
        return toReturn;
      }), mVanishingAnimations.end() );
      
      return toReturn;
  }
}