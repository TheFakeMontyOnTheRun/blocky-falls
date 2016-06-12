#ifndef BF_CCOLUMN_H
#define BF_CCOLUMN_H

namespace BlockyFalls {
  class CColumn : public Vipper::IEntity {

  public:
    using CCoordinates = std::pair<int,int>;
    using CIndex = int;
    static const int kColumnHeight = 7;
    
    enum class EColour{ eRed, eYellow, eGrey, eBlue, eNothing, eSpecial};
    explicit CColumn();
    EColour colourAt( int index );
    void breakBlockAt( int index );
    EColour getRandomPiece();
    bool isEmpty();
    std::vector<std::tuple<CCoordinates, CCoordinates, CColumn::EColour>> getDropList( int xPos);
    void dropBlocksAboveEmptySpaces();
    std::vector<EColour> mBlocks;    
  private:
    
  };
}
#endif
