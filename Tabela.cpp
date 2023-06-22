#include "Tabela.h"

Tabela::Tabela() {
	std::ifstream config("config.txt");
	
	std::string line;
	while (std::getline(config, line)) {
		if (boost::starts_with(line, "player_database: ")) {
			player_base_name = line.substr(17);
			break;
		}
	}
	
	tabela_arquivo = new std::ifstream(player_base_name);

	if (!tabela_arquivo) {
		//cria o arquivo
		std::ofstream tabela_arquivo2(player_base_name);
		tabela_arquivo2.close();
		tabela_arquivo = new std::ifstream(player_base_name);
	}

	//entrada esperada em toda linha:
	//nome id level cargo kicks ban
	
	
	while (std::getline(*tabela_arquivo, line)) {
		std::vector<std::string> strs;
		boost::split(strs, line, boost::is_any_of(","));
		if (strs.size() == 6) {
			std::cout << strs[0] << " - " << strs[3];
			
			if (strs[3] == "Admin") {
				tabela_id[strs[1]] = new Admin(strs[0], strs[1], std::stoi(strs[2]), std::stoi(strs[4]), std::stoi(strs[5]));
				tabela_nome[strs[0]] = new Admin(strs[0], strs[1], std::stoi(strs[2]), std::stoi(strs[4]), std::stoi(strs[5]));
			}
			else if (strs[3] == "Moderador") {
				tabela_id[strs[1]] = new Moderador(strs[0], strs[1], std::stoi(strs[2]), std::stoi(strs[4]));
				tabela_nome[strs[0]] = new Moderador(strs[0], strs[1], std::stoi(strs[2]), std::stoi(strs[4]));
			}
			else if (strs[3] == "Membro") {
				tabela_id[strs[1]] = new Membro(strs[0], strs[1], std::stoi(strs[2]));
				tabela_nome[strs[0]] = new Membro(strs[0], strs[1], std::stoi(strs[2]));
			}
		}
		
	}
}

Tabela::~Tabela() {
	save();
	for (auto it = tabela_id.begin(); it != tabela_id.end(); ++it) {
		delete it->second;
	}
	tabela_id.clear();
	tabela_nome.clear();
	delete tabela_arquivo;
}

void Tabela::save() {
	tabela_arquivo->close();
	
	std::ofstream tabela_arquivo_escrita(player_base_name);
	tabela_arquivo_escrita.clear();
	
	std::vector <basePlayer*> tabela = this->getTabela();

	for (auto player : tabela) {
		std::cout << player->getNome() << " - " << player->getCargo() << std::endl;

		if (player->getCargo() == "Membro") {
			tabela_arquivo_escrita << player->getNome() << "," << player->getId() << "," << player->getLevel() << "," << player->getCargo() << "," << "0" << "," << "0" << std::endl;
		}
		else if (player->getCargo() == "Moderador") {
			tabela_arquivo_escrita << player->getNome() << "," << player->getId() << "," << player->getLevel() << "," << player->getCargo() << "," << ((Moderador*)player)->getKicks() << "," << "0" << std::endl;
		}
		else if (player->getCargo() == "Admin") {
			tabela_arquivo_escrita << player->getNome() << "," << player->getId() << "," << player->getLevel() << "," << player->getCargo() << "," << ((Admin*)player)->getKicks() << "," << ((Admin*)player)->getBans() << std::endl;
		}
	}	
	
	
	tabela_arquivo_escrita.close();
	tabela_arquivo = new std::ifstream(player_base_name);
}

basePlayer Tabela::getPlayerByNome(std::string nome) {
	auto it = tabela_nome.find(nome);
	if (it != tabela_nome.end()) {
		return *it->second;
	}
	else {
		return basePlayer("", "", 0, "");
	}
}

basePlayer Tabela::getPlayerById(std::string id) {
	auto it = tabela_id.find(id);
	if (it != tabela_id.end()) {
		return *tabela_id[id];
	}
	else {
		return basePlayer("", "", 0, "");
	}
}

basePlayer* Tabela::getPlayerByNomePtr(std::string nome) {
	auto it = tabela_nome.find(nome);
	if (it != tabela_nome.end()) {
		return it->second;
	}
	else {
		return nullptr;
	}
}

basePlayer* Tabela::getPlayerByIdPtr(std::string id) {
	auto it = tabela_id.find(id);
	if (it != tabela_id.end()) {
		return tabela_id[id];
	}
	else {
		return nullptr;
	}
}

std::string Tabela::add_player(basePlayer player) {
	if (this->busca(player.getId())) {
		return "Ja existe um jogador com esse ID.";
	}
	else {
		basePlayer* novoPlayer = new Membro(player.getNome(), player.getId(), player.getLevel());
		tabela_nome[player.getNome()] = novoPlayer;
		tabela_id[player.getId()] = novoPlayer;
		this->save();
		return "Jogador adicionado com sucesso.";
	}
}

std::string Tabela::mudarCargo(std::string id, std::string cargo) {
	basePlayer * player = tabela_id[id];
	basePlayer Dados = *player;
	basePlayer* novoPlayer;
	
	if (player == nullptr) {
		return "Nao existe um jogador com esse ID.";
	}
	else {
		if (cargo == "Admin") {
			novoPlayer = new Admin(Dados.getNome(), Dados.getId(), Dados.getLevel(), 0, 0);
		}
		else if (cargo == "Moderador") {
			novoPlayer = new Moderador(Dados.getNome(), Dados.getId(), Dados.getLevel(), 0);
		}
		else if (cargo == "Membro") {
			novoPlayer = new Membro(Dados.getNome(), Dados.getId(), Dados.getLevel());
		}
		else {
			return "Cargo invalido.";
		}
		tabela_nome.erase(Dados.getNome());
		tabela_id.erase(Dados.getId());
		tabela_nome[novoPlayer->getNome()] = novoPlayer;
		tabela_id[novoPlayer->getId()] = novoPlayer;
		delete player;
		this->save();
		return "Cargo alterado com sucesso.";
	}
}

std::string Tabela::remove_player(std::string nome) {
	
	std::cout << "Removendo " << nome << std::endl;
	
	basePlayer * player = tabela_nome[nome];
	basePlayer Dados = *player;

	if (player == nullptr) {
		return "Nao existe um jogador com esse nome.";
	}
	else {
		tabela_nome.erase(Dados.getNome());
		tabela_id.erase(Dados.getId());
		delete player;
		this->save();
		return "Jogador removido com sucesso.";
	}
}

std::vector <basePlayer*> Tabela::getTabela() {
	std::vector <basePlayer*> tabela;

	for (auto i : tabela_nome) {
		tabela.push_back(i.second);
	}

	return tabela;
}

bool Tabela::busca(std::string id) {
	return tabela_id.find(id) != tabela_id.end();
}



std::string Tabela::getCargoByID(std::string id) {
	basePlayer* player = tabela_id[id];

	if (player == NULL) {
		return "Jogador nao encontrado.";
	}
	else {
		return player->getCargo();
	}
}

bool Tabela::isAutoridade(std::string id) {
	basePlayer * player = tabela_id[id];

	if (player == NULL)
		return false;
	
	if (player->isAutoridade())
		return true;
	else
		return false;
}

std::string Tabela::getStrTabela() {
	std::string str = "";
	std::vector <basePlayer*> tabela = this->getTabela();

	boost::sort::pdqsort(tabela.begin(), tabela.end(), compararPlayersPtr);
	
	for (auto player : tabela) {
		str += player->getNome() + " - LVL: " + std::to_string(player->getLevel()) + " - Cargo: " + player->getCargo() + "\n";
	}
	
	return str;	
}

std::string Tabela::getStrTabelaLevel() {
	std::string str = "";
	std::vector <basePlayer*> tabela = this->getTabela();
	
	boost::sort::pdqsort(tabela.begin(), tabela.end(), compararLevelsPtr);
	
	for (auto player : tabela) {
		str += player->getNome() + " - LVL: " + std::to_string(player->getLevel()) + " - Cargo: " + player->getCargo() + "\n";
	}
	
	return str;

}

std::string Tabela::attLevel(std::string id, int level) {
	basePlayer* player = tabela_id[id];

	if (player == nullptr) {
		return "Jogador nao encontrado.";
	}
	else {
		player->setLevel(level);
		this->save();
		return "Level atualizado com sucesso.";
	}
}