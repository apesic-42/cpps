
#include "ClapTrap.hpp"

void	alice_rundown(void)
{
	ClapTrap alice("Alice");

	alice.attack("Bob");
	alice.attack("Charlie");
	alice.attack("David");
	alice.attack("Eve");
	alice.attack("Frank");
	alice.attack("Grace");
	alice.attack("Hank");
	alice.attack("Ivy");
	alice.attack("John");
	alice.attack("Kate");
	alice.attack("Leo");
	alice.attack("Mia");

}

void	bob_rundown(void)
{
	ClapTrap	bob("Bob");

	while (bob.get_hp())
	{
		bob.takeDamage(2);
		bob.beRepaired(2);
	}
	bob.takeDamage(1);
}

int	main(void)
{
	std::cout << std::endl << std::endl << "Performing Alice's rundown..." << std::endl << std::endl;
	alice_rundown();
	std::cout << std::endl << std::endl << "Performing Bob's rundown..." << std::endl << std::endl;
	bob_rundown();
}
