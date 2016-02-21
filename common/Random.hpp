#if !defined  _Random
#define _Random

#include <random>

namespace common {

	class Random {
		private:

		Random(){}

		Random(Random const&);

        void operator=(Random const&);

        std::mt19937 generator;

        int rand(int min, int max){
        	this->generator.seed(std::random_device()());
        	std::uniform_int_distribution<std::mt19937::result_type> distribution(min, max);
        	return distribution(this->generator);
        }

		public:

		static Random* getInstance(){
            static Random *instance = new Random;
            return instance;
        }

        int getInt(int max = 99, int min = 0){
        	if(min > max){
        		int tmp = min;
        		min = max;
        		max = tmp;
        	}

        	if(min == max){
        		return min;
        	}

        	return this->rand(min, max);
        }

        char getChar(bool printableOnly = true){
        	char minChar = 0;
        	char maxChar = 127;

        	if(printableOnly){
        		minChar = 33;
        		maxChar = 126;
        	}

        	return (char) this->rand(minChar, maxChar);
        }

        double getDouble(){
        	int i, j;
        	do{

        		i = this->rand(1, 100);
        		j = this->rand(1, 200);

        	}while((j == 0) || (i % j == 0));

        	return ((double) i)/((double) j);
        }

        bool getBool(){
		  return (this->rand(0, 99) % 2 == 0);
		}
	};
}
#endif
