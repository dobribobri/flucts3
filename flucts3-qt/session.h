#ifndef SESSION_H
#define SESSION_H

#include <iostream>
#include <stdio.h>
#include <vector>

class session
{
    public:
        int freq;
        std::vector<double> t;
        std::vector<double> x;

        virtual ~session() {
            this->t.clear();
            this->x.clear();
            std::cout << "Деструктор... session ..OK" << std::endl;
        }
};

class tco : public session {
    public:
        tco(int _freq) { this->freq = _freq; }
        tco(int _freq, std::vector<double> _t, std::vector<double> _x) {
            this->freq = _freq;
            this->t = _t;
            this->x = _x;
        }
        void simpleinterp(int _degree);
        void thinning(double _interval);
        void elimemiss();
        void smoothing();
        ~tco();
};

class sfu : public session {
    private:

    public:
        double dt, c_tau;
        sfu(int _freq, double _dt, double _c_tau) : dt(_dt), c_tau(_c_tau) {
            this->freq = _freq;
        }
        void compute(tco* tco1);
        void compute(tco* tco1, tco* tco2);
        ~sfu();
};

#endif // SESSION_H
