#if !defined _Chronometer
#define _Chronometer

#include <chrono>

struct minuteAndSecond{
	int minutes;
	int seconds;
};

class Chronometer{
	protected:

	std::chrono::time_point<std::chrono::system_clock> startTime;
	std::chrono::time_point<std::chrono::system_clock> endTime;

	int unity;
	unsigned long long totalTime;
	bool paused;

	std::chrono::time_point<std::chrono::system_clock> getNowTime(){
		return std::chrono::system_clock::now();
	}

	public:

	static const int NANOSECONDS_UNITY = 0;
	static const int MICROSECONDS_UNITY = 1;
	static const int MILLISECONDS_UNITY = 2;
	static const int SECOND_UNITY = 3;
	static const int MINUTE_UNITY = 4;

	static struct minuteAndSecond toMinutesAndSeconds(int secondsTime){
		struct minuteAndSecond result;
		result.minutes = 0;
		result.seconds = 0;

		if(secondsTime < 0){
			return result;
		}

		while(secondsTime >= 60){
			result.minutes++;
			secondsTime -= 60;
		}

		result.seconds = secondsTime;

		return result;
	}

	static const char* getUnitySymble(int unity){

		switch(unity){
			case MILLISECONDS_UNITY: return "ms"; break;
			case SECOND_UNITY: return "s"; break;
			case MINUTE_UNITY: return "m"; break;
			case MICROSECONDS_UNITY: return "μs"; break;
		}

		return "ns";
	}

	Chronometer(){
		this->reset();
	}

	void reset(){
		this->paused = true;
		this->pause();
		this->totalTime = 0;
		this->unity = this->NANOSECONDS_UNITY;
	}

	void start(){
		if(!this->paused){
			return;
		}

		this->paused = false;
		this->startTime = this->getNowTime();
	}

	void pause(){
		if(this->paused){
			return;
		}

		this->endTime = this->getNowTime();

		this->totalTime += std::chrono::duration_cast<std::chrono::nanoseconds>(this->endTime - this->startTime).count();
	}

	int getResultTime(){

		unsigned long long resultTime = this->totalTime;

		if(this->unity == this->NANOSECONDS_UNITY){

			if(resultTime < 1000){
				return (int) resultTime;
			}

			resultTime = (unsigned long long) resultTime/1000;
			this->unity = this->MICROSECONDS_UNITY;
		}

		if(this->unity == this->MICROSECONDS_UNITY){

			if(resultTime < 1000){
				return (int) resultTime;
			}

			resultTime = (unsigned long long) resultTime/1000;
			this->unity = this->MILLISECONDS_UNITY;
		}

		if(this->unity == this->MILLISECONDS_UNITY){

			if(resultTime < 1000){
				return (int) resultTime;
			}

			resultTime = (unsigned long long) resultTime/1000;
			this->unity = this->SECOND_UNITY;
		}

		return (int) resultTime;
	}

	struct minuteAndSecond toMinutesAndSeconds(){

		if(this->unity == this->SECOND_UNITY){
			return Chronometer::toMinutesAndSeconds(this->getResultTime());
		}

		struct minuteAndSecond result;
		result.minutes = 0;
		result.seconds = 0;

		return result;
	}

	const char* getUnitySymble(){
		return Chronometer::getUnitySymble(this->unity);
	}

	int getUnity(){
		return this->unity;
	}

};

#endif
