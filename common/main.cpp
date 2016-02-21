#include "Application.hpp"
using namespace common;

int main (){
	
	Application *app = Application::getInstance();
	return app->main();
}
