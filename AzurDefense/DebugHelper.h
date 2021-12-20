#pragma once
#include <string>
#include <iostream>
#include <assert.h>
using namespace std;

class DebugHelper {
public:
	struct UndefineOperationException : public exception {
		const char* what() const throw() {
			return "Undefine Operation!";
		}
	};

	static void logInfo(string info) {
		cout << "[INFO]: " << info << endl;
	}

	static void logWarning(string warning) {
		cout << "[WARNING]: " << warning << endl;
	}

	static void logError(string error) {
		cout << "[ERROR]: " << error << endl;
		exit(-1);
	}
	static bool debug;
	static int count;
};