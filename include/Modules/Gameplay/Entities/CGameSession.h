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
  public:
    explicit CGameSession( int initialTimeLeft, int pointsNeeded, int levelOfDificulty);
    std::shared_ptr<CLevel> getLevel();
  };
}
#endif
