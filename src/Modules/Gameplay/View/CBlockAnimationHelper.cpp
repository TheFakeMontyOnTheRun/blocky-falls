#include <map>
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
  CBlockAnimationHelper::VanishingBlockAnimation::VanishingBlockAnimation(std::pair< int, int > position, std::function<void()> onEnded) : mPosition( position ), lerp( 0, 255, 1000 ), ellapsed( 0 ), mOnEnded( onEnded ) {
  }

    
  CBlockAnimationHelper::FallingBlockAnimation::FallingBlockAnimation(std::pair<int, int> from, std::pair<int, int> to, CColumn::EColour colour, std::function<void()> onEnded) : mPosition( from ), lerpX( from.first, to.first, 500 ), lerpY( from.second, to.second, 500 * ( to.second - from.second ) ), ellapsed( 0 ), mOnEnded(onEnded ), mColour( colour ) {
  std::cout << "animating for " << ( to.second - from.second ) << std::endl;
  }
    
    
  void CBlockAnimationHelper::animateFallingBlocks( std::vector<std::tuple< std::pair<int, int>, std::pair<int, int>, CColumn::EColour>> paths, std::function<void()> onEnded ) {
    for ( auto& path : paths ) {
      auto from = std::get<0>(path);
      auto to = std::get<1>(path);
      auto colour = std::get<2>(path);
      mFallingAnimations.push_back( std::make_shared<FallingBlockAnimation>(from, to, colour, onEnded));
    }
  }
    
  void CBlockAnimationHelper::vanishBlock( std::vector<std::pair< int, int >> position, std::function<void()> onEnded) {
    for ( auto& pair : position ) {
      mVanishingAnimations.push_back( std::make_shared<VanishingBlockAnimation>(pair, onEnded));
    }
  }
    
  bool CBlockAnimationHelper::draw( std::shared_ptr<Vipper::IRenderer> renderer) {

      bool toReturn = false;
      std::cout << "draw============" << std::endl;
      for ( auto& fall : mFallingAnimations ) {
        toReturn = true;
        fall->ellapsed += 33;
        float dx = fall->lerpX.getValue( fall->ellapsed );
        float dy = fall->lerpY.getValue( fall->ellapsed );
        float x = dx;
        float y = dy;
        
        std::cout << "falling " << y << std::endl;
        renderer->drawSquare( x * 64.0, y * 64.0, (x + 1.0) * 64.0, (y + 1.0) * 64.0, 0xFFFFFF);//coloursForBlocks[fall->mColour] );        
      }
      
      for ( auto& vanish : mVanishingAnimations ) {
        toReturn = true;
        int x = vanish->mPosition.first;
        int y = vanish->mPosition.second;
        vanish->ellapsed += 33;
        auto colour = vanish->lerp.getValue( vanish->ellapsed );
        std::cout << "vanishing " << colour << std::endl;
        renderer->drawSquare( x * 64, y * 64, (x + 1) * 64, (y + 1) * 64, colour );
      }
      
      
      mFallingAnimations.erase( std::remove_if(mFallingAnimations.begin(), mFallingAnimations.end(), [&](std::shared_ptr<FallingBlockAnimation> animation ){
        
        bool toReturn = (animation->ellapsed > animation->lerpY.mDuration); 
        
        if ( animation->mOnEnded != nullptr && toReturn ) {
          animation->mOnEnded();
        }
        
        return toReturn;
      }), mFallingAnimations.end() );
   
      mVanishingAnimations.erase( std::remove_if(mVanishingAnimations.begin(), mVanishingAnimations.end(), [&](std::shared_ptr<VanishingBlockAnimation> animation ){
        bool toReturn = (animation->ellapsed > animation->lerp.mDuration); 
        
        if ( animation->mOnEnded != nullptr && toReturn ) {
          animation->mOnEnded();
        }
        
        return toReturn;
      }), mVanishingAnimations.end() );
      
      return toReturn;
  }
}