#ifndef BF_CGame_H
#define BF_CGame_H

namespace BlockyFalls {

  class CGame {
    std::shared_ptr<IRenderer> mRenderer;
    std::shared_ptr<CLevel> mLevel;
  public:
    explicit CGame();
    void runGame( std::shared_ptr<IRenderer> renderer);
    void update();
  };
}
#endif
