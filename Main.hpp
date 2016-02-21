#if !defined _Main
#define _Main


#include "common/Application.hpp"

#include "dependencies/DLinkedList.hpp"
#include "dependencies/benchmark.h"
#include "dependencies/Chronometer.hpp"

#include <fstream>


class Main{

	protected:

	bool saveListInFile(const char *fileName, DLinkedList<int> *list){

		std::ofstream file;
		file.open(fileName, std::ios::out | std::ios::trunc);

		if(!file){
			return false;
		}

		list->moveToFirst();
		do{
			file << list->getValue() << " ";
		}while(list->moveToNext());

		file.close();
		return true;
	}

	DLinkedList<int> *loadListFromFile(const char *fileName){

		std::ifstream file;

		DLinkedList<int> *list = new DLinkedList<int>();
		int i;


		file.open(fileName, std::ios::in);
		do{

			file >> i;
			list->insertAfter(i);

		}while(!file.eof());
		file.close();

		list->moveToLast();
		list->remove();

		return list;
	}

	void addResult(struct benchmarkResult * results){
		for(int i = 0; i < 4; i++){

			if(this->results[i] == nullptr){
				this->results[i] = results;
				this->countResult++;
				return;
			}

			if(this->results[i]->sortType == results->sortType){
				delete [] this->results[i]->perFiles;
				delete this->results[i];

				this->results[i] = results;
				return;
			}
			
		}
	}

	common::Base * base;
	struct benchmarkResult * results[4];
	int countResult;


	public:

	Main(){
		this->base = common::Base::getInstance();

		for(int i = 0; i < 4; i++){
			this->results[i] = nullptr;
		}

		this->countResult = 0;
	}

	~Main(){
		for(int i = 0; i < this->countResult; i++){
			delete [] this->results[i]->perFiles;
			delete this->results[i];
		}

		this->countResult = 0;
	}

	int mainMenu(){
		int option = -1;
		while(true){

			base->console->clear();
			base->output->putString("\n\n");
			base->output->putString("\t+----------------------------------------------------------+\n");
			base->output->putString("\t|                                                          |\n");
			base->output->putString("\t|         Segundo Trabalho de Estrutura de Dados           |\n");
			base->output->putString("\t|                                                          |\n");
			base->output->putString("\t+----------------------------------------------------------+\n\n");

			
			base->output->putString("   Opções de ordenação:\n");
			base->output->putString("   1 -> Ordenar com Selection sort;\n");
			base->output->putString("   2 -> Ordenar com Bubble sort;\n");
			base->output->putString("   3 -> Ordenar com Merge sort;\n");
			base->output->putString("   4 -> Ordenar com Quick sort;\n");
			base->output->putString("\n   Outros:\n");
			base->output->putString("   5 -> Ver comparativo;\n");
			base->output->putString("   0 -> Sair do programa;\n");

			option = base->input->getInt("\n   Selecione uma opção do menu: ");

			if(option >= 0 && option <= 5){
				return option;
			}

			base->output->putString("\nOpção inválida! ");
			base->console->pause();
		}

		return 0;
	}


	void createFiles(){
		base->output->putString("Gerando arquivos:\n");

		base->console->exec("./createFolder.sh output");
		base->console->exec("./createFolder.sh output/nao_ordenados");
		base->console->exec("./createFolder.sh output/selection_sort");
		base->console->exec("./createFolder.sh output/bubble_sort");
		base->console->exec("./createFolder.sh output/merge_sort");
		base->console->exec("./createFolder.sh output/quick_sort");


		int numbers = 100;
		int i;
		DLinkedList<int> *list = new DLinkedList<int>();
		std::string str;
		do{
			base->output->flush();
			str = std::to_string (numbers) + " Números... ";
			base->output->putString(str);

			list->clear();

			for(i = 1; i <= numbers; i++){
				list->insertAfter(base->random->getInt(numbers));
			}
			
			str = "output/nao_ordenados/"+std::to_string (numbers)+".txt";

			if(this->saveListInFile(str.c_str(), list)){
				base->output->flush();
				base->output->putString("OK\n");
			}

			numbers *= 10;

		}while(numbers <= 100000);

		DLinkedList<int>::destroy(list);

		base->console->exec("sleep 1.5s");

	}

	void sortFiles(int sortType){

		std::string dir = "output/";
		std::string mode;
		std::string file;

		base->console->clear();

		switch(sortType){
			case DLinkedList<int>::SELECTION_SORT:
				base->output->putString("Ordenando com Selection sort:\n");
				mode = "selection_sort/";
			break;
			case DLinkedList<int>::BUBBLE_SORT:
				base->output->putString("Ordenando com Bubble sort:\n");
				mode = "bubble_sort/";
			break;
			case DLinkedList<int>::MERGE_SORT:
				base->output->putString("Ordenando com Merge sort:\n");
				mode = "merge_sort/";
			break;
			case DLinkedList<int>::QUICK_SORT:
				base->output->putString("Ordenando com Quick sort:\n");
				mode = "quick_sort/";
			break;
		}

		int numbers = 100;
		DLinkedList<int> *list = nullptr;

		struct benchmarkResult* result = new struct benchmarkResult;
		result->perFiles = new struct benchmark[4];
		result->sortType = sortType;
		int i = 0;

		do{
			base->output->putString(std::to_string(numbers) + " Números... ");
			
			file = dir + "nao_ordenados/" + std::to_string(numbers) + ".txt";
			list = this->loadListFromFile(file.c_str());

			list->sort(sortType);

			result->perFiles[i++] = list->getSortBenchmark();

			file = dir + mode + std::to_string(numbers) + ".txt";
			this->saveListInFile(file.c_str(), list);


			base->output->putString("OK\n");

			numbers *= 10;

		}while(numbers <= 100000);

		DLinkedList<int>::destroy(list);

		this->addResult(result);

		base->console->exec("sleep 1");
	}

	void showResults(){
		base->console->clear();

		if(this->countResult <= 0){
			this->base->output->putString("Nenhum arquivo foi ordenado!\n");
			this->base->console->pause();
			return;
		}

		int i, j;

		for(i = 0; i < 4; i++){

			switch(i){
				case 0: this->base->output->putString("\n\tOrdenação de 100 números:\n"); break;
				case 1: this->base->output->putString("\n\tOrdenação de 1000 números:\n"); break;
				case 2: this->base->output->putString("\n\tOrdenação de 10000 números:\n"); break;
				case 3: this->base->output->putString("\n\tOrdenação de 100000 números:\n"); break;
			}

			this->base->output->putString("\t+-----------+---------+-------------+---------------+\n");
			this->base->output->putString("\t| Algoritmo |  Tempo  | Comparações | Movimentações |\n");
			this->base->output->putString("\t+-----------+---------+-------------+---------------+\n");

			for(j = 0; j < this->countResult; j++){

				switch(this->results[j]->sortType){
					case DLinkedList<int>::SELECTION_SORT: this->base->output->putString("\t| Selection |"); break;
					case DLinkedList<int>::BUBBLE_SORT:    this->base->output->putString("\t|   Bubble  |"); break;
					case DLinkedList<int>::MERGE_SORT:     this->base->output->putString("\t|    Merge  |"); break;
					case DLinkedList<int>::QUICK_SORT:     this->base->output->putString("\t|    Quick  |"); break;
				}

				this->base->output->printF(" %*d %*s |", 4, this->results[j]->perFiles[i].time, 2, Chronometer::getUnitySymble(this->results[j]->perFiles[i].timeUnity));
				this->base->output->printF(" %*lu |", 11, this->results[j]->perFiles[i].compareds);
				this->base->output->printF(" %*lu |\n", 13, this->results[j]->perFiles[i].moves);
				this->base->output->putString("\t+-----------+---------+-------------+---------------+\n");
			}
		}

		this->base->output->putString("\n\t\t   ");
		this->base->console->pause();

	}

};
#endif