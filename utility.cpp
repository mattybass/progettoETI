#include "utility.h"
#include "angolo.h"


double angolo_XY(Coordinata &c1,Coordinata &c2){
	double angolo;
	if(c1.get_x()-c2.get_x()!=0){
        double m= ((c1.get_y()-c2.get_y())/(c1.get_x()-c2.get_x()));
        angolo= atan(m)*180/PI;
        
        if(angolo>0){
            if(c1.get_y()<c2.get_y()){
                angolo+=180;
            }
        }
		else{
            if(c1.get_y()<c2.get_y()){
                angolo+=360;
            }
			else{
                angolo+=180;
            }
        }
        
    }else{
        
        if(c1.get_y()>c2.get_y()){
            angolo= 90.0;
        }else{
            angolo= 270.0;
        }
    }
    return angolo;
}

double angolo_XZ(Coordinata &c1,Coordinata &c2){
	double angolo;
	if(c1.get_x()-c2.get_x()!=0){
        double m= ((c1.get_z()-c2.get_z())/(c1.get_x()-c2.get_x()));
        angolo= atan(m)*180/PI;
        
        if(angolo>0){
            if(c1.get_z()<c2.get_z()){
                angolo+=180;
            }
        }
		else{
            if(c1.get_z()<c2.get_z()){
                angolo+=360;
            }
			else{
                angolo+=180;
            }
        }
        
    }else{
        
        if(c1.get_z()>c2.get_z()){
            angolo= 90.0;
        }else{
            angolo= 270.0;
        }
    }
    return angolo;	
}

double angolo_azimut(Coordinata& c1, Coordinata& c2, Coordinata& c3){
    double angoloc1c2=angolo_XY(c1,c2);
    double angoloc2c3=angolo_XY(c3,c2);
    
//DIFFERENZA TRA I DUE ANGOLI = AZIMUT
    double azimut;
      
    azimut=angoloc2c3-angoloc1c2;
    if(azimut<0){
        azimut=360+azimut;
    }
    
    return azimut;
}

double angolo_zenit(Coordinata& c1, Coordinata& c2, Coordinata& c3){
    double angoloc1c2=angolo_XZ(c1,c2);
    double angoloc2c3=angolo_XZ(c3,c2);
    
//DIFFERENZA TRA I DUE ANGOLI = AZIMUT
    double zenit=angoloc2c3-angoloc1c2;
    if(zenit<0){
        zenit+=360;
    }
    
    return zenit;
}

double media_zenit(list<Angolo> _lista) {
	double mediazenit = 0;
	list<Angolo>::iterator iter;
	int index = 0;
	double sommazenit = 0;

	for (iter = _lista.begin(); iter != _lista.end(); ++iter) {
		++index;
		sommazenit = sommazenit + iter->get_zenit();
	}

	mediazenit = (double)sommazenit / index;

	return mediazenit;

}

double media_azimut(list<Angolo> _lista) {
	double mediaazimut = 0;
	list<Angolo>::iterator iter;
	int index = 0;
	double sommaazimut = 0;

	for (iter = _lista.begin(); iter != _lista.end(); ++iter) {
		++index;
		sommaazimut = sommaazimut + iter->get_azimut();
	}

	mediaazimut = (double)sommaazimut / index;

	return mediaazimut;

}

double devst_zenit(list<Angolo> _lista) {
	double devstzenit = 0;
	list<Angolo>::iterator iter;
	int n = 0;
	double mediazenit;
	mediazenit = media_zenit(_lista);

	for (iter = _lista.begin(); iter != _lista.end(); ++iter) {
		++n;
		devstzenit = devstzenit + pow(iter->get_zenit() - mediazenit, 2);
	}

	devstzenit = sqrt((double)devstzenit / n);

	return devstzenit;

}

double devst_azimut(list<Angolo> _lista) {
	double devstazimut = 0;
	list<Angolo>::iterator iter;
	int n = 0;
	double mediaazimut;
	mediaazimut = media_azimut(_lista);

	for (iter = _lista.begin(); iter != _lista.end(); ++iter) {
		++n;
		devstazimut = devstazimut + pow(iter->get_azimut() - mediaazimut, 2);
	}

	devstazimut = sqrt((double)devstazimut / n);

	return devstazimut;

}