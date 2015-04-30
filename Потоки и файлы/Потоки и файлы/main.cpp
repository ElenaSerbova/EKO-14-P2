#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;
typedef unsigned int uint;

class Exception
{
public:
	virtual void Print() = 0;
};

class OutOfDiapazone : public Exception
{
public:
	OutOfDiapazone();
	virtual void Print()
	{
		cout<<"Index more than booksize"<<endl;
	}
};

struct Member
{
	char name[50];
	char secondname[50];
	char lastname[50];

	char phone[10];
	char email[50];
	char skype[50];

	Member* next;
	Member* prev;
};

class PhoneBook
{
	int booksize;
	Member* head;
	Member* tail;

public:
	PhoneBook();
	void AddMember();
	void AddMember(const char* name, const char* secondname, const char* lastname, const char* phone, const char* email, const char* skype);

	void PrintAll();
	void PrintMemberData(uint index);
	int GetSize() { return booksize;}

	static void ClearScreen() { system("cls");}
	void SearchByName(const char* name);
	void SearchBySecondName(const char* secondname);

	void SaveToFile()
	{
		ofstream fout("C:\\Users\\result.txt", ios_base::out | ios_base::trunc);
		if(fout.is_open() )
		{
			Member * currentMember = head;

			for(int i=0; i<booksize; i++)
			{
				fout<<"Name: "<<currentMember->name;
				fout.put('\n');
				fout<<"Second name: "<<currentMember->secondname;
				fout.put('\n');
				fout<<"Last name: "<<currentMember->lastname;
				fout.put('\n');
				fout<<"Phone: "<<currentMember->phone;
				fout.put('\n');
				fout<<"Email: "<<currentMember->email;
				fout.put('\n');
				fout<<"Skype: "<<currentMember->skype;
				fout.put('\n').put('\n');

				currentMember = currentMember->next;
			}
			fout.close();
		}
	}

};

PhoneBook :: PhoneBook()
{
	booksize = 0;
	head = tail = NULL;
}

void PhoneBook :: AddMember()
{
	char tempInfo[50];

	if(booksize = 0)
	{
		Member* newMember = new Member;
		
		cout<<"Enter name: ";
		cin.getline(tempInfo, 50);
		strcpy(newMember->name, tempInfo);
		strcpy(tempInfo, '\0');

		cout<<"Enter Second name: ";
		cin.getline(tempInfo, 50);
		strcpy(newMember->secondname, tempInfo);
		strcpy(tempInfo, '\0');

		cout<<"Enter Last name: ";
		cin.getline(tempInfo, 50);
		strcpy(newMember->lastname, tempInfo);
		strcpy(tempInfo, '\0');

		cout<<"Enter Phone: ";
		cin.getline(tempInfo, 10);
		strncpy(newMember->phone, tempInfo, 10);
		strcpy(tempInfo, '\0');

		cout<<"Enter email: ";
		cin.getline(tempInfo, 50);
		strcpy(newMember->email, tempInfo);
		strcpy(tempInfo, '\0');

		cout<<"Enter skype: ";
		cin.getline(tempInfo, 50);
		strcpy(newMember->skype, tempInfo);
		strcpy(tempInfo, '\0');

		newMember->next = head;
		newMember->prev = NULL;

		if(head != NULL)
			head->prev = newMember;
		else
			tail = newMember;

		head = newMember;
		booksize++;
	}

	else
	{
		Member* newMember = new Member;
		
		cout<<"Enter name: ";
		cin.getline(tempInfo, 50);
		strcpy(newMember->name, tempInfo);
		strcpy(tempInfo, '\0');

		cout<<"Enter Second name: ";
		cin.getline(tempInfo, 50);
		strcpy(newMember->secondname, tempInfo);
		strcpy(tempInfo, '\0');

		cout<<"Enter Last name: ";
		cin.getline(tempInfo, 50);
		strcpy(newMember->lastname, tempInfo);
		strcpy(tempInfo, '\0');

		cout<<"Enter Phone: ";
		cin.getline(tempInfo, 10);
		strncpy(newMember->phone, tempInfo, 10);
		strcpy(tempInfo, '\0');

		cout<<"Enter email: ";
		cin.getline(tempInfo, 50);
		strcpy(newMember->email, tempInfo);
		strcpy(tempInfo, '\0');

		cout<<"Enter skype: ";
		cin.getline(tempInfo, 50);
		strcpy(newMember->skype, tempInfo);
		strcpy(tempInfo, '\0');

		newMember->next = 0;
		newMember->prev = tail;

		if(tail != 0)
			tail->next = newMember;
		else
			head = newMember;

		tail = newMember;
		booksize++;
	}
}

void PhoneBook :: AddMember(const char* name, const char* secondname, const char* lastname, const char* phone, const char* email, const char* skype)
{
	Member *newMember = new Member;
	strcpy(newMember->name, name);
	strcpy(newMember->secondname, secondname);
	strcpy(newMember->lastname, lastname);
	strcpy(newMember->phone, phone);
	strcpy(newMember->email, email);
	strcpy(newMember->skype, skype);

	newMember->next = 0;
	newMember->prev = tail;

	if(tail != 0)
		tail->next = newMember;
	else
		head = newMember;

	tail = newMember;
	booksize++;

}

void PhoneBook :: PrintAll()
{
	Member* currentMember = head;
	for(int i = 0; i < booksize; i++)
	{
		cout<<"Name: "<<currentMember->name<<endl
			<<"Second Name: "<<currentMember->secondname<<endl
			<<"Last Name: "<<currentMember->lastname<<endl
			<<"Phone: "<<currentMember->phone<<endl
			<<"Email: "<<currentMember->email<<endl
			<<"Skype: "<<currentMember->skype<<endl<<endl;

		currentMember = currentMember->next;
	}

}

void PhoneBook :: PrintMemberData(uint index)
{
	//try
	//{
	//	if(index >= booksize)
	//		throw OutOfDiapazone();

		Member* currentMember = head;

		for(int i = 0; i < index; i++)
			currentMember = currentMember->next;

		cout<<"Name: "<<currentMember->name<<endl
			<<"Second Name: "<<currentMember->secondname<<endl
			<<"Last Name: "<<currentMember->lastname<<endl
			<<"Phone: "<<currentMember->phone<<endl
			<<"Email: "<<currentMember->email<<endl
			<<"Skype: "<<currentMember->skype<<endl<<endl;

	//}
	//catch(OutOfDiapazone obj)
	//{
	//	obj.Print();
	//}

}

void PhoneBook :: SearchByName(const char* name)
{
	Member* currentMember = head;
	bool find = false;

	for(int i = 0; i < booksize; i++)
	{
		if(!strcmp(currentMember->name, name))
		{
			PrintMemberData(i);
			cout<<endl;
			find = true;
		}
		currentMember = currentMember->next;
	}

	if(find == false)
		cout<<"No contacts with such Name"<<endl;
}

void PhoneBook :: SearchBySecondName(const char* secondname)
{
	Member* currentMember = head;
	bool find = false;
	for(int i = 0; i < booksize; i++)
	{
		if(!strcmp(currentMember->secondname, secondname))
		{
			PrintMemberData(i);
			cout<<endl;
			find = true;
		}
		currentMember = currentMember->next;
	}
	if(find == false)
		cout<<"No contacts with such Second Name"<<endl;
}


void main()
{
	PhoneBook newBook;

	newBook.AddMember("111", "1", "1", "1", "1", "1");
	newBook.AddMember("111", "", "2", "2", "2", "2");
	newBook.AddMember("3", "3", "3", "3", "3", "3");

	newBook.PrintAll();

	newBook.SaveToFile();
}