
#include <iostream>
#include "Contact.class.hpp"
#include <cstring>
#include <string>
#include <vector>
using namespace std;

// contact
Contact::Contact( string number_p,  string name_p) : number(number_p), name(name_p) {
    cout << "number : " << this->number << endl << "name :" << this->name << endl;
    return;
}

Contact::Contact(void){
    // this->number = NULL;
    // this->name = NULL;
    return;}
Contact::~Contact(void){return;}




// phonebook

PhoneBook::PhoneBook(void) : count(0), index(0) {
    // cout << "phone book contruycteur call" << endl;
    return;}


PhoneBook::~PhoneBook(void){
    // cout << "phone book dectructeur call" << endl;
    return;}


void PhoneBook::add_contact( string number,  string name)
{
    // (void)number;
    // (void)name;
    if (this->contacts.size() < 8)
        this->contacts.push_back(Contact(number, name));
    else
        this->contacts[count] = Contact(number, name); // écrase l'ancien

    count = (count + 1) % 8;
    index = count;

    // if (count > 7)
    // {
    //     count=0;
    // }
    // this->contacts.push_back(Contact(number, name));
    // count++; index++;

    // cout << "phone book add contact call" << endl;
    // cout << "index : " << this->index << "    count : " << this->count << endl;

    return;
}

vector<string> PhoneBook::search_contact( string name)
{

    for(int i = 0; i <= 7; i++ )
    {
        if (contacts[i].name == name)
        {
            vector<string> ret;
            ret.push_back(contacts[i].name);
            ret.push_back(contacts[i].number);
            return ret;
        }
    }
    return vector<string>();
}
