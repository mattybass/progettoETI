#include <iostream>
#include <cmath>
#include "coordinata.h"
#include "angolo.h"
#include "utility.h"
#include "persona.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */



int main(int argc, char** argv) {
	/*
	Coordinata B(0,0,0);
	Coordinata A(9,4,0);
	Coordinata C(-2,4,0);
	double differenza=angolo_azimut(A,B,C);
	cout<<differenza;*/
	Persona p("spallagomitoModello.json");
	cout << p;
	return 0;
}
