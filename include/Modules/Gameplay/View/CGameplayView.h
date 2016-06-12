#ifndef BF_CGAMEPLAYVIEW_H
#define BF_CGAMEPLAYVIEW_H

namespace BlockyFalls {

  class CGameplayView : public Vipper::IView, public Vipper::IRenderer::IClickListener, public Vipper::IRenderer::IKeyListener {
    std::pair<int,int> mLastClick;
    std::shared_ptr<CGameSession> mGameSession;
    std::set<std::pair<int,int>> exclusionList;
    std::map<CColumn::EColour, Vipper::IRenderer::BitmapId> mBitmapsForColours;
    std::vector<Vipper::IRenderer::BitmapId> mExplosionEffect;
    bool animationFinishedForColumn( int x );
    std::function<void(std::pair<int,int>)> mClickDelegate;
    std::function<void(long keyCode)> mKeyDelegate;
    Vipper::IRenderer::SoundId mFallSound;
    Vipper::IRenderer::SoundId mCollapseSound;
    Vipper::IRenderer::SoundId mBustedSound;
    Vipper::IRenderer::SoundId mPullSound;
    
    Vipper::IRenderer::FontId mUIFont;
  public:
    void drawLimitLine();
    bool hasAllAnimationsCeased();
    explicit CGameplayView(std::shared_ptr<CGameSession> session, std::shared_ptr<Vipper::IRenderer> renderer);
    void setClickDelegate(std::function<void(std::pair<int,int>)> delegate);
    void setKeyDelegate(std::function<void(long keyCode)> delegate);
    void generateExplosions( std::shared_ptr<CLevel> level, std::function<void(std::pair<int,int>)> onExplosionsFinished );
    void generateDropAnimations( std::shared_ptr<CLevel> level, std::function<void(std::pair<int,int>)> onDropsFinished );
    void generateColumnCollapseAnimations( std::shared_ptr<CLevel> level, std::function<void(std::pair<int,int>)> onCollapseFinished );
    void drawTextAt( std::pair<int, int> position, std::string text );
    void drawGaugeAt( std::pair<int, int> position, int howFilled);
    std::pair<int, int> getLastClick();
    void onPull();
    void show() override;
    void onClick( std::pair< int, int> position ) override;
    void onKey( long keyCode ) override;
  };
}
#endif
