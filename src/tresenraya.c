/*
 * tresenraya.c
 *
 *  Created on: Nov 27, 2024
 *      Author: Gabriel Morejón
 *
 *      Juego de tres en raya
 */

//1
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#ifdef __linux__
#include <unistd.h>
#elif
#include<windows.h>
#endif

// Variables globales - 2
char tablero[3][3]; // Matriz para la gestión del tablero
const char jugador = 'X'; // Elemento del jugador
const char computadora = 'O';

void menu();
void jugarTER();
void instrucciones();
void acercaDe();

// 8
void imprimirTablero();
// 9
void limpiarTablero();
int revisarEspaciosLibres();
void movJugador();
void movComputadora();

// 10
char revisarGanador();
void mostrarGanador(char);



// 3
void menu() {
	#ifdef __linux__
		printf("\e[1;1H\e[2J");
	#elif __WIN32__
		system("cls");
	#endif

	int opcion=-1;

	while (opcion != 4) {
		printf("\n\t\t*************************\n");
		printf("\t\t* JUEGO DE TRES EN RAYA *\t\t\n");
		printf("\t\t*************************");
		printf("\n1. Jugar.");
		printf("\n2. Instrucciones.");
		printf("\n3. Acerca de.");
		printf("\n4. Salir.");
		printf("\nEscoja una opción: ");
		scanf("%d", &opcion);

		switch (opcion) {
		case 1: {
			jugarTER();
			break;
		}
		case 2: {
			instrucciones();
			sleep(2);

			break;
		}
		case 3: {
			acercaDe();
			sleep(2);
			break;
		}
		case 4: {
			printf("\nAdiós...\n");
			sleep(1);
			break;
		}

		default:
			printf("\nOpción incorrecta.");
			break;
		}

	}


}

// 5
void instrucciones() {
	printf("\nInstrucciones:\n");
	printf("\nJUGADOR (Humano): X");
	printf("\nOPONENTE (Computadora): O\n");
	printf("\nRegresando al menú anterior en breve...");
	//getchar();

}


// 6
void acercaDe() {
	// 15
	#ifdef __linux__ // Para validar el SO
		printf("\n\t\tEstás usando GNU/Linux.");
	#elif __WIN32__
		printf("\n\t\tEstás usando Windows.");
	#elif __APPLE__
		printf("\n\t\tEstás usando algo de Apple.");
	#elif __unix__
		printf("\n\t\tEstás usando algún Unix.");
	#endif
	printf("\nJuego de Tres En Raya\n");
	printf("\nFundamentos de Programación");
	printf("\nProfesor: Gabriel Morejón López");
	printf("\nSemestre: 2024-S2");
	printf("\nRegresando al menú anterior en breve...");
	//printf("\nPresione una tecla...\n");
	//getchar();
}

// 4

void jugarTER() {

	char ganador = ' ';
	// 9
	limpiarTablero();
	while (ganador == ' ' && revisarEspaciosLibres() != 0) {
		imprimirTablero();

		movJugador();
		ganador = revisarGanador();

		if (ganador != ' ' || revisarEspaciosLibres() == 0) {
			break; // Sale si el juego se termina
		}

		movComputadora();
		ganador = revisarGanador();

		if (ganador != ' ' || revisarEspaciosLibres() == 0) {
			break; // Sale si el juego se termina
		}
	}

	imprimirTablero();
	mostrarGanador(ganador);


}

// 9
int revisarEspaciosLibres() {
	int libres = 9;

	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			if (tablero[i][j] != ' ') {
				libres--; // Se reduce por cada espacio ocupado.
			}
		}
	}
	return libres;
}

// 10
void movJugador() {
	int x, y;

	do {
		printf("\nIngrese una fila: (1-3): ");
		scanf("%d", &x);
		x--;
		printf("\nIngrese una columna: (1-3): ");
		scanf("%d", &y);
		y--;
		printf("\n");

		if (tablero[x][y] != ' ') {
			printf("Movimiento inválido, reintenta.\n");
			printf("\n");
		} else {
			tablero[x][y] = jugador;
			break;
		}

	} while (tablero[x][y] != ' ');

}

// 12
void movComputadora() {
	srand(time(NULL)); // Genera un número aleatorio
	int x, y;

	if (revisarEspaciosLibres() > 0) {
		do {
			x = rand() % 3;
			y = rand() % 3; // Genera números aleatorios de 3 en 3, para x e y.
		} while(tablero[x][y] != ' ');

		tablero[x][y] = computadora;
	}
}

// 13
char revisarGanador() {
	// Revisar filas
	for (int i=0; i<3; i++) {
		if (tablero[i][0] == tablero[i][1] && tablero[i][0] == tablero[i][2]) {
			return tablero[i][0];
		}
	}

	// Revisar columnas
	for (int i=0; i<3; i++) {
		if (tablero[0][i] == tablero[1][i] && tablero[0][i] == tablero[2][i]) {
			return tablero[0][i];
		}
	}

	// Diagonales
	if (tablero[0][0] == tablero[1][1] && tablero[0][0] == tablero[2][2]) {
		return tablero[0][0];
	}

	if (tablero[0][2] == tablero[1][1] && tablero[0][2] == tablero[2][0]) {
		return tablero[0][2];
	}

	return ' '; // En caso de no haber ganador
}

// 11
void limpiarTablero() {
	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			tablero[i][j] = ' ';
		}
	}
}

//14
void mostrarGanador(char ganador) {
	if (ganador == jugador) {
		printf("\n\t\t --- Juego terminado ---\n");
		printf("\t*** FELICIDADES, ¡¡¡Ganaste!!! ***\n");
		printf("\t\tGracias por jugar.\n");
	} else if (ganador == computadora) {
		printf("\n\t\t --- Juego terminado ---\n");
		printf("\t*** Lo siento, ¡¡¡Perdiste!!! ***\n");
		printf("\t\tGracias por jugar.\n");
	} else {
		printf("\n\t\t --- Juego terminado ---\n");
		printf("\t*** Empataron ***\n");
		printf("\t\tGracias por jugar.\n");
	}
}

// 7
void imprimirTablero() {

	printf(" %c | %c | %c \n", tablero[0][0], tablero[0][1], tablero[0][2]);
	printf("---|---|---\n");
	printf(" %c | %c | %c \n", tablero[1][0], tablero[1][1], tablero[1][2]);
	printf("---|---|---\n");
	printf(" %c | %c | %c \n", tablero[2][0], tablero[2][1], tablero[2][2]);
	printf("\n\n");

}

// 1
int main() {

	//1 printf("Juego de tres en raya");
	menu();
	return 0;
}

