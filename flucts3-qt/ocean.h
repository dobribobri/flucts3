#ifndef OCEAN_H
#define OCEAN_H

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>

#define PI 3.14159265

typedef std::string model;

class Ocean
{
    private:

        double T;
        double Sw;
        model _model_;
        double alpha;
        double theta;
        double lamda;

        double _sigma();

        std::vector<double> eps;

        std::vector<double> _division_complex(std::vector<double> z1, std::vector<double> z2);
        std::vector<double> _sqrt_complex(std::vector<double> e);

    public:

        Ocean();

        void initialize(model _model, double _temperature, double _saltiness, double _lamda, double _theta, double _alpha);
        void setTemperature(double _temperature);
        void setSaltiness(double _saltiness);
        void setLamda(double _lamda);
        void setTheta(double _theta);
        void setAlpha(double _alpha);
        void setModel(model _model);

        void _set_eps(double _re, double _im);

        double epsO_NoSalt();
        double epsS_NoSalt();
        double lamdaS_NoSalt();

        double epsilonO();
        double epsilonS();
        double lamdaS();

        double epsilon1();
        double epsilon2();

        std::vector<double> getEps();
        void recalculateEps();

        std::vector<double> M_h();
        std::vector<double> M_v();

        double _M_h_double();
        double _M_v_double();

        double kappa_h();
        double kappa_v();

        double kappa();

        void __debugPrint_kappa_theta();
};

#endif // OCEAN_H
