#ifndef BF_CGAMEPLAYVIEW_H
#define BF_CGAMEPLAYVIEW_H

namespace BlockyFalls {

  class CGameplayView : public Vipper::IView, public Vipper::IRenderer::IClickListener {
    std::pair<int,int> mLastClick;
  public:
    explicit CGameplayView(std::shared_ptr<Vipper::IRenderer> renderer);

    void drawSquareAt( std::tuple<int, int, CLevel::EColour> block );
    void drawTextAt( std::pair<int, int> position, std::string text );
    void drawGaugeAt( std::pair<int, int> position, float howFilled);
    std::pair<int, int> getLastClick();
    void show() override;
    void onClick( std::pair< int, int> position ) override;
  };
}
#endif
