#include "utility.h"
#include "angolo.h"

double angolo_XY(Coordinata &c1,Coordinata &c2){
	double angolo;
	if(c1.get_x()-c2.get_x()!=0){
        double m= ((c1.get_y()-c2.get_y())/(c1.get_x()-c2.get_x()));
        angolo= atan(m)*180/PI;
        
        if(angolo>=0){
			if (angolo == 0) {
				if (c1.get_x() < c2.get_x()) {
					angolo = 180;
				}
			}
			else {
				if (c1.get_y() < c2.get_y()) {
					angolo += 180;
				}
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
        
        if(angolo>=0){
			if (angolo == 0) {
				if (c1.get_x() < c2.get_x()) {
					angolo = 180;
				}
			}
			else {
				if (c1.get_z() < c2.get_z()) {
					angolo += 180;
				}
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
    
    double azimut=angoloc2c3-angoloc1c2;
    if(azimut<0){
        azimut+=360;
    }
    return azimut;
}

double angolo_zenit(Coordinata& c1, Coordinata& c2, Coordinata& c3){
    double angoloc1c2=angolo_XZ(c1,c2);
    double angoloc2c3=angolo_XZ(c3,c2);
   
    double zenit=angoloc2c3-angoloc1c2;
    if(zenit<0){
        zenit+=360;
    }
    return zenit;
}

double media_zenit(list<Angolo> _lista) {
	double mediazenit = 0;
	list<Angolo>::iterator iter;
	int index = _lista.size();
	double sommazenit = 0;
	for (iter = _lista.begin(); iter != _lista.end(); ++iter) {
		sommazenit += iter->get_zenit();
	}
	mediazenit = (double)sommazenit / index;
	return mediazenit;
}

double media_azimut(list<Angolo> _lista) {
	double mediaazimut = 0;
	list<Angolo>::iterator iter;
	int index = _lista.size();
	double sommaazimut = 0;
	for (iter = _lista.begin(); iter != _lista.end(); ++iter) {
		sommaazimut += iter->get_azimut();
	}
	mediaazimut = (double)sommaazimut / index;
	return mediaazimut;
}

float normalizza_percentuale(float _perc) {
	if (_perc > 100.0) {
		if (_perc > 200.0) {
			_perc = 0;
		}
		else {
			_perc = 200 - _perc;
		}
	}
	return _perc;
}