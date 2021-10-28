// Atividade assíncrona 4 
// Fundamentos de Algoritmos para Otimização
// Problema da Arvore geradora mínima

// Autor: Gustavo Lima
// prof: Raphael Kramer

// numeração das cidades:
// 0-sao luiz; 1-teresina; 2-fortaleza; 3-natal; 4-joao pessoa; 5-recife; 6-maceio; 7-aracaju; 8-salvador
// 9-belo horizonte; 10-sao paulo; 11-rio de janeiro; 12-vitoria; 13-cuiaba; 14-goiania; 15-campo grande
// 16-brasilia



#include <iostream>
#include <vector>
#include <algorithm> 

std::vector<std::pair<int, int>> arvore;
std::vector<int> conjunto;
std::vector<bool> cidades;
int custoTotal = 0;
std::vector<std::string> nomes = { {"sao luiz"}, {"teresina"}, {"fortaleza"}, {"natal"},
{"joao pessoa"}, {"recife"}, {"maceio"}, {"aracaju"}, {"salvador"},
{"belo horizonte"}, {"sao paulo"}, {"rio de janeiro"}, {"vitoria"},
{"cuiaba"}, {"goiania"}, {"campo grande"}, {"brasilia"} };

int checkConjunto(std::pair<int, int> arco)
{
	if (conjunto[arco.first] == NULL && conjunto[arco.second] == NULL)
	{
		std::cout << "adiciona: ";
		for (int i = 0; i < nomes[arco.first].size(); i++)
		{
			std::cout << nomes[arco.first][i];
		}
		std::cout << '-';
		for (int i = 0; i < nomes[arco.second].size(); i++)
		{
			std::cout << nomes[arco.second][i];
		}
		return 1;
	}
	else if (conjunto[arco.first] == NULL && conjunto[arco.second] != NULL)
	{
		std::cout << "adiciona: ";
		for (int i = 0; i < nomes[arco.first].size(); i++)
		{
			std::cout << nomes[arco.first][i];
		}
		std::cout << '-';
		for (int i = 0; i < nomes[arco.second].size(); i++)
		{
			std::cout << nomes[arco.second][i];
		}
		return 4;
	}
	else if (conjunto[arco.second] == NULL && conjunto[arco.first] != NULL)
	{
		std::cout << "adiciona: ";
		for (int i = 0; i < nomes[arco.first].size(); i++)
		{
			std::cout << nomes[arco.first][i];
		}
		std::cout << '-';
		for (int i = 0; i < nomes[arco.second].size(); i++)
		{
			std::cout << nomes[arco.second][i];
		}
		return 5;
	}
	else if (conjunto[arco.first] < conjunto[arco.second])
	{
		std::cout << "adiciona: ";
		for (int i = 0; i < nomes[arco.first].size(); i++)
		{
			std::cout << nomes[arco.first][i];
		}
		std::cout << '-';
		for (int i = 0; i < nomes[arco.second].size(); i++)
		{
			std::cout << nomes[arco.second][i];
		}
		return 2;
	}
	else if (conjunto[arco.first] > conjunto[arco.second])
	{
		std::cout << "adiciona: ";
		for (int i = 0; i < nomes[arco.first].size(); i++)
		{
			std::cout << nomes[arco.first][i];
		}
		std::cout << '-';
		for (int i = 0; i < nomes[arco.second].size(); i++)
		{
			std::cout << nomes[arco.second][i];
		}
		return 3;
	}
	else 
	{
		return 6;
	}
}

bool checkPath(int a, int b)
{
	for (int i = 0; i < arvore.size(); i++)
	{
		if (conjunto[a] == conjunto[b] && (conjunto[a] != 0 || conjunto[b] != 0))
		{
			return true;
		}
	}
	return false;
}

void kruskal(std::vector<std::vector<std::pair<int, int>>> matrix)
{
	int conjS;
	int conjF;
	int menorDist;
	std::pair<int, int> arco;
	int step = 0;
	int opConj = 0;

	for (int cidade = 0; cidade < matrix.size(); cidade++) {
		std::sort(matrix[cidade].begin(), matrix[cidade].end());
	}

	for (int coluna = 1; coluna < matrix.size(); coluna++)
	{
		step = 0;
		while (step != matrix.size())
		{
			menorDist = std::numeric_limits<int>::max();
			for (int linha = 0; linha < matrix.size(); linha++)
			{
				if (!checkPath(linha, matrix[linha][coluna].second))
				{
					if (menorDist > matrix[linha][coluna].first)
					{
						menorDist = matrix[linha][coluna].first;
						arco = { linha, matrix[linha][coluna].second };
					}
				}		
			}
			
			switch (checkConjunto(arco))
			{
			case(1):
				opConj++;
				conjunto[arco.first] = opConj;
				conjunto[arco.second] = opConj;
				arvore.push_back(arco);
				cidades[arco.first] = true;
				cidades[arco.second] = true;
				std::cout << "  distancia: " << menorDist << std::endl;
				custoTotal += menorDist;
				break;
			case(2):
				conjF = conjunto[arco.first];
				for (int i = 0; i < conjunto.size(); i++)
				{
					if (conjunto[i] == conjF)
					{
						conjunto[i] = conjunto[arco.second];
					}
				}
				arvore.push_back(arco);
				std::cout << "  distancia: " << menorDist << std::endl;
				custoTotal += menorDist;
				break;
			case(3):
				conjS = conjunto[arco.second];
				for (int i = 0; i < conjunto.size(); i++)
				{
					if (conjunto[i] == conjS)
					{
						conjunto[i] = conjunto[arco.first];
					}
				}
				arvore.push_back(arco);
				std::cout << "  distancia: " << menorDist << std::endl;
				custoTotal += menorDist;
				break;
			case(4):
				conjunto[arco.first] = conjunto[arco.second];
				arvore.push_back(arco);
				std::cout << "  distancia: " << menorDist << std::endl;
				custoTotal += menorDist;
				break;
			case(5):
				conjunto[arco.second] = conjunto[arco.first];
				arvore.push_back(arco);
				std::cout << "  distancia: " << menorDist << std::endl;
				custoTotal += menorDist;
				break;
			case(6):
				step = matrix.size() - 1;
				break;
			}
			step++;
		}
		
	}


}


int main(int argc, char *argv[])
{
	std::vector<std::vector<std::pair<int, int>>> matrix = { 
	{{0,0},{43,1},{90,2},{142,3},{157,4},{171,5},{162,6},{155,7},{158,8},{251,9},{293,10},{293,11},{255,12},{268,13},{201,14},{287,15},{199,16}},
	{{43,0},{0,1},{62,2},{105,3},{120,4},{112,5},{119,6},{111,7},{115,8},{202,9},{265,10},{245,11},{212,12},{254,13},{188,14},{272,15},{168,16}} ,
	{{90,0},{62,1},{0,2},{52,3},{67,4},{77,5},{94,6},{110,7},{118,8},{232,9},{294,10},{258,11},{215,12},{302,13},{216,14},{300,15},{196,16}} ,
	{{142,0},{105,1},{52,2},{0,3},{17,4},{28,5},{54,6},{49,7},{109,8},{236,9},{292,10},{259,11},{213,12},{346,13},{260,14},{333,15},{240,16}} ,
	{{157,0},{120,1},{67,2},{17,3},{0,4},{11,5},{36,6},{61,7},{91,8},{219,9},{275,10},{227,11},{195,12},{329,13},{243,14},{316,15},{171,16}} ,
	{{171,0},{112,1},{77,2},{28,3},{11,4},{0,5},{25,6},{50,7},{80,8},{208,9},{263,10},{230,11},{184,12},{318,13},{232,14},{305,15},{212,16}} ,
	{{162,0},{119,1},{94,2},{54,3},{36,4},{25,5},{0,6},{27,7},{57,8},{185,9},{241,10},{208,11},{161,12},{295,13},{209,14},{282,15},{189,16}} ,
	{{155,0},{111,1},{110,2},{49,3},{61,4},{50,5},{27,6},{0,7},{31,8},{160,9},{215,10},{182,11},{136,12},{270,13},{184,14},{257,15},{164,16}} ,
	{{158,0},{115,1},{118,2},{109,3},{91,4},{80,5},{57,6},{31,7},{0,8},{140,9},{196,10},{163,11},{117,12},{250,13},{164,14},{237,15},{144,16}} ,
	{{251,0},{202,1},{232,2},{236,3},{219,4},{208,5},{185,6},{160,7},{140,8},{0,9},{58,10},{44,11},{51,12},{156,13},{88,14},{126,15},{72,16}} ,
	{{293,0},{265,1},{294,2},{292,3},{275,4},{263,5},{241,6},{215,7},{196,8},{58,9},{0,10},{43,11},{94,12},{152,13},{89,14},{98,15},{100,16}} ,
	{{293,0},{245,1},{258,2},{259,3},{227,4},{230,5},{208,6},{182,7},{163,8},{44,9},{43,10},{0,11},{52,12},{192,13},{130,14},{141,15},{116,16}} ,
	{{255,0},{212,1},{215,2},{213,3},{195,4},{184,5},{161,6},{136,7},{117,8},{51,9},{94,10},{52,11},{0,12},{208,13},{139,14},{191,15},{124,16}} ,
	{{268,0},{254,1},{302,2},{346,3},{329,4},{318,5},{295,6},{270,7},{250,8},{156,9},{152,10},{192,11},{208,12},{0,13},{89,14},{70,15},{105,16}} ,
	{{201,0},{188,1},{216,2},{260,3},{243,4},{232,5},{209,6},{184,7},{164,8},{88,9},{89,10},{130,11},{139,12},{89,13},{0,14},{84,15},{20,16}} ,
	{{287,0},{272,1},{300,2},{333,3},{316,4},{305,5},{282,6},{257,7},{237,8},{126,9},{98,10},{141,11},{191,12},{70,13},{84,14},{0,15},{104,16}} ,
	{{199,0},{168,1},{196,2},{240,3},{171,4},{212,5},{189,6},{164,7},{144,8},{72,9},{100,10},{116,11},{124,12},{105,13},{20,14},{104,15},{0,16}} };

	for (int i = 0; i < matrix.size(); i++)
	{
		conjunto.push_back(NULL);
		cidades.push_back(false);
	}
	
	std::cout << "Peso dos arcos = Distancia na ordem de 10km" << std::endl;
	std::cout << "Algoritmo de Kruskal:" << std::endl;
	kruskal(matrix);
	
	std::cout << "Custo total: "<< custoTotal << std::endl;
	return 0;
}


