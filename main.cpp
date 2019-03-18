#include <iostream>
#include <cmath>
#include "coordinata.h"
#include "angolo.h"
#include "utility.h"
#include "persona.h"
#include "valutazione.h"


int main(int argc, char** argv) {
	
    Persona p(60,"modellomattyspalla.json");
	p.processa_angolo(2);
	Persona p2(60,"B2movim.json");
	p2.processa_angolo(2);
	Valutazione v(&p2, &p);
	v.insert_angolidiscriminati_zenit(2);
	v.valutaSingleJoint(2);
	v.valutaRelationJoint(2);
	v.stampavalutazione();
	system("PAUSE");

    return 0;
}
