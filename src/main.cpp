#include "systemc.h"

#include "processor.cpp"

#include <vector>
#include <string>
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
        if (words[0] == "J")
        {
            tmpInt = 3;

            decodedInstruction |= (tmpInt << 29);
        }
        else if (words[0] == "JN")
        {
            tmpInt = 37;

            decodedInstruction |= (tmpInt << 26);
        }
        else if (words[0] == "JZ")
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
    sc_int<32> dataMem[32]; // Vetor com dados para entrarem na memória de dados
    fileData.open("../data/data_memory.dat");
    if (!fileData)
    {
        cout << "Erro no carregamento do arquivo de dados";
        exit(1);
    }

    int data, i{0};
    while (fileData >> data)
    {
        dataMem[i] = data;
        i++;
    }

    fstream fileInstruction;
    sc_int<32> instructionMem[32]; // Vetor com dados para entrarem na memória de instruções
    string fileName = argv[1];
    fileInstruction.open(fileName);
    if (!fileInstruction)
    {
        cout << "Erro no carregamento do arquivo de instruções";
        exit(1);
    }
    string instStr;
    int instInt;
    i = 0;
    while (fileInstruction >> instStr)
    {
        instInt = decode(instStr);
        instructionMem[i] = instInt;
        i++;
    }

    processor prc("Processor", dataMem, instructionMem);
    sc_clock clock("clock", 10, SC_NS, 0.5);
    prc.clock(clock);

    return 0;
}