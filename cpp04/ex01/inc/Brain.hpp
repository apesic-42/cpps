

#ifndef BRAIN_CLASS_H
# define BRAIN_CLASS_H

# include <string>

# define BRAIN_IDEAS_NUM 100

class Brain {
private:
	std::string ideas[BRAIN_IDEAS_NUM];

public:
	Brain(void);
	Brain(const Brain &src);
	~Brain(void);
	Brain	&operator =(const Brain &src);

	const std::string	*getIdeas(void) const;
	void				setIdeas(const std::string *new_ideas);
	void				setIdea(std::string idea, int index);
};

#endif
