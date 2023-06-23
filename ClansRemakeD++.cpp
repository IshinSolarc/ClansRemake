#include <iostream>
#include <dpp/dpp.h>
#include "TratamentoDeComando.h"

int main()
{

	std::string token;

	std::ifstream file("config.txt");
	
	if (!file.is_open()) {
		std::cout << "Erro ao abrir arquivo de config" << std::endl;
		return 1;
	}
		
	std::string line;

	while (std::getline(file, line)) {
		if (line.substr(0, 7) == "token: ") {
			token = line.substr(7, line.length() - 7);
		}
	}


	file.close();

	std::cout << "Token: " << token << std::endl;
	
	dpp::cluster bot(token);

	bot.on_ready([&bot](const dpp::ready_t& event) {
		std::cout << "Logged in as " << bot.me.username << std::endl;
		});
	
	bot.intents = dpp::intents::i_all_intents;

	bot.on_slashcommand([](auto event) {
		if (event.command.get_command_name() == "ping") {
			event.reply("Pong!");
		}
	});


	bot.on_message_create([&bot](const dpp::message_create_t& event) {
		if (event.msg.author == bot.me) 
			return;

		if(boost::starts_with(event.msg.content, "!"))
			event.reply(tdc::comando(event, bot));
	});
	
	bot.start(dpp::st_wait);
	

   
	return 0;
}

