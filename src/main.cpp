#include "systemc.h"
#include "./processor.cpp"
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int decode(string instruction)
{
	// Faz a decodificação da entrada das instruções
	// Para instruçõs de ULA ela deve vir "Operação" "Registrador Um" "Registrador Dois" "Registrador Destino"
	// Para instruções de Mémoria, ela deve vir como "Operação" "Registrador Fonte" "Registrador Destino"
	// Para instruções de Jump, deve vir como "Operação" "Posição"

	int decodedInstruction = 0;
	int tmpInt;

	string tmp;
	stringstream ss(instruction);
	vector<string> words;

	while (getline(ss, tmp, ','))
	{
		words.push_back(tmp);
	}

	if (words.size() == 4) // Ula
	{
		if (words[0] == "AND")
		{
			tmpInt = 1;
		}
		else if (words[0] == "OR")
		{
			tmpInt = 2;
		}
		else if (words[0] == "XOR")
		{
			tmpInt = 3;
		}
		else if (words[0] == "NOT")
		{
			tmpInt = 4;
		}
		else if (words[0] == "CMP")
		{
			tmpInt = 5;
		}
		else if (words[0] == "ADD")
		{
			tmpInt = 6;
		}
		else if (words[0] == "SUB")
		{
			tmpInt = 7;
		}
		decodedInstruction |= (tmpInt << 26);

		decodedInstruction |= (stoi(words[1]) << 21);

		decodedInstruction |= (stoi(words[2]) << 16);

		decodedInstruction |= (stoi(words[3]) << 11);
	}
	else if (words.size() == 3) // Memória
	{
		if (words[0] == "LD")
		{
			tmpInt = 1;
		}
		else if (words[0] == "ST")
		{
			tmpInt = 2;
		}

		decodedInstruction |= (tmpInt << 29);

		decodedInstruction |= (stoi(words[1]) << 21);

		decodedInstruction |= (stoi(words[2]) << 16);
	}
	else if (words.size() == 2) // Jump
	{
		if (words[0] == "AND")
		{
			tmpInt = 3;

			decodedInstruction |= (tmpInt << 29);
		}
		else if (words[0] == "OR")
		{
			tmpInt = 37;

			decodedInstruction |= (tmpInt << 26);
		}
		else if (words[0] == "XOR")
		{
			tmpInt = 45;
			decodedInstruction |= (tmpInt << 26);
		}

		decodedInstruction |= (stoi(words[1]) << 21);
	}

	return decodedInstruction;
}

int sc_main(int argc, char *argv[])
{

	fstream fileData;
	vector<int> dataMem;
	fileData.open("data_memory.txt");
	if (!fileData)
	{
		cout << "Erro no carregamento do arquivo de dados";
		return 1;
	}

	int data;
	while (fileData >> data)
		dataMem.push_back(data);

	fstream fileInstruction;
	vector<int> dataInstruction;
	string fileName = argv[1];
	fileInstruction.open(fileName);
	if (!fileInstruction)
	{
		cout << "Erro no carregamento do arquivo de instruções";
		return 1;
	}
	string instStr;
	int instInt;
	while (fileInstruction >> instStr)
	{
		instInt = decode(instStr);
		dataInstruction.push_back(instInt);
	}

	return 0;
}