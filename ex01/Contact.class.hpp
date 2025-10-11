


# ifndef CONTACT_CLASS_HPP
# define CONTACT_CLASS_HPP
#include <vector>
#include <string>
using namespace std;

class Contact {

    public :
    string number;
    string name;

    Contact();
    ~Contact();
    Contact( string number_p,  string name_p);

};


class PhoneBook {
    public :
    vector<Contact> contacts;
    int count;
    int index;

    PhoneBook(void);
    ~PhoneBook(void);

    void add_contact( string number,  string name);
    vector<string> search_contact( string name);
};
# endif
