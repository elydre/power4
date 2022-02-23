/*|~|--|~|--|~|--|~|--|~|--|~|--

██  ████        ██████        ██
████    ██     ██           ████
██      ██   ████████     ██  ██
████████       ██       ██    ██
██             ██       █████████
██             ██             ██
██
 - codé en : UTF-8
 - langage : python 3
 - GitHub  : github.com/pf4-DEV
--|~|--|~|--|~|--|~|--|~|--|~|*/

#include <iostream>

// pour le sleep
#include <chrono>
#include <thread>



// macro pour remonter une ligne et effacer
#define UP "\033[F"
#define CLEAR "\033[K"

using namespace std;

int grille[8][8] = {0};

char get_piont(int num) {
	if (num == 1) {
		return '@';
	}
	if (num == 2) {
		return 'X';
	}
	return ' ';
}

void print_grille() {
	cout << "   1   2   3   4   5   6   7   8\n\n";

	for (int l = 0; l < 8; l++) {
		for (int c = 0; c < 8; c++) {
			cout << " | " << get_piont(grille[c][l]);
		}
		cout << " |" << endl;
	}
	cout << endl;
}

void clear_all() {
	for (int x = 0; x < 14; x++) {
		cout << UP << CLEAR;
	}
}

int get_user_choix() {
	int inp;

	clear_all();
	print_grille();

	cout << "SAISIR LA COLONNE -> ";
	while (1) {
		cin >> inp;
		cin.ignore();

		inp--;

		clear_all();
		print_grille();

		if (inp < 8 && inp >= 0 && grille[inp][0] == 0) {
			cout << "DONE!";
			return inp;
		}
		else {
			cout << "CASE NON VALIDE! -> ";
		}
	}
}

void chute(int colonne) {

	for (int l = 0; l < 7; l++) {
		if (grille[colonne][l] > 0 && grille[colonne][l + 1] == 0) {
			grille[colonne][l + 1] = grille[colonne][l];
			grille[colonne][l] = 0;
			clear_all();
			print_grille();
			this_thread::sleep_for(chrono::milliseconds(100));
		}
		else {
			break;
		}
	}
}

int main() {
	bool fin = 0;
	bool tour = 0;
	int colonne;

	while (!fin) {
		print_grille();
		colonne = get_user_choix();
		
		grille[colonne][0] = tour + 1;
		
		chute(colonne);
		
		clear_all();

		tour = !tour;
	}
}