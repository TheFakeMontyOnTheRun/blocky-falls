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
      std::function<void()> mOnEnded;
      VanishingBlockAnimation(std::pair< int, int > position, std::function<void()> onEnded);
    };
    
    class FallingBlockAnimation {
      public:

      Vipper::CLerp lerpX;
      Vipper::CLerp lerpY;
      long ellapsed;
      std::pair< int, int > mPosition;
      std::function<void()> mOnEnded;
            
      FallingBlockAnimation(std::pair<int, int> from, std::pair<int, int> to, CColumn::EColour colour, std::function<void()> onEnded);
    };
    
    std::vector<std::shared_ptr<VanishingBlockAnimation>> mVanishingAnimations;
    std::vector<std::shared_ptr<FallingBlockAnimation>> mFallingAnimations;
    
    void drawBlock( std::pair<int, int> from, std::pair<int, int> to, CColumn::EColour colour );
    void vanishBlock( std::vector<std::pair< int, int >> position, std::function<void()> onEnded);
    bool draw( std::shared_ptr<Vipper::IRenderer> renderer);
  };
}
#endif
