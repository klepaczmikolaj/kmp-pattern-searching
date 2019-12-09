
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

int main(){
	std::string textStr = readTextFile("test_data/enwik8.txt");
	char *text = new char[textStr.length() + 1];
	strcpy(text, textStr.c_str());
	char pattern[] = "John";
	int result1, result2, result1OMP, result2OMP;
	clock_t start, end;
	double timeElapsed;

	//std::cout << text << std::endl;

	start = clock();
	result1 = morrisPratt(text, pattern);
	end = clock();
	timeElapsed = (double) (end - start) / CLOCKS_PER_SEC;
	std::cout << "Time elapsed, sequential MP algorithm " << timeElapsed << std::endl;
	std::cout << "Number of " << pattern << " occurrences: " << result1 << std::endl;

	start = clock();
	result2 = knuthMorrisPratt(text, pattern);
	end = clock();
	timeElapsed = (double)(end - start) / CLOCKS_PER_SEC;
	std::cout << "Time elapsed, sequential KMP algorithm " << timeElapsed << std::endl;
	std::cout << "Number of " << pattern << " occurrences: " << result2 << std::endl;

	// open MP
	start = clock();
	result1 = morrisPrattMP(text, pattern);
	end = clock();
	timeElapsed = (double)(end - start) / CLOCKS_PER_SEC;
	std::cout << "Time elapsed, parallel MP algorithm " << timeElapsed << std::endl;
	std::cout << "Number of " << pattern << " occurrences: " << result1 << std::endl;

	start = clock();
	result2 = knuthMorrisPrattMP(text, pattern);
	end = clock();
	timeElapsed = (double)(end - start) / CLOCKS_PER_SEC;
	std::cout << "Time elapsed, parallel KMP algorithm " << timeElapsed << std::endl;
	std::cout << "Number of " << pattern << " occurrences: " << result2 << std::endl;

	delete[] text;
	return 0;
}
