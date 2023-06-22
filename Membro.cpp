
#include "Membro.h"

Membro::Membro(std::string nome, std::string id, int level) : basePlayer(nome, id, level, "Membro")
{
}

Membro::~Membro()
{
}

Membro::Membro(std::string nome, std::string id, int level, std::string cargo) : basePlayer(nome, id, level, cargo)
{
}

