#include <iostream>
#include <fstream>
#include <string>
#define FILE "/sys/class/backlight/intel_backlight/brightness"

using namespace std;

void error(const char* error, int errnum = 1) {
	std::cout << error << std::endl;
	exit(errnum);
}

void write(int val) {
	ofstream i;
	i.open(FILE, ios::trunc | ios::out);
	if (!i.is_open())
		error("Could not open file\n\tAre you privileged?");
	i << val;
	i.close();
}

int main(int argc, char** argv) {
	int val = -1;

	if (argc < 2)
		error("Not enough arguments");

	if (sscanf(argv[1], "%i", &val) != 1)
		error("Invalid arguments");

	write(val);
	return 0;
}
