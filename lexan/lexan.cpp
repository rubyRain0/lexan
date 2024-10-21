#include <iostream>
#include <fstream>
#include <ctype.h>
#include <conio.h>
#include <string>

class FiniteStateMachine
{
private:
	static int D[7][3];

	static int sclass(char c)
	{
		if (c == '"') return 0; //apostrophe "
		if (c == '\'') return 1;// apostrophe '
		return 2; // other symbols
	}

	static void checkString(std::string s)
	{
		int st = 0; //initial state
		int i = 0; //initial index

		while (i < s.length())
		{
			int myClass = sclass(s[i]);
			std::cout << s[i] << " [" << st << " -> ";

			st = D[st][myClass];
			std::cout << st << "]" << std::endl;

			if (st == -1)
			{
				std::cout << "Ошибка, неправильное закрытие апострофами." << std::endl;
				return;
			}

			++i;
		}
		std::cout << "Строка корректна." << std::endl;
	}

public:
	static void readFromFile(const std::string& filename)
	{
		std::ifstream file(filename);
		if (file.is_open())
		{
			std::string line;
			while (std::getline(file, line))
			{
				checkString(line);
			}
			file.close();
		}
		else
		{
			std::cout << "Не удалось открыть файл." << std::endl;
		}
	}
};

int FiniteStateMachine::D[7][3] = {
	// ",',[.]
	{2, 1, -1},   // s0
	{3, -1, 1},   // s1
	{-1, 4, 2},   // s2
	{6, 5, -1},   // s3
	{6, 5, -1},   // s4
	{-1, -1, 1},  // s5
	{-1, -1, 2}   // s6
};

int main()
{
	setlocale(LC_ALL, "Russian");
	FiniteStateMachine::readFromFile("input.txt");
	return 0;
}
