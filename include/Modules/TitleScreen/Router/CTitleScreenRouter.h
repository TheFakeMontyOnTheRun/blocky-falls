#ifndef BF_CTITLESCREENROUTER_H
#define BF_CTITLESCREENROUTER_H

namespace BlockyFalls {
	class CTitleScreenRouter : public Vipper::IRouter {
		std::shared_ptr<CGameplayRouter> mGameplayRouter;
		public:

		explicit CTitleScreenRouter( std::shared_ptr<Vipper::IRenderer> renderer, std::shared_ptr<CGameplayRouter> gameplayRouter );

		void goToGameplay();
		void initWithDefaults() override;
		void onFocus() override;
    	void onRelinquishFocus() override;
	};	
}
#endif