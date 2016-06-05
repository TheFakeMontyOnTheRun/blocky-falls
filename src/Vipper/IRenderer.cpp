#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <typeinfo>
#include <memory>
#include <cmath>

#include "Vipper/Vipper.h"

namespace Vipper {
	void IRenderer::registerClickListener( std::shared_ptr<IClickListener> listener ) {
		mClickListeners.push_back( listener );
	}
	
    void IRenderer::unregisterClickListener( std::shared_ptr<IClickListener> listener ) {
		auto elementIterator = std::find( mClickListeners.begin(), mClickListeners.end(), listener );

		//remove and erase is kinda ugly...
		
		if ( elementIterator != mClickListeners.end() ) {
			std::swap( *elementIterator, mClickListeners.back() );
			mClickListeners.pop_back();
		}
	}
		
	void IRenderer::dispatchClickToListeners( std::pair<int, int > pointerPosition ) {
		for ( auto& listener : mClickListeners ) {	
			listener->onClick( pointerPosition );
		}
	}
}


