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
#include "Modules/Gameplay/Entities/CColumn.h"
#include "Modules/Gameplay/View/CBlockAnimationHelper.h"

namespace BlockyFalls {

  std::map<CColumn::EColour, int> colorsForBlocks;

  CBlockAnimationHelper::VanishingBlockAnimation::VanishingBlockAnimation(std::pair< int, int > position, std::function<void(std::pair<int, int>)> onEnded) : mPosition( position ), lerp( 0, 255, 500 ), ellapsed( 0 ), mOnEnded( onEnded ) {
  }

    
  CBlockAnimationHelper::FallingBlockAnimation::FallingBlockAnimation(std::pair<int, int> from, std::pair<int, int> to, CColumn::EColour colour, std::function<void(std::pair<int, int>)> onEnded) : mPosition( from ), lerpX( from.first, to.first, 500 ), lerpY( from.second, to.second, 500 * ( to.second - from.second ) ), ellapsed( 0 ), mOnEnded(onEnded ), mColour( colour ) {
  }


  CBlockAnimationHelper::MoveColumnAnimation::MoveColumnAnimation(std::pair<int, int> movement, std::vector<CColumn::EColour> column, std::function<void(std::pair<int, int>)> onEnded):
  mColumn(column), ellapsed( 0 ), lerpX( movement.second, movement.first, 500 * ( movement.first - movement.second ) ) , mMovement( movement ), mOnEnded( onEnded ) {
  } 
  

  void CBlockAnimationHelper::moveColumn( std::pair<int, int> movement, std::vector<CColumn::EColour> column, std::function<void(std::pair<int, int>)> onEnded) {
    mCollapseAnimations.push_back( std::make_shared<MoveColumnAnimation>(movement, column, onEnded) );
  }
    
    
  void CBlockAnimationHelper::animateFallingBlocks( std::vector<std::tuple< std::pair<int, int>, std::pair<int, int>, CColumn::EColour>> paths, std::function<void(std::pair<int,int>)> onEnded ) {
    for ( auto& path : paths ) {
      auto from = std::get<0>(path);
      auto to = std::get<1>(path);
      auto colour = std::get<2>(path);
      mFallingAnimations.push_back( std::make_shared<FallingBlockAnimation>(from, to, colour, onEnded));
    }
  }
    
  void CBlockAnimationHelper::vanishBlock( std::vector<std::pair< int, int >> position, std::function<void(std::pair<int,int>)> onEnded) {
    for ( auto& pair : position ) {
      mVanishingAnimations.push_back( std::make_shared<VanishingBlockAnimation>(pair, onEnded));
    }
  }
    
  bool CBlockAnimationHelper::draw( std::shared_ptr<Vipper::IRenderer> renderer) {

		colorsForBlocks[ CColumn::EColour::eRed 	] = 0xFF0000;
		colorsForBlocks[ CColumn::EColour::eYellow ] = 0xFFFF00;
		colorsForBlocks[ CColumn::EColour::eGrey	] = 0x999999;
		colorsForBlocks[ CColumn::EColour::eBlue 	] = 0x0000FF;
		colorsForBlocks[ CColumn::EColour::eNothing] = 0x00FF00;


      bool toReturn = false;

      for ( auto& move : mCollapseAnimations ) {
        toReturn = true;
        move->ellapsed += 33;
        float x = 1.0f - move->lerpX.getValue( move->ellapsed );

        // std::cout << "ellapsed " << move->ellapsed << " of " << move->lerpX.mDuration << std::endl;
        
        for ( int y = 0; y < CColumn::kColumnHeight; ++y ) {
          auto colour = move->mColumn[ y ];
          // if ( colour != CColumn::EColour::eNothing ) {
            renderer->drawSquare( x * 64.0, y * 64.0, (x + 1.0) * 64.0, (y + 1.0) * 64.0, colorsForBlocks[ colour ] );
          // }
        }        
      }

      for ( auto& fall : mFallingAnimations ) {
        toReturn = true;
        fall->ellapsed += 33;
        float dx = fall->lerpX.getValue( fall->ellapsed );
        float dy = fall->lerpY.getValue( fall->ellapsed );
        float x = dx;
        float y = dy;
        
        renderer->drawSquare( x * 64.0, y * 64.0, (x + 1.0) * 64.0, (y + 1.0) * 64.0, colorsForBlocks[fall->mColour] );        
      }
      
      for ( auto& vanish : mVanishingAnimations ) {
        toReturn = true;
        int x = vanish->mPosition.first;
        int y = vanish->mPosition.second;
        vanish->ellapsed += 33;
        auto colour = ( 255 - ( (int) vanish->lerp.getValue( vanish->ellapsed ) ) ) << 8;
        renderer->drawSquare( x * 64, y * 64, (x + 1) * 64, (y + 1) * 64, colour );
      }


      mCollapseAnimations.erase( std::remove_if(mCollapseAnimations.begin(), mCollapseAnimations.end(), [&](std::shared_ptr<MoveColumnAnimation> animation ){
        
        bool toReturn = (animation->ellapsed > animation->lerpX.mDuration); 
        
        if ( animation->mOnEnded != nullptr && toReturn ) {
          for ( int c = 0; c < CColumn::kColumnHeight; ++c ) {
              animation->mOnEnded( std::pair<int,int>( animation->lerpX.mInitialValue, c ) );
          }
        }
        
        return toReturn;
      }), mCollapseAnimations.end() );


      mFallingAnimations.erase( std::remove_if(mFallingAnimations.begin(), mFallingAnimations.end(), [&](std::shared_ptr<FallingBlockAnimation> animation ){
        
        bool toReturn = (animation->ellapsed > animation->lerpY.mDuration); 
        
        if ( animation->mOnEnded != nullptr && toReturn ) {
          animation->mOnEnded( animation->mPosition );
        }
        
        return toReturn;
      }), mFallingAnimations.end() );
   
      mVanishingAnimations.erase( std::remove_if(mVanishingAnimations.begin(), mVanishingAnimations.end(), [&](std::shared_ptr<VanishingBlockAnimation> animation ){
        bool toReturn = (animation->ellapsed > animation->lerp.mDuration); 
        
        if ( animation->mOnEnded != nullptr && toReturn ) {
          animation->mOnEnded( animation->mPosition );
        }
        
        return toReturn;
      }), mVanishingAnimations.end() );
      
      return toReturn;
  }
}