#ifndef BF_CLevel_H
#define BF_CLevel_H

namespace BlockyFalls {
  class CLevel : public Vipper::IEntity {
    static const int kColumnHeight = 20;
    static const int kNumberOfColumns = 20;

  public:
    enum class EColour{ eRed, eYellow, eGrey, eBlue, eNothing};
    explicit CLevel();
    EColour colourAt( int x, int y );
    bool isGameOver();
    bool isLevelCompleted();
  private:
    CLevel::EColour map[ 20 ][ 20 ];
  };
}
#endif
