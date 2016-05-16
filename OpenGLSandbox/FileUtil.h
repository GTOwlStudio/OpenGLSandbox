#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "Util.h"

enum MODE_WRITTING_ARRAY_ENUM{
	MODE_DONOTHING = 0,
	MODE_OVERRIDE = 1,
	MODE_ADD = 2
};

class FileUtil
{
public:
	template <typename T>
static std::string arrayToString(T arr[], int size, int col=0){
	int c = col;
	std::string str = "{";
	for (int i=0;i<size-1;i++){
		str += std::to_string(arr[i]) + ",";
		if (i>=c-1){
			c+=col;
			str+="\n";
		}
	}
	str+=std::to_string(arr[size-1]) + "}";
	return str;
}

	static bool isChainInFile(std::string filename, std::string chainToFind);
	static bool arrayToFile(std::string filename, float *arr, int ID, int rows, int cols, int writtingMode);
	static void fileToArray(std::string filename, int ID, float *dst);
	static void stringToFile(std::string content, std::string filename);
	static void startlog(std::string file);

};

