#ifndef BF_CLEVEL_H
#define BF_CLEVEL_H

namespace BlockyFalls {
  class CLevel : public Vipper::IEntity {

  public:
    static const int kNumberOfColumns = 20;

    explicit CLevel( int initialColumns );
    CColumn::EColour colourAt( int x, int y );
    std::vector<std::pair<int, int>> breakBlockAt( std::pair<int, int> position );
    void addRandomColumn();
    bool canBreakAt( int x, int y );
    std::vector<std::pair<int, int>> propagate( int x, int y );
    void collapseEmptyColumns();
    std::vector<std::tuple<std::pair<int,int>, std::pair<int, int>, CColumn::EColour>> getDropList();
    void dropBlocksAboveEmptySpaces( int column );
  private:
    std::vector<std::shared_ptr<CColumn>> mColumns;
  };
}
#endif
