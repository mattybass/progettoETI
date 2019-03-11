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
    p.stampaFile_angolo(3, "angolo3");
    p.mediamobile_angolo(3, 30);
    p.mediamobile_angolo(3, 30);
    p.mediamobile_angolo(3, 30);
    p.stampaFile_angolo(3, "elab");
    p.stampaFile_coordinate(4, "coordinata4", "matlab");
    p.stampaFile_coordinate(3, "coordinata3", "matlab");
    p.stampaFile_coordinate(2, "coordinata2", "matlab");
    
	return 0;
}
