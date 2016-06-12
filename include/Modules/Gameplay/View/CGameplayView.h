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
  public:
    explicit CGameplayView(std::shared_ptr<CGameSession> session, std::shared_ptr<Vipper::IRenderer> renderer);

    void generateExplosions( std::shared_ptr<CLevel> level, std::function<void(std::pair<int,int>)> onExplosionsFinished );
    void generateDropAnimations( std::shared_ptr<CLevel> level, std::function<void(std::pair<int,int>)> onDropsFinished );
    void generateColumnCollapseAnimations( std::shared_ptr<CLevel> level, std::function<void(std::pair<int,int>)> onCollapseFinished );
    void drawSquareAt( std::tuple<int, int, CColumn::EColour> block );
    void drawTextAt( std::pair<int, int> position, std::string text );
    void drawGaugeAt( std::pair<int, int> position, float howFilled);
    std::pair<int, int> getLastClick();
    void show() override;
    void onClick( std::pair< int, int> position ) override;
    void onKey( long keyCode ) override;
  };
}
#endif
