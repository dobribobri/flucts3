#include "ocean.h"

Ocean::Ocean() { }

void Ocean::initialize(model _model, double _temperature, double _saltiness, double _lamda, double _theta, double _alpha) {
    this->lamda = _lamda;
    this->T = _temperature;
    this->Sw = _saltiness;
    this->_model_ = _model;
    this->alpha = _alpha;
    this->theta = _theta;
    return;
}

void Ocean::setAlpha(double _alpha) {
    this->alpha = _alpha;
    return;
}

void Ocean::setLamda(double _lamda) {
    this->lamda = _lamda;
    return;
}

void Ocean::setSaltiness(double _saltiness) {
    this->Sw = _saltiness;
    return;
}

void Ocean::setTemperature(double _temperature) {
    this->T = _temperature;
    return;
}

void Ocean::setTheta(double _theta) {
    this->theta = _theta;
    return;
}

void Ocean::setModel(model _model) {
    this->_model_ = _model;
    return;
}

double Ocean::epsO_NoSalt() {
    double EpsO = 5.5;
    if (this->_model_ == "2") EpsO = 4.9;
    return EpsO;
}

double Ocean::epsS_NoSalt() {
    double EpsS;
    EpsS = 88.2 - 0.40885 * T + 0.00081 * pow(T, 2);
    if (this->_model_ == "2") {
        EpsS = 87.74 - 0.4008 * T + 0.0009398 * pow(T, 2) + 1.41 * pow(10, -6) * pow(T, 3);
    }
    return EpsS;
}

double Ocean::lamdaS_NoSalt() {
    double lamdaS;
    lamdaS = 1.8735116 - 0.027296 * T + 0.000136 * pow(T, 2) + 1.662 * exp(-0.0634 * T);
    if (this->_model_ == "2") {
        lamdaS = 3 * (1.1109 - 0.03824 * T + 0.0006938 * pow(T, 2) - 5.096 * pow(10, -6) * pow(T, 3));
    }
    return lamdaS;
}

double Ocean::epsilonO() {
    return this->epsO_NoSalt();
}

double Ocean::epsilonS() {
    return this->epsS_NoSalt() - 17.2 * Sw / 60;
}

double Ocean::lamdaS() {
    return this->lamdaS_NoSalt() - 0.206 * Sw / 60;
}

double Ocean::_sigma() {
    return pow(10, -5) * (2.63 * T + 77.5) * Sw;
}

double Ocean::epsilon1() {
    return this->epsilonO() + (this->epsilonS() - this->epsilonO())/(1 + pow(this->lamdaS()/lamda, 2));
}

double Ocean::epsilon2() {
    double Eps2 = (this->lamdaS()/lamda) * ((this->epsilonS() - this->epsilonO())/(1 + pow(this->lamdaS()/lamda, 2)));
    Eps2 += 60 * this->_sigma() * lamda;
    return Eps2;
}

std::vector<double> Ocean::getEps() {
    double e1 = this->epsilon1();
    double e2 = this->epsilon2();
    std::vector<double> Eps;
    Eps.push_back(e1);
    Eps.push_back(-e2);
    return Eps;
}

void Ocean::recalculateEps() {
    double e1 = this->epsilon1();
    double e2 = this->epsilon2();
    std::vector<double> Eps;
    Eps.push_back(e1);
    Eps.push_back(-e2);
    this->eps = Eps;
    return;
}

std::vector<double> Ocean::M_h() {
    double psi = (90 - theta) * PI/180;
    std::vector<double> e = this->eps;
    e[0] -= pow(cos(psi), 2);
    std::vector<double> z1 = this->_sqrt_complex(e);
    z1[0] = sin(psi) - z1[0];
    z1[1] = 0 - z1[1];
    std::vector<double> z2 = this->_sqrt_complex(e);
    z2[0] = sin(psi) + z2[0];
    z2[1] = 0 + z2[1];
    std::vector<double> Mh = this->_division_complex(z1, z2);
    return Mh;
}

std::vector<double> Ocean::M_v() {
    double psi = (90 - theta) * PI/180;
    std::vector<double> e = this->eps;
    e[0] -= pow(cos(psi), 2);
    std::vector<double> z1 = this->_sqrt_complex(e);
    z1[0] = this->eps[0]*sin(psi) - z1[0];
    z1[1] = this->eps[1]*sin(psi) - z1[1];
    std::vector<double> z2 = this->_sqrt_complex(e);
    z2[0] = this->eps[0]*sin(psi) + z2[0];
    z2[1] = this->eps[1]*sin(psi) + z2[1];
    std::vector<double> Mv = this->_division_complex(z1, z2);
    return Mv;
}

double Ocean::_M_h_double() {
    double phi = (90 - this->theta) * PI/180;
    double e = this->eps[0];
    double Mh = ( sqrt(e - pow(cos(phi),2)) - sin(phi) ) / ( sqrt(e - pow(cos(phi),2)) + sin(phi) );
    return Mh;
}

double Ocean::_M_v_double() {
    double psi = (90 - this->theta) * PI/180;
    double e = this->eps[0];
    double Mv = abs( e*sin(psi) - sqrt(e - pow(cos(psi),2)) ) / ( e*sin(psi) + sqrt(e - pow(cos(psi),2)) );
    return Mv;
}

std::vector<double> Ocean::_division_complex(std::vector<double> z1, std::vector<double> z2) {
    std::vector<double> res;
    double a1 = z1[0];
    double b1 = z1[1];
    double a2 = z2[0];
    double b2 = z2[1];
    double a, b;
    a = (a1*a2 + b1*b2) / ( pow(a2,2) + pow(b2,2) );
    b = (a2*b1 - a1*b2) / ( pow(a2,2) + pow(b2,2) );
    res.push_back(a);
    res.push_back(b);
    return res;
}

std::vector<double> Ocean::_sqrt_complex(std::vector<double> e) {
    std::vector<double> res;
    double a, b;
    a = sqrt(( sqrt( pow(e[0],2) + pow(e[1],2) ) + e[0] ) / 2);
    res.push_back(a);
    b = sqrt(( sqrt( pow(e[0],2) + pow(e[1],2) ) - e[0] ) / 2);
    if (b >= 0) res.push_back(b);
    else res.push_back(-b);
    return res;
}

double Ocean::kappa_h() {
    std::vector<double> Mh = this->M_h();
    double kh = 1 - ( pow(Mh[0],2) + pow(Mh[1],2) );
    return kh;
}

double Ocean::kappa_v() {
    std::vector<double> Mv = this->M_v();
    double kv = 1 - ( pow(Mv[0],2) + pow(Mv[1],2) );
    return kv;
}

double Ocean::kappa() {
    return this->kappa_v() * pow(cos(alpha * PI/180), 2) + this->kappa_h() * pow(sin(alpha * PI/180), 2);
}

void Ocean::_set_eps(double _re, double _im) {
    std::vector<double> e;
    e.push_back(_re);
    e.push_back(_im);
    this->eps = e;
    return;
}

void Ocean::__debugPrint_kappa_theta() {
    std::cout << std::endl;
    std::cout << " ! Temperature: " << this->T << "; ";
    std::cout << "Saltiness: " << this->Sw << "; ";
    std::cout << "Wave length: " << this->lamda << "; " << std::endl;
    std::cout << "/// EpsO-NoSalt: " << this->epsO_NoSalt() << "; " << std::endl;
    std::cout << "/// EpsS-NoSalt: " << this->epsS_NoSalt() << "; " << std::endl;
    std::cout << "/// LamdaS-NoSalt: " << this->lamdaS_NoSalt() << "; " << std::endl;
    std::cout << "/// EpsilonO: " << this->epsilonO() << "; " << std::endl;
    std::cout << "/// EpsilonS: " << this->epsilonS() << "; " << std::endl;
    std::cout << "/// LamdaS: " << this->lamdaS() << "; " << std::endl;
    std::cout << "/// Epsilon1: " << this->epsilon1() << "; " << std::endl;
    std::cout << "/// Epsilon2: " << this->epsilon2() << "; " << std::endl;
    std::cout << "/// The dielectric constant: " << " Re=" << this->eps[0] << "; Im=" << this->eps[1] << "; /// " << std::endl;
    std::cout << " ! Theta: " << this->theta << "; " << std::endl;
    std::cout << "/// Fresnel coefficients (Re): M_{h} = " << this->M_h()[0] << ", M_{v} = " << this->M_v()[0] << "; /// " << std::endl;
    std::cout << "/// Fresnel coefficients (Im): M_{h} = " << this->M_h()[1] << ", M_{v} = " << this->M_v()[1] << "; /// " << std::endl;
    std::cout << "/// Kappas: kappa_{h} = " << this->kappa_h() << ", kappa_{v} = " << this->kappa_v() << "; /// " << std::endl;
    std::cout << " ! Alpha: " << this->alpha << "; ";
    std::cout << "/// Total kappa: " << this->kappa() << ";" << std::endl;
    return;
}


