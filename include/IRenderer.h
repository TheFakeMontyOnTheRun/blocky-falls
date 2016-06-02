#ifndef BF_IRENDERER_H
#define BF_IRENDERER_H

namespace BlockyFalls {
  class IRenderer {
  public:
    virtual void render() = 0;
    virtual void update() = 0;
    virtual void shutdown() = 0;
  };
}
#endif
