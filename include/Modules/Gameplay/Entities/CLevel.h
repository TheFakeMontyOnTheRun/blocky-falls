#ifndef BF_CLEVEL_H
#define BF_CLEVEL_H

namespace BlockyFalls {
  class CLevel : public Vipper::IEntity {

  public:
    static const int kNumberOfColumns = 11;

    explicit CLevel( int initialColumns );
    CColumn::EColour colourAt( int x, int y );
    std::vector<CColumn::CCoordinates> breakBlockAt( CColumn::CCoordinates position );
    void addRandomColumn();
    bool canBreakAt( int x, int y );
    std::vector<CColumn::CCoordinates> propagate( int x, int y );
    void collapseEmptyColumns();
    std::vector<std::tuple<CColumn::CCoordinates, CColumn::CCoordinates, CColumn::EColour>> getDropList();
    void dropBlocksAboveEmptySpaces( int column );
    std::set< CColumn::CCoordinates> getColumnCollapseList();
    bool isColumnEmpty( int index );
  private:
    std::vector<std::shared_ptr<CColumn>> mColumns;
  };
}
#endif
