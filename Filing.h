
#ifndef FILING_H
#define FILING_H

#include <string>
using namespace std;
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;


const int MAX_FILENAME = 255;

void intToChars(int num, char*& str) {
	if (str)
		delete[] str;
	str = nullptr;
	int len = 0;
	while (num > 0) {
		int digit = num % 10;
		num /= 10;
		char* tmp = new char[len + 1];
		int j = len;
		for (int i = len - 1; i >= 0; i--) {
			tmp[j] = str[i];
			j--;
		}
		tmp[0] = digit + 48;
		delete[] str;
		str = tmp;
		len++;
	}
	char* tmp = new char[len + 1];
	for (int i = 0; i < len; i++)
		tmp[i] = str[i];
	tmp[len] = 0;
	delete[] str;
	str = tmp;
}

char* generateFileName(int numNodes) { //of first key
	char* filename = new char[MAX_FILENAME];
	for (int i = 0; i < 20; i++)
		filename[i] = 0;
	filename[0] = 'n';
	filename[1] = 'o';
	filename[2] = 'd';
	filename[3] = 'e';
	filename[4] = '-';
	int index = 5;
	char* nodeNum = nullptr;
	intToChars(numNodes + 1, nodeNum);
	int j = 0;
	while (nodeNum[j] != 0) {
		filename[index++] = nodeNum[j];
		j++;
	}
	filename[index++] = '.';
	filename[index++] = 't';
	filename[index++] = 'x';
	filename[index++] = 't';
	return filename;
}


#endif