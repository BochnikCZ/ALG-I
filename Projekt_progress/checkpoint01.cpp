#include <iostream>
//#include <fstream>>
#include <vector>

using namespace std;

int main(int argc, char**argv)
{
	const string input_file_filename = "input.txt";
	const string output_file_filename = "output.txt";

	FILE* input_file;
	fopen_s(&input_file, "input.txt", "r");


	vector<string> test;
	char line[32];
	while (fgets(line, sizeof(line), input_file)) {
		test.push_back(line);
	}

	fclose(input_file);

	for (int i = 0; i < test.size(); i++)
	{
		cout << test[i];
	}

	return 0;
}
