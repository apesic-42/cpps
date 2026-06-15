
// Data = struct minimale a serialiser/deserialiser (ex01)
#pragma once // empeche la double inclusion (equivalent du include guard)

#include <string>

// typedef struct = on cree un alias "Data" pour s_Data (habitude du C)
typedef struct	s_Data
{
	std::string	data; // un seul champ, juste pour avoir quelque chose a stocker
}				Data;
