#include "Record.h"


double decode_battery(double hex)
{
	return (30.0 * hex);
}
double decode_temperature_humidity(double b2, double b1)
{
	int temp = (256 * b1) + b2;
	return (temp / 10.0);
}


Record::Record(string line)
{
	char year_in_string[4];
	int year_count = 0;
	char other_data_in_string[2];
	int data_count = 0;

	Date temp_date;
	Time temp_time;

	double temp_humidity;
	//double temp_battery;
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
				int hex;
				sscanf_s(other_data_in_string, "%x", &hex);


				switch (i)
				{
				case 21:
					this->bytes.first_byte = hex;
					this->battery = decode_battery(hex);
					break;
				case 23:
					this->bytes.second_byte = hex;
					temp_temperature = hex;
					break;
				case 25:
					this->bytes.third_byte = hex;
					this->temperature = decode_temperature_humidity(hex, temp_temperature);
					break;
				case 27:
					this->bytes.fourth_byte = hex;
					temp_humidity = hex;
					break;
				case 29:
					this->bytes.fifth_byte = hex;
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
Bytes Record::GetBytes()
{
	return this->bytes;
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
