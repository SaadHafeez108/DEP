#include<iostream>
#include<vector>
#include<string>
using namespace std;

int menu()
{
	int n;
	cout << "\n______________________________";
	cout << "\n-----Contact Books------";
	cout << "\n1. Add New Contact.\n2.View Contact.\n3. Delete Contact.\n4. Exit.\n Choose (1-3): ";
	cin >> n;
	return n;
}

class contact
{
public:
	string name, ph_nu;
	void input()
	{
		cout << " Enter the Name: ";
		cin.ignore();
		getline(cin, name);
		cout << "Enter the Phone Number: ";
		getline(cin, ph_nu);
	}
	void disp()
	{
		cout << "Name: " << name << "\nPhone Number: " << ph_nu;
	}
};

int main()
{
	string del_name;
	vector<contact> ct;
	int choice;
	bool temp = true;
	while (temp)
	{
		choice = menu();
		switch (choice)
		{
		case 1:
		{
			system("cls");
			contact newcontact;
			newcontact.input();
			ct.push_back(newcontact);
			cout << "Contact Added Successfully.";
			break;
		}
		case 2:
		{
			system("cls");
			if (ct.empty())
			{
				cout << "No Contacts added!";

			}
			else
			{
				cout << "\t\t*****List of Contacts*****\n";
				for (int i = 0; i < ct.size(); i++)
				{
					ct[i].disp();
					cout << endl;
				}
			}
			break;
		}
		case 3:
		{
			system("cls");
			if (ct.empty())
			{
				cout << "No contact to delete";
			}
			else
			{
				cout << "Enter the name of the contact to delete: ";
				cin.ignore();
				getline(cin, del_name);
				auto it = find_if(ct.begin(), ct.end(), [&del_name](const contact& c) {
					return c.name == del_name;
					});
				if (it != ct.end())
				{
					ct.erase(it);
					cout << "Contact deleted Successfully.";
				}
				else
				{
					cout << "Contact not found.";
				}
			}
			break;
		}
		case 4:
		{
			system("cls");
			cout << "Exiting the program";
			temp = false;
			break;
		}
		default:
		{
			cout << "Wrong Choice! Select from 1-3. ";
			break;
		}
		}
	}
	return 0;
}