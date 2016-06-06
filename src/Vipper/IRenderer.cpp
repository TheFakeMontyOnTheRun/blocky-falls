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
	
	void IRenderer::registerKeyListener( std::shared_ptr<IKeyListener> listener ) {
		mKeyListeners.push_back( listener );
	}
	
    void IRenderer::unregisterKeyListener( std::shared_ptr<IKeyListener> listener ) {
		auto elementIterator = std::find( mKeyListeners.begin(), mKeyListeners.end(), listener );
		
		if ( elementIterator != mKeyListeners.end() ) {
			std::swap( *elementIterator, mKeyListeners.back() );
			mKeyListeners.pop_back();
		}
	}

	void IRenderer::dispatchKeyToListeners( long keyCode ) {
		for ( auto& listener : mKeyListeners ) {	
			listener->onKey( keyCode );
		}
	}	
		
	void IRenderer::dispatchClickToListeners( std::pair<int, int > pointerPosition ) {
		for ( auto& listener : mClickListeners ) {	
			listener->onClick( pointerPosition );
		}
	}
}


