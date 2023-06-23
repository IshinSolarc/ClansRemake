#include "basePlayer.h"

basePlayer::basePlayer(std::string nome, std::string id, int level, std::string cargo)
{
	this->nome = nome;
	this->id = id;
	this->level = level;
	this->cargo = cargo;
}

basePlayer::~basePlayer()
{
}

std::string basePlayer::getNome()
{
	return this->nome;
}

std::string basePlayer::getId()
{
	return this->id;
}

int basePlayer::getLevel()
{
	return this->level;
}

std::string basePlayer::getCargo()
{
	return this->cargo;
}

void basePlayer::setNome(std::string nome)
{
	this->nome = nome;
}

void basePlayer::setId(std::string id)
{
	this->id = id;
}

void basePlayer::setLevel(int level)
{
	this->level = level;
}

void basePlayer::setCargo(std::string cargo)
{
	this->cargo = cargo;
}

bool basePlayer::isAutoridade()
{
	if (this->cargo == "Moderador" || this->cargo == "Administrador")
	{
		return true;
	}
	
	return false;
}

bool basePlayer::operator<(basePlayer& player)
{
	if (this->cargo == "Membro" && player.getCargo() != "Membro")
	{
		return true;
	}
	else if (this->cargo == "Moderador" && player.getCargo() == "Admin")
	{
		return true;
	}
	else if (this->cargo == "Admin" && player.getCargo() != "Admin")
	{
		return false;
	}
	else if (this->cargo == player.getCargo())
	{
		if (this->nome < player.getNome())
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}

bool basePlayer::operator>(basePlayer& player)
{
	return !(*this < player);
}

bool compararPlayers(basePlayer player1, basePlayer player2)
{
	return player1 > player2;
}

bool compararLevels(basePlayer player1, basePlayer player2)
{
	return player1.getLevel() > player2.getLevel();
}

bool compararPlayersPtr(basePlayer* player1, basePlayer* player2)
{
	return *player1 > *player2;
}

bool compararLevelsPtr(basePlayer* player1, basePlayer* player2)
{
	return player1->getLevel() > player2->getLevel();
}