#ifndef BF_CISLEVELCOMPLETE_H
#define BF_CISLEVELCOMPLETE_H

namespace BlockyFalls {

  class CIsLevelComplete : public Vipper::IInteractor {
    std::shared_ptr<CLevel> mLevel;
  public:
    explicit CGameSession( std::shared_ptr<CLevel> level);
    bool isLevelComplete();
  };
}
#endif
