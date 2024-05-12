#include <iostream>
#include <vector>

using namespace std;

double decode_battery(double hex)
{
	return (30.0 * hex);
}
double decode_temperature_humidity(double b2, double b1)
{
	int temp = (256 * b1) + b2;
	return (temp / 10.0);
}

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
	Date date;
	Time time;
	double humidity;
	double temperature;
	double battery;

public:
	Record(string line);

	Date GetDate();
	Time GetTime();
	double GetBattery();
	double GetHumidity();
	double GetTemperature();
};

Record::Record(string line)
{
	char year_in_string[4];
	int year_count = 0;
	char other_data_in_string[2];
	int data_count = 0;

	Date temp_date;
	Time temp_time;

	double temp_humidity;
	double temp_battery;
	double temp_temperature;

	for (int i = 0; i < 30; i++)
	{
		if (i < 4)
		{
			year_in_string[year_count] = line[i];
			year_count += 1;
		}

		else if (i == 4 && year_count == 4)
		{
			sscanf_s(year_in_string, "%d", &temp_date.year);
		}

		else if (4 < i && i < 20)
		{
			if (i == 7 || i == 10 || i == 13 || i == 16 || i == 19 && data_count == 2)
			{
				int temp;
				sscanf_s(other_data_in_string, "%d", &temp);

				switch (i)
				{
				case 7:
					temp_date.month = temp;
					break;

				case 10:
					temp_date.day = temp;
					break;

				case 13:
					temp_time.hour = temp;
					break;

				case 16:
					temp_time.minute = temp;
					break;

				case 19:
					temp_time.second = temp;
					break;

				default:
					break;
				}

				data_count = 0;
			}
			else
			{
				if (4 < i && i < 7)
				{
					other_data_in_string[data_count] = line[i];
					data_count += 1;
				}

				else if (7 < i && i < 10)
				{
					other_data_in_string[data_count] = line[i];
					data_count += 1;
				}

				else if (10 < i && i < 13)
				{
					other_data_in_string[data_count] = line[i];
					data_count += 1;
				}
				else if (13 < i && i < 16)
				{
					other_data_in_string[data_count] = line[i];
					data_count += 1;
				}
				else if (16 < i && i < 19)
				{
					other_data_in_string[data_count] = line[i];
					data_count += 1;
				}
			}
		}

		else
		{
			other_data_in_string[data_count] = line[i];
			data_count += 1;

			if (data_count == 2)
			{
				/*
				int r;
				int hex = 0;
				int len = 2;
				for (int x = 0; x < data_count; x++)
				{
					len--;
					if (other_data_in_string[x] >= '0' && other_data_in_string[x] <= '9')
					{
						r = other_data_in_string[x] - 48;
					}
					else if (other_data_in_string[x] >= 'a' && other_data_in_string[x] <= 'f')
					{
						r = other_data_in_string[x] - 87;
					}
					else if (other_data_in_string[x] >= 'A' && other_data_in_string[x] <= 'F')
					{
						r = other_data_in_string[x] - 55;
					}


					hex += r * pow(16, len);
				}*/

				int hex;
				sscanf_s(other_data_in_string, "%x", &hex);


				switch (i)
				{
				case 21:
					this->battery = decode_battery(hex);
					break;
				case 23:
					temp_temperature = hex;
					break;
				case 25:
					this->temperature = decode_temperature_humidity(hex, temp_temperature);
					break;
				case 27:
					temp_humidity = hex;
					break;
				case 29:
					this->humidity = decode_temperature_humidity(hex, temp_humidity);
				default:
					break;
				}

				data_count = 0;
			}
		}
	}

	this->date = temp_date;
	this->time = temp_time;
}

Date Record::GetDate()
{
	return this->date;
}
Time Record::GetTime()
{
	return this->time;
}
double Record::GetBattery()
{
	return this->battery;
}
double Record::GetHumidity()
{
	return this->humidity;
}
double Record::GetTemperature()
{
	return this->temperature;
}


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
	/*
	const char* input_file_filename = "input.txt";
	const char* output_file_filename = "output.txt";
	vector<string> input_data_unconverted;
	vector<Record> input_data_converted;
	int records_with_duplicates;
	int records_without_duplicates;


	input_data_unconverted = load_data_from_input(input_file_filename);
	records_with_duplicates = input_data_unconverted.size();

	removeDuplicates(input_data_unconverted);
	records_without_duplicates = input_data_unconverted.size();
	*/
	/*
	cout << records_with_duplicates << endl;
	cout << records_without_duplicates << endl;
	for (int i = 0; i < test.size(); i++)
	{
		cout << test[i];
	}
	*/

	
	string test_input = "2024-02-01T10:03:56 7300FD015E";

	Record* test = new Record(test_input);

	cout << test->GetDate().year << endl;
	cout << test->GetDate().month << endl;
	cout << test->GetDate().day << endl;

	cout << test->GetTime().hour << endl;
	cout << test->GetTime().minute << endl;
	cout << test->GetTime().second << endl;

	cout << test->GetBattery() << endl;
	cout << test->GetTemperature() << endl;
	cout << test->GetHumidity() << endl;
	
	int temp;
	sscanf_s("02", "%d", &temp);
	cout << temp << endl;
	return 0;
}
