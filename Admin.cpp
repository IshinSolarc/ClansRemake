#include "Admin.h"

Admin::Admin(std::string nome, std::string id, int level, int kicks, int bans) : Moderador(nome, id, level, kicks)
{
	this->bans = bans;
	this->setCargo("Admin");
}

Admin::~Admin()
{
}

void Admin::setBans(int bans)
{
	this->bans = bans;
}

int Admin::getBans()
{
	return this->bans;
}