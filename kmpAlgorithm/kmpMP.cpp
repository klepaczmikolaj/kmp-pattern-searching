#include "pch.h"
#include <iostream>
#include <algorithm>
#include "kmpMP.h"

void computePrefixSuffixMP(char *text, int *P, int textLength) {
	P[0] = -1;
	int t = -1;
	#pragma omp for
	for (int j = 1; j <= textLength; j++) {
		while (t >= 0 && text[t] != text[j - 1]) {
			t = P[t];
		}
		t++;
		P[j] = t;
	}
/*	
	//display prefix-suffix
	for (int i = 1; i < textLength + 1; i++)
		std::cout << P[i];
	std::cout << std::endl;
*/
}

void computeStrongPrefixSuffixMP(char *text, int *Pp, int textLength) {
	Pp[0] = -1;
	int t = -1;
	#pragma omp for
	for (int j = 1; j <= textLength; j++) {
		while (t >= 0 && text[t] != text[j - 1]) {
			t = Pp[t];
		}
		t++;
		if (j == textLength | text[t] != text[j])
			Pp[j] = t;
		else
			Pp[j] = Pp[t];
	}
	/*
	//display prefix-suffix
	for (int i = 1; i < textLength + 1; i++)
		std::cout << Pp[i];
	std::cout << std::endl;
	*/
}

int kmpAlgorithmMP(char *text, char *pattern, bool isPSStrong) {

	int textLength = strlen(text); // y, n
	int patLength = strlen(pattern); //x, m
	int pLength = textLength + 1;
	int *P = new int[pLength];
	int occurrences = 0;
	int i = 0;
	int j = 0;

	
	#pragma omp parallel
	{
	
		if (isPSStrong)
			computeStrongPrefixSuffixMP(text, P, textLength);
		else
			computePrefixSuffixMP(text, P, textLength);

		while (i < textLength - patLength) {
			while (j < patLength && pattern[j] == text[i + j])
				j++;
			if (j == patLength) {
				// std::cout << "Found pattern at index: " << i << std::endl;
				occurrences++;
			}
			i = i + j - P[j];
			j = std::max(0, P[j]);
		}
	}

	delete[] P;
	return occurrences;
}

int morrisPrattMP(char *text, char *pattern) {
	return kmpAlgorithmMP(text, pattern, false);
}

int knuthMorrisPrattMP(char *text, char *pattern) {
	return kmpAlgorithmMP(text, pattern, true);
}
