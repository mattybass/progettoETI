#ifndef __valutazioneSJ_h__
#define __valutazioneSJ_h__

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

class ValutazioneSJ{
private:
    int angolo;
    vector<double> deltadist_zenit;
    vector<double> deltatime_zenit;
    double media_deltadist_zenit;
    double media_deltatime_zenit;
    vector<double> deltadist_azimut;
    vector<double> deltatime_azimut;
    double media_deltadist_azimut;
    double media_deltatime_azimut;
public:
    ValutazioneSJ(int _angolo);
    void media_deltadist();
    void media_deltatime();
    void insert_deltadist_zenit(double _n);
    void insert_deltadist_azimut(double _n);
    void insert_deltatime_zenit(double _n);
    void insert_deltatime_azimut(double _n);
    double get_media_deltadist_zenit();
    double get_media_deltadist_azimut();
    double get_media_deltatime_zenit();
    double get_media_deltatime_azimut();
};

void test_valuta();
#endif
