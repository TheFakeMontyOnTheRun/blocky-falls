#ifndef BF_CGame_H
#define BF_CGame_H

namespace BlockyFalls {

  class CGame {
    IRenderer *renderer;
    std::shared_ptr<CLevel> map;
  public:
    explicit CGame();
    GameResult runGame( IRenderer *renderer);
    void update();
    GameResult tick();
  };
}
#endif
