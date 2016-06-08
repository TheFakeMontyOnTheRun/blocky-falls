#ifndef BF_CBLOCKSMUSTFALL_H
#define BF_CBLOCKSMUSTFALL_H

namespace BlockyFalls {

  class CBlocksMustFall : public Vipper::IInteractor {
    std::shared_ptr<CLevel> mLevel;
  public:
    explicit CBlocksMustFall( std::shared_ptr<CLevel> level);
    void settleBlocksInPosition();
  };
}
#endif
