#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <cstdio>

int numOfContacts;

using namespace std;

struct Contact
{
    int id;
    string name, lastName, phoneNum, email, homeAdress;
};

struct User
{
    int id;
    string name,password;
};
/*======= @TODO ======*//*
DODAC EKRAN LOGOWANIA



*/

void addNewContact(vector<Contact> &contacts);
void loadFile(vector<Contact> &contacts);
void printAllContacts(vector<Contact> contacts);
void searchByName(vector<Contact> contacts);
void application();
int searchMenu();
void searchByLastName(vector<Contact> contacts, string lastNameToFind);
void searchByName(vector<Contact> contacts, string nameToFind);
void removeContact(vector<Contact> &contacts, int idToRemove);
void updateFile(vector<Contact> &contacts);
void modifyContact(vector<Contact> &contacts, int idToModify);
int loginMenuAndApp(vector<User>&users);
void registerNewUser(vector<User>&users);
int loginExistingUser(vector <User>users);
void changePassword(vector<User>&users, int loggedUserId);

int main()
{  int loggedId=0;
    vector<User> users;
    loggedId=loginMenuAndApp(users);
        fstream file;
    Contact contact;
    vector<Contact> contacts;
    loadFile(contacts);
    string nameToFind, lastNameToFind;
        while (loggedId!=0)
        {
            system("cls");
            cout << " ________________________________" << endl;
            cout << "|" << "    >>> KSIAZKA ADRESOWA <<<"
                 << "    |" << endl;
            cout << "|" << " 1. Dodaj nowa osobe."
                 << "           |" << endl;
            cout << "| 2. Wyszukaj po imieniu."
                 << "        |" << endl;
            cout << "| 3. Wyszukaj po nazwisku."
                 << "       |" << endl;
            cout << "| 4. Wyswietl wszystkie kontakty."
                 << "|"
                 << endl;
            cout << "| 5. Usun adresata.              |" << endl;
            cout << "| 6. Edytuj adresata.            |" << endl;
            cout << "| 7. Zmien haslo.                |" <<endl;
            cout << "| 8. Wyloguj sie.                |" <<endl;
            cout << "| 9. Zamknij program."
                 << "            |" << endl;
            cout << "|________________________________|" << endl;
            char option;
            cin >> option;
            cin.sync();

            if (option == '1')
            {
                addNewContact(contacts);

                Sleep(1000);
                system("cls");
                cout << "Kontakt dodany.";
                Sleep(2000);
            }

            if (option == '2')
            {
                system("cls");
                cout << "Wpisz szukane imie: ";
                cin >> nameToFind;
                cout << endl;
                searchByName(contacts, nameToFind);
                searchMenu();
            }

            if (option == '3')
            {
                system("cls");
                cout << "Wpisz szukane nazwisko: ";
                cin >> lastNameToFind;
                cout << endl;
                searchByLastName(contacts, lastNameToFind);
                searchMenu();
            }

            if (option == '4')
            {
                system("cls");
                printAllContacts(contacts);
                cout << "Powrot do poprzedniego menu - wcisnij jakikolwiek klawisz" <<endl;

                system("pause");
            }

            if (option == '5')
            {
                system("cls");
                int idToRemove;
                int i=0;
                cout << "Podaj ID do usuniecia: ";
                cin >> idToRemove;
                while(contacts[i].id != idToRemove) i++;

                cout << "Id:                     " << contacts[i].id << endl;
                cout << "Imie:                   " << contacts[i].name << endl;
                cout << "Nazwisko:               " << contacts[i].lastName << endl;
                cout << "Numer telefonu:         " << contacts[i].phoneNum << endl;
                cout << "Email:                  " << contacts[i].email << endl;
                cout << "Adres:                  " << contacts[i].homeAdress << endl << endl;
                cout << "Czy usunac kontakt? Y/N" << endl;
                char option;
                i=0;
                cin >> option;
                if(option=='y' || option=='Y') removeContact(contacts, idToRemove);

                cout << "Kontakt usuniety" << endl;
                Sleep(1000);
                system("cls");
                printAllContacts(contacts);
                cout << "Powrot do poprzedniego menu - wcisnij jakikolwiek klawisz"<<endl;

                system("pause");
            }

            if (option == '6')
            {
                system("cls");
                int idToModify;
                cout << "Podaj ID do edycji: ";
                cin >> idToModify;
                modifyContact(contacts, idToModify);
                Sleep(1000);
                system("cls");
                printAllContacts(contacts);
                cout << "Powrot do poprzedniego menu - wcisnij jakikolwiek klawisz"<<endl;

                system("pause");
            }

            if(option == '7')
            {
                changePassword(users,loggedId);
            }
            if(option=='8')
            {
                loggedId=0;
            }

            if (option == '9')
            {
                exit(0);
            }
        }
    file.close();

}
char getCharFromUser()
{
    char userInput;
    cin >> userInput;
    cin.ignore();
    return userInput;
}

string getStringFromUser()
{

    string userInput;
    cin >> userInput;
    return userInput;
}

int loginMenuAndApp(vector<User>&users)
{


    int loggedUserId=0;

    char option;

    while(1)
    {
        if(loggedUserId == 0)
        {
            system("cls");
            cout << "1. Rejestracja"<<endl;
            cout << "2. Logowanie"<<endl;
            cout << "9. Zakoncz program"<<endl;
            option = getCharFromUser();
            if(option=='1')
            {
                registerNewUser(users);

            }
            else if(option =='2')
            {
                loggedUserId= loginExistingUser(users);
                return loggedUserId;

            }
            else if(option=='9')
            {
                exit(0);
            }
        }

    }
    return loggedUserId;
}
void registerNewUser(vector<User>&users)
{
    User user;
    string name,password;
    cout << "Podaj nazwe uzytkownika: ";
    name=getStringFromUser();
    int i =0;
    int j=0;
    while(i<users.size())
    {
        if(users[i].name == name)
        {
            cout << "Taki uzytkownik juz istnieje. Podaj inna nazwe uzytkownika: ";
            name=getStringFromUser();
            i=0;
        }
        else
        {
            i++;
        }
    }
    cout << "Podaj haslo: ";
    password=getStringFromUser();
    cout << "Wpisz ponownie haslo: ";
    string temp =getStringFromUser();
    while(password != temp)
    {
        cout << "Hasla do siebie nie pasuja. Sprobuj ponownie. ";
        cout << "Podaj haslo: ";
        password=getStringFromUser();
        cout << "Wpisz ponownie haslo: ";
        string temp =getStringFromUser();
    }
    cin.sync();
    if(password == temp)
    {
        user.id = users.size()+1;
        user.name = name;
        user.password = password;
        users.push_back(user);
        cout << "Konto zalozone" << endl;


        Sleep(1000);
    }

}
int loginExistingUser(vector<User>users)
{
    string name,password;
    cout << "Podaj nazwe: ";
    name=getStringFromUser();
    int i =0;
    while(i<users.size())
    {
        if(users[i].name == name)
        {
            for(int incorrectPasswordCount =0; incorrectPasswordCount<3; incorrectPasswordCount++)
            {
                cout << "Podaj haslo. Pozostalo prob "<< 3-incorrectPasswordCount << endl ;
                password=getStringFromUser();
                if(users[i].password == password)
                {
                    cout << "Zalogowales sie." << endl;
                    Sleep(1000);
                    return users[i].id;
                }
            }
            cout << "Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba"<< endl;
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout << "Nie ma takiego uzytkownika." <<endl;;
    Sleep(1500);
    return users[i].id;
}

void changePassword(vector<User> &users,int loggedUserId)
{

    string password;
    cout << "Podaj nowe haslo: ";
    password=getStringFromUser();
    for(int i=0; i<users.size(); i++)
    {
        if(users[i].id == loggedUserId)
        {
            users[i].password = password;
            cout << "Haslo zostalo zmienione." <<endl;
            Sleep(1500);
        }
    }
}



void modifyContact(vector<Contact> &contacts, int idToModify)
{
    int i = 0;
    string temp = "";
    while (contacts[i].id != idToModify) i++;
    cout << "Id:                     " << contacts[i].id << endl;
    cout << "Imie:                   " << contacts[i].name << endl;
    cout << "Nazwisko:               " << contacts[i].lastName << endl;
    cout << "Numer telefonu:         " << contacts[i].phoneNum << endl;
    cout << "Email:                  " << contacts[i].email << endl;
    cout << "Adres:                  " << contacts[i].homeAdress << endl << endl;

    char option;
    cout << "Wybierz dane do edycji." << endl;
    cout << "1. Imie" << endl;
    cout << "2. Nazwisko." << endl;
    cout << "3. Numer telefonu." << endl;
    cout << "4. Adres e-mail." << endl;
    cout << "5. Adres domowy." << endl;
    cout << "9. Powrot do menu glownego"<<endl;
    cin >> option;

    switch (option)
    {
    case '1':
        cout << "Podaj nowe imie: ";
        cin >> temp;
        contacts[i].name = temp;
        break;
    case '2':
        cout << "Podaj nowe nazwisko: ";
        cin >> temp;
        contacts[i].lastName = temp;
        break;
    case '3':
        cout << "Podaj nowy numer telefonu: ";
        cin >> temp;
        contacts[i].phoneNum = temp;
        break;
    case '4':
        cout << "Podaj nowy email: ";
        cin >> temp;
        contacts[i].email = temp;
        break;
    case '5':
        cout << "Podaj nowy adres: ";
        cin >> temp;
        contacts[i].homeAdress = temp;
        break;
    case '0':
        Sleep(500);
        break;
    }

    cout << "Kontakt zmieniony" << endl;
    system("cls");
    cout << "Id:                     " << contacts[i].id << endl;
    cout << "Imie:                   " << contacts[i].name << endl;
    cout << "Nazwisko:               " << contacts[i].lastName << endl;
    cout << "Numer telefonu:         " << contacts[i].phoneNum << endl;
    cout << "Email:                  " << contacts[i].email << endl;
    cout << "Adres:                  " << contacts[i].homeAdress << endl << endl;
    system("pause");

    updateFile(contacts);
}

void removeContact(vector<Contact> &contacts, int idToRemove)
{
    int i = 0;
    while (contacts[i].id != idToRemove)
    {
        i++;
    }

    contacts.erase(contacts.begin() + i);
    updateFile(contacts);
}

void updateFile(vector<Contact> &contacts)
{
    fstream file;
    file.open("kontakty.txt", ios::out);
    if (file.good() == true)
    {
        for (const auto &contact : contacts)
        {
            file << contact.id << "|"
                 << contact.name << "|"
                 << contact.lastName << "|"
                 << contact.phoneNum << "|"
                 << contact.email << "|"
                 << contact.homeAdress << "|" << endl;
        }
    }
    else
    {
        cout << "Nie mozna uzyskac dostepu do pliku.";
    }
    file.close();
}

int searchMenu()
{
    char option;

    cout << "0. Powrot do poprzedniego menu" << endl;
    cin >> option;
    if (option == '0')
    {
        Sleep(500);
        return 0;
    }
    else
    {
        cout << "Nieprawidlowy wybor.";
        Sleep(2000);
        searchMenu();
    }
}

void searchByLastName(vector<Contact> contacts, string lastNameToFind)
{
    for (size_t i = 0; i < contacts.size(); i++)
    {
        if (contacts[i].lastName == lastNameToFind)
        {
            cout << "Id:                     " << contacts[i].id << endl;
            cout << "Imie:                   " << contacts[i].name << endl;
            cout << "Nazwisko:               " << contacts[i].lastName << endl;
            cout << "Numer telefonu:         " << contacts[i].phoneNum << endl;
            cout << "Email:                  " << contacts[i].email << endl;
            cout << "Adres:                  " << contacts[i].homeAdress << endl
                 << endl;
        }
    }
}

void searchByName(vector<Contact> contacts, string nameToFind)
{
    for (size_t i = 0; i < contacts.size(); i++)
    {
        if (contacts[i].name == nameToFind)
        {
            cout << "Id:                     " << contacts[i].id << endl;
            cout << "Imie:                   " << contacts[i].name << endl;
            cout << "Nazwisko:               " << contacts[i].lastName << endl;
            cout << "Numer telefonu:         " << contacts[i].phoneNum << endl;
            cout << "Email:                  " << contacts[i].email << endl;
            cout << "Adres:                  " << contacts[i].homeAdress << endl
                 << endl;
        }
    }
}
/*
void application()
{
    fstream file;
    Contact contact;
    vector<Contact> contacts;
    vector<User> users;
    loadFile(contacts);
    string nameToFind, lastNameToFind;
    int loggedId;

    while(1)
    {

        while (loggedIn==true)
        {
            system("cls");
            cout << " ________________________________" << endl;
            cout << "|" << "    >>> KSIAZKA ADRESOWA <<<"
                 << "    |" << endl;
            cout << "|" << " 1. Dodaj nowa osobe."
                 << "           |" << endl;
            cout << "| 2. Wyszukaj po imieniu."
                 << "        |" << endl;
            cout << "| 3. Wyszukaj po nazwisku."
                 << "       |" << endl;
            cout << "| 4. Wyswietl wszystkie kontakty."
                 << "|"
                 << endl;
            cout << "| 5. Usun adresata.              |" << endl;
            cout << "| 6. Edytuj adresata.            |" << endl;
            cout << "| 7. Zmien haslo.                |" <<endl;
            cout << "| 8. Wyloguj sie.                |" <<endl;
            cout << "| 9. Zamknij program."
                 << "            |" << endl;
            cout << "|________________________________|" << endl;
            char option;
            cin >> option;
            cin.sync();

            if (option == '1')
            {
                addNewContact(contacts);

                Sleep(1000);
                system("cls");
                cout << "Kontakt dodany.";
                Sleep(2000);
                application();
            }

            if (option == '2')
            {
                system("cls");
                cout << "Wpisz szukane imie: ";
                cin >> nameToFind;
                cout << endl;
                searchByName(contacts, nameToFind);
                searchMenu();
            }

            if (option == '3')
            {
                system("cls");
                cout << "Wpisz szukane nazwisko: ";
                cin >> lastNameToFind;
                cout << endl;
                searchByLastName(contacts, lastNameToFind);
                searchMenu();
            }

            if (option == '4')
            {
                system("cls");
                printAllContacts(contacts);
                cout << "Powrot do poprzedniego menu - wcisnij jakikolwiek klawisz" <<endl;

                system("pause");
            }

            if (option == '5')
            {
                system("cls");
                int idToRemove;
                int i=0;
                cout << "Podaj ID do usuniecia: ";
                cin >> idToRemove;
                while(contacts[i].id != idToRemove) i++;
                cout << "Id:                     " << contacts[i].id << endl;
                cout << "Imie:                   " << contacts[i].name << endl;
                cout << "Nazwisko:               " << contacts[i].lastName << endl;
                cout << "Numer telefonu:         " << contacts[i].phoneNum << endl;
                cout << "Email:                  " << contacts[i].email << endl;
                cout << "Adres:                  " << contacts[i].homeAdress << endl << endl;
                cout << "Czy usunac kontakt? Y/N" << endl;
                char option;
                i=0;
                cin >> option;
                if(tolower(option)) removeContact(contacts, idToRemove);

                cout << "Kontakt usuniety" << endl;
                Sleep(1000);
                system("cls");
                printAllContacts(contacts);
                cout << "Powrot do poprzedniego menu - wcisnij jakikolwiek klawisz"<<endl;

                system("pause");
            }

            if (option == '6')
            {
                system("cls");
                int idToModify;
                cout << "Podaj ID do edycji: ";
                cin >> idToModify;
                modifyContact(contacts, idToModify);
                Sleep(1000);
                system("cls");
                printAllContacts(contacts);
                cout << "Powrot do poprzedniego menu - wcisnij jakikolwiek klawisz"<<endl;

                system("pause");
            }

            if(option == '7')
            {
                changePassword(users,loggedId);
            }
            if(option=='8')
            {
                loggedId=0;
                loggedIn=false;
            }

            if (option == '9')
            {
                exit(0);
            }
        }
    }
    file.close();
}
*/
void addNewContact(vector<Contact> &contacts)
{
    cin.sync();

    fstream file;
    string name, lastName, phoneNum, email, homeAdress;
    string line;
    string option = "";
    Contact contact;
    int position = 0;
    file.open("kontakty.txt", ios::out | ios::app);
    if (file.good() == true)
    {
        contact.id = contacts.back().id + 1;
        file << contact.id << "|";
        cout << "Podaj imie: ";
        getline(cin, name);
        contact.name = name;
        file << name << "|";
        cout << "Podaj nazwisko: ";
        getline(cin, lastName);
        contact.lastName = lastName;
        file << lastName << "|";
        cout << "Podaj numer telefonu: ";
        getline(cin, phoneNum);
        contact.phoneNum = phoneNum;
        file << phoneNum << "|";
        cout << "Podaj adres email: ";
        getline(cin, email);
        contact.email = email;
        file << email << "|";
        cout << "Podaj adres domowy: ";
        getline(cin, homeAdress);
        contact.homeAdress = homeAdress;
        file << homeAdress << "|" << endl;
        file.close();
        position++;
        contacts.push_back(contact);
        Sleep(1000);
        system("cls");
        cout << "Kontakt dodany.";
        Sleep(2000);
        /*  SPRAWDZANIE CZY KONTAKT ISTNIEJE I EWENTUALNA AKTUALIZACJA - TODO
        */
    }
}

void loadFile(vector<Contact> &contacts)
{
    fstream file;
    file.open("kontakty.txt", ios::in);
    Contact contact;
    string line = "";
    string temp;
    int numberOfLine = 1;
    char separator = '|';
    int repsOfSeparator = 0;
    if (file.good())
    {
        while (getline(file, line))
        {
            for (size_t i = 0; i < line.length(); i++)
            {
                if (line[i] != separator)
                {
                    while (repsOfSeparator == 0 && isdigit(line[i]) && line[i] != separator)
                    {
                        /* ZCZYTAJ ID*/
                        temp += line[i];

                        i++;
                        if (line[i] == separator)
                        {
                            int id = stoi(temp);
                            contact.id = id;
                            repsOfSeparator++;
                            i++;
                        }
                    }

                    temp = "";
                    while (repsOfSeparator == 1 && line[i] != separator)
                    {
                        /* ZCZYTAJ IMIE*/
                        temp += line[i];

                        i++;
                        if (line[i] == separator)
                        {
                            contact.name = temp;
                            repsOfSeparator++;
                            i++;
                        }
                    }
                    temp = "";
                    while (repsOfSeparator == 2 && line[i] != separator)
                    {
                        /* ZCZYTAJ NAZWISKO*/
                        temp += line[i];

                        i++;
                        if (line[i] == separator)
                        {
                            contact.lastName = temp;
                            repsOfSeparator++;
                            i++;
                        }
                    }
                    temp = "";
                    while (repsOfSeparator == 3 && line[i] != separator)
                    {
                        /* ZCZYTAJ NR TELEFONU*/
                        temp += line[i];

                        i++;
                        if (line[i] == separator)
                        {
                            contact.phoneNum = temp;
                            repsOfSeparator++;
                            i++;
                        }
                    }
                    temp = "";
                    while (repsOfSeparator == 4 && line[i] != separator)
                    {
                        /* ZCZYTAJ EMAIL*/
                        temp += line[i];

                        i++;
                        if (line[i] == separator)
                        {
                            contact.email = temp;
                            repsOfSeparator++;
                            i++;
                        }
                    }
                    temp = "";
                    while (repsOfSeparator == 5 && line[i] != separator)
                    {
                        /* ZCZYTAJ ADRES*/
                        temp += line[i];

                        i++;
                        if (line[i] == separator)
                        {
                            contact.homeAdress = temp;
                            repsOfSeparator++;
                            i++;
                        }
                    }
                    temp = "";
                    contacts.push_back(contact);
                }
            }
            numberOfLine++;
            repsOfSeparator = 0;
        }
    }

    file.close();

}

void printAllContacts(vector<Contact> contacts)
{
    int numOfContacts = contacts.size();
    for (int i = 0; i < numOfContacts; i++)
    {
        cout << "Id:                     " << contacts[i].id << endl;
        cout << "Imie:                   " << contacts[i].name << endl;
        cout << "Nazwisko:               " << contacts[i].lastName << endl;
        cout << "Numer telefonu:         " << contacts[i].phoneNum << endl;
        cout << "Email:                  " << contacts[i].email << endl;
        cout << "Adres:                  " << contacts[i].homeAdress << endl << endl;
    }
}

