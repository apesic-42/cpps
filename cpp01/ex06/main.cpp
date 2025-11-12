#include "Harl.hpp"

int main(int c, char ** argv)
{
    Harl harl;



    harl.complain("DEBUG");
    harl.complain("INFO");
    harl.complain("WARNING");
    harl.complain("ERROR");
    harl.complain("RANDOM");

    return 0;
}
