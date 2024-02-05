#include <iostream>
#include <iterator>
#include <array>
#include <cassert>
#include <exception>

using namespace std;

struct Organizator
{
	char nazwa[200];
};
enum TypWycieczki
{
	turystyczna=0, klasowa=1, edukacyjna=2
};

struct Wycieczka
{
	char miesceDocelowe[100];
	double cena;
	TypWycieczki typ; // 0 - turystyczna, 1 - klasowa, 2 - edukacyjna
	Organizator* organizator;
};

void wczytajWycieczke(Wycieczka& wycieczka)
{
	cout << "pobieranie danych wycieczki:" << endl;
	
	cout << "podaj miejscie docelowe:";
	cin >> wycieczka.miesceDocelowe;

	cout << "podaj cene :";
	cin >> wycieczka.cena;

	
	int typ;
	do {
		cout << "wybierz typ wycieczki:" << endl;
		cout << "0 - turystyczna" << endl;
		cout << "1 - klasowa" << endl;
		cout << "2 - edukacyjna" << endl;
		cin >> typ;
		if (typ < 0 || 2 < typ)
		{
			cout << "wybrano nie prawidlowy typ wycieeczki." << endl;
		}
	} while (typ < 0 || 2 < typ);
	



	wycieczka.typ = (TypWycieczki)typ;
	cout << "podaj organizatora wycieczki:";
	cin >> wycieczka.organizator->nazwa;
}
void wypiszWycieczke(Wycieczka wycieczka)
{
	cout << "miejsce docelowe:" << wycieczka.miesceDocelowe;
	cout << " cena: " << wycieczka.cena;
	cout << " typ wycieczki:";
	switch (wycieczka.typ)
	{
	case turystyczna:
		cout << "turystyczna";
		break;
	case klasowa:
		cout << "klasowa";
		break;
	case edukacyjna:
		cout << "edukacyjna";
		break;
	}
	
	
	cout << " organizator:" << wycieczka.organizator->nazwa << endl;



}


Organizator* najtanszaTypu(Wycieczka dane[],int iloscElementow, TypWycieczki typ)
// Funkcja ma przyjać tablicę wszytskich wycieczek i typ wycieczki
// a następnie znaleźć i zwrócić nazwę orgaizatora najtanszej
// wycieczki tego typu)
{
	assert(iloscElementow > 0);

	int najtansza;
	Organizator* organizator = NULL;
	for (int i = 0; i < iloscElementow; i++)
	{
		if (dane[i].typ == typ)
		{
			if (organizator == NULL)
			{
				najtansza = dane[i].cena;
				organizator = dane[i].organizator;
			}
			else if (dane[i].cena < najtansza)
			{
				najtansza = dane[i].cena;
				organizator = dane[i].organizator;
			}
		}
	}
	if (organizator == NULL)
	{
		throw logic_error("nie znaleziono ogranizatora");
	}

	return organizator;
}

void test_najtanszaTypu_1_wyrzucenie_wyjatku()
{
	//1. przygotowanie danych testowych
	cout << "test_najtanszaTypu_1_wyrzucenie_wyjatku " << endl;

	Organizator organizator1{ "A-Z Podroze" };
	Organizator organizator2{ "Histora i Pamiec" };
	Organizator organizator3{ "Szokla w plenerze" };

	Wycieczka wycieczki[] =
	{
		{"Bieszczady",2000.0,TypWycieczki::turystyczna,&organizator1},
		{"Oswiecim",1000,TypWycieczki::edukacyjna,&organizator2},
		{"Szczyrk",1500,TypWycieczki::edukacyjna,&organizator3},
		// dodaj jeszcze prznajmniej 4 instancje
	};

	wczytajWycieczke(wycieczki[0]);

	int iloscElementow = 3;
	string komunikatOczekiwany = "nie znaleziono ogranizatora";

	try {
		//2. Wywołanie testowanej funkcji
		najtanszaTypu(wycieczki, iloscElementow, TypWycieczki::klasowa);
		//3 Weryfikacja poprawnisi i raport
		cout << "FAIL!\n";
	}
	catch (logic_error e)
	{
		//3 Weryfikacja poprawnisi i raport
		string komunikatFaktyczny(e.what());
		if (komunikatOczekiwany == komunikatFaktyczny)
		{
			cout << "OK!\n";
		}
		else
		{
			cout << "FAIL!\n";
		}
	}

}
void test_najtanszaTypu_2_znalezienie_najtanszego_organizatora()
{
	//1. przygotowanie danych testowych
	cout << "test_najtanszaTypu_2_znalezienie_najtanszego_organizatora " << endl;

	Organizator organizator1{ "A-Z Podroze" };
	Organizator organizator2{ "Histora i Pamiec" };
	Organizator organizator3{ "Szokla w plenerze" };

	Wycieczka wycieczki[] =
	{
		{"Bieszczady",2000.0,TypWycieczki::turystyczna,&organizator1},
		{"Oswiecim",1000,TypWycieczki::edukacyjna,&organizator2},
		{"Szczyrk",1500,TypWycieczki::edukacyjna,&organizator3},
		// dodaj jeszcze prznajmniej 4 instancje
	};
	int iloscElementow = 3;
	string oczekiwanaNazwaOranizatora = "Histora i Pamiec";

	try {
		//2. Wywołanie testowanej funkcji
		Organizator* organizator = najtanszaTypu(wycieczki, iloscElementow, TypWycieczki::edukacyjna);
		
		//3 Weryfikacja poprawnisi i raport
		if (oczekiwanaNazwaOranizatora == organizator->nazwa)
		{
			cout << "OK!\n";
		}
		else
		{
			cout << "FAIL!\n";
		}
	}
	catch (logic_error e)
	{
		//3 Weryfikacja poprawnisi i raport
		cout << "FAIL!\n";
		
	}
}

int main()
{
	Organizator organizator1{ "A-Z Podroze"};
	Organizator organizator2{ "Histora i Pamiec" };
	Organizator organizator3{ "Szokla w plenerze" };

	Wycieczka wycieczki[] =
	{
		{"Bieszczady",2000.0,TypWycieczki::turystyczna,&organizator1},
		{"Oswiecim",1000,TypWycieczki::edukacyjna,&organizator2},
		{"Szczyrk",1500,TypWycieczki::klasowa,&organizator3},
		// dodaj jeszcze prznajmniej 4 instancje
	};

	int iloscWycieczek = 3;

	for (int i = 0; i<iloscWycieczek; i++)
	{
		wypiszWycieczke(wycieczki[i]);
	}
	//TypWycieczki typ = TypWycieczki::klasowa; 
	try {
		Organizator* o = najtanszaTypu(wycieczki, iloscWycieczek, TypWycieczki::klasowa);
		cout << "najtanczy organizator wycieczki klasowej to:" << o->nazwa << endl;
	}
	catch (logic_error e)
	{
		cout << e.what() << endl;;
	}
	//najtanszaTypu(dane, TypWycieczki::klasowa); //


	test_najtanszaTypu_1_wyrzucenie_wyjatku();
	test_najtanszaTypu_2_znalezienie_najtanszego_organizatora();
}