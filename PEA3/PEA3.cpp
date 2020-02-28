// PEA3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>;
#include "genetyczny.h"
#include "Menu.h"
#include <ctime>
#include "stdlib.h"
int _tmain(int argc, _TCHAR* argv[])
{
	
	srand(time(0));

	Menu m =  Menu();
	/*Genetic g = Genetic();
	string s = "tsp_10.txt";
	string ss = "rbg403.atsp";
	g.download(ss);
	//g.pobierz(s);
	
	g.stop = 60*6;
	g.population = 10;
		g.geneticAlg();
		cout << g.bestCost << endl;
		cout << double(g.bestCost - 2465) / double(2465) << endl;
		g.geneticAlg();
		cout << g.bestCost << endl;
		cout << double(g.bestCost - 2465) / double(2465) << endl;

		*/
	return 0;
}

