#ifndef BF_CLevel_H
#define BF_CLevel_H

namespace BlockyFalls {
  class CLevel : public Vipper::IEntity {

  public:
    static const int kColumnHeight = 20;
    static const int kNumberOfColumns = 20;

    enum class EColour{ eRed, eYellow, eGrey, eBlue, eNothing};
    explicit CLevel();
    EColour colourAt( int x, int y );
    bool isGameOver();
    bool isLevelCompleted();
    void breakBlockAt( std::pair<int, int> position );
    EColour getRandomPiece();
  private:
    EColour map[ kColumnHeight ][ kNumberOfColumns ];
  };
}
#endif
