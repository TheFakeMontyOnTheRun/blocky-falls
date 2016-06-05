#ifndef BF_CGAMEPLAYROUTER_H
#define BF_CGAMEPLAYROUTER_H

namespace BlockyFalls {
  class CGameplayRouter : public Vipper::IRouter {
  public:
    explicit CGameplayRouter(std::shared_ptr<Vipper::IRenderer> renderer);
    void displayGameOverScreen();
    void displayNextLevelScreen();
    
    void initWithDefaults() override;
    void onFocus() override;
    void onRelinquishFocus() override;
  };
}
#endif
