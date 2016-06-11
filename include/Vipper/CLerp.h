#ifndef VIPPER_CLERP_H
#define VIPPER_CLERP_H

namespace Vipper {
	class CLerp {
		float mInitialValue;
		float mDelta;
		
		public:
		float mDuration;
		explicit CLerp( long initialValue, long finalValue, long duration );
		float getValue( long ellapsed );	
	};
}
#endif