
#if !defined _StdOutput
#define _StdOutput

#include <iostream>
#include <cstdio>

namespace common {

    class StdOutput{

    	private:
            
		StdOutput(){}
		StdOutput(StdOutput const&);
        void operator=(StdOutput const&);

        public:

		static StdOutput* getInstance(){
            static StdOutput *instance = new StdOutput;
            return instance;
        }
        
        void flush(){
            std::cout.flush();
        }

        void printF(const char *strFormat){
            this->putString(strFormat);
        }

        template<typename... Params>
        void printF(const char *strFormat, Params... params){
            std::printf(strFormat, params...);
        }

        void putString(const std::string str, bool newLine = false){

            std::cout << str;

            if(newLine){
                std::cout << '\n';
            }
        }

        void putChar(char c){
            std::cout << c;
        }

        void putInt(int i){
            std::cout << i;
        }

        void putDouble(double d){
            std::cout << d;
        }

        template<class T> void put(T v){
            std::cout << v;
        }
    };
}

#endif
