/*|~|--|~|--|~|--|~|--|~|--|~|--

██  ████        ██████        ██
████    ██     ██           ████
██      ██   ████████     ██  ██
████████       ██       ██    ██
██             ██       █████████
██             ██             ██
██
 - codé en : UTF-8
 - langage : c++
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

int grille[8][8] = { 0 };

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

int check_eg(int v1, int v2, int v3, int v4) {
	if (v1 == v2 && v1 == v3 && v1 == v4) {
		return v1;
	}
	return 0;
}

int is_gagnant(int tab[8][8]) {
	for (int c = 0; c < 8; c++) {
		for (int l = 0; l < 5; l++) {
			if (check_eg(tab[c][l], tab[c][l + 1], tab[c][l + 2], tab[c][l + 3]) > 0) {
				return 1;
			}
			if (check_eg(tab[l][c], tab[l + 1][c], tab[l + 2][c], tab[l + 3][c]) > 0) {
				return 2;
			}
		}
	}
	return 0;
}

int start_ia() {
	// TODO
	// duplication de grille dans temp
	int temp[8][8] = { 0 };
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			temp[i][j] = grille[i][j];
		}
	}

	return 0;
}

int main() {
	bool tour = 0;
	int colonne;

	while (1) {
		print_grille();
		colonne = get_user_choix();

		grille[colonne][0] = tour + 1;

		chute(colonne);

		clear_all();

		if (is_gagnant(grille) > 0) {
			break;
		}

		tour = !tour;
	}
	cout << "Bravo joueur " << get_piont(tour + 1) << " vous avec gagner avec une ";
	if (is_gagnant(grille) == 1) {
		cout << "colonne!\n";
	}
	else if (is_gagnant(grille) == 2) {
		cout << "ligne!\n";
	}
}