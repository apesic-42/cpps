
#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP
# include <iostream>

class ClapTrap
{
	private:
		std::string	_name;
		int			_hp;
		int			_nrj_pts;
		int			_dmg;
	public:
		ClapTrap(void);
		ClapTrap(std::string const &name);
		ClapTrap(ClapTrap const &copy);
		~ClapTrap(void);

		void	attack(std::string const &target);
		void	takeDamage(unsigned int amount);
		void	beRepaired(unsigned int amount);

		ClapTrap	&operator=(ClapTrap const &copy);

		std::string const	&get_name(void) const;
		int const			&get_hp(void) const;
		int const			&get_nrj_pts(void) const;
		int const			&get_dmg(void) const;
		void				set_name(std::string const &name);
		void				set_hp(int const &value);
		void				set_nrj_pts(int const &value);
		void				set_dmg(int const &value);
};

#endif
