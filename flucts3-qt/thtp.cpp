#include "files.h"

void thtp::parse() {
    std::cout << "\nПарсер..." << std::endl;
    std::ifstream fin(this->fname);
    std::string buff;
    std::vector<double> array;
    int line_numb = 0, bl_numb = 0;
    std::string tab = "\t";
    while (getline(fin, buff)) {
        line_numb++;
        if (line_numb == 1) continue;
        array.clear();
        size_t pos;
        bool ok = true;
        pos = buff.find(tab);
        std::string elem = buff.substr(0, pos);
        std::string hh = elem.substr(9, 2);
        std::string mm = elem.substr(12, 2);
        std::string sc = elem.substr(15, 2);
        std::string ms = elem.substr(18, 3);
        double time = std::stod(ms) + std::stod(sc)*1000 + std::stod(mm)*60*1000 +
                std::stod(hh)*3600*1000;
        buff.erase(0, pos + tab.length());
        while ((pos = buff.find(tab)) != std::string::npos) {
            elem = buff.substr(0, pos);
            buff.erase(0, pos + tab.length());
            if (!push(elem, array)) {
                bl_numb++;
                ok = false;
            }
        }
        if (!ok) continue;
        push(buff, array);

        if (array.size() != 6) {
            bl_numb++;
            continue;
        }
        int f1 = floor(array[2]);
        int f2 = floor(array[4]);
        bool f1found = false, f2found = false;
        for (tco* a : this->tco_vec) {
            if (a->freq == f1) {
                a->t.push_back(time);
                a->x.push_back(array[3]);
                f1found = true;
            }
            if (a->freq == f2) {
                a->t.push_back(time);
                a->x.push_back(array[5]);
                f2found = true;
            }
            if (f1found && f2found) break;
        }
        if (!f1found) {
            tco* tco1 = new tco(f1);
            tco1->t.push_back(time);
            tco1->x.push_back(array[3]);
            this->tco_vec.push_back(tco1);
        }
        if (!f2found) {
            tco* tco2 = new tco(f2);
            tco2->t.push_back(time);
            tco2->x.push_back(array[3]);
            this->tco_vec.push_back(tco2);
        }
    }
    fin.close();

    std::cout << "Total: " << line_numb << " lines" << std::endl;
    std::cout << "Bad lines: " << (float)bl_numb/line_numb*100 << "% " << std::endl;
    this->tco_delete0freq();
    this->shift();
    std::cout << "OK" << std::endl;
    return;
}

void thtp::shift() {
    std::cout << "...Подгонка полуспектров.." << std::endl;
    if ((tco_find(18000) == NULL) && (tco_find(21200) == NULL)) {
        //TBD
        return;
    }
    unsigned int ssize = this->tco_find(18000)->t.size();
    unsigned int msize = this->tco_find(21200)->t.size();
    std::vector<tco*> delta1, delta2;
    for (int f = 21200; f <= 24000; f += 200) {
        tco* tco1 = this->tco_find(f);
        if (tco1 == NULL) continue;
        if (tco1->t.size() > 1.25 * ssize) {
            unsigned int k = 0;
            std::vector<double> av_x, av_t;
            std::vector<double> d1, d2;
            for (unsigned int i = 0; i < tco1->t.size() - 1; i += 2) {
                double tt = (tco1->t[i] + tco1->t[i+1]) / 2;
                double xx = (tco1->x[i] + tco1->x[i+1]) / 2;
                av_t.push_back(tt);
                av_x.push_back(xx);
                d1.push_back(tco1->x[i] - xx);
                d2.push_back(tco1->x[i+1] - xx);
                k++;
            }
            tco1->t = av_t;
            tco1->x = av_x;
            delta1.push_back(new tco(f, av_t, d1));
            delta2.push_back(new tco(f, av_t, d2));
            d1.clear(); d2.clear();
            if (k < msize) msize = k;
        }
    }

    this->sh = new session();
    for (unsigned int i = 0; i < msize; i++) {
        double avg_delta1 = 0, avg_delta2 = 0; int k = 0;
        for (unsigned int j = 0; j < delta1.size(); j++) {
            k++;
            avg_delta1 += delta1[j]->x[i];
            avg_delta2 += delta2[j]->x[i];
        }
        avg_delta1 /= k;
        avg_delta2 /= k;
        this->sh->x.push_back(fabs(avg_delta1) + fabs(avg_delta2));
        this->sh->t.push_back(i);
    }
    std::cout << "...OK" << std::endl;
    return;
}

session* thtp::tco_getshift() {
    return this->sh;
}

void thtp::tco_thinning() {
    std::cout << "Прореживание..." << std::endl;
    for (tco* a : this->tco_vec) a->thinning(this->dt);
    this->tco_samelength();
    std::cout << "OK" << std::endl;
    return;
}

void thtp::tco_simpleinterp() {
    std::cout << "Простая интерполяция..." << std::endl;
    for (tco* a : this->tco_vec) a->simpleinterp(this->si_d);
    this->tco_samelength();
    std::cout << "OK" << std::endl;
    return;
}

void thtp::tco_calibrate() { return; }

void thtp::sfu_compute() {
    std::cout << "Подсчёт структурных функций...(1)" << std::endl;
    for (tco* a : this->tco_vec) {
        sfu* sfu1 = new sfu(a->freq, this->dt, this->c_tau);
        sfu1->compute(a);
        this->sfu_vec.push_back(sfu1);
    }
    std::cout << "OK" << std::endl;
    return;
}

void thtp::sfu_compute(std::string _fname) {
    std::cout << "Подсчёт структурных функций...(2)" << std::endl;
    f17* file = new f17(_fname);
    file->parse();
    file->tco_simpleinterp();
    file->tco_thinning();
    std::vector<tco*> f_tco = file->get_tco();
    for (unsigned int i = 0; i < this->tco_vec.size(); i++) {
        tco* a = this->tco_find(f_tco[i]->freq);
        if (a != NULL) {
            sfu* sfu2 = new sfu(a->freq, this->dt, this->c_tau);
            sfu2->compute(a, f_tco[i]);
            this->sfu_vec.push_back(sfu2);
        }
    }
    std::cout << "OK" << std::endl;
    return;
}

thtp::~thtp() {

}
