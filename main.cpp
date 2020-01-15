#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdio.h>

using namespace std;

struct User
{
    int idUser;
    string name, password;
};

struct AddressBook
{
    int id = 0, idUser = 0;
    string name = "", surname = "", phone = "", mail = "", address = "";
};

int loadUsers (vector<User> &usersOfAddressBook);

int registration(vector <User> &usersOfAddressBook, int numberOfUsers );

int logging(vector <User> usersOfAddressBook, int numberOfUsers);

void  changePassword (vector <User> &usersOfAddressBook, int idLoggedUser, int numberOfUsers);

void editTextFileUsers (vector <User> usersOfAddressBook, int numberOfUserss);

int loadAddressBook(vector <AddressBook> &contacts, int &lastID,  int idLoggedUser);

char *strToChar(string line);

int addContact (vector <AddressBook> &contacts,int numberOfContacts, int &lastID,  int idLoggedUser);

void searchName (vector <AddressBook> contacts,int numberOfContacts);

void searchSurname (vector <AddressBook> contacts, int numberOfContacts);

void viewAllContacts (vector <AddressBook> contacts, int numberOfContacts);

int eraseContact(vector <AddressBook> &contacts, int numberOfContacts, int &lastID);

int editContact (vector <AddressBook> &contacts, int numberOfContacts);

void editTextFileContacts (vector <AddressBook> contacts, int i);

void editTextFileContacts (vector <AddressBook> contacts, int i, int contactToChange, string whatToDo);

void printContact (vector <AddressBook> contacts, int i);


int main()
{
    vector <User> usersOfAddressBook;
    int idLoggedUser=0;
    int numberOfUsers=0;

    vector <AddressBook> contacts;
    int numberOfContacts=0;
    int lastID=0;

    numberOfUsers = loadUsers(usersOfAddressBook);


    char choice;

    while(1)
    {
        if (idLoggedUser==0)
        {
            system("cls");
            cout<<"1. Rejestracja"<<endl;
            cout<<"2. Logowanie"<<endl;
            cout<<"9. Zakoncz program"<<endl;
            choice = getch();

            if (choice=='1')
            {
                numberOfUsers = registration(usersOfAddressBook, numberOfUsers);
            }
            else if (choice=='2')
            {
                idLoggedUser=logging(usersOfAddressBook, numberOfUsers);
                if (idLoggedUser!=0)
                    numberOfContacts = loadAddressBook(contacts, lastID, idLoggedUser);
            }
            else if (choice=='9')
            {
                exit(0);
            }
        }

        else
        {
            system("cls");
            char choice;


            cout<< "------KSIAZKA ADRESOWA------"<< endl<< endl;
            cout<< "1. Dodaj adresata"<< endl;
            cout<< "2. Wyszukaj po imieniu"<< endl;
            cout<< "3. Wyszukaj po nazwisku"<< endl;
            cout<< "4. Wyswietl wszystkich adresatow"<< endl;
            cout<< "5. Usun adresata"<< endl;
            cout<< "6. Edytuj adresata"<< endl;
            cout<< "7. Zmien haslo"<< endl;
            cout<< "9. Wyloguj"<< endl;
            choice = getch();

            switch (choice)
            {
            case '1':
                numberOfContacts = addContact (contacts, numberOfContacts, lastID, idLoggedUser);
                break;

            case '2':
                searchName (contacts, numberOfContacts);
                break;

            case '3':
                searchSurname (contacts, numberOfContacts);
                break;

            case '4':
                viewAllContacts (contacts, numberOfContacts);
                break;

            case '5':
                numberOfContacts = eraseContact(contacts, numberOfContacts, lastID);
                break;

            case '6':
                editContact (contacts, numberOfContacts);
                break;

            case '7':
                changePassword (usersOfAddressBook, idLoggedUser, numberOfUsers);
                break;

            case '9':
                idLoggedUser=0;
                contacts.clear();
            }
        }
    }
    return 0;
}


int loadUsers (vector<User> &usersOfAddressBook)
{
    string line;
    int numberOfUsers = 0;

    User oneUser;

    string name = "", password = "";
    int idUser;

    fstream file;
    file.open("users.txt", ios::in);

    if (file.good() == true)
    {
        while (getline(file, line))
        {
            char space[] = "|";
            char *word;
            word = strtok (strToChar(line), space);
            while( word != NULL )
            {
                char wordToInt = *word;
                oneUser.idUser = wordToInt-'0';
                word = strtok( NULL, space );
                oneUser.name=word;
                word = strtok( NULL, space );
                oneUser.password=word;
                word = strtok( NULL, space );
            }
            usersOfAddressBook.push_back(oneUser);

            numberOfUsers++;
        }
    }
    file.close();
    return numberOfUsers;
}

int registration(vector <User> &usersOfAddressBook, int numberOfUsers )
{
    User oneUser;
    string name, password;
    cout<<"Podaj nazwe uzytkownika: ";
    cin>>name;
    int i=0;
    while (i<numberOfUsers)
    {
        if (usersOfAddressBook[i].name==name)
        {
            cout<<"Taki uzytkownik istnieje, wpisz inna nazwe: "<<endl;
            cin>>name;
            i=0;
        }
        else
        {
            i++;
        }
    }
    cout<<"Podaj haslo:";
    cin>>password;

    oneUser.idUser=numberOfUsers+1;
    oneUser.name = name;
    oneUser.password = password;

    usersOfAddressBook.push_back(oneUser);

    fstream file;
    file.open("users.txt", ios::out|ios::app);
    if (file.good() == true)
    {
        file<< oneUser.idUser<<"|"<<oneUser.name<<"|"<<oneUser.password<<endl;
        file.close();

        cout << "Utworzono nowego uzytkownika";
        Sleep(1500);
    }
    else
    {
        cout<< "Nie udalo sie otworzyc pliku.";
        system("pause");
    }
    return numberOfUsers+1;
}

int logging(vector <User> usersOfAddressBook, int numberOfUsers)
{
    string name, password;
    cout<<"Wpisz login: "<<endl;
    cin>>name;
    int i=0;
    while (i<=numberOfUsers)
    {
        if (usersOfAddressBook[i].name==name)
        {
            for (int j=0; j<3; j++)
            {
                cout<<"Wpisz haslo. Pozostalo prob: "<<3-j<<endl;
                cin>>password;
                if (usersOfAddressBook[i].password==password)
                {
                    cout<<"Zalogowales sie"<<endl;
                    Sleep(1000);
                    return usersOfAddressBook[i].idUser;
                }
            }
            cout<<"Podales 3 razy bledne haslo. Przejdz do menu glownego"<<endl;
            Sleep(1500);
            return 0;
        }
        i++;
    }
    cout<<"Nie ma uzytkownika z takim loginem";
    Sleep(2000);
    return 0;
}

void  changePassword (vector <User> &usersOfAddressBook, int idLoggedUser, int numberOfUsers)
{
    system("cls");
    string password;
    cout<<"Podaj nowe haslo ";
    cin>>password;
    for (int i=0; i< numberOfUsers; i++)
    {
        if (usersOfAddressBook[i].idUser==idLoggedUser)
        {
            usersOfAddressBook[i].password=password;
            editTextFileUsers (usersOfAddressBook, numberOfUsers);
            cout<<"Twoje haslo zostalo zmienione";
            Sleep(1500);
        }
    }
}

void editTextFileUsers (vector <User> usersOfAddressBook, int numberOfUsers)
{
    fstream file;
    file.open("users.txt", ios::out| ios::trunc);
    file.clear();
    if (file.good() == true)
    {
        for (int i=0; i<numberOfUsers; i++ )
        {
            file<< usersOfAddressBook[i].idUser<<"|"<<usersOfAddressBook[i].name<<"|"<<usersOfAddressBook[i].password<<endl;
        }
    }
    else
    {
        cout<< "Nie udalo sie otworzyc pliku.";
        system("pause");
    }
    file.close();
}


int loadAddressBook (vector<AddressBook> &contacts, int &lastID, int idLoggedUser)
{
    string line;
    int numberOfContacts = 0;

    AddressBook contact;

    string name = "", surname = "", phone = "", mail = "", address = "";
    int id;

    int tempId = 0;
    int tempIdUser = 0;

    fstream file;
    file.open("Address_book.txt", ios::in);

    if (file.good() == true)
    {
        while (getline(file, line))
        {
            char space[] = "|";
            char *word;
            word = strtok (strToChar(line), space);
            while( word != NULL )
            {
                tempId = atoi (word);
                word = strtok( NULL, space );
                tempIdUser = atoi (word);
                word = strtok( NULL, space );

                if (tempIdUser == idLoggedUser)
                {
                    contact.id = tempId;
                    contact.idUser = tempIdUser;
                    contact.name=word;
                    word = strtok( NULL, space );
                    contact.surname=word;
                    word = strtok( NULL, space );
                    contact.phone= word;
                    word = strtok( NULL, space );
                    contact.mail=word;
                    word = strtok( NULL, space );
                    contact.address = word;
                    word = strtok( NULL, space );
                    contacts.push_back(contact);
                }
                else
                    break;
            }
            lastID = tempId;
        }
    }

    file.close();
    numberOfContacts = contacts.size();
    return numberOfContacts;
}

char *strToChar(string line)
{
    char *lineChar = new char[line.size() + 1];
    strcpy(lineChar, line.c_str() );
    return lineChar;
    delete [] lineChar;
}

int addContact (vector <AddressBook> &contacts, int numberOfContacts, int &lastID, int idLoggedUser)
{
    system("cls");
    AddressBook contact;
    string name = "", surname = "", phone = "", mail = "", address = "";

    cout<< "Podaj imie: ";
    cin>> name;

    cout<< "Podaj nazwisko: ";
    cin>> surname;

    cin.clear();
    cin.ignore( 1000, '\n' );
    cout<< "Podaj numer telefonu: ";
    getline (cin, phone);

    cout<< "Podaj adres email: ";
    cin>> mail;

    cin.clear();
    cin.ignore( 1000, '\n' );
    cout<< "Podaj adres: ";
    getline (cin, address);

    contact.id = lastID+1;
    contact.idUser = idLoggedUser;
    contact.name = name;
    contact.surname = surname;
    contact.address = address;
    contact.phone = phone;
    contact.mail = mail;

    contacts.push_back(contact);
    lastID++;

    fstream file;
    file.open("Address_book.txt", ios::out|ios::app);
    if (file.good() == true)
    {
        file<< contact.id<<"|"<<contact.idUser<<"|"<<contact.name<<"|"<<contact.surname<<"|"<<contact.phone<<"|"<<contact.mail<<"|"<<contact.address<<"|"<<endl;
        file.close();

        cout << "Utworzono nowy kontakt";
        Sleep(1500);
    }
    else
    {
        cout<< "Nie udalo sie otworzyc pliku.";
        system("pause");
    }

    return numberOfContacts+1;
}

void searchName (vector <AddressBook> contacts, int numberOfContacts)
{
    system("cls");
    string name;
    cout<< "Podaj imie: ";
    cin>> name;
    int i = 0;
    int numberOfExistingName = 0;
    while (i < numberOfContacts)
    {
        if (contacts[i].name == name)
        {
            printContact (contacts, i);
            numberOfExistingName++;
        }
        i++;
    }
    if (numberOfExistingName==0)
        cout<< "Podane imie nie wystepuje w ksiazce adresowej" << endl;

    cout<< "Powrot do menu glownego - wcisnij dowolny klawisz";
    getch();
}

void searchSurname (vector <AddressBook> contacts, int numberOfContacts)
{
    system("cls");
    string surname;
    cout<< "Podaj nazwisko: ";
    cin>> surname;
    int i = 0;
    int numberOfExistingSurname = 0;
    while (i < numberOfContacts)
    {
        if (contacts[i].surname == surname)
        {
            printContact (contacts, i);
            numberOfExistingSurname++;
        }
        i++;
    }
    if (numberOfExistingSurname==0)
        cout<< "Podane nazwisko nie wystepuje w ksiazce adresowej"<< endl;

    cout<< "Powrot do menu glownego - wcisnij dowolny klawisz";
    getch();
}

void viewAllContacts (vector <AddressBook> contacts, int numberOfContacts)
{
    system("cls");
    for (int i=0; i < numberOfContacts; i++)
    {
        printContact (contacts, i);
    }
    cout <<"Powrot do menu glownego - wcisnij dowolny klawisz";
    getch();
}

int eraseContact(vector <AddressBook> &contacts, int numberOfContacts, int &lastID)
{
    string whatToDo = "erase";
    system("cls");
    cout<<"Podaj id adresata, ktorego chcesz usunac: ";
    int contactIDtoErase;
    cin>>contactIDtoErase;

    int numberOfExistingContact = 0;

    for (int i=0; i< numberOfContacts; i++)
    {
        if (contactIDtoErase == contacts[i].id)
        {
            numberOfExistingContact++;
            cout<<"Czy na pewno usunac ten kontakt? (t)"<<endl;
            printContact (contacts, i);
            char sign;
            sign = getch();
            if (sign == 't')
            {
                if (lastID == contacts[i].id)
                    lastID--;

                contacts.erase(contacts.begin()+ i);
                numberOfContacts--;

                editTextFileContacts(contacts, i, contactIDtoErase, whatToDo);
                cout<<"Kontakt usunieto";
                Sleep(1500);
            }
            else
                break;
        }
    }
    if (numberOfExistingContact==0)
        cout<< "Podane ID nie wystepuje w Twojej ksiazce adresowej"<< endl;

    cout<< "Powrot do menu glownego - wcisnij dowolny klawisz";
    getch();

    return numberOfContacts;
}

int editContact (vector <AddressBook> &contacts, int numberOfContacts)
{
    string whatToDo = "edit";
    system("cls");
    cout<< "Wpisz ID adresata, ktorego dane chcesz zmienic: ";
    int contactToChange;
    cin>>contactToChange;

    int i=0;
    while (i<numberOfContacts)
    {
        if (contacts[i].id == contactToChange)
        {
            break;
        }
        i++;
        if (i==numberOfContacts)
        {
            cout<< "Podane dane (ID) nie wystepuje w Twojej ksiazce adresowej"<< endl;
            Sleep(1500);
            return i;
        }
    }
    cout<< "Edytuj: "<< endl;
    cout<< "1. Imie"<< endl;
    cout<< "2. Nazwisko"<< endl;
    cout<< "3. Numer telefonu"<< endl;
    cout<< "4. Email"<< endl;
    cout<< "5. Adres"<< endl;
    cout<< "6. Powrot do menu glownego"<< endl;

    string newData;
    char editMenuChoice;
    editMenuChoice = getch();

    switch (editMenuChoice)
    {
    case '1':
    {
        cout<<"Podaj nowe imie: ";
        cin>>newData;
        contacts[i].name = newData;
        editTextFileContacts(contacts, i, contactToChange, whatToDo);
        cout<<"Imie zostalo zmienione na: "<<newData;
        Sleep(1000);
    }
    break;

    case '2':
    {
        cout<<"Podaj nowe nazwisko: ";
        cin>>newData;
        contacts[i].surname = newData;
        editTextFileContacts(contacts, i, contactToChange, whatToDo);
        cout<<"Nazwisko zostalo zmienione na: "<<newData;
        Sleep(1000);
    }
    break;

    case '3':
    {
        cin.clear();
        cin.ignore( 1000, '\n' );
        cout<<"Podaj nowy numer telefonu: ";
        getline (cin, newData);
        contacts[i].phone = newData;
        editTextFileContacts(contacts, i, contactToChange, whatToDo);
        cout<<"Numer telefonu zostal zmieniony na: "<<newData;
        Sleep(1000);
    }
    break;

    case '4':
    {
        cout<<"Podaj nowy mail: ";
        cin>>newData;
        contacts[i].mail = newData;
        editTextFileContacts(contacts, i, contactToChange, whatToDo);
        cout<<"Adres mail zostal zmieniony na: "<<newData;
        Sleep(1000);
    }
    break;

    case '5':
    {
        cin.clear();
        cin.ignore( 1000, '\n' );
        cout<<"Podaj nowy adres: ";
        getline (cin, newData);
        contacts[i].address = newData;
        editTextFileContacts(contacts, i, contactToChange, whatToDo);
        cout<<"Adres zostal zmieniony na: "<<newData;
        Sleep(1000);
    }
    break;

    case '6':
        break;
    }
}

void editTextFileContacts (vector <AddressBook> contacts, int i, int contactToChange, string whatToDo)
{
    fstream file, fileTemp;
    file.open("Address_book.txt", ios::in);
    fileTemp.open ("Address_book_temp.txt", ios::out);

    int tempId, tempIdUser;
    string tempName, tempSurname, tempPhone, tempMail, tempAddress;

    string line;
    //file.clear();
    if (file.good() == true)
    {
        while (getline(file, line))
        {
            char space[] = "|";
            char *word;
            word = strtok (strToChar(line), space);
            while( word != NULL )
            {
                tempId = atoi (word);

                if (tempId == contactToChange && whatToDo == "erase")
                    break;

                else if (tempId==contactToChange && whatToDo == "edit")
                {
                    fileTemp<< contacts[i].id<<"|"<<contacts[i].idUser<<"|"\
                            <<contacts[i].name<<"|"<<contacts[i].surname<<"|"\
                            <<contacts[i].phone<<"|"<<contacts[i].mail<<"|"<<contacts[i].address<<"|"<<endl;
                    break;
                }
                else
                {
                    word = strtok( NULL, space );
                    tempIdUser = *word - '0';
                    word = strtok( NULL, space );
                    tempName=word;
                    word = strtok( NULL, space );
                    tempSurname=word;
                    word = strtok( NULL, space );
                    tempPhone= word;
                    word = strtok( NULL, space );
                    tempMail=word;
                    word = strtok( NULL, space );
                    tempAddress = word;
                    word = strtok( NULL, space );

                    fileTemp<< tempId<<"|"<<tempIdUser<<"|"<<tempName<<"|"\
                            <<tempSurname<<"|"<<tempPhone<<"|"<<tempMail<<"|"<<tempAddress<<"|"<<endl;
                }
            }
        }
    }
    else
    {
        cout<< "Nie udalo sie otworzyc pliku.";
        system("pause");
    }
    file.close();
    fileTemp.close();

    remove("Address_book.txt") ;
    rename("Address_book_temp.txt", "Address_book.txt");
}

void printContact (vector <AddressBook> contacts, int i)
{
    cout<< contacts[i].name<< "   "<< contacts[i].surname<< endl;
    cout<< "Nr telefonu: "<< contacts[i].phone<< endl<<"Adres email: "<< contacts[i].mail;
    cout<<endl<< "Adres: "<< contacts[i].address<< endl<<"ID: "<< contacts[i].id<< endl<< "ID User: " <<contacts[i].idUser<<endl<<endl;
}

