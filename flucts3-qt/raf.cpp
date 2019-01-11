#include "files.h"

void raf::parse() {
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
        std::string delim = "\t";
        while ((pos = buff.find(delim)) != std::string::npos) {
            std::string elem = buff.substr(0, pos);
            elem = remove_plus(elem);
            buff.erase(0, pos + delim.length());
            if (!push(elem, array)) {
                bl_numb++;
                ok = false;
                break;
            }
        }
        if (!ok) continue;
        push(buff, array);

        if (array.size() != 3) {
            bl_numb++;
            continue;
        }
        int f = floor(array[1]);
        bool ffound = false;
        for (tco* a : this->tco_vec) {
            if (a->freq == f) {
                a->t.push_back(array[0]);
                a->x.push_back(array[2]);
                ffound = true;
                break;
            }
        }
        if (!ffound) {
            tco* tco1 = new tco(f);
            tco1->t.push_back(array[0]);
            tco1->x.push_back(array[2]);
            this->tco_vec.push_back(tco1);
        }
    }
    fin.close();
    std::cout << "Total: " << line_numb << " lines" << std::endl;
    std::cout << "Bad lines: " << (float)bl_numb/line_numb*100 << "% " << std::endl;
    this->tco_delete0freq();
    std::cout << "OK" << std::endl;
    return;
}

void raf::tco_thinning() {
    std::cout << "Прореживание..." << std::endl;
    for (tco* a : this->tco_vec) a->thinning(this->dt);
    this->tco_samelength();
    std::cout << "OK" << std::endl;
    return;
}

void raf::tco_simpleinterp() {
    std::cout << "Простая интерполяция..." << std::endl;
    for (tco* a : this->tco_vec) a->simpleinterp(this->si_d);
    this->tco_samelength();
    std::cout << "OK" << std::endl;
    return;
}

void raf::tco_calibrate() { return; }

void raf::sfu_compute() {
    std::cout << "Подсчёт структурных функций...(1)" << std::endl;
    for (tco* a : this->tco_vec) {
        sfu* sfu1 = new sfu(a->freq, this->dt, this->c_tau);
        sfu1->compute(a);
        this->sfu_vec.push_back(sfu1);
    }
    std::cout << "OK" << std::endl;
    return;
}

void raf::sfu_compute(std::string _fname) {
//TBD
    std::cout << "Подсчёт структурных функций...(2)" << std::endl;
    std::cout << "OK" << std::endl;
    return;
}

raf::~raf() {
    //std::cout << "Деструктор.. raf ..OK" << std::endl;
}
