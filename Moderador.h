#pragma once
#include "Membro.h"
#include <iostream>
#include <vector>

class Moderador :public Membro
{
	int kicks;
public:
	Moderador(std::string nome, std::string id, int level, int kicks);
	~Moderador();
	
	void setKicks(int kicks);
	int getKicks();
};

