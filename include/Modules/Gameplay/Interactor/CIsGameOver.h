#ifndef BF_CISGAMEOVER_H
#define BF_CISGAMEOVER_H

namespace BlockyFalls {

  class CIsGameOver : public Vipper::IInteractor {
    std::shared_ptr<CLevel> mLevel;
  public:
    explicit CIsGameOver(std::shared_ptr<CLevel> level);
    bool isGameOver();
  };
}
#endif
