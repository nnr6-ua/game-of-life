#include "../lib/cell_t.hpp"
#include "../lib/board_t.hpp"

#include <cstdlib>
#include <fstream>
#include <ctime>
#include <iostream>

using namespace std;

/* Función que comprueba que la opción introducida por teclado es correcta */
void opc_corr (int &opc){
	while (cin.fail()){
		cin.clear();
		cin.ignore(99, '\n');
		cout << "Enter a valid option: ";
		cin >> opc;
	}
}


/* Función que pide los datos del tablero por teclado */
void manual_input (board_t &game){
	int row = 0;
	int col = 0;
	int n_cells = -1;

	/* Se pide las dimensiones del tablero por teclado */
	cout << "Enter the board dimensions:" << endl;
	while ((row*col)<1){
		cout << "Number of rows: ";
		cin >> row;
		opc_corr(row);
		cout << "Number of columns: ";
		cin >> col;
		opc_corr(col);
		if ((row*col)<1){
			cout << "Insufficient board, there must be at least one cell." << endl;
			cout << "Enter the data again:" << endl;
		}
	}

	/* Se crea un tablero con las dimensiones especificadas */
	game.resize_board(row, col);

	/* Se pide el número de células vivas iniciales por teclado */
	cout << "\nEnter the number of alive cells the starting board will have: ";
	cin >> n_cells;
	opc_corr(n_cells);
	while ((n_cells<0) || (n_cells>(row*col))){
		if (n_cells<0)
			cout << "Insufficient amount!" << endl;
		else
			if (n_cells>(row*col))
				cout << "Insufficient board for too many cells!" << endl;
		cout << "Enter the alive cells amount again: ";
		cin >> n_cells;
		opc_corr(n_cells);
	}

	if (n_cells>0){  /* Si se va a introducir alguna célula viva... */
		int m;
		int n;
		cout << "\nEnter the initial alive cells coordinates:" << endl;
		for (int i=1; i<=n_cells; i++){
			bool dead_cell = true;
			while (dead_cell){
				cout << "\nCell " << i << ":" << endl;
				cout << "Row: ";
				cin >> m;
				opc_corr(m);
				while ((m<0) || (m>=row)){
					cout << "Row out of range\nEnter a valid row number: ";
					cin >> m;
					opc_corr(m);
				}
				cout << "Column: ";
				cin >> n;
				opc_corr(n);
				while ((n<0) || (n>=col)){
					cout << "Column out of range\nEnter a valid column number: ";
					cin >> n;
					opc_corr(n);
				}
				if (game.alive_cell(m, n)){
					cout << "Cell already alive!" << endl;
					cout << "Enter the initial alive cells coordinates again:" << endl;
				}
				else{
					game.set_cell_alive(m, n);
					dead_cell = false;
				}
			}
		}
	}
}


int main (int argc, char *argv[])
{
	system("cls");
	cout << "Welcome to The Game of Life (Benchmark mode).\n" << endl;

	if (argc > 1) {  /* Si se ejecuta el programa con archivos por parámetro */
		
		for (int f = 1; f < argc; f++) {
			cout << "=================================================" << endl;
			cout << " EVALUANDO ARCHIVO: " << argv[f] << endl;
			cout << "=================================================" << endl;

			double suma_tiempos = 0.0; /* Variable para acumular los tiempos de las 3 ejecuciones */

			for (int run = 1; run <= 3; run++) {
				board_t game;
				ifstream fi;
				fi.open(argv[f]);

				if (!fi) {
					cerr << "Error opening the file " << argv[f] << ".\n" << endl;
					break; 
				}
				
				int row, col, n_cells, m, n;

				/* Se leen los datos del fichero abierto */
				fi >> row;
				fi >> col;

				game.resize_board(row, col);

				fi >> n_cells;

				for (int i = 0; i < n_cells; i++) {
					fi >> m;
					fi >> n;
					game.set_cell_alive(m, n);
				}
				fi.close();

				clock_t inicio = clock();
				
				game.game_of_life(); /* El write ya está comentado en la clase, así que esto volará */
				
				clock_t fin = clock(); 
				double tiempo = static_cast<double>(fin - inicio) / CLOCKS_PER_SEC;
				
				suma_tiempos += tiempo; /* Sumamos el tiempo obtenido al total de este archivo */

				cout << " - Partida " << run << ": " << tiempo << " segundos." << endl;
			}
			
			/* Terminadas las 3 partidas, calculamos y mostramos la media */
			double media = suma_tiempos / 3.0;
			cout << "\n>>> TIEMPO MEDIO PARA " << argv[f] << ": " << media << " segundos <<<\n\n" << endl;
		}
	}
	else {  /* Si no se ejecuta el programa con parámetros, se pide los datos por teclado */
		board_t game;
		manual_input(game);
		
		clock_t inicio = clock();
		game.game_of_life(); 
		clock_t fin = clock(); 

		double tiempo = static_cast<double>(fin - inicio) / CLOCKS_PER_SEC;
		cout << "\nEl programa ha tardado: " << tiempo << " segundos." << endl; 
	}

	return 0;
}
