#include <iostream>
#include "Vipper/Vipper.h"

namespace Vipper {
	IRouter::IRouter( std::shared_ptr<Vipper::IRenderer> renderer, std::string name ): mName( name ), mNextRoute( nullptr ), mRenderer( renderer ) {
	}
	
	std::shared_ptr<IRouter> IRouter::route() {
		auto toReturn = mNextRoute;
		mNextRoute = nullptr;
		
		return toReturn;
	}
	
	void IRouter::setNextRoute( std::shared_ptr<IRouter> nextRoute ) {
		if ( nextRoute != nullptr ) {
			std::cout << "A new route was set!" << std::endl;
		}
		mNextRoute = nextRoute;
	}
	
	void IRouter::setPresenter( std::shared_ptr<IPresenter> presenter ) {
		mPresenter = presenter;	
	}
	
	std::shared_ptr<IPresenter> IRouter::getPresenter() {
		return mPresenter;
	}
	
	void IRouter::setName( std::string name ) {
		mName = name;
	}
	
	std::string IRouter::getName() {
		return mName;
	}
	
	void IRouter::setInteractor( std::shared_ptr<IInteractor> interactor ) {
		mInteractor = interactor;	
	}
	
	std::shared_ptr<IInteractor> IRouter::getInteractor() {
		return mInteractor;
	}
	
	void IRouter::setRenderer( std::shared_ptr<Vipper::IRenderer> renderer ) {
		mRenderer = renderer;
	}
	
	std::shared_ptr<Vipper::IRenderer> IRouter::getRenderer() {
		return mRenderer;
	}
	
	void IRouter::onFocus() {
	}
		
	void IRouter::onRelinquishFocus() {
	}	
}