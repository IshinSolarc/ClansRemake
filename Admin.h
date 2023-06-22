#pragma once
#include "Moderador.h"
class Admin :public Moderador
{
	int bans;
public:
	Admin(std::string nome, std::string id, int level, int kicks, int bans);
	~Admin();

	void setBans(int bans);
	int getBans();
};

