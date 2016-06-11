#ifndef VIPPER_CLERP_H
#define VIPPER_CLERP_H

namespace Vipper {
	class CLerp {
		
		float mDelta;
		
		public:
		float mDuration;
		float mInitialValue;
		explicit CLerp( long initialValue, long finalValue, long duration );
		float getValue( long ellapsed );	
	};
}
#endif