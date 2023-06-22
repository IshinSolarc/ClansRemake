#pragma once
#include "basePlayer.h"
class Membro : public basePlayer
{
public:
	Membro(std::string nome, std::string id, int level, std::string cargo);
	Membro(std::string nome, std::string id, int level);
	~Membro();
};