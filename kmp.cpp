#include "pch.h"
#include <iostream>
#include <algorithm>
#include <cstring>
#include "kmp.h"

void computePrefixSuffix(char *text, int *P, int textLength) {
	P[0] = -1;
	int t = -1;
	for (int j = 1; j <= textLength; j++) {
		while (t >= 0 && text[t] != text[j - 1]) {
			t = P[t];
		}
		t++;
		P[j] = t;
	}
}

void computeStrongPrefixSuffix(char *text, int *Pp, int textLength) {
	Pp[0] = -1;
	int t = -1;
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
}

int kmpAlgorithm(char *text, char *pattern, bool isPSStrong, int *patPositions) {

	int textLength = strlen(text); // y, n
	int patLength = strlen(pattern); //x, m
	int pLength = textLength + 1;
	int *P = new int[pLength];
	int occurrences = 0;
	
	int i = 0;
	int j = 0;
	if (isPSStrong)
		computeStrongPrefixSuffix(text, P, textLength);
	else
		computePrefixSuffix(text, P, textLength);

	for (i = 0; i < textLength - patLength; i = i + j - P[j]){
		if (i > 0)
			j = std::max(0, P[j]);
		while (j < patLength && pattern[j] == text[i + j])
			j++;
		if (j == patLength) {
			// std::cout << "Found pattern at index: " << i << std::endl;
			patPositions[occurrences] = i;
			occurrences++;

		}
	}


	delete[] P;
	return occurrences;
}

int morrisPratt(char *text, char *pattern, int *patPositions) {
	return kmpAlgorithm(text, pattern, false, patPositions);
}

int knuthMorrisPratt(char *text, char *pattern, int *patPositions) {
	return kmpAlgorithm(text, pattern, true, patPositions);
}
