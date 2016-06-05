#ifndef BF_CPULLCOLUMNS_H
#define BF_CPULLCOLUMNS_H

namespace BlockyFalls {

  class CPullColumns : public Vipper::IInteractor {
    std::shared_ptr<CLevel> mLevel;
  public:
    explicit CPullColumns( std::shared_ptr<CLevel> level);
    void pull();
  };
}
#endif
