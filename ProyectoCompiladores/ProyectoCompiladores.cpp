#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <cstdio>
#include <string.h>
#include <string>
#include <cctype>
#pragma warning(disable:4996)

#define xx 60
#define KEY_HOME       71

using namespace std;

// FUNCION POCICIONAR CURSOR
void gotoxy(int x, int y)

{
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}

//DEFINIENDO VARIABLES GENERALES


//DEFINIENDO NOMBRE DE ARCHIVOS
string FileSimbolosGramatica = "tablaDeSimbolos.txt";

//ESTRUCTURA TABLA DE SIMBOLOS GRAMATICA
struct Struct_simbolosGramatica {
	int idSimbolo;
	char simbolo[xx];
	char traduccion[xx];
	char categoriaSimbolo[xx];
};


//DECLARANDO FUNCIONES
void init();
void menu();

int func_InsertarSimbolo(int id, string simbolo, string traduccion, string categoria);
 
void func_ingresarSimboloGramatica();
void func_verSimbolos();
int IdSimbolo();

//INICIADOR DE TODO EL FUNCIONAMIENTO
void init() {
	menu();

}


int IdSimbolo() {
	FILE* file = fopen(FileSimbolosGramatica.c_str(), "rb");
	int filas = 0;
	Struct_simbolosGramatica simbolos;
	fread(&simbolos, sizeof(Struct_simbolosGramatica), 1, file);
	while (!feof(file)) {
		fread(&simbolos, sizeof(Struct_simbolosGramatica), 1, file);
		filas += 1;
	}
	fclose(file);
	return filas;

}
//IMGRESANDO SIMBOLOS AL .TXT

void func_ingresarSimboloGramatica() {
	char continuar;
	int id;
 
	string simbolo, traduccion, categoria;

	system("cls");

	id = IdSimbolo() + 1;
	fflush(stdin);

	cout << ("\nIngrese simbolo: ");
	cin >> simbolo;

	cout << ("\nIngrese traduccion: ");
	cin >> traduccion;
	cout << ("\nIngrese categoria: ");
	cin >> categoria;

	int retorno = func_InsertarSimbolo(id, simbolo, traduccion, categoria);

	if (retorno == 1) {
		cout << ("\n\nDatos registrados correctamente") << endl;
	}
	else {
		cout << ("\n\nVaya ha ocurrido un error") << endl;
	}
	cout << ("\n\nDesea agregar otro simbolo[s/n]: ");
	cin >> continuar;
	if (continuar == 's') {
		func_ingresarSimboloGramatica();
	}
	else {
		menu();
	}

	getch();

}


int func_InsertarSimbolo(int id, string simbolo, string traduccion, string categoria) {
	 
	FILE* file = fopen(FileSimbolosGramatica.c_str(), "ab");
	Struct_simbolosGramatica simbolos;


	simbolos.idSimbolo = id;
	strcpy_s(simbolos.simbolo, simbolo.c_str());
	strcpy_s(simbolos.traduccion, traduccion.c_str());
	strcpy_s(simbolos.categoriaSimbolo, categoria.c_str());

	fwrite(&simbolos, sizeof(Struct_simbolosGramatica), 1, file);
	fclose(file);

	return 1;
}

void func_verSimbolos() {
	FILE* file = fopen(FileSimbolosGramatica.c_str(), "rb");
	int  xa = 8, xb = 8, xc = 8, xd = 8, za = 8, zb = 8, zc = 8, zd = 8, ze = 8, zf = 8;

	if (!file) {
		file = fopen(FileSimbolosGramatica.c_str(), "w+b");
	}

	Struct_simbolosGramatica simbolos;
	fread(&simbolos, sizeof(Struct_simbolosGramatica), 1, file);

	gotoxy(30, 2);
	cout << ("*********         T A B L A      D E     S I M B O L O S       *********");
	gotoxy(30, 3);
	cout << ("-----------------------------------------------------------------------\n");
	gotoxy(32, 5);
	cout << ("----------------------------------------------------------------");
	gotoxy(32, 6);
	cout << ("|  ID  | SIMBOLOS|  DEFINICION  |              TIPO            |");
	gotoxy(32, 7);
	cout << ("----------------------------------------------------------------");

	do {

		gotoxy(33, xa++);
		cout << simbolos.idSimbolo; // ID
		gotoxy(40, xb++);
		cout << simbolos.simbolo;   //SIMBOLOS
		gotoxy(50, xc++);
		cout << simbolos.traduccion;  //TRADUCCION
		gotoxy(65, xd++);
		cout << simbolos.categoriaSimbolo; //CATEGORIA
		fread(&simbolos, sizeof(Struct_simbolosGramatica), 1, file); //LEENDO EL ARCHIVO DE TEXTO

		gotoxy(32, za++);
		cout << ("|");

		gotoxy(39, zb++);
		cout << ("|");

		gotoxy(49, zc++);
		cout << ("|");

		gotoxy(64, zd++);
		cout << ("|");

		gotoxy(95, ze++);
		cout << ("|");

	} while (feof(file) == 0);
	cout << ("\n\t\t\t\t----------------------------------------------------------------") << endl;
	cout << endl;
	fclose(file);
	getch();

}

void menu() {
	system("COLOR F0");
	int opcion;

	do {
		system("cls");
		gotoxy(50, 28);
		cout << ("[      3 para salir        ]");
		gotoxy(35, 2);
		cout << ("|**********************************************************|");
		gotoxy(35, 3);
		cout << ("|**      M E N U          D E        O P C I O N E S     **|");
		gotoxy(35, 4);
		cout << ("|**********************************************************|");
		gotoxy(50, 8);
		cout << (" 1. Ingresar Simbolo");
		gotoxy(50, 9);
		cout << (" 2. Ver Simbolos");
		gotoxy(50, 12);
		cout << (" Ingresar opcion: ");
		cin >> opcion;

		switch (opcion) {
		case 1:
			system("cls");
			func_ingresarSimboloGramatica();
			break;
		case 2:
			system("cls");
			func_verSimbolos();
			break;

		}


	} while (opcion != 3);

}

int main() {
	init();

}

 
 