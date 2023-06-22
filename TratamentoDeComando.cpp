#include "TratamentoDeComando.h"

std::string tdc::registrar(dpp::message_create_t event, Tabela& tabela) {
	
	if (tabela.busca(std::to_string(event.msg.author.id))){
		throw std::invalid_argument("Você já está registrado!");
	}

	//mensagem deve incluir o nome do jogador e o level
	//entrada esperada: !registarar [nome] [level]
	//exemplo: !registrarar Alvaroz 10

	std::vector <std::string> args;

	boost::split(args, event.msg.content, boost::is_any_of(" "));

	if (args.size() != 3) {
		throw std::invalid_argument("Numero de argumentos invalido");
	}
	
	std::string nome = args[1];
	int level;
	try {
		level = std::stoi(args[2]);
	}
	catch (std::invalid_argument& e) {
		throw std::invalid_argument("Level invalido");
	}
	
	std::string id = std::to_string(event.msg.author.id);
	std::string cargo = "Membro";
	basePlayer player(nome, id, level, cargo);

	
	return tabela.add_player(player);
}

std::string tdc::addPlayer(dpp::message_create_t event, Tabela& tabela) {
	std::string id_autor = std::to_string(event.msg.author.id);
	basePlayer autor = tabela.getPlayerById(id_autor);
	if (autor.getCargo() == "Membro" || autor.getCargo() == "") {
		throw std::invalid_argument("Voce nao tem permissao para usar esse comando!");
	}
	//mensagem deve incluir o nome do jogador, level e id

	std::vector <std::string> args;
	boost::split(args, event.msg.content, boost::is_any_of(" "));

	if (args.size() != 4) {
		throw std::invalid_argument("Comando invalido! Use !addPlayer [nome] [level] [id]");
	}
	
	std::string nome = args[1];
	int level;
	try {
		level = std::stoi(args[2]);
	}
	catch (std::invalid_argument& e) {
		throw std::invalid_argument("Level invalido!");
	}
	std::string id = args[3];
	std::string cargo = "Membro";
	
	basePlayer player(nome, id, level, cargo);
	return tabela.add_player(player);
}

std::string tdc::removePlayer(dpp::message_create_t event, Tabela& tabela) {
	std::string id_autor = std::to_string(event.msg.author.id);
	basePlayer autor = tabela.getPlayerById(id_autor);
	if (autor.getCargo() == "Membro" || autor.getCargo() == "") {
		throw std::invalid_argument("Voce nao tem permissao para usar esse comando");
	}

	//mensagem deve incluir o id do jogador
	std::vector <std::string> args;
	boost::split(args, event.msg.content, boost::is_any_of(" "));

	if (args.size() != 2) {
		throw std::invalid_argument("Comando invalido! Use !removePlayer [Nome]");
	}
	
	std::string id = args[1];
	return tabela.remove_player(id);
}

std::string tdc::getTabela(Tabela& tabela) {
	return tabela.getStrTabela();
}

std::string tdc::getTabelaLevel(Tabela& tabela) {
	return tabela.getStrTabelaLevel();
}

std::string tdc::mudarCargo(dpp::message_create_t event, Tabela& tabela) {
	std::string id_autor = std::to_string(event.msg.author.id);
	basePlayer autor = tabela.getPlayerById(id_autor);
	
	if (autor.getCargo() != "Admin") {
		throw std::invalid_argument("Voce nao tem permissao para usar esse comando");
	}	

	//mensagem deve incluir o id do jogador e o cargo
	std::vector <std::string> args;
	boost::split(args, event.msg.content, boost::is_any_of(" "));

	if (args.size() != 3) {
		throw std::invalid_argument("Comando invalido! Use !mudarCargo [Nome] [cargo]");
	}

	basePlayer player = tabela.getPlayerByNome(args[1]);
	std::string cargo = args[2];

	if (cargo == "Admin") {
		throw std::invalid_argument("Voce nao pode dar cargo de Admin");
	}

	if (cargo != "Membro" || cargo != "Moderador") {
		throw std::invalid_argument("Cargo invalido! Use Membro ou Moderador");
	}
	
	return tabela.mudarCargo(player.getId(), cargo);
}

std::string tdc::kickPlayer(dpp::message_create_t event, Tabela& tabela, dpp::cluster& bot) {
	const std::string id_autor = std::to_string(event.msg.author.id);
	basePlayer autor = tabela.getPlayerById(id_autor);
	if (autor.getCargo() != "Admin" && autor.getCargo() != "Moderador") {
		throw std::invalid_argument("Voce nao tem permissao para usar esse comando");
	}


	std::vector <std::string> args;
	boost::split(args, event.msg.content, boost::is_any_of(" "));
	std::cout << args.size() << std::endl;

	if (args.size() != 2) {
		throw std::invalid_argument("Comando invalido! Use !kickPlayer [Nome]");
	}
	
	basePlayer player = tabela.getPlayerByNome(args[1]);
	if (player.getNome() == "") {
		throw std::invalid_argument("Jogador nao encontrado");
	}
	
	if (player.getCargo() == "Admin" || player.getCargo() == "Moderador") {
		throw std::invalid_argument("Voce nao pode kickar um moderador ou admin");
	}
	
	std::string resposta = tabela.remove_player(player.getNome());
	if (resposta == "Jogador removido com sucesso.") {
		printf("kickando\n");
		
		try {
			dpp::snowflake guild = event.msg.guild_id;
			bot.guild_member_kick(guild, dpp::snowflake(player.getId()));
		}
		catch (std::exception& e) {
			return "Jogador removido da tabela, mas nao foi possivel kickar do servidor";
		}

		Moderador* autorPTR = (Moderador*)tabela.getPlayerByIdPtr(id_autor);
		autorPTR->setKicks(autorPTR->getKicks() + 1);
	}
	
	return resposta;
}

std::string tdc::banPlayer(dpp::message_create_t event, Tabela& tabela, dpp::cluster& bot) {
	const std::string id_autor = std::to_string(event.msg.author.id);
	basePlayer autor = tabela.getPlayerById(id_autor);
	if (autor.getCargo() != "Admin") {
		throw std::invalid_argument("Voce nao tem permissao para usar esse comando");
	}

	std::vector <std::string> args;
	boost::split(args, event.msg.content, boost::is_any_of(" "));

	if (args.size() != 2) {
		throw std::invalid_argument("Comando invalido! Use !banPlayer [Nome]");
	}

	basePlayer player = tabela.getPlayerByNome(args[1]);
	if (player.getCargo() == "Admin" || player.getCargo() == "Moderador") {
		throw std::invalid_argument("Voce nao pode banir um moderador ou admin");
	}

	std::string resposta = tabela.remove_player(player.getId());
	if (resposta == "Jogador removido com sucesso!") {
		dpp::snowflake guild = event.msg.guild_id;
		bot.guild_ban_add(guild, dpp::snowflake(player.getId()));
		
		Admin* autorPTR = (Admin*)tabela.getPlayerByIdPtr(id_autor);
		autorPTR->setBans(autorPTR->getBans() + 1);
	}
	
	return resposta;
}

std::string tdc::attLevel(dpp::message_create_t event, Tabela& tabela) {
	std::string id_autor = std::to_string(event.msg.author.id);

	std::vector <std::string> args;
	boost::split(args, event.msg.content, boost::is_any_of(" "));

	if (args.size() != 2) {
		throw std::invalid_argument("Comando invalido! Use !attLevel [Level]");
	}
	
	int level;
	try {
		level = std::stoi(args[2]);
	}
	catch (std::exception& e) {
		throw std::invalid_argument("Level invalido");
	}

	if (level < 0 || level > 100) {
		throw std::invalid_argument("Level invalido! Use um numero entre 0 e 100");
	}

	return tabela.attLevel(id_autor, level);
}

std::string tdc::comando(dpp::message_create_t event, dpp::cluster& bot) {
	Tabela tabela;
	std::string resposta = "";
	std::cout << event.msg.content << " - " << event.msg.author.username << std::endl;

	try {

		if (boost::starts_with(event.msg.content, "!registrar"))
		{
			resposta = tdc::registrar(event, tabela);
		}
		else if (boost::starts_with(event.msg.content, "!addPlayer"))
		{
			resposta = tdc::addPlayer(event, tabela);
		}
		else if (boost::starts_with(event.msg.content, "!removePlayer"))
		{
			resposta = tdc::removePlayer(event, tabela);
		}
		else if (event.msg.content == "!tabela")
		{
			resposta = tdc::getTabela(tabela);
		}
		else if (event.msg.content == "!tabelalevel")
		{
			resposta = tdc::getTabelaLevel(tabela);
		}
		else if (boost::starts_with(event.msg.content, "!mudarCargo"))
		{
			resposta = tdc::mudarCargo(event, tabela);
		}
		else if (boost::starts_with(event.msg.content, "!kickPlayer"))
		{
			resposta = tdc::kickPlayer(event, tabela, bot);
		}
		else if (boost::starts_with(event.msg.content, "!banPlayer"))
		{
			resposta = tdc::banPlayer(event, tabela, bot);
		}
		else if (boost::starts_with(event.msg.content, "!help"))
		{
			resposta = "Comandos disponiveis: \n"
				"!registrar [nome] [level] - Registra um novo jogador\n"
				"!addPlayer [nome] [level] [id] - Adiciona um jogador a tabela\n"
				"!removePlayer [nome] - Remove um jogador da tabela\n"
				"!tabela - Mostra a tabela de jogadores\n"
				"!tabelalevel - Mostra a tabela de jogadores ordenada por level\n"
				"!mudarCargo [nome] [cargo] - Muda o cargo de um jogador\n"
				"!kickPlayer [nome] - Kicka um jogador do servidor\n"
				"!banPlayer [nome] - Bane um jogador do servidor\n"
				"!help - Mostra os comandos disponiveis\n";
		}
		else
		{
			resposta = "Comando invalido! Use !help para ver os comandos disponiveis";
		}
	}
	catch (std::invalid_argument& e) {
		resposta = e.what();
	}
	catch (...) {
		resposta = "Erro desconhecido";
	}
	
	
	
	std::cout << "Finalizando comando" << std::endl;
	return resposta;
}