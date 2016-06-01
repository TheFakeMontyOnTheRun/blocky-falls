#ifndef BF_CSDLRenderer_H
#define BF_CSDLRenderer_H

namespace BlockyFalls {
  class CSDLRenderer : public IRenderer {

    SDL_Surface *video;
    std::map<char, SDL_Surface*> sprites;
  public:
    explicit void init(std::shared_ptr<CLevel> level) override;
    void render() override;
    void shutdown() override;
    char update() override;
  };
}
#endif
