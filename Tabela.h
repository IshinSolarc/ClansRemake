#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <dpp/dpp.h>
#include "Admin.h"


#include <boost/algorithm/string.hpp>
#include <boost/sort/pdqsort/pdqsort.hpp>


class Tabela {
	
	std::map<std::string, basePlayer*> tabela_id;
	std::map<std::string, basePlayer*> tabela_nome;
	
	std::string player_base_name;
	std::ifstream * tabela_arquivo;
	
	std::vector <basePlayer*> getTabela();
	void save();

public:
	Tabela();
	~Tabela();
	bool busca(std::string id);
	basePlayer getPlayerById(std::string id);
	basePlayer getPlayerByNome(std::string nome);
	basePlayer* getPlayerByNomePtr(std::string nome);
	basePlayer* getPlayerByIdPtr(std::string id);

	std::string getCargoByID(std::string id);
	std::string add_player(basePlayer player);
	std::string remove_player(std::string id);
	std::string mudarCargo(std::string id, std::string cargo);
	bool isAutoridade(std::string id);
	std::string getStrTabelaLevel();
	std::string getStrTabela();
	std::string attLevel(std::string id, int level);
};

