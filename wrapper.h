#pragma once
#include <vector>
#include <map>
#include <functional>
#include <exception>

class Wrapper {
public:
	template<typename Obj, typename... Args>
	Wrapper(Obj* object, int (Obj::* func)(Args...), std::vector<std::pair<std::string, int>> args) {
		for (auto& p : args) {
			argName.push_back(p.first);
		}

		if (args.size() != argName.size())
		{
			throw std::exception("WRAPPER: name must be unique");
		}

		caller = [object, func](std::vector<int>& argsForFunc) {
			return executeFunction(object, func, argsForFunc, std::make_index_sequence<sizeof...(Args)>{});
		};

	}

	int execute(const std::map<std::string, int>& argsMap) {
		std::vector<int> argsVec;
		for (auto& arg : argsMap) {
			if (!isExist(arg.first)) {
				throw std::exception("WRAPPER: command is`t init");
			}
				
			argsVec.push_back(arg.second);
		}
		return caller(argsVec);
	}
	Wrapper() = default;
	Wrapper(Wrapper const&) = delete;
	Wrapper& operator=(Wrapper const&) = delete;
	Wrapper(Wrapper&&) = default;
	Wrapper& operator=(Wrapper&&) = default;
	~Wrapper() = default;
private:
	bool isExist(std::string name) {
		for (auto& n : argName) {
			if (n.compare(name) == 0) {
				return true;
			}
		}
		return false;
	}

	template<typename Obj, typename FuncName, size_t... Indxs>
	static int executeFunction(Obj* object, FuncName funcName, std::vector<int>& args, std::index_sequence<Indxs...>) {
		return ((object->*funcName)(args[Indxs]...));
	}

	std::function<int(std::vector<int>&)> caller;
	std::vector<std::string> argName;
};