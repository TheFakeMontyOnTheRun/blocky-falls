#ifndef BF_IRENDERER_H
#define BF_IRENDERER_H

namespace Vipper {
  class IRenderer {
    
  public:
    class IClickListener {
      public:
      virtual void onClick( std::pair<int, int > pointerPosition ) = 0;
    };
    
    class IKeyListener {
      public:
      virtual void onKey( long keyCode ) = 0;  
    };
    
    void dispatchClickToListeners( std::pair<int, int > pointerPosition );
    void dispatchKeyToListeners( long keyCode );
    
    std::vector< std::shared_ptr<IClickListener>> mClickListeners;
    std::vector< std::shared_ptr<IKeyListener>> mKeyListeners;
  
    using BitmapId = long;
    using SoundId = long;

    virtual void render() = 0;
    virtual BitmapId loadBitmap( std::string path ) = 0;
    virtual SoundId loadSound( std::string path ) = 0;
    virtual void drawSquare( int x, int y, int x2, int y2, int colour ) = 0;
    virtual void drawTextAt( int x, int y, std::string text ) = 0;
    virtual void drawBitmapAt( int x, int y, int w, int h, const BitmapId& id ) = 0;
    virtual void playSound( const SoundId& id ) = 0;
    virtual void update() = 0;
    virtual void shutdown() = 0;
    
    void registerClickListener( std::shared_ptr<IClickListener> listener );
    void unregisterClickListener( std::shared_ptr<IClickListener> listener );
    
    void registerKeyListener( std::shared_ptr<IKeyListener> listener );
    void unregisterKeyListener( std::shared_ptr<IKeyListener> listener );
  };
}
#endif
