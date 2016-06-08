#ifndef BF_CPULLCOLUMNS_H
#define BF_CPULLCOLUMNS_H

namespace BlockyFalls {

  class CPullsHappenPeriodically : public Vipper::IInteractor {
    std::shared_ptr<CLevel> mLevel;
    int mHowOften;
  public:
    explicit CPullsHappenPeriodically( std::shared_ptr<CLevel> level, int howOften );
    bool shouldAPullHappen( int ellapsedTime, int timeSinceLastPull);
  };
}
#endif
