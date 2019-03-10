#include <iostream>
#include <cmath>
#include "coordinata.h"
#include "angolo.h"
#include "utility.h"
#include "persona.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */



int main(int argc, char** argv) {
    Persona p("spallagomitoModello60fps.json");	
    p.stampaFile_angolo(2, "angolo2");
    p.stampaFile_coordinate(6, "joint3");
/*
    p.mediamobile_angolo(2, 30);
	p.mediamobile_angolo(2, 30);
	p.maxminFind_angolo(2, 50);
	p.maxminClean_angolo(2);
	p.stampaConsole_maxmin(2);
	p.stampaFile_angolo(2,"modello");

	//p.stampaFile_maxmin(2,"zenit");
	//p.stampaFile_coordinate(2, "coord");

	Coordinata A(-0.394733, 2.531678,  -0.083642);//2
	Coordinata B(-0.153494, 2.559698,-0.197415 );//3
	Coordinata C(0.112958, 2.580957, -0.332918);//4
	cout << angolo_XZ(A, B)<<endl;
	cout << angolo_XZ(C, B)<<endl;
	cout << angolo_zenit(C,B,A) << endl << angolo_azimut(C,B,A);*/


	//Coordinata D(0.071944, 2.463781, -0.384147);//1
	//cout << endl << angolo_azimut(D, A, B);*/
	



	
	//system("PAUSE");

	return 0;
}
