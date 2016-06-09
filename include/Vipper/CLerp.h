#ifndef VIPPER_CLERP_H
#define VIPPER_CLERP_H

namespace Vipper {
	class CLerp {
		long mInitialValue;
		long mDelta;
		long mDuration;
		public:
		explicit CLerp( long initialValue, long finalValue, long duration );
		long getValue( long ellapsed );	
	};
}
#endif