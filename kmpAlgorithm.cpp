
#include "pch.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <cstring>
#include <sstream>
#include <sys/time.h>
#include <omp.h>
#include <iomanip>
#include "kmp.h"
#include "kmpMP.h"


std::string readTextFile(std::string fileName) {

	std::ifstream file(fileName);
	if (file.fail()) {
		std::cout << fileName << " file does not exist, exiting" << std::endl;
		exit(1);
	}
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

void displayPositions(int count, int *positions){
	for (int i = 0; i < count; i++){
		std::cout << positions[i] << ", ";
	}
	std::cout << std::endl;
}

double getWallTime(){
    struct timeval time;
    if (gettimeofday(&time,NULL)){
        //  Handle error
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

int main(int argc, char **argv){
	bool isSequential;
	int thread_count;
	// cmd args 
	std::string textStr = readTextFile(argv[1]);
	std::string patStr = argv[2];

	if(argc == 3){
		isSequential = true;
		std::cout << "Using sequential algorithm" << std::endl;
	}else if (argc == 4){
		thread_count = atoi(argv[3]);
		isSequential = false;
		std::cout << "Using openMP with " << thread_count << " thread(s)" << std::endl;
	}else{
		std::cout << "Wrong number of arguments" << std::endl;
		exit(1);
	}

	//variables
	char *text = new char[textStr.length() + 1];
	char *pattern = new char[patStr.length() + 1];
	int *patPositions = new int[textStr.length() + 1];
	strcpy(text, textStr.c_str());
	strcpy(pattern, patStr.c_str());
	int result1, result2, result1OMP, result2OMP;
	double start, end;
	double startMP, endMP, timeElapsed;

	if(isSequential){
		//sequential
		start = getWallTime();
		result1 = morrisPratt(text, pattern, patPositions);
		end = getWallTime();
		timeElapsed = (double) (end - start);
		std::cout << "Time elapsed, sequential MP algorithm: " << timeElapsed << std::endl;
		std::cout << "Number of \'" << pattern << "\' occurrences: " << result1 << std::endl << std::endl;

		start = getWallTime();
		result2 = knuthMorrisPratt(text, pattern, patPositions);
		end = getWallTime();
		timeElapsed = (double)(end - start);
		std::cout << "Time elapsed, sequential KMP algorithm: " << timeElapsed << std::endl;
		std::cout << "Number of \'" << pattern << "\' occurrences: " << result2 << std::endl << std::endl;
	}
	else{
		// open MP
		startMP = getWallTime();
		result1 = morrisPrattMP(text, pattern, patPositions, thread_count);
		endMP = getWallTime();
		timeElapsed = (double)(endMP - startMP);
		std::cout << "Time elapsed, parallel MP algorithm: " << timeElapsed << std::endl;
		std::cout << "Number of \'" << pattern << "\' occurrences: " << result1 << std::endl << std::endl;

		startMP = getWallTime();
		result2 = knuthMorrisPrattMP(text, pattern, patPositions, thread_count);
		endMP = getWallTime();
		timeElapsed = (double)(endMP - startMP);
		std::cout << "Time elapsed, parallel KMP algorithm: " << timeElapsed << std::endl;
		std::cout << "Number of \'" << pattern << "\' occurrences: " << result2 << std::endl << std::endl;

		delete[] text;
		delete[] patPositions;
		return 0;
	}
}
