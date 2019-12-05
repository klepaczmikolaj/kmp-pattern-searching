
#include "pch.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <cstring>
#include <sstream>
#include "kmp.h"


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
	std::string textStr = readTextFile("text.txt");
	char *text = new char[textStr.length() + 1];
	strcpy(text, textStr.c_str());
	char pattern[] = "be";
	int result1, result2;

	std::cout << text << std::endl;

	result1 = morrisPratt(text, pattern);
	std::cout << "Number of " << pattern << " occurrences: " << result1 << std::endl;

	result2 = knuthMorrisPratt(text, pattern);
	std::cout << "Number of " << pattern << " occurrences: " << result2 << std::endl;

	delete[] text;
	return 0;
}
