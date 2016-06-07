#ifndef BF_CCOLUMN_H
#define BF_CCOLUMN_H

namespace BlockyFalls {
  class CColumn : public Vipper::IEntity {

  public:
    static const int kColumnHeight = 7;

    enum class EColour{ eRed, eYellow, eGrey, eBlue, eNothing};
    explicit CColumn();
    EColour colourAt( int index );
    void breakBlockAt( int index );
    EColour getRandomPiece();
    bool isEmpty();
    void dropBlocksAboveEmptySpaces();;
  private:
    std::vector<EColour> mBlocks;
  };
}
#endif
