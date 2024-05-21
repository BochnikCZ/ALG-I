#include <iostream>
#include <vector>
#include "Record.h"
using namespace std;

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
				j = i; // Snížit j, abychom se vyhnuli pøeskoèení dalšího potenciálního duplikátu
			}
		}
	}
}

bool compare_dates(Record& a, Record& b) {
	if (a.GetDate().year != b.GetDate().year)
		return a.GetDate().year < b.GetDate().year;
	if (a.GetDate().month != b.GetDate().month)
		return a.GetDate().month < b.GetDate().month;
	if (a.GetDate().day != b.GetDate().day)
		return a.GetDate().day < b.GetDate().day;
	if (a.GetTime().hour != b.GetTime().hour)
		return a.GetTime().hour < b.GetTime().hour;
	if (a.GetTime().minute != b.GetTime().minute)
		return a.GetTime().minute < b.GetTime().minute;
	if (a.GetTime().second != b.GetTime().second)
		return a.GetTime().second < b.GetTime().second;

	return false;
}

vector<Record*> convert_and_put_in_order(vector<string>& vec)
{
	vector<Record*> converted;

	for (int i = 0; i < vec.size(); i++)
	{
		Record* temp_record = new Record(vec[i]);

		if (converted.empty()) {
			converted.push_back(temp_record);
		}
		else {
			int it = 0;
			for (; it < converted.size(); it++) {
				if (compare_dates(*temp_record, *converted[it])) {
					converted.insert(converted.begin() + it, temp_record);
					break;
				}
			}
			if (it == converted.size()) {
				converted.push_back(temp_record);
			}
		}
	}

	return converted;
}

void print_out_records(vector<Record*> vec, const char* filename)
{
	FILE* output1_file;
	fopen_s(&output1_file, filename, "w");
	if (output1_file != NULL) {
		for (int i = 0; i < vec.size(); i++) {
			fprintf(output1_file, "%d-", vec[i]->GetDate().year);
			if (vec[i]->GetDate().month < 10)
			{
				fprintf(output1_file, "0%d-", vec[i]->GetDate().month);
			}
			else
			{
				fprintf(output1_file, "%d-", vec[i]->GetDate().month);
			}
			if (vec[i]->GetDate().day < 10)
			{
				fprintf(output1_file, "0%dT", vec[i]->GetDate().day);
			}
			else
			{
				fprintf(output1_file, "%dT", vec[i]->GetDate().day);
			}

			if (vec[i]->GetTime().hour < 10)
			{
				fprintf(output1_file, "0%d:", vec[i]->GetTime().hour);
			}
			else
			{
				fprintf(output1_file, "%d:", vec[i]->GetTime().hour);
			}
			if (vec[i]->GetTime().minute < 10)
			{
				fprintf(output1_file, "0%d:", vec[i]->GetTime().minute);
			}
			else
			{
				fprintf(output1_file, "%d:", vec[i]->GetTime().minute);
			}
			if (vec[i]->GetTime().second < 10)
			{
				fprintf(output1_file, "0%d ", vec[i]->GetTime().second);
			}
			else
			{
				fprintf(output1_file, "%d ", vec[i]->GetTime().second);
			}

			fprintf(output1_file, "%x%x%x%x%x", vec[i]->GetBytes().first_byte,
				vec[i]->GetBytes().second_byte,
				vec[i]->GetBytes().third_byte,
				vec[i]->GetBytes().fourth_byte,
				vec[i]->GetBytes().fifth_byte);


			fprintf(output1_file, "\n");
		}


		fclose(output1_file);
	}
}

void swap(Record& x, Record& y)
{
	Record temp = x;
	x = y;
	y = temp;
}


int main()
{

	const char* input_file_filename = "input.txt";
	const char* output_file1_filename = "output1.txt";
	const char* output_file2_filename = "output2.txt";
	vector<string> input_data_unconverted;
	vector<Record*> input_data_converted;
	size_t records_with_duplicates;
	size_t records_without_duplicates;


	input_data_unconverted = load_data_from_input(input_file_filename);
	records_with_duplicates = input_data_unconverted.size();

	removeDuplicates(input_data_unconverted);

	records_without_duplicates = input_data_unconverted.size();

	input_data_converted = convert_and_put_in_order(input_data_unconverted);
	
	print_out_records(input_data_converted, output_file1_filename);
	

	int temp = input_data_converted.size() - 1;
	FILE* output2_file;
	fopen_s(&output2_file, output_file2_filename, "w");
	fprintf(output2_file, "casova razitka %d.%d. %d - %d.%d. %d, zaznamy jsou posilany kazdou hodinu\n", input_data_converted[0]->GetDate().day, input_data_converted[0]->GetDate().month, input_data_converted[0]->GetDate().year, input_data_converted[temp]->GetDate().day, input_data_converted[temp]->GetDate().month, input_data_converted[temp]->GetDate().year);
	fprintf(output2_file, "\ncelkový poèet záznamù vèetnì duplicit: %d\n", records_with_duplicates);
	fprintf(output2_file, "\ncelkový poèet záznamù bez duplicit: %d\n", records_without_duplicates);

	for (int i = 0; i < (input_data_converted.size() - 1); i++)
	{
		int min = i;
		for (int j = i + 1; j < input_data_converted.size(); j++)
		{
			if (input_data_converted[j]->GetTemperature() < input_data_converted[min]->GetTemperature()) 
			{
				min = j;
			}
		}
		swap(input_data_converted[i], input_data_converted[min]);
	}
	

	fprintf(output2_file, "\nmaximalni teplota = %.2f\n", input_data_converted[0]->GetTemperature());
	fprintf(output2_file, "\nminimalni teplota = %.2f\n", input_data_converted[temp]->GetTemperature());

	fprintf(output2_file, "\nHistogram tepoloty:\n");
	for (int i = 1; i < input_data_converted.size(); i++)
	{
		int j = i - 1;
		if (input_data_converted[i]->GetTemperature() == input_data_converted[j]->GetTemperature())
		{
			fprintf(output2_file, "| ");
		}
		else
		{
			fprintf(output2_file, "\n");
			fprintf(output2_file, "%.2f   | ", input_data_converted[i]->GetTemperature());
		}
	}



	for (int i = 0; i < (input_data_converted.size() - 1); i++)
	{
		int min = i;
		for (int j = i+1; j < input_data_converted.size(); j++)
		{
			if (input_data_converted[j]->GetHumidity() < input_data_converted[min]->GetHumidity())
			{
				min = j;
			}
		}
		swap(input_data_converted[i], input_data_converted[min]);
	}

	fprintf(output2_file, "\nmaximalni vlhkost = %.2f\n", input_data_converted[0]->GetHumidity());
	fprintf(output2_file, "\nminimalni vlhkost = %.2f\n", input_data_converted[temp]->GetHumidity());

	fprintf(output2_file, "\nHistogram vlhkosti:\n");
	fprintf(output2_file, "%.2f   | ", input_data_converted[0]->GetHumidity());
	for (int i = 1; i < input_data_converted.size(); i++)
	{
		int j = i - 1;
		if (input_data_converted[i]->GetHumidity() == input_data_converted[j]->GetHumidity())
		{
			fprintf(output2_file, "| ");
		}
		else
		{
			fprintf(output2_file, "\n");
			fprintf(output2_file, "%.2f   | ", input_data_converted[i]->GetHumidity());
		}
	}
		

	fclose(output2_file);

	return 0;
}