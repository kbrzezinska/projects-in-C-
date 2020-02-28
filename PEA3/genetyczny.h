#pragma once
#include <string>
#include <ratio>
#include <chrono>
#include <cmath>
#include <algorithm>
#define M_E 2.71828182845904523536
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include "stdlib.h"
#include <climits>
#include <algorithm>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <iomanip>

using namespace std;
using namespace std::chrono;
typedef     vector<int>     c_v_i;              // vector of int
typedef     vector<c_v_i>   c_v_v_i;            // vector of vector of int
#define HEADER_LINES  7;
#define COMPARATOR(code) [this](auto && l, auto && r) -> bool { return code ; }
class Genetic{

	public:
		int m = 0;//wybór mutacji
	int **matrix;
	c_v_i bestWay;
	int bestCost;
	c_v_i road; 
	c_v_i tabCost;
	int size;
	int population=10;
	c_v_i costPopulation;
	c_v_v_i parent;
	c_v_v_i popul;
	c_v_v_i child;
	c_v_i costChild;
	float wspolczynnik_cross=0.8;
	float wspolczynnik_mutation = 0.01;
	double stop = 2.0;
	int download(std::string FILE_IN);
	void pobierz(string s);
	vector<int> cross(vector<int>q, vector<int>qq);
	vector<int> mutation(vector<int>t);
	vector<int>mutation2(vector<int>t);
	int costOfRoad(int *tab);
	int costOfRoad(vector<int>tab);
	c_v_v_i sort2(c_v_v_i p);
	void geneticAlg();
	c_v_v_i sort(c_v_v_i p);
	c_v_v_i noMatches(c_v_v_i p);
};



void Genetic::pobierz(string s)
{
	delete[] matrix; ;
	matrix = NULL; 
	road.erase(road.begin(), road.end());
	bestWay.erase(bestWay.begin(), bestWay.end());
	std::ifstream plik;
	plik.open(s.c_str());
	plik >> size;

	matrix = new int*[size];
	bestWay.resize(size);
	road.resize(size);
	for (int i = 0; i < size && !plik.eof(); i++)
	{
		matrix[i] = new int[size];
		road[i] = i;
		for (int j = 0; j < size && !plik.eof(); j++){

			plik >> matrix[i][j];
		}

	}
	plik.close();std:: cout << "close" << endl;
}

int Genetic::costOfRoad(int *tab)
{
	int cost = 0;
	for (int i = 0; i < size - 1; i++)
	{
		cost += matrix[tab[i]][tab[i + 1]];

	}
	cost += matrix[tab[size - 1]][tab[0]];
	return cost;
}

int Genetic::costOfRoad(vector<int>tab)
{
	int cost = 0;
	for (int i = 0; i < size - 1; i++)
	{
		cost += matrix[tab[i]][tab[i + 1]];

	}
	cost += matrix[tab[size - 1]][tab[0]];
	return cost;
}

vector<int> Genetic::cross(vector<int>q, vector<int>qq)
{
	
	int *p=new int[size]; 


	int min = rand() % size ;
	int max = min+ rand()%(size-2);
	if (max >= size){ max = max - size; }

	c_v_i buff; //buff.resize(size);
	c_v_i pp; 
	
	//std::cout << " min " << min << "  max" << max << " " << std::endl;
	
	for (int i = min; i != max; i++)
	{
		if (i == size && max == 0){ break;  }
		if (i == size && max!=0 ){ i = 0; }
		
		p[i] = q[i]; 		
		buff.push_back(q[i]);
	}
	p[max] = q[max];
	buff.push_back(q[max]);
	
	bool flaga = true;
	for (int i = max + 1, l = max + 1; i != min; l++)
	{
		if (i == size){ i = 0; }
		if (l == size){ l = 0; }

		for (int o = 0; o <buff.size(); o++)
		{
			if (buff[o] == qq[l]){ flaga = false; }

		}
		if (flaga == true)
		{

			p[i] = qq[l]; i++;
		}
		if (i == size){ i = 0; }
		flaga = true;
	}
	//cout << "uda³os";
	for (int i = 0; i <size; i++)
	{
		pp.push_back(p[i]);
	}
	return pp;
}

vector<int> Genetic::mutation(vector<int>t)
{
	
	int min = rand() % size ;
	int max = min + size /( 2+rand()%3);
	if (max >= size)max = max - size;
	//std::cout << min << " " << max << " " << std::endl;
	int *k = new int[size];
	for (int i= min,j=max; i !=max; i++,j--)
	{
		if (i == size && max == 0)break;
		if (i == size)i = 0;
		
		if (j < 0)j = size - 1;
	k[i] = t[j];

	}
	k[max] = t[min];
	for (int i = min; i != max; i++)
	{
		if (i == size && max == 0)break;
		if (i == size)i = 0;
		t[i] = k[i];

	}
	t[max] = k[max];

	k = NULL;delete[] k;
	return t;
}
vector<int> Genetic::mutation2(vector<int>t)
{

	
	int *k = new int[size];
	for (int i = 0; i <size; i++ )
	{
	
		k[i] = t[i];

	}
	
	for (int i = 0; i <size/2; i++)
	{
		
		t[i] = k[size-1-i];

	}
	for (int i = size / 2, j = 0; i < size; j++, i++)
	{

		t[i] = k[j];

	}

	k = NULL; delete[] k;
	return t;
}

void Genetic::geneticAlg()
{
	
	srand(time(0));
	
	bestWay.erase(bestWay.begin(), bestWay.end());
	high_resolution_clock::time_point t2;
	std::chrono::duration<double> diff;
	double time = 0;
	vector<unsigned long long> costRuletka;

	unsigned long long sumRuletka = 0;
	parent.resize(population/2);
	costPopulation.resize(population);
	popul.resize(population);
	costRuletka.resize(population);
	int wsp = population*wspolczynnik_cross;

	bestCost = 99999999999999;

	for (int i = 0; i < population; i++)
	{
		popul[i].resize(size);
	}

	int p = 0;
	do{
		popul[p] = road;
		p++;
	} while (next_permutation(road.begin() + rand() % ((size / 2)-2), road.end() - rand() % size / 2) && p<population);
	
	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	
	while (time<stop)
	{
		///ewolucja
		popul=sort2(popul);
		sumRuletka = 0;

		for (int i = 0; i < population; i++)
		{
			costPopulation[i] = costOfRoad(popul[i]);

			if (bestCost > costPopulation[i])
			{
				bestCost = costPopulation[i];
				bestWay = popul[i];
			}

			costRuletka[i] = UINT_MAX - costPopulation[i];
			sumRuletka += costRuletka[i];

		}

		
		

		//selekcja rodzica

		for (int j = 0; j < population / 2; j++){

			double ruletka = 0.0;
			double r = double(rand()) / double(RAND_MAX);

			for (int i = 0; i < population; i++)
			{
				ruletka += double(costRuletka[i]) / double(sumRuletka);
				
				if (r < ruletka){ parent[j] = (popul[i]); break; }

			}
		}
		
		//krzyzowanie
		for (int k = 0; k < wsp; k = k + 1)
		{
			int parent1 =  rand() % parent.size();
			int parent2 = rand() % parent.size();
			if (parent1 == parent2){ parent1 = rand() % parent.size(); }
			//cout << endl << parent1 << " " << parent2 << " " << endl;
			child.push_back(cross(parent[parent1], parent[parent2]));
			
		}
		//mutacja
		
		for (int m = 0; m < int( ceil(population*wspolczynnik_mutation)); m++)
		{
			int r = rand() % child.size();
			if (m == 0){ child[r] = mutation(child[r]); }
			if (m == 1){ child[r] = mutation2(child[r]);; }
		}
		popul = sort(popul);
		child = sort(child);
	
		
		c_v_v_i newPopulation;

		for (int i = 0; i < population; i++)
		{


			if (child.empty() && !popul.empty() )
			{
				
				while (popul.back() == newPopulation.back() && popul.size()>size - newPopulation.size())
				{
					popul.pop_back();
				}
				newPopulation.push_back(popul.back()); popul.pop_back();
			}

			if (!child.empty() && popul.empty())
			{
				
				while (newPopulation.back() == child.back() && child.size()>size-newPopulation.size() )
				{
					child.pop_back();
				}
				newPopulation.push_back(child.back()); child.pop_back();
			}
			if (!child.empty() && !popul.empty())
			{
				while (popul.back() == child.back() && child.size()>1)
				{
					child.pop_back();
				}
				
				if (costOfRoad(popul.back()) < costOfRoad(child.back()))
				{
					
					newPopulation.push_back(popul.back()); popul.pop_back();
				}
				else
				{
					
					newPopulation.push_back(child.back()); child.pop_back();

				}
				
			}
		}
		
		popul = newPopulation;
		child.erase(child.begin(), child.end());
		newPopulation.erase(newPopulation.begin(), newPopulation.end());
		
		t2 = high_resolution_clock::now();
		diff = t2 - t1;
		 time = diff.count();

	}

	for (int i = 0; i < population; i++)
	{


		if (bestCost > costPopulation[i])
		{
			bestCost = costPopulation[i];
			bestWay = popul[i];
		}


	}
	cout << endl<< "time: " << time << endl;
}

c_v_v_i Genetic::sort(c_v_v_i p)//od najw do najm
{

	c_v_v_i pp;
	int best ,ii;

	while (!p.empty()){
		best = 0;
		for (int i = 0; i < p.size(); i++)
		{

			if (best < costOfRoad(p[i]))
			{
				ii = i;
				best = costOfRoad(p[i]);
			}
		}

		pp.push_back(p[ii]); p.erase(p.begin() + ii);
	}
	return pp;
}
c_v_v_i Genetic::sort2(c_v_v_i p)//od namn do najw
{

	c_v_v_i pp;
	int best, ii;

	while (!p.empty()){
		best = 9999999999999;
		for (int i = 0; i < p.size(); i++)
		{

			if (best > costOfRoad(p[i]))
			{
				ii = i;
				best = costOfRoad(p[i]);
			}
		}

		pp.push_back(p[ii]); p.erase(p.begin() + ii);
	}
	return pp;
}

c_v_v_i Genetic::noMatches(c_v_v_i p)//od namn do najw
{

	c_v_v_i pp;
	int best, ii;
	int psize = p.size();
	
		
		for (int i = 0; i < psize-1; i++)
		{

			if (p[i]==p[i+1])
			{
				p.erase(p.begin() + i + 1); i--; psize--;
			}
		}
		pp.resize(p.size());
		pp = p;
		return pp;
	
}


void error_exit(const string &msg)
{
	cout << msg << endl;
	system("PAUSE");
	exit(1);
}

//---------------------------------------------------------------------
// Odczyt liczby miast z naglowka pliku TSPLIB
// Odczytywane sa wszystkie linie naglowka 
//---------------------------------------------------------------------
int header_get_size(ifstream &file)
{
	int     header_lines = 0;
	int     size = 0;
	string  line;

	for (;;)
	{
		getline(file, line);
		if (file.fail() || line.empty())
			error_exit("File READ error - HEADER");

		if (line.find("DIMENSION") != string::npos)
		{
			istringstream in_ss(line);
			string tmp;
			in_ss >> tmp;
			in_ss >> size;
		}
		else
			if (line.find("EDGE_WEIGHT_SECTION") != string::npos)
				if (size <= 0)
					error_exit("File READ error - SIZE");
				else
					return(size);

		if (++header_lines >= 7)
			error_exit("File READ error - HEADER");
	}
}



//---------------------------------------------------------------------
int Genetic::download(std::string FILE_IN)
{
	delete[] matrix;
	matrix = NULL;
	road.erase(road.begin(), road.end());
	bestWay.erase(bestWay.begin(), bestWay.end());

	ifstream    file_in;
	ofstream    file_out;


	int         diagonal;
	int         dist, dist_max;
	c_v_v_i     city_distance;

	file_in.open(FILE_IN);
	if (!file_in.is_open())
		error_exit("File OPEN error - FILE_IN");

	size = header_get_size(file_in);

	
	bestWay.resize(size);
	road.resize(size);
	
	matrix = new int *[size];

	city_distance.resize(size);
	for (int i = 0; i < size; i++)
	{
		city_distance[i].resize(size);
		matrix[i] = new int[size];
		road[i] = i;
	}
	dist_max = 0;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			file_in >> dist;
			if (file_in.fail())
				error_exit("File READ error - DATA");

			if (i == j)
			{
				if (i == 0)
					diagonal = dist;
				else
					if (dist != diagonal)
						cout << "WARNING: Diagonal data inconsistent (" << i << "," << j << ")" << endl << endl;
				dist = 0;
			}

			city_distance[i][j] = dist;
			matrix[i][j] = dist;
			if (dist > dist_max)
				dist_max = dist;
		}

	file_in.close();


	//system("PAUSE");
	return(0);
}
