#ifndef BF_IRENDERER_H
#define BF_IRENDERER_H

namespace BlockyFalls {
  class IRenderer {
  public:
    virtual void init(std::shared_ptr<CLevel> level) = 0;
    virtual void render() = 0;
    virtual char update() = 0;
    virtual void shutdown() = 0;
  };
}
#endif
