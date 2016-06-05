#ifndef BF_CGAMEPLAYPRESENTER_H
#define BF_CGAMEPLAYPRESENTER_H

namespace BlockyFalls {

  class CGameplayPresenter : public Vipper::IPresenter {
    std::shared_ptr<CGameSession> mGameSession;
    std::shared_ptr<Vipper::IView> mView;
  public:
    explicit CGameplayPresenter(std::shared_ptr<CGameSession> gameSession, std::shared_ptr<Vipper::IView> view ); 
    
    void setScore( int score );
    void setPullTime( int timeToPull );
    void setPointsUntilNextLevel( int points );
    
    void present() override;
  };
}
#endif
