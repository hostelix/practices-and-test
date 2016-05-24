#include <iostream>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

#define MAX 8

#define VACIO 0
#define PEON 1
#define REINA 2
#define REY 3
#define ALFIL 4
#define TORRE 5
#define CABALLO 6

#define PIEZA_PEON "[P]"
#define PIEZA_REINA "[R]"
#define PIEZA_REY "[K]"
#define PIEZA_ALFIL "[A]"
#define PIEZA_TORRE "[T]"
#define PIEZA_CABALLO "[C]"

#define COLOR_ROJO     91
#define COLOR_VERDE    92

#define COLOR_JUGADOR_A COLOR_ROJO
#define COLOR_JUGADOR_B COLOR_VERDE


#define IMPRIME_COLOR_PIEZA(color, texto) printf("\x1b[%dm%s\x1b[0m",color, texto)


typedef struct{
	int pieza; // Numero de la pieza identidificada en las constantes simbolicas
	int color_pieza; //Numero del color identificada en las contantes simbolicas
}Pieza;

typedef struct {
	Pieza tabla[MAX][MAX];
}Tablero;

typedef struct {
	int x;
	int y;
}Posicion;


void senal_terminar_programa(int senal)
{
	if (senal == SIGINT){
		cout << endl << "Se presiono CTRL + C Saliendo del programa . . . ." << endl;
		exit(EXIT_SUCCESS);
	}
}

void llenar_tablero(Tablero *tablero_ajedrez){
	for(int fila = 0; fila < MAX; fila++){
		for(int colum = 0; colum < MAX; colum++){
			//Peones
			if(fila == 1){
				tablero_ajedrez->tabla[fila][colum].pieza = PEON;
				tablero_ajedrez->tabla[fila][colum].color_pieza = COLOR_JUGADOR_A;
			}
			else if(fila == 6){
				tablero_ajedrez->tabla[fila][colum].pieza = PEON;
				tablero_ajedrez->tabla[fila][colum].color_pieza = COLOR_JUGADOR_B;
			}
			//Torres
			else if((fila == 0 && colum == 0) || (fila == 0 && colum == 7)){
				tablero_ajedrez->tabla[fila][colum].pieza = TORRE;
				tablero_ajedrez->tabla[fila][colum].color_pieza = COLOR_JUGADOR_A;
			}
			else if((fila == 7 && colum == 0)|| (fila == 7 && colum == 7)){
				tablero_ajedrez->tabla[fila][colum].pieza = TORRE;
				tablero_ajedrez->tabla[fila][colum].color_pieza = COLOR_JUGADOR_B;
			}
			//Caballos
			else if((fila == 0 && colum == 1) || (fila == 0 && colum == 6)){
				tablero_ajedrez->tabla[fila][colum].pieza = CABALLO;
				tablero_ajedrez->tabla[fila][colum].color_pieza = COLOR_JUGADOR_A;
			}
			else if((fila == 7 && colum == 1) || (fila == 7 && colum == 6)){
				tablero_ajedrez->tabla[fila][colum].pieza = CABALLO;
				tablero_ajedrez->tabla[fila][colum].color_pieza = COLOR_JUGADOR_B;
			}
			//Alfiles
			else if((fila == 0 && colum == 2) || (fila == 0 && colum == 5)){
				tablero_ajedrez->tabla[fila][colum].pieza = ALFIL;
				tablero_ajedrez->tabla[fila][colum].color_pieza = COLOR_JUGADOR_A;
			}
			else if((fila == 7 && colum == 2) || (fila == 7 && colum == 5)){
				tablero_ajedrez->tabla[fila][colum].pieza = ALFIL;
				tablero_ajedrez->tabla[fila][colum].color_pieza = COLOR_JUGADOR_B;
			}
			//Reina
			else if((fila == 0 && colum == 3)){
				tablero_ajedrez->tabla[fila][colum].pieza = REINA;
				tablero_ajedrez->tabla[fila][colum].color_pieza = COLOR_JUGADOR_A;
				
			}
			else if((fila == 7 && colum == 3)){
				tablero_ajedrez->tabla[fila][colum].pieza = REINA;
				tablero_ajedrez->tabla[fila][colum].color_pieza = COLOR_JUGADOR_B;
			}
			//Rey
			else if((fila == 0 && colum == 4)){
				tablero_ajedrez->tabla[fila][colum].pieza = REY;
				tablero_ajedrez->tabla[fila][colum].color_pieza = COLOR_JUGADOR_A;
			}
			else if((fila == 7 && colum == 4)){
				tablero_ajedrez->tabla[fila][colum].pieza = REY;
				tablero_ajedrez->tabla[fila][colum].color_pieza = COLOR_JUGADOR_B;
			}
			else{
				tablero_ajedrez->tabla[fila][colum].pieza = VACIO;
			}
		}
	}
}
void mostrar_tablero(Tablero *tablero_ajedrez){
	
	cout << "  "; for(int i=0; i<MAX; i++){ cout << " " << i+1 << " " ;} cout << endl; // Para imprimir los numeros indicadores arriba del tablero
	
	for(int fila = 0; fila < MAX; fila++){
		
		cout << fila+1 << " "; // Para imprimir los numero indicadores del lado izquierdo del tablero
		
		for(int colum = 0; colum < MAX; colum++){
			switch(tablero_ajedrez->tabla[fila][colum].pieza){
				case PEON:
					IMPRIME_COLOR_PIEZA(tablero_ajedrez->tabla[fila][colum].color_pieza,PIEZA_PEON);
					break;	
				case REINA:
					IMPRIME_COLOR_PIEZA(tablero_ajedrez->tabla[fila][colum].color_pieza,PIEZA_REINA);
					break;
				case REY:
					IMPRIME_COLOR_PIEZA(tablero_ajedrez->tabla[fila][colum].color_pieza,PIEZA_REY);
					break;
				case TORRE:
					IMPRIME_COLOR_PIEZA(tablero_ajedrez->tabla[fila][colum].color_pieza,PIEZA_TORRE);
					break;
				case ALFIL:
					IMPRIME_COLOR_PIEZA(tablero_ajedrez->tabla[fila][colum].color_pieza,PIEZA_ALFIL);
					break;
				case CABALLO:
					IMPRIME_COLOR_PIEZA(tablero_ajedrez->tabla[fila][colum].color_pieza,PIEZA_CABALLO);
					break;
				default:
					cout << "[ ]";
					break;
			}
		}
		cout << endl;
	}
}

void cambio_piezas(Tablero *tablero_ajedrez,Posicion origen, Posicion destino){
	Pieza tmp;
	tmp = tablero_ajedrez->tabla[origen.x][origen.y];
	tablero_ajedrez->tabla[origen.x][origen.y] = tablero_ajedrez->tabla[destino.x][destino.y];
	tablero_ajedrez->tabla[destino.x][destino.y] = tmp;
}

void mover_pieza(Tablero *tablero_ajedrez,Posicion origen, Posicion destino){
	cambio_piezas(tablero_ajedrez,origen,destino);
}

Posicion leer_posicion(){
	Posicion tmp;
	do{
		cout << "Introduzca la fila >"; cin >> tmp.x;
		cout << "Introduzca la columna >"; cin >> tmp.y;
		
		tmp.x = tmp.x - 1; //REstandole -1 porque en el tablero que se muestra las posiciones comienzan en 1
		tmp.y = tmp.y - 1; //REstandole -1 porque en el tablero que se muestra las posiciones comienzan en 1
		
		if(!(tmp.x < MAX && tmp.x >= 0) && !(tmp.y < MAX && tmp.y >= 0)){
			cout << "Error, Intente nuevamente" << endl;
		}
	}while(!(tmp.x < MAX && tmp.x >= 0) && !(tmp.y < MAX && tmp.y >= 0));
	
	return tmp;
}

void pausar(const char *mensaje){
	setbuf(stdin, NULL);
	cout << mensaje << endl;
	getchar();
}



int main()
{
	Tablero *tablero_juego = new Tablero;
	int opcion;
	bool salir = false;
	Posicion posicion_origen_mover, posicion_destino_mover;
	
	llenar_tablero(tablero_juego); // iniciamos el tablero
	
	cout << "Bienvenido al juego de ajedrez" << endl << endl;
	cout << "1)Comenzar a jugar" << endl;
	cout << "2)Ver puntajes" << endl;
	cout << "3)Intrucciones" << endl;
	cout << "4)Salir" << endl;
	cout << ">"; cin >> opcion;
	
	do{
		switch(opcion){
			
			case 1:{
				
				//Se llama la funcion signal que escuchara el SIGINT
				signal(SIGINT, senal_terminar_programa);
				
				mostrar_tablero(tablero_juego); //Mostramos el tablero de juego
				
				//Bucle infinito para la senal
				while(1){
					do{
						system("clear");
						cout << "---------------------------------------------------------------" << endl;
						cout << "# # # # # # # #  PRESIONE CTRL + C PARA SALIR # # # # # # # # " << endl;
						cout << "---------------------------------------------------------------" << endl;
						
						mostrar_tablero(tablero_juego);//Mostramos el tablero
						
						cout << "Introduce la posicion de la pieza que desea mover" << endl;
						posicion_origen_mover = leer_posicion();
						
						cout << "Introduce la posicion a donde movera la pieza" << endl;
						posicion_destino_mover = leer_posicion();
						
						//Movemos la pieza a la posicion
						mover_pieza(tablero_juego, posicion_origen_mover, posicion_destino_mover);
						
						
					}while(true);
				}
				break;
			};
			case 4:
				salir = true;
				break;
			default:
				cout << "Opcion invalida intente nuevamente" << endl;
				break;
		}
	} while(!salir);

	
	return 0;
}