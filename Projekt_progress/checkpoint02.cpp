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

int main(int argc, char** argv)
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

	int records_with_duplicates = test.size();

	for (int i = 0; i < test.size(); i++)
	{
		for (int j = i + 1; j < test.size(); j++)
		{
			if (test[i] == test[j])
			{
				test.erase(test.begin() + j);
				j = i;
			}
		}
	}

	int records_without_duplicates = test.size();

	cout << records_with_duplicates << endl;
	cout << records_without_duplicates << endl;
	for (int i = 0; i < test.size(); i++)
	{
		cout << test[i];
	}


	return 0;
}
