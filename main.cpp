#include <iostream>
#include <cmath>
#include "coordinata.h"
#include "angolo.h"
#include "utility.h"
#include "persona.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */



int main(int argc, char** argv) {
    Persona p("spallagomitoModello.json");
	p.stampa_max(1);
	p.stampa_max(2);
	p.stampa_max(3);
	p.stampa_max(4);
	p.stampa_max(5);
	cout << endl;
	p.stampa_angoli(2);
	return 0;
}
