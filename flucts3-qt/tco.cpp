#include "session.h"

void tco::simpleinterp(int _degree) {
    for (int d = 0; d < _degree; d++) {
        std::vector<double> new_t, new_x;
        for (int i = 0; i < t.size() - 1; i += 2) {
            new_t.push_back(t[i]);
            new_t.push_back((t[i] + t[i+1]) / 2);
            new_t.push_back(t[i+1]);
            new_x.push_back(x[i]);
            new_x.push_back((x[i] + x[i+1]) / 2);
            new_x.push_back(x[i+1]);
        }
        this->t = new_t;
        this->x = new_x;
    }
    return;
}

void tco::thinning(double _interval) {
    double val = this->t[0];
    std::vector<double>::iterator it;
    std::vector<double>::iterator ix = this->x.begin();
    for (it = this->t.begin() + 1; it != this->t.end(); it++) {
        ix++;
        if (*it < val + _interval) {
            this->t.erase(it);
            it--;
            this->x.erase(ix);
            ix--;
        } else val = *it;
    }
    return;
}

void tco::elimemiss() {
//TBD
}

void tco::smoothing() {
//TBD
}

tco::~tco() {
    //std::cout << "Деструктор... tco ..OK" << std::endl;
}
