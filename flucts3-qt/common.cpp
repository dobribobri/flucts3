#include "common.h"

std::string itos(int i) {
    std::stringstream s;
    s << i;
    return s.str();
}

std::string dtos(double i) {
    std::stringstream s;
    s << i;
    return s.str();
}

std::vector<std::string> __get_datetime(std::string filename) {
    size_t pos = filename.find("/");
    while (pos != std::string::npos) {
        filename.erase(0, pos + 1);
        pos = filename.find("/");
    }
    pos = filename.find(".");
    std::string cur = filename.substr(0, pos);
    std::string year = cur.substr(5, 4);
    std::string month = cur.substr(10, 2);
    std::string day = cur.substr(13, 2);
    std::string hour = cur.substr(17, 2);
    std::string minutes = cur.substr(20, 2);
    std::string seconds = cur.substr(23, 2);
    std::vector<std::string> datetime;
    datetime.push_back(day);
    datetime.push_back(month);
    datetime.push_back(year);
    datetime.push_back(hour);
    datetime.push_back(minutes);
    datetime.push_back(seconds);
    return datetime;
}

std::string str_datetime(std::vector<std::string> _datetime) {
    int hh = std::stoi(_datetime[3]);
    hh += 3 - (hh % 3);
    if (hh >= 10) {
        _datetime[3] = itos(hh);
    } else {
        _datetime[3] = "0" + itos(hh);
    }
    std::string datetime = _datetime[0] + "." + _datetime[1] + "." + _datetime[2] + ' ' + _datetime[3] + ":00";
    return datetime;
}

int push(std::string elem, std::vector<double>& array) {
    double d = 0.;
    try {
        QString qelem = QString::fromStdString(elem);
        d = qelem.toDouble();
    }
    catch (...) {
        return 0;
    }
    array.push_back(d);
    return 1;
}

std::string remove_plus(std::string str) {
    size_t plc = str.find("+");
    if (plc != std::string::npos) str.erase(plc, plc+1);
    return str;
}



double gammaO2(double _freq /*GHz*/, double _Pressure /*hPa*/, double _T /*Cels*/) {
    double gamma = 0;
    //Standart:
    //double P = 1013; //hPa
    //double T = 15; //Celsium
    double f = _freq;
    double Rp = _Pressure/1013;
    double Rt = 288/(273 + _T);
    if (f <= 57) {
        gamma = ((7.27*Rt/(pow(f,2) + 0.351*pow(Rp,2)*pow(Rt,2))) + (7.5/(pow(f-57,2)+2.44*pow(Rp,2)*pow(Rt,5)))) * pow(f,2) * pow(Rp,2) * pow(Rt,2) / 1000;
    }
    if ((57 < f) && (f < 63)) {
        double gamma_57 = ((7.27*Rt/(pow(57,2) + 0.351*pow(Rp,2)*pow(Rt,2))) + (7.5/(pow(57-57,2)+2.44*pow(Rp,2)*pow(Rt,5)))) * pow(57,2) * pow(Rp,2) * pow(Rt,2) / 1000;
        double gamma_63 = ((7.27*Rt/(pow(63,2) + 0.351*pow(Rp,2)*pow(Rt,2))) + (7.5/(pow(63-57,2)+2.44*pow(Rp,2)*pow(Rt,5)))) * pow(63,2) * pow(Rp,2) * pow(Rt,2) / 1000;
        gamma = (f-60)*(f-63)/18*gamma_57 - 1.66*pow(Rp,2)*pow(Rt,8.5)*(f-57)*(f-63) + (f-57)*(f-60)/18*gamma_63;
    }
    if ((63 <= f) && (f <= 350)) {
        gamma = (2*pow(10,-4)*pow(Rt,1.5)*(1-1.2*pow(10,-5)*pow(f,1.5)) + 4/(pow(f-63,2)+1.5*pow(Rp,2)*pow(Rt,5)) + 0.28*pow(Rt,2)/(pow(f-118.75,2)+2.84*pow(Rp,2)*pow(Rt,2)))*pow(f,2)*pow(Rp,2)*pow(Rt,2) / 1000;
    }
    return gamma;
}

double gammaO2_t(double _freq /*GHz*/, DBase* _dbase) {
    /*Берём из БД текущие давление и температуру*/
    /*Частота должна быть в ГГц, давление в гПа, температура в С*/

    double P_mmrtst = std::stod(_dbase->Po);
    double P_hpa = P_mmrtst * 1.33322;
    //double T = std::stod(_dbase->T) - 15;
    double T = std::stod(_dbase->T);

    //return gammaO2(_freq, 1013, 15);
/*
    if (_freq == 18) return 0.0099;
    if (_freq == 21) return 0.0112;
    if (_freq == 22) return 0.0125;
    if (_freq == 27) return 0.015;
*/
    return gammaO2(_freq, P_hpa, T);
}

double gammaH2O(double _freq /*GHz*/, double _Pressure /*hPa*/, double _T /*Cels*/, double _rho /*(g/m^3)*/) {
    double gamma = 0;
    //Standart:
    //double P = 1013; //hPa
    //double T = 15; //Celsium
    //double rho = 7.5; ///g/m^3
    double f = _freq;
    double Rp = _Pressure/1013;
    double Rt = 288/(273 + _T);
    double rho = _rho;
    if (f <= 350) {
        gamma = (3.27*pow(10,-2)*Rt + 1.67*pow(10,-3)*rho*pow(Rt,7)/Rp + 7.7*pow(10,-4)*pow(f,0.5) + 3.79/(pow(f-22.235,2)+9.81*pow(Rp,2)*Rt) + 11.73*Rt/(pow(f-183.31,2)+11.85*pow(Rp,2)*Rt) + 4.01*Rt/(pow(f-325.153,2)+10.44*pow(Rp,2)*Rt)) * pow(f,2) * rho * Rp * Rt / 10000;
    }
    return gamma;
}

double gammaH2O_t(double _freq /*GHz*/, DBase* _dbase) {
    /*Берём из БД текущие давление, температуру и абсолютную влажность*/
    /*Частота должна быть в ГГц, давление в гПа, температура в С, абс.влажность в г/м^3 (переводится из
     * относительной влажности [%]) */

    double P_mmrtst = std::stod(_dbase->Po);
    double P_hpa = P_mmrtst * 1.333;
    //double T = std::stod(_dbase->T) - 15;
    double T = std::stod(_dbase->T);
    //Определить RHO!
    RHO rh;
    double rho_rel = std::stod(_dbase->U);
    double rho_abs = rh.get(T, rho_rel);
    //return gammaH2O(_freq, 1013, 15, 7.5);
/*
    if (_freq == 18) return 0.073;
    if (_freq == 21) return 0.1271;
    if (_freq == 22) return 0.1357;
    if (_freq == 27) return 0.1286;
*/
    return gammaH2O(_freq, P_hpa, T, rho_abs);
}

double tau_t(double _T_lamda /*K*/, double _T_avg /*Cels*/) { //По яркостной температуре
    //Standart:
    //double _T_avg = 290; //К
    _T_avg += 273;
    double tau = -log((_T_lamda - _T_avg) / ((-1) * _T_avg));
    return tau * costhk;
}

double tau_t(double _T_lamda /*К*/, DBase* _dbase) {
    double T_avg = std::stod(_dbase->T) - 15; /*Cels*/
    return tau_t(_T_lamda, T_avg);
}

double tauO2_t(double _freq /*GHz*/, DBase* _dbase) {
    return gammaO2_t(_freq, _dbase) * 6 * dB2np / costhk;  /* H = 5.3 км*/
}


double k_phi(double _freq /*GHz*/) {
    if ((_freq < 10) || (_freq > 50)) return 0.;
    int index = int((_freq-10)/0.2);
    return KPHI[index];
}

double k_phi_t(double _freq /*GHz*/, DBase* _dbase) {
    /*
    double T = std::stod(_dbase->T);
    RHO rh;
    double rho_rel = std::stod(_dbase->U);
    double rho_abs = rh.get(T, rho_rel);
    std::cout << "\nRHO ABS = " << rho_abs << "\n" << std::endl;
    return gammaH2O_t(_freq, _dbase) / rho_abs / 1000;
    */
    return gammaH2O_t(_freq, _dbase) * 1.6 / 1.575 * dB2np / costhk;
}

double k_w(double _freq /*Ghz*/, double _T_obl /*Cels*/) {
    /*
    if ((18 < _freq) && (_freq < 19)) return 0.082;
    if ((22 < _freq) && (_freq < 23)) return 0.113;
    */
    /* Cu hum - кучевые низкие : Tobl = 2.9 C
     * Cu med - кучевые средние : Tobl = -2.0 C
     * Cu cong - кучевые мощные : Tobl = -14.1 C
    */
    double lamda = (299792458/(_freq*pow(10, 9)))*100; /*lamda в [см]*/
    Ocean* water = new Ocean();
    water->setModel("1");
    water->setSaltiness(0.);
    water->setLamda(lamda /*[см]*/);
    water->setTemperature(_T_obl);
    /*
    std::vector<double> d_EpsC = water->getEps();
    std::complex<double> EpsC_ch(d_EpsC[0] - 1, d_EpsC[1]);
    std::complex<double> EpsC_zn(d_EpsC[0] + 2, d_EpsC[1]);
    */
    water->recalculateEps();
    double y = water->lamdaS() / lamda;
    double Im = -3 * (water->epsilonO() - water->epsilonS()) * y / (pow(water->epsilonS()+2,2) + pow(water->epsilonO()+2,2) * pow(y,2));
    //double kw = 0.6 * M_PI / lamda * std::imag(EpsC); /*lamda в [см]*/
    double kw = 0.6 * M_PI / lamda * Im; /*lamda в [см]*/
    return kw;
}

double k_w_t(double _freq /*GHz*/, double _T_lamda_oblaka /*Cels*/, DBase* _dbase) {
    /*Берём из БД тип облака и находим в связанной таблице
     * температуру его серединного слоя*/
    /*Температура в C*/
    return k_w(_freq, _T_lamda_oblaka);
}

double tau(double _freq /*GHz*/, DBase *_dbase) {
    return (gammaO2_t(_freq, _dbase) * 6 + gammaH2O_t(_freq, _dbase) * 1.6) * dB2np / costhk;
}
