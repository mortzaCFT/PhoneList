#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>

using namespace std;

typedef struct list
{
	string Fullname;
	string phoneNumber;
	string info;
	struct list *next;
	struct list *prev;
}list;

bool checkIfNumberCanBeConverted(string number);
short fromStringToInt(string number);
list* createNewConttac();
void addlist(list *&head);
void goBack(list *&head);
void listlist(list *&head);
void mainMenu(list *&head);
void modifylist(list *&head);
void modifylistField(list *&head, list *iterator);
void readlistFromFile(list *&head);
void searchlist(list *&head);
void searchlistBy(list *&head, char option);
void selectlistToDelete(list *&head);
void writelistInFile(list *&head);

/*
Function used to check if a string can be converted to a number
*/

bool checkIfNumberCanBeConverted(string number)
{
	//A number can't start with 0
	if ((number.length() > 1) && (number[0] == '0'))
	{
		return false;
	}

	short iterator = 0;

	while (iterator < number.length())
	{
		if ((number[iterator] < '0') || (number[iterator] > '9'))
		{
			return false;
		}
		iterator++;
	}

	return true;
}

/*
Creating a new list
*/

list* createNewlist()
{
	list *newlist = new list;

	cout << "\n\tEnter Full name: ";
	getline(cin, newlist->Fullname);
	cout << "\n\tIntroduce the number: ";
	getline(cin, newlist->phoneNumber);
	cout << "\n\tIntroduce the info: ";
	getline(cin, newlist->info);

	return newlist;
}

/*
Function used to transform a string number into a int
*/

short fromStringToInt(string number)
{
	short iterator = 0;
	short numberInt = 0;

	while (iterator < number.length())
	{
		numberInt = numberInt * 10 + (number[iterator] - '0');
		iterator++;
	}

	return numberInt;
}



void addlist(list *&head)
{
	system("cls");
	cout << "\n\n\n\t\t\tAdd a new list\n";

	list *iterator = head;
	list *newlist = createNewlist();

	int compareTwolistBy = 2;

	while (((iterator != NULL) && (iterator->next != NULL)) 
	{
		iterator = iterator->next;
	}

	if (iterator != NULL)
	{
		compareTwolistBy = iterator->Full.compare(newlist->Fullname);
	}

	//If they have the same last name we start compare by first name
	if ((iterator != NULL) && (iterator->Fullname.compare(newlist->Fullname) == 0))
	{
		while (((iterator != NULL) && (iterator->next != NULL)) &&
			(iterator->Fullname.compare(newlist->Fullname) < 0))
		{
			iterator = iterator->next;
		}
		compareTwolistBy = iterator->Fullname.compare(newlist->Fullname);
	}

	//if the list is empty or the new list is < than the first list from the Phone List
	if ((iterator == NULL) || ((iterator == head) &&
		(compareTwolistBy > 0)))
	{
		//Adding the new list on first position of the list
		newlist->next = head;
		newlist->prev = NULL;
		if (head != NULL)
		{
			head->prev = newlist;
		}
		head = newlist;
	}
	else
	{
		//If we are at the last list and the new list is > than the last list from the Phone List
		if ((iterator->next == NULL) &&
			(compareTwolistBy < 0))
		{
			//Adding the new list on the last position of the list
			newlist->next = NULL;
			newlist->prev = iterator;
			iterator->next = newlist;
		}
		else
		{
			//Checking if the lastName and firstName are not the same with the new list
			if (compareTwolistBy != 0)
			{
				//Adding at the position iterator is at
				newlist->next = iterator;
				newlist->prev = iterator->prev;
				iterator->prev->next = newlist;
				iterator->prev = newlist;
			}
		}
	}
}

/*
Function used after an operation is done (adding a new list, modifying a list,
deleting a list,searching for a list) to go back to the main menu or to exit the Phone List
*/

void goBack(list *&head)
{
	cout << "\n\n\t1.Go back to main menu.";
	cout << "\n\t2.Exit the Phone List.";
	cout << "\n\tIntroduce the number of the option you want : ";
	char number = _getch();

	switch (number)
	{
	case '1':
		mainMenu(head);
		break;
	case '2':
		return;
		break;
	default:
		cout << "\n\n\tYou introduced a wrong number.";
		goBack(head);
		break;
	}
}

/*
Listing all the list alphabetical that are in the Phone List
by parsing the list and writing the info about every list
*/

void listlist(list *&head)
{
	system("cls");
	cout << "\n\n\n\t\t\tlist";

	list *iterator = head;
	short index = 0;

	if (iterator == NULL)
	{
		cout << "\n\n\tThe list is empty.";
	}
	else
	{
		cout << "\n\n\tThere Your List:";
		while (iterator != NULL)
		{
			cout << "\n\t" << index << ".";
			cout << iterator->Fullname << " " ;
			cout << iterator->phoneNumber << " " << iterator->info;
			iterator = iterator->next;
			index++;
		}
	}
}



void mainMenu(list *&head)
{
	system("cls");
	cout << "\n\n\n\t\t\tBlackDataPh. Main Menu";
	cout << "\n\n----------------------";
	cout << "\n\n\tChoose an option :\n";
	cout << "\n------------------------";
	cout << "\n\t1.List all the list";
	cout << "\n\t2.Add a new list";
	cout << "\n\t3.Modify a list";
	cout << "\n\t4.Delete a list";
	cout << "\n\t5.Search for a list";
	cout << "\n\t6.Exit the BlackDataPh";
	cout << "\n\n\tthe number of the option you want:";
	char option = _getch();

	switch (option)
	{
	case '1':
		listlist(head);
		break;
	case '2':
		addlist(head);
		break;
	case '3':
		modifylist(head);
		break;
	case '4':
		selectlistToDelete(head);
		break;
	case '5':
		searchlist(head);
		break;
	case '6':
		return;
		break;
	default:
		cout << "\n\n\tYou introduced a wrong number.";
		break;
	}
	goBack(head);
}


void modifylist(list *&head)
{
	system("cls");
	cout << "\n\n\n\t\t\tModify a list from the Phone List";
	if (head == NULL)
	{
		cout << "\n\n\tThe Phone List is empty.";
		return;
	}

	short iteratorInt = 0;
	short numberInt = 0;
	string number;
	list *iterator = head;

	listlist(head);
	do
	{
		cout << "\n\n\tIntroduce the number of the list that you want to modify from the Phone List: ";
		getline(cin, number);
	} while ((checkIfNumberCanBeConverted(number) == false) || (number.length() >= 5));

	numberInt = fromStringToInt(number);

	while ((iterator != NULL) && (iteratorInt < numberInt))
	{
		iterator = iterator->next;
		iteratorInt++;
	}

	if (iteratorInt == numberInt)
	{
		modifylistField(head, iterator);
	}
	else
	{
		cout << "\n\tThe list with the number " << numberInt << " doesn't exist.";
	}
}


void modifylistField(list *&head, list *iterator)
{
	cout << "\n\tWhat do you want to modify in this list?";
	cout << "\n\t1.Modify the Fullname";
	cout << "\n\t3.Modify the phone number";
	cout << "\n\t4.Modify the info";
	cout << "\n\n\tIntroduce the number of the option you want:";

	char answer = _getch();
	string newInfo;

	switch (answer)
	{
	case '1':
		cout << "\n\tIntroduce the new first name: ";
		getline(cin, newInfo);
		iterator->Fullname = newInfo;
		break;
	case '2':
		cout << "\n\tIntroduce the new phone number: ";
		getline(cin, newInfo);
		iterator->phoneNumber = newInfo;
		break;
	case '3':
		cout << "\n\tIntroduce the new info: ";
		getline(cin, newInfo);
		iterator->info = newInfo;
		break;
	default:
		cout << "\n\n\tYou introduced a wrong number.";
		break;
	}

	cout << "\n\n\tDo you want to modify anything else about this list?";
	cout << "\n\t1.Yes";
	cout << "\n\t2.No";
	cout << "\n\n\tIntroduce the number of the option you want:";
	char option = _getch();

	switch (option)
	{
	case '1':
		modifylistField(head, iterator);
		break;
	case '2':
		break;
	default:
		cout << "\n\n\tYou introduced a wrong number.";
		break;
	}
}



void readlistFromFile(list *&head)
{
	char aux[100];
	list *iterator = head;
	ifstream input("list.in");

	while (input.getline(aux, 100, '|'))
	{
		list *newlist = new list;

		newlist->Fullname = aux;


		input.getline(aux, 100, '|');
		newlist->phoneNumber = aux;

		input.getline(aux, 100);
		newlist->info = aux;

		if (head == NULL)
		{
			head = newlist;
			newlist->prev = NULL;
			newlist->next = NULL;
			iterator = head;
		}
		else 
		{
			iterator->next = newlist;
			newlist->prev = iterator;
			newlist->next = NULL;
			iterator = iterator->next;
		}
	}
	input.close();
}



void searchlist(list *&head)
{
	system("cls");
	cout << "\n\n\n\t\t\tSearch for a specific list\n";
	cout << "\n\t1.Search by Fullname";
	cout << "\n\t3.Search by phone number";
	cout << "\n\tIntroduce the number of the option you want : ";

	char number = _getch();

	switch (number)
	{
	case '1':
	case '2':
	case '3':
		searchlistBy(head, number);
		break;
	default:
		cout << "\n\n\tYou introduced a wrong number.";
		break;
	}
}

/*
Function used to search for a list(or multiple list) by parsing 
the list of list using a iterator and checking if the list contain 
the name/number the user introduced.
*/

void searchlistBy(list *&head, char option)
{
	list *iterator = head;
	short index = 0;
	string searchText;

	switch (option)
	{
	case '1':
		// Search list by Fullname
		cout << "\n\tFor search pls enter a Fullname or part of it: ";
		getline(cin, searchText);
		cout << "\n\tThe list that you are searching for are:";
		while (iterator != NULL)
		{
			if ((searchText.length() <= head->lastName.length()) &&
				(head->lastName.find(searchText) < head->lastName.length()))
			{
				cout << "\n\t" << index << ".";
				cout << iterator->Fullname << " ";
				cout << " " << iterator->phoneNumber << " " << iterator->info;
			}
			iterator = iterator->next;
		}
		break;

	case '2':
		// Search list by phone number 
		cout << "\n\tIntroduce the phone number or a part of it: ";
		getline(cin, searchText);
		cout << "\n\tThe list that you are searching for are:";
		while (iterator != NULL)
		{
			if ((searchText.length() < head->phoneNumber.length()) &&
				(head->phoneNumber.find(searchText) < head->phoneNumber.length()))
			{
				cout << "\n\t" << index << ".";
				cout << iterator->Fullname << " ";
				cout << " " << iterator->phoneNumber << " " << iterator->info;
			}
			iterator = iterator->next;
		}
		break;
	default:
		cout << "\n\n\tYou Entered a wrong number.";
		break;
	}
}



void selectlistToDelete(list *&head)
{
	system("cls");
	cout << "\n\n\n\t\t\tDelete a list from the Phone List";
	if (head == NULL)
	{
		cout << "\n\n\tThe Phone List is empty.";
		return;
	}

	list *iterator = head;
	short iteratorInt = 0;
	short numberInt = 0;
	string number;

	listlist(head);
	do
	{
		cout << "\n\n\tpls enter a number of the list that you want to delete from the Phone List: ";
		getline(cin, number);
	} while ((checkIfNumberCanBeConverted(number) == false) || (number.length() >= 5));

	numberInt = fromStringToInt(number);

	while ((iterator != NULL) && (iteratorInt < numberInt))
	{
		iterator = iterator->next;
		iteratorInt++;
	}

	if (iterator != NULL)
	{
		
		if (iteratorInt == 0)
		{
			if (iterator->next == NULL)
			{
				
				head = NULL;
			}
			else 
			{
			
				head = head->next;
				head->prev = NULL;
			}
		}
		else
		{
		
			if (iterator->next == NULL)
			{
			
				iterator->prev->next = NULL;
			}
			else
			{
				
				iterator->next->prev = iterator->prev;
				iterator->prev->next = iterator->next;
			}
		}
		delete iterator;
		cout << "\n\tThe list has been deleted.";
	}
	else
	{
		cout << "\n\n\tYou introduced a wrong number.";
	}
}



void writelistInFile(list *&head)
{
	list *iterator = head;
	ofstream output("list.in");

	while (iterator != NULL)
	{
		output << iterator->Fullname << "|" << iterator->phoneNumber<< "|";
		output << iterator->info;
		if (iterator->next != NULL)
		{
			output << "\n";
		}
		iterator = iterator->next;
	}

	output.close();
}

int main()
{
	list *head = NULL;

	readlistFromFile(head);
	mainMenu(head);
	writelistInFile(head);

	return 0;
}