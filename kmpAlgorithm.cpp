﻿
#include "pch.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <cstring>
#include <sstream>
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

int main(){
	std::string textStr = readTextFile("test_data/enwik8_cp.txt");
	char *text = new char[textStr.length() + 1];
	int *patPositions = new int[textStr.length() + 1];
	strcpy(text, textStr.c_str());
	char pattern[] = "John is";
	int result1, result2, result1OMP, result2OMP;
	clock_t start, end;
	double startMP, endMP, timeElapsed;

	//std::cout << text << std::endl;

	start = clock();
	result1 = morrisPratt(text, pattern, patPositions);
	end = clock();
	// displayPositions(result1, patPositions);
	timeElapsed = (double) (end - start) / CLOCKS_PER_SEC;
	std::cout << "Time elapsed, sequential MP algorithm: " << timeElapsed << std::endl;
	std::cout << "Number of \'" << pattern << "\' occurrences: " << result1 << std::endl << std::endl;

	start = clock();
	result2 = knuthMorrisPratt(text, pattern, patPositions);
	end = clock();
	// displayPositions(result1, patPositions);
	timeElapsed = (double)(end - start) / CLOCKS_PER_SEC;
	std::cout << "Time elapsed, sequential KMP algorithm: " << timeElapsed << std::endl;
	std::cout << "Number of \'" << pattern << "\' occurrences: " << result2 << std::endl << std::endl;

	// open MP
	startMP = omp_get_wtime();
	result1 = morrisPrattMP(text, pattern, patPositions);
	endMP = omp_get_wtime();
	// displayPositions(result1, patPositions);
	timeElapsed = (double)(endMP - startMP);
	std::cout << "Time elapsed, parallel MP algorithm: " << timeElapsed << std::endl;
	std::cout << "Number of \'" << pattern << "\' occurrences: " << result1 << std::endl << std::endl;

	startMP = omp_get_wtime();
	result2 = knuthMorrisPrattMP(text, pattern, patPositions);
	endMP = omp_get_wtime();
	// displayPositions(result1, patPositions);
	timeElapsed = (double)(endMP - startMP);
	std::cout << "Time elapsed, parallel KMP algorithm: " << timeElapsed << std::endl;
	std::cout << "Number of \'" << pattern << "\' occurrences: " << result2 << std::endl << std::endl;

	delete[] text;
	delete[] patPositions;
	return 0;
}