#include <utility>
#include <algorithm>
#include <functional>

#include "Vipper/Vipper.h"
#include "Vipper/CLerp.h"
#include "Vipper/CAnimation.h"

namespace Vipper {
		CAnimation::CAnimation( std::pair<int, int> from, std::pair<int, int> to, std::function< void(std::shared_ptr<IRenderer>)> drawFunction, long duration, std::function<void()> onEnded ):
		mOrigin( from ), mDestination( to ), mDrawFunction( drawFunction ), mDuration( duration ), mOnAnimationEnded( onEnded ) {
		}
		
		// void update( long ms ) {
		// 	mEllapsed += ms;
			
			
		// }
}
