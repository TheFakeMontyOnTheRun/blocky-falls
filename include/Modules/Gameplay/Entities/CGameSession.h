#ifndef BF_CGAMESESSION_H
#define BF_CGAMESESSION_H

namespace BlockyFalls {

  class CGameSession : public Vipper::IEntity {
    int mTimeLeft;
    int mHowFastThePullFill;
    int mPullMeter;
    int mPointsUntilNextLevel;
    int mLevelOfDificulty;
    std::shared_ptr<CLevel> mLevel;
    int mInitialTime;
    int mScore;
  public:
    explicit CGameSession( int initialTimeLeft, int pointsNeeded, int levelOfDificulty);
    std::shared_ptr<CLevel> getLevel();
    int getTimeLeft();
    bool shouldAddLine();
    void addLine();
    int getPullMeter();
    void update();
    int getScore();
    void addToScore( int score );
  };
}
#endif
