#include<cpprest/http_client.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::client;

class Location
{
public:
	string name;
};
class weather
{
public:
	int temp, windspeed, humidity;
};
int menuform()
{
	int menu;
	cout << "-----My Weather App	\n";
	cout << "What operation do you want to perform?\n";
	cout << "1. Add Cities\n";
	cout << "2. See Added Cities\n"; 
	cout << "3. Check Weather\n"; 
	cout << "4. Delete Cities\n";
	cout << "5. Exit\n";
	cin >> menu; 
	return menu;
}

int main()
{
	Location lc; vector<string> list;
	int choice;
	string cityName;

	do
	{
		system("cls");
		choice = menuform();
		system("cls");

		switch (choice)
		{
		case 1:
		{
			int n;
			cout << "How many cities do you want to add? ";

			cin >> n;
			cin.ignore(); // To clear the newline character left by cin for (int i = 0; i < n; i++)
			{
				cout << "Enter the name of city " << i + 1 << ": ";
				getline(cin, lc.name);
				list.push_back(lc.name);
			}
			cout << "***Cities added successfully***\n"; 
			break;
		}
		case 2:
		{
			cout << "------List of Cities	\n";
			for (int i = 0; i < list.size(); i++)
			{
				cout << i + 1 << ". " << list.at(i) << endl;
			}
			cout << "\nPress Enter to continue...";
			cin.ignore();
			cin.get();
			break;
		}
		case 3:
		{
			cout << "Enter the city name for which you want to check the weather: ";
			cin.ignore();
			getline(cin, lc.name);
			http_client client(U("https: //api.openweathermap.org/data/2.5"));
			uri_builder builder(U("/weather"));
			builder.append_query(U("q"), utility::conversions::to_string_t(lc.name));
			builder.append_query(U("appid"), U("15b249c4faa994279c71a7714afeb606"));
			http_request request(methods::GET);
			request.set_request_uri(builder.to_string());

			client.request(request).then([](http_response response) {return response.extract_json();
				}).then([](web::json::value body)
					{
						cout << "The city to check the weather is: " << lc.name << endl;
						cout << "\tTemperature: " << body[U("main")][U("temp")].as_double() << " k" << endl; cout << "\tHumidity: " << body[U("main")][U("humidity")].as_double() << " %" << endl; cout << "\tWeather: " <<
							utility::conversions::to_utf8string(body[U("weather")][0][U("main")].as_string());
					}
				).wait();

				break;
		}
		case 4:
		{
			cout << "Enter the city name you want to delete: ";
			cin.ignore();
			getline(cin, cityName);
			auto it = find(list.begin(), list.end(), cityName);
			if (it != list.end()) {
				list.erase(it);
				cout << "***City deleted successfully***\n";
			}
			else {
				cout << "City not found!\n";
			}
			cout << "\nPress Enter to continue..."; 
			cin.get();
			break;
		}
		case 5:
		{
			cout << "Exiting the application.\n"; 
			return 0;
		}
		default:
		{
			cout << "Invalid choice! Please enter a number between 1 and 5.\n";
			cout << "\nPress Enter to continue...";
			cin.ignore();
			cin.get();
			break;
		}
		}
	} while (true);
	return 0;
}

