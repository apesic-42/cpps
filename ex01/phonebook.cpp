
#include <iostream>
#include "Contact.class.hpp"
#include <cstring>
using namespace std;


int main()
{
    PhoneBook phonebook;

    cout << "Welcom to phon book, please make ADD or SEARCH or EXIT" << endl;
    char commande[300];
    while (true)
    {
        commande[0] = '\0';
        cin >> commande;
        if (strcmp(commande, "ADD") == 0)
        {
            char name[100]; char number[100];
            cout << "please type name :" << endl;
            cin >> name;
            cout << "please type number :" << endl;
            cin >> number;
            phonebook.add_contact(number, name);
            cout << "phone book contact added" << endl;
            cout << "name : "
                      << phonebook.contacts[phonebook.index == 0 ? 7 : phonebook.index - 1].name
                      << " number : "
                      << phonebook.contacts[phonebook.index == 0 ? 7 : phonebook.index - 1].number
                      << endl;

                cout << endl << "ADD or SEARCH or EXIT" << endl;

        }
        else if (strcmp(commande, "SEARCH") == 0)
        {
            string nm;
            cout << "search what ?:" << endl;
            cin >> nm;
            vector<string>res  = phonebook.search_contact(nm);
            if (res.empty())
                cout << "contact not found" << endl;
            else
                cout << "contact find : " << res[0] << " : " << res[1] << endl ;
            cout << endl << "ADD or SEARCH or EXIT" << endl;

        }
        else if (strcmp(commande, "EXIT") == 0)
        {
            cout << "exit" << endl;
            return 0;
        }
        else
        {
            cout << "wrong commande : " << commande <<  endl;
        }

    }

    return 0;
}
