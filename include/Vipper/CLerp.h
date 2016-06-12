#ifndef VIPPER_CLERP_H
#define VIPPER_CLERP_H

namespace Vipper {
	class CLerp {
		

		
		public:
		float mDelta;
		float mDuration;
		float mInitialValue;
		long mEllapsed;
		explicit CLerp( long initialValue, long finalValue, long duration );
		float getValue( long ellapsed );	
		float getFinalValue();
		bool isFinished();
		float getCurrentValue();
		long getEllapsed();
		long getDuration();
		void update( long ms );
	};
}
#endif