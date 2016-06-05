#ifndef BF_CCOLUMNSMUSTCOLLAPSE_H
#define BF_CCOLUMNSMUSTCOLLAPSE_H

namespace BlockyFalls {

  class CColumnsMustCollapse : public Vipper::IInteractor {
    std::shared_ptr<CLevel> mLevel;
  public:
    explicit CColumnsMustCollapse( std::shared_ptr<CLevel> level);
    void collapseColumns();
  };
}
#endif
