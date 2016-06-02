#ifndef BF_CSDLRenderer_H
#define BF_CSDLRenderer_H

namespace BlockyFalls {
  class CSDLRenderer : public IRenderer {

    SDL_Surface *video;
    std::map<char, SDL_Surface*> sprites;
  public:
    void init(std::shared_ptr<CGame> game);
    void render() override;
    void shutdown() override;
    void update() override;
  };
}
#endif
