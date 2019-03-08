#include "angolo.h"
#include "utility.h"

Angolo::Angolo(Coordinata& _c1,Coordinata& _c2,Coordinata& _c3, int _numeroframe){
	maxmin = 0;
	azimut = angolo_azimut(_c1, _c2, _c3);
    zenit= angolo_zenit(_c1,_c2,_c3);
    numeroframe=_numeroframe;
}

Angolo::Angolo(double _azimut, double _zenit, double _numeroframe,int _maxmin) {
	azimut = _azimut;
	zenit = _zenit;
	numeroframe = _numeroframe;
	maxmin = _maxmin;
}

//FUNZIONI GET
double Angolo::get_zenit()const{ return zenit; }
double Angolo::get_azimut()const{ return azimut; }
int Angolo::get_numeroframe()const{return numeroframe;}

//FUNZIONI SET
void Angolo::set_zenit(double z) { zenit = z; }
void Angolo::set_azimut(double a) { azimut = a; }
void Angolo::set_maxmin(int i) { maxmin = i; }

ostream& operator << (ostream& os,const Angolo& _angolo){
	os << _angolo.numeroframe << " " << _angolo.azimut << " " << _angolo.zenit;
	if (_angolo.maxmin == 1)
		os << "     Questo angolo e' un max";
	else if (_angolo.maxmin == -1)
		os << "     Questo angolo e' un min";
	return os;
}
