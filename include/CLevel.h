#ifndef BF_CLevel_H
#define BF_CLevel_H

namespace BlockyFalls {
  class CLevel {
    
  public:
    enum class EColour{ eRed, eYellow, eGrey, eBlue};
    explicit CLevel();
    void pull();
    EColour colourAt( int x, int y );
    bool isGameOver();
    bool isLevelCompleted();
  private:
    std::shared_ptr<EColour> map[ 20 ][ 20 ];
  };
}
#endif
