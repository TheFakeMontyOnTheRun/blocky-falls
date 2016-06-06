#ifndef BF_CLEVEL_H
#define BF_CLEVEL_H

namespace BlockyFalls {
  class CLevel : public Vipper::IEntity {

  public:
    static const int kNumberOfColumns = 20;

    explicit CLevel( int initialColumns );
    CColumn::EColour colourAt( int x, int y );
    bool isGameOver();
    bool isLevelCompleted();
    void breakBlockAt( std::pair<int, int> position );
    void addRandomColumn();
  private:
    std::vector<std::shared_ptr<CColumn>> mColumns;
  };
}
#endif
