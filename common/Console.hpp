#if !defined  _Console
#define _Console

#include "StdOutput.hpp"

#include <cstdlib>

#if defined WIN32
	#include <windows.h>
#endif

namespace common {

	class Console {
		private:

		Console(){
			output = StdOutput::getInstance();
		}

		Console(Console const&);

        void operator=(Console const&);

    	StdOutput *output;
		public:

		static Console* getInstance(){
            static Console *instance = new Console;
            return instance;
        }

        void clear(){
        	this->output->flush();

	    	#if defined WIN32
	        	system("cls");
	    	#else
	        	this->output->putString("\033c");
	    	#endif
        }

        void pause(){

	    	#if defined WIN32
	        	this->output->flush();
			    std::system("pause");
			#else
				this->output->putString("Pressione enter para continuar...");
			    this->output->flush();
			    std::system("read KEYPRESS");
			#endif
        }

        void gotoXY(int x, int y){
    		#if defined WIN32
	        	COORD pos = {x, y};
			    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
			    SetConsoleCursorPosition(output, pos);
			#else
				this->output->printF("\033[%d;%dH",y,x);
			#endif
        }

        void exec(const char *cmd){
        	std::system(cmd);
        }
	};
}
#endif
