#include <iostream>
#include <vector>

using namespace std;
/*
struct Date
{
	int year;
	int month;
	int day;
};

struct Time {
	int hour;
	int minute;
	int second;
};



class Record
{
private:
	Date* date;
	Time* time;
	double humadity;
	double temperature;

public:
	Record(string line);

	Date* GetDate();
	Time* GetTime();
	double GetHumadity();
	double GetTemperature();
};

Record::Record(string line)
{
	for (int i = 0; i < 30; i++)
	{
		
	}
}

Date* Record::GetDate()
{
	return this->date;
}
Time* Record::GetTime()
{
	return this->time;
}
double Record::GetHumadity()
{
	return this->humadity;
}
double Record::GetTemperature()
{
	return this->temperature;
}

*/

vector<string> load_data_from_input(const char* filename)
{
	vector<string> lines;
	FILE* file;
	fopen_s(&file, filename, "r");
	if (file) {
		char line[32];
		while (fgets(line, sizeof(line), file)) {
			lines.push_back(line);
		}
		fclose(file);
	}
	return lines;
}

void removeDuplicates(vector<string>& vec) {
	for (int i = 0; i < vec.size(); i++) {
		for (int j = i + 1; j < vec.size(); j++) {
			if (vec[i] == vec[j]) {
				vec.erase(vec.begin() + j);
				j = i;
			}
		}
	}
}


int main()
{
	const char* input_file_filename = "input.txt";
	const char* output_file_filename = "output.txt";

	vector<string> test = load_data_from_input(input_file_filename);
	int records_with_duplicates = test.size();

	removeDuplicates(test);
	int records_without_duplicates = test.size();

	cout << records_with_duplicates << endl;
	cout << records_without_duplicates << endl;
	for (int i = 0; i < test.size(); i++)
	{
		cout << test[i];
	}


	return 0;
}
