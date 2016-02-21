#if !defined  _AppBase
#define _AppBase

#include "StdInput.hpp"
#include "StdOutput.hpp"
#include "Types.hpp"
#include "Console.hpp"
#include "Random.hpp"

namespace common {

	class Base {
		private:

		Base(){
			input = StdInput::getInstance();
			output = StdOutput::getInstance();
			types = Types::getInstance();
			console = Console::getInstance();
			random = Random::getInstance();
		}

		Base(Base const&);

        void operator=(Base const&);

		public:

		static Base* getInstance(){
            static Base *instance = new Base;
            return instance;
        }

        StdInput *input;
        StdOutput *output;
        Types *types;
        Console *console;
        Random * random;
	};
}
#endif
