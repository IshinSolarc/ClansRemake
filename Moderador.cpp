#include "Moderador.h"

Moderador::Moderador(std::string nome, std::string id, int level, int kicks) : Membro(nome, id, level, "Moderador")
{
	this->kicks = kicks;
}

Moderador::~Moderador()
{
}

void Moderador::setKicks(int kicks)
{
	this->kicks = kicks;
}

int Moderador::getKicks()
{
	return this->kicks;
}