#ifndef BF_CCOLUMNVIEW_H
#define BF_CCOLUMNVIEW_H

namespace BlockyFalls {

  class CBlockAnimationHelper {
    public:
    
    class VanishingBlockAnimation {
      public:
      
      Vipper::CLerp lerp;
      long ellapsed;
      std::pair< int, int > mPosition;
      std::function<void(std::pair<int,int>)> mOnEnded;
      VanishingBlockAnimation(std::pair< int, int > position, std::function<void(std::pair<int,int>)> onEnded);
    };
    
    class FallingBlockAnimation {
      public:

      Vipper::CLerp lerpX;
      Vipper::CLerp lerpY;
      long ellapsed;
      std::pair< int, int > mPosition;
      std::function<void(std::pair<int, int>)> mOnEnded;
      CColumn::EColour mColour;
            
      FallingBlockAnimation(std::pair<int, int> from, std::pair<int, int> to, CColumn::EColour colour, std::function<void(std::pair<int, int>)> onEnded);
    };
    
    std::vector<std::shared_ptr<VanishingBlockAnimation>> mVanishingAnimations;
    std::vector<std::shared_ptr<FallingBlockAnimation>> mFallingAnimations;
    
    void animateFallingBlocks( std::vector<std::tuple< std::pair<int, int>, std::pair<int, int>, CColumn::EColour>> paths, std::function<void(std::pair<int,int>)> onEnded );
    void vanishBlock( std::vector<std::pair< int, int >> position, std::function<void(std::pair<int,int>)> onEnded);
    bool draw( std::shared_ptr<Vipper::IRenderer> renderer);
  };
}
#endif
