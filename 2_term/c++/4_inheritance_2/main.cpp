// 20

#include "function.hpp"

#include <string>

void usage()
{
	std::cout << "pick [const | linear | quadratic] - picks a function\n";
	std::cout << "init [manually | randomly] - fetches data from your keyboard to the function or fills it randomly\n";
	std::cout << "print [function | derivative] - prints the current function or it's derivative\n";
}

int main()
{
	std::cout << "Demo\n\n";

	IFunction* func = nullptr;

	while (true)
	{
		std::string cmd[3];
		
		std::cout << "> ";
		
		std::string s;
		std::getline(std::cin, s);

		size_t j = 0;
		for (size_t i = 0; i < s.length(); i++)
		{
			if (s[i] == ' ')
				j++;
			else
				cmd[j].append(1, s[i]);
		}

		if (cmd[0].empty())
			continue;

		if (cmd[0] == "quit")
			break;
		else if (cmd[0] == "clear")
			system("cls"); // WIN32
		else if (cmd[0] == "pick")
		{
			if (func)
				delete func;

			if (cmd[1] == "const") func = new Function_Const();
			else if (cmd[1] == "linear") func = new Function_Linear();
			else if (cmd[1] == "quadratic") func = new Function_Quadratic();
		}
		else if (cmd[0] == "init")
		{
			if (cmd[1] == "manually") std::cin >> func;
			else if (cmd[1] == "randomly") func->fill_randomly();
		}
		else if (cmd[0] == "print")
		{
			if (cmd[1] == "function") std::cout << func << std::endl;
			else if (cmd[1] == "derivative")
			{
				IFunction* derivative = func->derivative();
				std::cout << derivative << std::endl;
				delete derivative;
			}
		}
		else if (cmd[0] == "usage")
			usage();
		else
			std::cout << "Unknown command" << std::endl;
	}
}
