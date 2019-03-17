#include <iostream>
#include <cmath>
#include "coordinata.h"
#include "angolo.h"
#include "utility.h"
#include "persona.h"
#include "valutazione.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

/*
Improvements 
Fatta funzione che popola i vettori per quanto riguarda la relazione tra joint. Si era presentato il problema del frame iniziale
che in alcuni casi, nel paziente poteva presentarsi prima del modello, restistuendo misure errate
Ho fatto in modo che se il numero frame del paziente è minore o uguale del n frame modello, questo punto viene confrontato 
con il valore iniziale del modello. 
Calcolate le medie dei vari scostamenti dei joint in relazione.
Ora basta capire come valutare i dati ottenuti
Osservo che sull'azimut i dati ricevuti sono molto altalenanti, non buoni per una corretta valutazione, anche perchè
probabilmente dipendono molto dalla fisionomia della persona e dalla sua postura, al contrario dei dati sullo zenit
- 
*/

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
