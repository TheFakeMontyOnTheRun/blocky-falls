#ifndef BF_CSDLSHOWIMAGERENDERER_H
#define BF_CSDLSHOWIMAGERENDERER_H

namespace BlockyFalls {
  class CSDLShowImageRenderer : public IRenderer {
    SDL_Surface *mTarget;
    SDL_Surface *mImageToShow;
    CSDLShowImageRenderer( SDL_Surface *target, SDL_Surface* imageToShow );
  public:
    virtual void render() override;
    virtual void update() override;
    virtual void shutdown() override;
    //make builder method here
  };
}
#endif
