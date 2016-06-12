#include <iostream>

#include <utility>
#include <algorithm>
#include <functional>

#include "Vipper/Vipper.h"
#include "Vipper/CLerp.h"
#include "Vipper/CAnimation.h"

namespace Vipper {
		CAnimation::CAnimation( std::pair<int, int> from, std::pair<int, int> to, std::function< void(std::shared_ptr<IRenderer>)> drawFunction, long duration, std::function<void(std::pair<int,int>)> onEnded ):
		mOrigin( from ), mDestination( to ), mDrawFunction( drawFunction ), mOnAnimationEnded( onEnded ),
		mLerpX( from.first, to.first, duration ), mLerpY( from.second, to.second, duration ) {
		}

		std::pair<float, float> CAnimation::getPosition() {
			return std::pair<float,float>( mLerpX.getCurrentValue(), mLerpY.getCurrentValue() );
		}

		long CAnimation::getEllapsed() {
			return mLerpX.getEllapsed();
		}

		long CAnimation::getDuration() {
			return mLerpX.getDuration();
		}

		std::pair<int, int> CAnimation::getOrigin() {
			return mOrigin;
		}

		std::pair<int, int> CAnimation::getDestination() {
			return mDestination;
		}

		


		void CAnimation::update( long ms ) {
			mLerpX.update( ms );
			mLerpY.update( ms );
			
			if ( mOnAnimationEnded != nullptr && isFinished() ) {
				mOnAnimationEnded( mOrigin );
			}
		}

		bool CAnimation::isFinished() {
			return mLerpX.isFinished() && mLerpY.isFinished();
		}

		void CAnimation::draw(std::shared_ptr<IRenderer> renderer) {
			mDrawFunction(renderer);
		}
}
