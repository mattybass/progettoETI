#include <iostream>
#include <cmath>
#include "coordinata.h"
#include "angolo.h"
#include "utility.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */



int main(int argc, char** argv) {

	Coordinata B(-10,30,0);
	Coordinata A(-30,10,0);
	Coordinata C(10,20,0);
	double differenza=angolo_azimut(A,B,C);
	cout<<differenza;
	return 0;
}

