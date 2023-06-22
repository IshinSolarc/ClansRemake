#pragma once

#include <iostream>

class basePlayer
{
	std::string nome;
	std::string id;
	int level;
	std::string cargo;
	
public:
	static int PlayerCount;
	
	basePlayer(std::string nome, std::string id, int level, std::string cargo);
	~basePlayer();

	std::string getNome();
	std::string getId();
	int getLevel();
	std::string getCargo();

	void setNome(std::string nome);
	void setId(std::string id);
	void setLevel(int level);
	void setCargo(std::string cargo);
	bool isAutoridade();

	bool operator < (basePlayer& player);
	bool operator > (basePlayer& player);

};


bool compararPlayers(basePlayer player1, basePlayer player2);

bool compararLevels(basePlayer player1, basePlayer player2);
	
bool compararPlayersPtr(basePlayer* player1, basePlayer* player2);

bool compararLevelsPtr(basePlayer* player1, basePlayer* player2);
