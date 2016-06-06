#ifndef BF_CLEVELPRESENTER_H
#define BF_CLEVELPRESENTER_H

namespace BlockyFalls {

  class CLevelPresenter : public Vipper::IPresenter {
  
  public:
    explicit CLevelPresenter();
    
    void showPullAnimation();
    void showBlocksExplosionAt( std::vector<std::pair<int, int>> positions );
    void drawBlockAt( std::tuple<int, int, CColumn::EColour> block );
    void animateBlockFalling( std::tuple<int, int, CColumn::EColour> block, std::pair<int, int> position);
    void drawScoreGain(int gain);
    void playVanishSound();
    void playFallSound();
    void playPullSound();
  };
}
#endif
