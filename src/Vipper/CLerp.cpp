#include <algorithm>
#include "Vipper/CLerp.h"

namespace Vipper {
	CLerp::CLerp( long initialValue, long finalValue, long duration ) : 
	mInitialValue( initialValue ), mDelta( finalValue - initialValue ), mDuration( duration ) {
	}
	
	long CLerp::getValue( long ellapsed ) {
		return mInitialValue + std::min( ( ( mDelta * ellapsed ) / mDuration ), mDelta ); 
	}
}