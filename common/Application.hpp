#if !defined  _Application
#define _Application
#include "Base.hpp"

namespace common {
	class Application{
		private:

		Application(){
			base = Base::getInstance();
		}

		Application(Application const&);

        void operator=(Application const&);

		public:

		static Application* getInstance(){
            static Application *instance = new Application;
            return instance;
        }

		int main();
		
		const Base * base;
	};
}
#endif
