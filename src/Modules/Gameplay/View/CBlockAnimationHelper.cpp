#include <iostream>
#include <cmath>
#include <set>
#include <tuple>
#include <map>
#include <vector>
#include <memory>
#include <utility>
#include <functional>
#include <algorithm>
#include "Vipper/Vipper.h"
#include "Vipper/CLerp.h"
#include "Modules/Gameplay/Entities/CColumn.h"
#include "Vipper/CAnimation.h"
#include "Modules/Gameplay/View/CBlockAnimationHelper.h"

namespace BlockyFalls {

  CBlockAnimationHelper::CCompoundAnimation::CCompoundAnimation( CColumn::CCoordinates from, CColumn::CCoordinates to, std::function< void( std::function<void(std::pair<float,float>, CColumn::EColour)>  )> drawFunction, long duration, std::function<void(std::pair<int,int>)> onEnded ):
  mAnimation( from, to, drawFunction, duration, onEnded ) {
  }

  void CBlockAnimationHelper::CCompoundAnimation::draw(std::function<void( std::pair<float,float>, CColumn::EColour)> helper) {
    mAnimation.draw(helper);
  }

  bool CBlockAnimationHelper::CCompoundAnimation::isFinished() {
    return mAnimation.isFinished();
  }

  void CBlockAnimationHelper::CCompoundAnimation::update( long ms ) {
    mAnimation.update( ms );
  }
  

  Vipper::CAnimation CBlockAnimationHelper::CCompoundAnimation::getAnimation() {
    return mAnimation;
  }

  CBlockAnimationHelper::VanishingBlockAnimation::VanishingBlockAnimation(std::pair< int, int > from, std::function<void(std::pair<int, int>)> onEnded) 
  :CCompoundAnimation( from, from, [&](std::function<void(std::pair<float,float>, CColumn::EColour)> drawHelper ) {
        mFrameLerp.update( 33 );
        update( 33 );
        drawHelper( getAnimation().getPosition(), static_cast<CColumn::EColour>(floor( mFrameLerp.getCurrentValue() ) ) );
    }, 500, onEnded ), mFrameLerp( static_cast<int>(CColumn::EColour::eSpark1), static_cast<int>(CColumn::EColour::eSpark5), 500 ) {
  }

  CBlockAnimationHelper::FallingBlockAnimation::FallingBlockAnimation(std::pair<int, int> from, std::pair<int, int> to, CColumn::EColour colour, std::function<void(std::pair<int, int>)> onEnded) 
  : CCompoundAnimation( from, to, [&](std::function<void(std::pair<float,float>, CColumn::EColour)> drawHelper ) {
        update( 33 ); 
        auto animation = getAnimation();
        auto position = animation.getPosition();
        float x = position.first;
        float y = position.second;
        drawHelper( position, mColour );
    }, 500 , onEnded), mColour( colour ) {
  }

  CBlockAnimationHelper::MoveColumnAnimation::MoveColumnAnimation(std::pair<int, int> from, std::pair<int, int> to, CColumn::EColour colour, std::function<void(std::pair<int, int>)> onEnded) 
  : CCompoundAnimation( to, from, [&](std::function<void(std::pair<float,float>, CColumn::EColour)> drawHelper ) {  
      update( 33 );
      auto animation = getAnimation();
      auto destination = animation.getDestination();
      auto origin = animation.getOrigin();
      auto position = animation.getPosition();
      position.first = ( fabs( destination.first - origin.first ) - ( position.first - origin.first)) + destination.first;
      drawHelper( position, mColour );
    }, 500, onEnded), mColour( colour ) {
  }

  void CBlockAnimationHelper::moveColumn( std::pair<int, int> movement, std::vector<CColumn::EColour> column, std::function<void(std::pair<int, int>)> onEnded) {
    
    int y = 0;
    for ( auto& block : column ) {
      auto to = std::pair<int,int>( movement.first, CColumn::kColumnHeight - y - 1 );
      auto from = std::pair<int,int>( movement.second, CColumn::kColumnHeight - y - 1 );
      mAnimations.push_back( std::make_shared<MoveColumnAnimation>(from, to, block, onEnded));
      ++y;
    }
  }
  
  void CBlockAnimationHelper::animateFallingBlocks( std::vector<std::tuple< std::pair<int, int>, std::pair<int, int>, CColumn::EColour>> paths, std::function<void(std::pair<int,int>)> onEnded ) {
    for ( auto& path : paths ) {
      auto from = std::get<0>(path);
      auto to = std::get<1>(path);
      auto colour = std::get<2>(path);
      mAnimations.push_back( std::make_shared<FallingBlockAnimation>(from, to, colour, onEnded));
    }
  }
    
  void CBlockAnimationHelper::vanishBlock( std::vector<CColumn::CCoordinates> position, std::function<void(CColumn::CCoordinates)> onEnded) {
    for ( auto& pair : position ) {
      mAnimations.push_back( std::make_shared<VanishingBlockAnimation>(pair, onEnded));
    }
  }
    
  void CBlockAnimationHelper::draw( std::shared_ptr<Vipper::IRenderer> renderer, std::function<void(std::pair<float, float>, CColumn::EColour)> drawBlock) {

    for ( auto& move : mAnimations ) {
      move->draw(drawBlock );
    }
      mAnimations.erase( std::remove_if(mAnimations.begin(), mAnimations.end(), [&](std::shared_ptr<CCompoundAnimation> animation ){
        return animation->isFinished();
      }), mAnimations.end() );
  }
}
