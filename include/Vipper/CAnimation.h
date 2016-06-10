#ifndef VIPPER_CANIMATION_H
#define VIPPER_CANIMATION_H

namespace Vipper {
	class CAnimation {

		std::pair<int, int> mOrigin;
		std::pair<int, int> mDestination;
		std::function< void( std::shared_ptr<IRenderer> ) > mDrawFunction;
		std::function< void()> mOnAnimationEnded;
		long mDuration;
		
		public:
		explicit CAnimation( std::pair<int, int> from, std::pair<int, int> to, std::function< void(std::shared_ptr<IRenderer>)> drawFunction, long duration, std::function<void()> onEnded );	
	};
}
#endif