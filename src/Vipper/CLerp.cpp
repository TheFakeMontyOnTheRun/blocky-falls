#include <algorithm>
#include "Vipper/CLerp.h"

namespace Vipper {
	CLerp::CLerp( long initialValue, long finalValue, long duration ) : 
	mInitialValue( initialValue ), mDelta( fabs(finalValue - initialValue) ), mDuration( duration ), mEllapsed( 0 ) {
	}
	
	float CLerp::getValue( long ellapsed ) {
		return mInitialValue + std::min( ( ( mDelta * ellapsed ) / mDuration ), mDelta ); 
	}

	float CLerp::getFinalValue() {
		return mInitialValue + mDelta;
	}

	long CLerp::getEllapsed() {
		return mEllapsed;
	}

	float CLerp::getCurrentValue() {
		return getValue( mEllapsed );
	}

	void CLerp::update( long ms ) {
		mEllapsed += ms;
	}

	long CLerp::getDuration() {
		return mDuration;
	}

	bool CLerp::isFinished() {
		return mEllapsed >= mDuration;
	}
}