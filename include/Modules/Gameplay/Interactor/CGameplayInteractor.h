#ifndef BF_CGAMEPLAYINTERACTOR_H
#define BF_CGAMEPLAYINTERACTOR_H
namespace BlockyFalls {
	class CGameplayInteractor : public Vipper::IInteractor {
		std::shared_ptr<Vipper::IRouter> mRouter;
		public:
		explicit CGameplayInteractor(std::shared_ptr<Vipper::IRouter> router);
	
		void interact() override;
	};
}
#endif