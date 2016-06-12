#include <iostream>

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
#include "Vipper/CAnimation.h"
#include "Modules/Gameplay/Entities/CColumn.h"
#include "Modules/Gameplay/View/CBlockAnimationHelper.h"

namespace BlockyFalls {

  std::map<CColumn::EColour, int> colorsForBlocks;

  CBlockAnimationHelper::CCompoundAnimation::CCompoundAnimation( CColumn::CCoordinates from, CColumn::CCoordinates to, std::function< void(std::shared_ptr<Vipper::IRenderer>)> drawFunction, long duration, std::function<void(std::pair<int,int>)> onEnded ):
  mAnimation( from, to, drawFunction, duration, onEnded ) {
  }

  void CBlockAnimationHelper::CCompoundAnimation::draw(std::shared_ptr<Vipper::IRenderer> renderer) {
    mAnimation.draw(renderer);
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
  :CCompoundAnimation( from, from, [&](std::shared_ptr<Vipper::IRenderer> renderer ) {
        mFrameLerp.update( 33 );
        update( 33 );
        auto position = getAnimation().getPosition();
        float x = position.first;
        float y = position.second;
        auto colour = ( 255 - ( (int) mFrameLerp.getCurrentValue() ) ) << 8;
        renderer->drawSquare( x * 64, y * 64, (x + 1) * 64, (y + 1) * 64, colour );
    }, 500, onEnded ), mFrameLerp( 0, 255, 500 ) {
  }

  bool CBlockAnimationHelper::VanishingBlockAnimation::isFinished() {
    return mFrameLerp.isFinished();
  }

  CBlockAnimationHelper::FallingBlockAnimation::FallingBlockAnimation(std::pair<int, int> from, std::pair<int, int> to, CColumn::EColour colour, std::function<void(std::pair<int, int>)> onEnded) 
  : CCompoundAnimation( from, to, [&](std::shared_ptr<Vipper::IRenderer> renderer ) {
        update( 33 ); 
        auto animation = getAnimation();
        auto position = animation.getPosition();
        float x = position.first;
        float y = position.second;
        renderer->drawSquare( x * 64.0, y * 64.0, (x + 1.0) * 64.0, (y + 1.0) * 64.0, colorsForBlocks[mColour] );
    }, 500 * ( to.second - from.second ), onEnded), mColour( colour ) {
  }

  CBlockAnimationHelper::MoveColumnAnimation::MoveColumnAnimation(std::pair<int, int> from, std::pair<int, int> to, CColumn::EColour colour, std::function<void(std::pair<int, int>)> onEnded) 
  : CCompoundAnimation( to, from, [&](std::shared_ptr<Vipper::IRenderer> renderer ) {  
      update( 33 );
      auto animation = getAnimation();
      auto destination = animation.getDestination();
      auto origin = animation.getOrigin();
      auto position = animation.getPosition();
      auto x = ( fabs( destination.first - origin.first ) - ( position.first - origin.first)) + destination.first;
      auto y = position.second;
      // std::cout << "x = " << x << " [ " << origin.first << " : " << destination.first << " ] " << std::endl;
      renderer->drawSquare( x * 64.0, y * 64.0, (x + 1.0) * 64.0, (y + 1.0) * 64.0, colorsForBlocks[mColour] );
    }, 500 * fabs( to.first - from.first ), onEnded), mColour( colour ) {
  }

  void CBlockAnimationHelper::moveColumn( std::pair<int, int> movement, std::vector<CColumn::EColour> column, std::function<void(std::pair<int, int>)> onEnded) {
    
    int y = 0;
    for ( auto& block : column ) {
      auto to = std::pair<int,int>( movement.first, CColumn::kColumnHeight - y - 1 );
      auto from = std::pair<int,int>( movement.second, CColumn::kColumnHeight - y - 1 );
      mCollapseAnimations.push_back( std::make_shared<MoveColumnAnimation>(from, to, block, onEnded));
      ++y;
    }
  }
    
    
  void CBlockAnimationHelper::animateFallingBlocks( std::vector<std::tuple< std::pair<int, int>, std::pair<int, int>, CColumn::EColour>> paths, std::function<void(std::pair<int,int>)> onEnded ) {
    for ( auto& path : paths ) {
      auto from = std::get<0>(path);
      auto to = std::get<1>(path);
      auto colour = std::get<2>(path);
      mFallingAnimations.push_back( std::make_shared<FallingBlockAnimation>(from, to, colour, onEnded));
    }
  }
    
  void CBlockAnimationHelper::vanishBlock( std::vector<CColumn::CCoordinates> position, std::function<void(CColumn::CCoordinates)> onEnded) {
    for ( auto& pair : position ) {
      mVanishingAnimations.push_back( std::make_shared<VanishingBlockAnimation>(pair, onEnded));
    }
  }
    
  void CBlockAnimationHelper::draw( std::shared_ptr<Vipper::IRenderer> renderer) {

		colorsForBlocks[ CColumn::EColour::eRed 	] = 0xFF0000;
		colorsForBlocks[ CColumn::EColour::eYellow ] = 0xFFFF00;
		colorsForBlocks[ CColumn::EColour::eGrey	] = 0x999999;
		colorsForBlocks[ CColumn::EColour::eBlue 	] = 0x0000FF;
		colorsForBlocks[ CColumn::EColour::eNothing] = 0x00FF00;

    for ( auto& move : mCollapseAnimations ) {
      move->draw( renderer );
    }

    for ( auto& fall : mFallingAnimations ) {
      fall->draw( renderer );        
    }
      
    for ( auto& vanish : mVanishingAnimations ) {
      vanish->draw(renderer);
    }


      mCollapseAnimations.erase( std::remove_if(mCollapseAnimations.begin(), mCollapseAnimations.end(), [&](std::shared_ptr<MoveColumnAnimation> animation ){
        return animation->isFinished();
      }), mCollapseAnimations.end() );

      mFallingAnimations.erase( std::remove_if(mFallingAnimations.begin(), mFallingAnimations.end(), [&](std::shared_ptr<FallingBlockAnimation> animation ){
        return animation->isFinished();
      }), mFallingAnimations.end() );
   
      mVanishingAnimations.erase( std::remove_if(mVanishingAnimations.begin(), mVanishingAnimations.end(), [&](std::shared_ptr<VanishingBlockAnimation> animation ){
        return animation->isFinished();
      }), mVanishingAnimations.end() );
  }
}