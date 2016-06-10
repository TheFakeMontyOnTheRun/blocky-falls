#ifndef VIPPER_CLERP_H
#define VIPPER_CLERP_H

namespace Vipper {
	class CLerp {
		float mInitialValue;
		float mDelta;
		float mDuration;
		public:
		explicit CLerp( long initialValue, long finalValue, long duration );
		float getValue( long ellapsed );	
	};
}
#endif