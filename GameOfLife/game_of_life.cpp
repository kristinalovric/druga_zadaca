#include "game_of_life.h"

// private
bool game_of_life::slucajna_vrijednost()
{
	return rand25();
}

bool game_of_life::celija_zauzeta(int i, int j)
{
	return false;
}

// vraca 0 ili 1 s 50% vjerojatnosti
int game_of_life::rand50()
{
	return rand() & 1;
}

// vraca 1 s 25% vjerojatnosti, jer f-ja AND samo u 1 od 4 slucaja vraca 1
int game_of_life::rand25()
{
	return rand50() & rand50();
}

void game_of_life::prva_generacija()
{
	for (int i = 0; i < REDAKA; i++)
	{
		for (int j = 0; j < STUPACA; j++)
		{
			_generacija[i][j] = slucajna_vrijednost();
		}
	}
}

int game_of_life::broj_susjeda(int i, int j)
{
	int broj_susjeda = 0;

	int stupac_lijevo = j - 1;
	int stupac_desno = j + 1;
	int redak_iznad = i + 1;
	int redak_ispod = i - 1;
	
	// redak iznad: redak_iznad
	if (redak_iznad >= 0)
	{
		// stupac lijevo
		if (stupac_lijevo >= 0 && _generacija[redak_iznad][stupac_lijevo])
			broj_susjeda++;

		// isti stupac
		if (_generacija[redak_iznad][j])
			broj_susjeda++;

		// stupac desno
		if (stupac_desno < STUPACA && _generacija[redak_iznad][stupac_desno])
			broj_susjeda++;
	}

	// isti redak: i
	// stupac lijevo
	if (stupac_lijevo >= 0 && _generacija[i][stupac_lijevo])
		broj_susjeda++;

	// stupac desno
	if (stupac_desno < STUPACA && _generacija[i][stupac_desno])
		broj_susjeda++;

	// redak ispod: redak_ispod
	if (redak_ispod < REDAKA)
	{
		// stupac lijevo
		if (stupac_lijevo >= 0 && _generacija[redak_ispod][stupac_lijevo])
			broj_susjeda++;

		// isti stupac
		if (_generacija[redak_ispod][j])
			broj_susjeda++;

		// stupac desno
		if (stupac_desno < STUPACA && _generacija[redak_ispod][stupac_desno])
			broj_susjeda++;
	}

	return broj_susjeda;
}

// public
game_of_life::game_of_life()
{
	//inicijalizira random num. generator
	srand(time(NULL));
	prva_generacija();
}

void game_of_life::sljedeca_generacija()
{
	// organizam odumire jer je br. susjeda < 2 ili > 3
	for (int i = 0; i < REDAKA; i++)
	{
		for (int j = 0; j < STUPACA; j++)
		{
			int susjedi = broj_susjeda(i, j);
			if (susjedi < 2 || susjedi > 3)
			{
				_sljedeca_generacija[i][j] = false;
			}
		}
	}

	// novi organizam u praznoj celiji
	for (int i = 0; i < REDAKA; i++)
	{
		for (int j = 0; j < STUPACA; j++)
		{
			if (!_generacija[i][j])
			{ 
				int susjedi = broj_susjeda(i, j);
				if (susjedi == 3)
				{
					_sljedeca_generacija[i][j] = true;
				}
			}
		}
	}

	// kopiraj _sljedeca_generacija u _generacija
	for (int i = 0; i < REDAKA; i++)
	{
		for (int j = 0; j < STUPACA; j++)
		{
			_generacija[i][j] = _sljedeca_generacija[i][j];
		}
	}
}

void game_of_life::iscrtaj()
{
	// obrisi konzolu
	system("cls");

	for (int i = 0; i < REDAKA; i++)
	{
		for (int j = 0; j < STUPACA; j++)
		{
			if (_generacija[i][j])
			{
				cout << '*';
			}
			else
			{
				cout << '-';
			}
		}
		cout << endl;
	}
}
