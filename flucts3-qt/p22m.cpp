#include "files.h"

void p22m::parse() {
    std::cout << "\nПарсер..." << std::endl;
    std::ifstream fin(this->fname);
    std::string buff;
    std::vector<double> array;
    int line_numb = 0, bl_numb = 0;
    while (getline(fin, buff)) {
        line_numb++;
        array.clear();
        size_t pos;
        bool ok = true;
        while ((pos = buff.find(" ")) != std::string::npos) {
            std::string elem = buff.substr(0, pos);
            if (elem == "") {
                buff.erase(pos, pos + 1);
                continue;
            }
            elem = remove_plus(elem);
            buff.erase(0, pos + 1);
            if (!push(elem, array)) {
                bl_numb++;
                ok = false;
                break;
            }
        }
        if (!ok) continue;
        buff = remove_plus(buff);
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
                a->t.push_back(array[0]);
                a->x.push_back(array[3]);
                f1found = true;
            }
            if (a->freq == f2) {
                a->t.push_back(array[0]);
                a->x.push_back(array[5]);
                f2found = true;
            }
            if (f1found && f2found) break;
        }
        if (!f1found) {
            tco* tco1 = new tco(f1);
            tco1->t.push_back(array[0]);
            tco1->x.push_back(array[3]);
            this->tco_vec.push_back(tco1);
        }
        if (!f2found) {
            tco* tco2 = new tco(f2);
            tco2->t.push_back(array[0]);
            tco2->x.push_back(array[3]);
            this->tco_vec.push_back(tco2);
        }
    }
    fin.close();
    std::cout << "Total: " << line_numb << " lines" << std::endl;
    std::cout << "Bad lines: " << (float)bl_numb/line_numb*100 << "% " << std::endl;
    this->tco_delete0freq();
    std::cout << "OK" << std::endl;
    return;
}

void p22m::tco_thinning() {
    std::cout << "Прореживание..." << std::endl;
    for (tco* a : this->tco_vec) a->thinning(this->dt);
    this->tco_samelength();
    std::cout << "OK" << std::endl;
    return;
}

void p22m::tco_simpleinterp() {
    std::cout << "Простая интерполяция..." << std::endl;
    for (tco* a : this->tco_vec) a->simpleinterp(this->si_d);
    this->tco_samelength();
    std::cout << "OK" << std::endl;
    return;
}

void p22m::tco_calibrate() { return; }

void p22m::sfu_compute() {
    std::cout << "Подсчёт структурных функций...(1)" << std::endl;
    for (tco* a : this->tco_vec) {
        sfu* sfu1 = new sfu(a->freq, this->dt, this->c_tau);
        sfu1->compute(a);
        this->sfu_vec.push_back(sfu1);
    }
    std::cout << "OK" << std::endl;
    return;
}

void p22m::sfu_compute(std::string _fname) {
//TBD
    std::cout << "Подсчёт структурных функций...(2)" << std::endl;
    std::cout << "OK" << std::endl;
    return;
}

p22m::~p22m() {
    //std::cout << "Деструктор.. p22m ..OK" << std::endl;
}
