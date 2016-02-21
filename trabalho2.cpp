#include "Main.hpp"

using namespace common;

int Application::main(){

	Main * mainProgram = new Main();

	mainProgram->createFiles();
	bool endProgram = false;

	while(!endProgram){
		switch(mainProgram->mainMenu()){
			case 1:
				mainProgram->sortFiles(DLinkedList<int>::SELECTION_SORT);
			break;
			case 2:
				mainProgram->sortFiles(DLinkedList<int>::BUBBLE_SORT);
			break;
			case 3:
				mainProgram->sortFiles(DLinkedList<int>::MERGE_SORT);
			break;
			case 4:
				mainProgram->sortFiles(DLinkedList<int>::QUICK_SORT);
			break;

			case 5:
				mainProgram->showResults();
			break;

			default:
				endProgram = true;
		}
	}
	
	delete mainProgram;

	return 0;
}