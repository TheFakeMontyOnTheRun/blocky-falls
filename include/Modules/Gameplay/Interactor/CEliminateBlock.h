#ifndef BF_CELIMINATEBLOCK_H
#define BF_CELIMINATEBLOCK_H

namespace BlockyFalls {

  class CEliminateBlock : public Vipper::IInteractor {
    std::shared_ptr<CLevel> mLevel;
    int propagateBlockDistruction( int x, int y );
  public:
    explicit CEliminateBlock( std::shared_ptr<CLevel> level);
    int eliminateBlockAtForScoreGain( int x, int y );
  };
}
#endif
