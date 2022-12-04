#pragma once
#include "wrapper.h"
#include <string>


class Engine {
public:
	void register_command(Wrapper* wrapper, const std::string& nameCommand) {
		if (functions.find(nameCommand) != functions.end()) {
			throw std::exception("ENGINE: This command already exist");
		}
			
		functions.insert({ nameCommand, wrapper });
	}

	int execute(std::string const& nameCommand, const std::map<std::string, int> const& args) {
		auto it = functions.find(nameCommand);
		if (it == functions.end()) {
			throw std::exception("ENGINE: This command is not registred");
		}
			

		Wrapper* wrapper = static_cast<Wrapper*>(it->second);
		return wrapper->execute(args);
	}
	Engine() = default;
	Engine(Engine const&) = delete;
	Engine& operator =(Engine const&) = delete;
	Engine(Engine&&) = default;
	Engine& operator =(Engine&&) = default;
	~Engine() = default;
private:
	std::map<std::string, void*> functions;
};