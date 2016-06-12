#ifndef BF_CSDLRenderer_H
#define BF_CSDLRenderer_H

namespace BlockyFalls {
  class CSDLRenderer : public Vipper::IRenderer {
    SDL_Surface *video;
    std::map<IRenderer::BitmapId, SDL_Surface*> mSprites;
    std::map<IRenderer::SoundId, Mix_Chunk*> mSounds;
  public:
    explicit CSDLRenderer();
    void render() override;
    void shutdown() override;
    void update() override;        
    BitmapId loadBitmap( std::string path ) override;
    SoundId loadSound( std::string path ) override;
    void drawSquare( int x, int y, int x2, int y2, int colour ) override;
    void drawTextAt( int x, int y, std::string text ) override;
    void drawBitmapAt( int x, int y, int w, int h, const BitmapId& id ) override;
    void playSound( const SoundId& id ) override;    
  };
}
#endif
