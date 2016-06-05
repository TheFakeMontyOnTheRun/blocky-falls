#ifndef VIPPER_IROUTER_H
#define VIPPER_IROUTER_H

namespace Vipper {
	class IRouter : public std::enable_shared_from_this<IRouter>{
		std::shared_ptr<IRouter> mNextRoute;
		std::shared_ptr<IPresenter> mPresenter;
		std::shared_ptr<IInteractor> mInteractor;
		std::shared_ptr<IRenderer> mRenderer;
		std::string mName;
		public:
		explicit IRouter( std::shared_ptr<IRenderer> renderer, std::string name );
		
		void setName( std::string name );
		std::string getName();
		
		void setNextRoute( std::shared_ptr<IRouter> nextRoute );
		virtual std::shared_ptr<IRouter> route();
		
		void setPresenter( std::shared_ptr<IPresenter> presenter );
		std::shared_ptr<IPresenter> getPresenter();
		
		void setInteractor( std::shared_ptr<IInteractor> interactor );
		std::shared_ptr<IInteractor> getInteractor();
		
		void setRenderer( std::shared_ptr<IRenderer> renderer );
		std::shared_ptr<IRenderer> getRenderer();
		
		virtual void onFocus();
		virtual void onRelinquishFocus();
		virtual void initWithDefaults() = 0;
	};
}
#endif