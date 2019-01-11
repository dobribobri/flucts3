#include "session.h"
#include "math.h"

void sfu::compute(tco* tco1) {
    int nsize = tco1->x.size();
    for (int m = 0; m < this->c_tau * nsize; m++) {
        double Em = 0;
        for (int k = 0; k < nsize - m; k++) {
            Em += pow(tco1->x[k + m] - tco1->x[k], 2);
        }
        Em = sqrt(Em / (nsize - m));
        this->x.push_back(Em);
        this->t.push_back(this->dt * m);
    }
    return;
}

void sfu::compute(tco* tco1, tco* tco2) {
    unsigned int nsize = tco1->x.size();
    if (tco2->x.size() < nsize) {
        int sh = nsize - tco2->x.size();
        for (int i = 0; i < sh; i++) {
            tco2->x.push_back(tco2->x[i]);
        }
    }

    int tt = 0, kk = 0;
    for (int m = 0; m < this->c_tau * nsize; m++) {
        double Em = 0;
        for (int k = 0; k < nsize - m; k++) {
            Em += fabs(pow(tco1->x[k + m] - tco1->x[k], 2) -
                    pow(tco2->x[k + m] - tco2->x[k], 2));

            tt++;
            if (pow(tco2->x[k + m] - tco2->x[k], 2) > pow(tco1->x[k + m] - tco1->x[k], 2)) kk++;

        }
        Em = sqrt(Em / (nsize - m));
        this->x.push_back(Em);
        this->t.push_back(this->dt * m);
    }
    std::cout << "freq: " << tco1->freq << std::endl;
    std::cout << "tt = " << tt << std::endl;
    std::cout << "kk = " << kk << std::endl;
    return;
}

sfu::~sfu() {
    //std::cout << "Деструктор... sfu ..OK" << std::endl;
}
