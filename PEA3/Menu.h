#pragma once
#include "stdafx.h"
#include<iostream>
#include<fstream>
#include "genetyczny.h"
#include <string>

class Menu{



public:	Menu(){
	int i, j;
	Genetic p = Genetic();

	cout << "1-Pobirz Plik" << endl;
	cout << "2-czas stopu" << endl;
	cout << "3-wielkosc populacji" << endl;
	cout << "4-wspolczynnik krzyrzowania" << endl;
	cout << "5-wspolczynnik mutacji" << endl;
	cout << "6-wybór metody mutacji" << endl;
	cout << "7-Algorytm genetyczny" << endl;

	while (true){
		cin >> i;
		switch (i)
		{
		case 1:
			cout << "47-ftv47" << endl;
			cout << "170-ftv170" << endl;
			cout << "403-rbg403" << endl;
			cin >> j;
			switch (j)
			{
			case 47:
				p.download("ftv47.atsp");

				break;
			case 170:
				p.download("ftv170.atsp");
				break;
			case 403:
				p.download("rbg403.atsp");
				break;
			default:
				break;
			}

		case 2:

			float w;
			cout << "Podaj czas zatrzymania" << endl;
			cin >> w;
			p.stop = w;

			break;

		case 3:
			cout << "Podaj wielkosc populacji: ";
			cout << p.population << endl;
			cin >> w;
			p.population = w;

			break;

		case 4:
			cout << "Podaj wspó³czynnik krzyrzowania: ";
			cout << p.wspolczynnik_cross << endl;
			cin >> w;
			p.wspolczynnik_cross = w;

			break;

		case 5:
			cout << "Podaj wspó³czynnik mutacji: ";
			cout << p.wspolczynnik_mutation << endl;
			cin >> w;
			p.wspolczynnik_mutation = w;

			break;
		case 6:
			cout << "Wybierz metode mutacji: ";
			int o;
			cout << "1- inverse: ";
			cout << "2- swap: ";
			cin >> o;
			switch (o)
			{
			case 1:
				p.m = 0;
				break;
			case 2:
				p.m = 1;
				break;
			default:
				break;
			}
			break;

		case 7:
			p.geneticAlg();
			cout << "najlepszy koszt " << p.bestCost << endl;
			if (p.size == 48){ cout << "b³ad " << (double(p.bestCost - 1776) /double( 1776)) * 100 << endl; }
			if (p.size == 171){ cout << "b³ad " << (double(p.bestCost - 2755) /double( 2755) )* 100 << endl; }
			if (p.size == 403){ cout << "b³ad " << (double(p.bestCost - 2465) /double( 2465)) * 100 << endl; }

			break;

		}
	}
}
};