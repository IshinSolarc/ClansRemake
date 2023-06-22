#pragma once
#include <iostream>
#include <dpp/dpp.h>
#include <dpp/ban.h>
#include <string>
#include "Moderador.h"
#include "Membro.h"
#include "Tabela.h"


#include <boost/algorithm/string.hpp>


namespace tdc {


	std::string registrar(dpp::message_create_t event, Tabela& tabela);

	std::string addPlayer(dpp::message_create_t event, Tabela& tabela);
	
	std::string removePlayer(dpp::message_create_t event, Tabela& tabela);

	std::string mudarCargo(dpp::message_create_t event, Tabela& tabela);

	std::string getTabela(Tabela& tabela);

	std::string getTabelaLevel(Tabela& tabela);

	std::string kickPlayer(dpp::message_create_t event, Tabela& tabela, dpp::cluster& bot);
	
	std::string banPlayer(dpp::message_create_t event, Tabela& tabela, dpp::cluster& bot);

	std::string attLevel(dpp::message_create_t event, Tabela& tabela);
	
	std::string comando(dpp::message_create_t event, dpp::cluster& bot);
	
	
	

}