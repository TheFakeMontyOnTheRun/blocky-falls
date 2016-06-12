#ifndef BF_CCOLUMNVIEW_H
#define BF_CCOLUMNVIEW_H

namespace BlockyFalls {

  class CBlockAnimationHelper {
    public:

    class CCompoundAnimation {
      Vipper::CAnimation mAnimation;

      public:
      explicit CCompoundAnimation( CColumn::CCoordinates from, CColumn::CCoordinates to, std::function< void(std::function<void(std::pair<float,float>, CColumn::EColour)>)> drawFunction, long duration, std::function<void(std::pair<int,int>)> onEnded );
      Vipper::CAnimation getAnimation();
	    virtual void draw(std::function<void(std::pair<float,float>, CColumn::EColour)> drawBlock);
      virtual bool isFinished();
      void update( long ms );
    };
    
    class VanishingBlockAnimation : public CCompoundAnimation {
      public:
      Vipper::CLerp mFrameLerp;
      VanishingBlockAnimation(CColumn::CCoordinates position, std::function<void(CColumn::CCoordinates)> onEnded);
    };
    
    class FallingBlockAnimation : public CCompoundAnimation {
      public:
      CColumn::EColour mColour;
      FallingBlockAnimation(CColumn::CCoordinates from, CColumn::CCoordinates to, CColumn::EColour colour, std::function<void(CColumn::CCoordinates)> onEnded);
    };
    
    class MoveColumnAnimation : public CCompoundAnimation {
      public:
      CColumn::EColour mColour;
      MoveColumnAnimation(CColumn::CCoordinates from, CColumn::CCoordinates to, CColumn::EColour colour, std::function<void(CColumn::CCoordinates)> onEnded);
    };

    std::vector<std::shared_ptr<CCompoundAnimation>> mAnimations;

    void moveColumn( std::pair<CColumn::CIndex, CColumn::CIndex> movement, std::vector<CColumn::EColour> column, std::function<void(CColumn::CCoordinates)>);    
    void animateFallingBlocks( std::vector<std::tuple< CColumn::CCoordinates, CColumn::CCoordinates, CColumn::EColour>> paths, std::function<void(CColumn::CCoordinates)> onEnded );
    void vanishBlock( std::vector<CColumn::CCoordinates> position, std::function<void(CColumn::CCoordinates)> onEnded);
    void draw( std::shared_ptr<Vipper::IRenderer> renderer, std::function<void(std::pair<float,float>, CColumn::EColour)> drawBlock  );
  };
}
#endif
