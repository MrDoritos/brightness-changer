#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string.h>

using namespace std;

#define BL_DIR "/sys/class/backlight/intel_backlight/"
#define MAX_FILE BL_DIR"max_brightness"
#define FILE BL_DIR"brightness"

int write(const char* path, int value) {
	ofstream ofile(path);
	if (!ofile.is_open()) {
		return -1;
	}
	ofile << value;
	ofile.close();
	return 0;
}

int read(const char* path) {
	int value = -1;
	ifstream ifile(path);
	if (!ifile.is_open()) {
		return -1;
	}
	ifile >> value;
	return value;
}

void error(const char* error, int errcode) {
	printf("%s\n", error);
	exit(errcode);
	return;
}

int main(int argc, char** argv) {
	int newbrightness = -1;
	if (argc < 2) {
		int cur_bat = read(FILE);
		int max_bat = read(MAX_FILE);
		printf("%.1f%% %i\n", float(cur_bat)*(1/float(max_bat))*100.0f, cur_bat);
		return 0;
		//error("Not enough arguments", 1);
	}
	if (sscanf(argv[1], "%i", &newbrightness) != 1)
		error("Invalid arguments", 1);

	if (strcmp(argv[1], "%")) {
		if (write(FILE, float(newbrightness)*0.01*float(read(MAX_FILE))) == -1)
			error("Can't access file, try as root?", 1);
		return 0;
	}

	if (write(FILE, newbrightness) == -1)
		error("Can't access file, try as root?", 1);

	return 0;
}
