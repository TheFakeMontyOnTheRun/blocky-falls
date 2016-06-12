#ifndef VIPPER_CANIMATION_H
#define VIPPER_CANIMATION_H

namespace Vipper {
	class CAnimation {

		std::pair<int, int> mOrigin;
		std::pair<int, int> mDestination;
		CLerp mLerpX;
      	CLerp mLerpY;
		std::function< void( std::function< void( std::pair<float,float>, BlockyFalls::CColumn::EColour)> ) > mDrawFunction;
		std::function< void( std::pair<int,int>)> mOnAnimationEnded;
		
		public:
		std::pair<int, int> getOrigin();
		std::pair<int, int> getDestination();

		bool isFinished();
		void update( long ms );
		long getEllapsed();
		long getDuration();
		std::pair<float, float> getPosition();
		void draw(std::function<void(std::pair<float,float>,BlockyFalls::CColumn::EColour)> drawHelper ); 
		explicit CAnimation() = delete;
		explicit CAnimation( std::pair<int, int> from, std::pair<int, int> to, std::function< void( std::function< void( std::pair<float,float>, BlockyFalls::CColumn::EColour)> )> drawFunction, long duration, std::function<void(std::pair<int,int>)> onEnded );	
	};
}
#endif