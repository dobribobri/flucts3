#ifndef TXTFILE_H
#define TXTFILE_H

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <math.h>

#include "session.h"
#include "common.h"
#include "dcolor.h"
#include "dbase.h"

enum class Source : int { p1727, p22m, raf, f17, thtp };

class txtfile
{
    private:
        int minLength1Freq = 600;
        int strFuncOutputLength = 120;
        int strFuncOutputBegin = 20;

    protected:
        std::string fname;

        std::vector<tco*> tco_vec;
        std::vector<sfu*> sfu_vec;
        double dt;
        double c_tau;
        double k_av;
        int si_d;

        session* sh;

        void tco_delete0freq();
        void tco_deleteshortfreq();


        int i_start = 0, i_stop = 0;

    public:
        std::vector<std::string> datetime;
        DBase* d_base;

        virtual void parse() = 0; //get tcos

        void tco_cut(int _from, int _to);
        void tco_samelength();
        virtual void tco_simpleinterp() = 0;
        virtual void tco_thinning() = 0;
        virtual void tco_calibrate() = 0;
        void tco_elimemiss();
        void tco_smoothing();
        tco* tco_find(int _freq);
        void tco_freqsort();
        void tco_show();
        void tco_show(std::vector<int> _freqs);
        //void tco_show_sc();
        void tco_show_sc(std::vector<int> _freqs);

        virtual void sfu_compute() = 0; //get sfus
        virtual void sfu_compute(std::string _fname) = 0;
        sfu* sfu_find(int _freq);
        void sfu_show();
        void sfu_show(std::vector<int> _freqs);

        std::vector<tco*> get_tco();
        std::vector<sfu*> get_sfu();

        void set_dt(double _dt) { this->dt = _dt; }
        void set_c_tau(double _c_tau) { this->c_tau = _c_tau; }
        void set_k_av(double _k_av) { this->k_av = _k_av; }
        void set_si_d(int _si_d) { this->si_d = _si_d; }

        void spectrum_show();
        void deltas_show();

        std::vector<session*> QW;
        void computeQW();
        void computeQW_(int freq_1, int freq_2);

        //void computeQW_summar();
        void showQW(std::string caption = "");
        void showQW(std::vector<std::string> caption);
        void clearQW();

        void firstderivcl();

        void init_datetime();
        void init_dbase();

        void setNoCloudsInterval(int _start, int _stop);

        virtual ~txtfile() {
            std::cout << " Деструктор... txtfile" << std::endl;
            for (tco* a : this->tco_vec) a->~tco();
            for (sfu* a : this->sfu_vec) a->~sfu();
            std::cout << " ..OK" << std::endl;
        }
};

class p1727 : public txtfile {
    private:

    public:
        p1727(std::string _fname) {
            this->fname = _fname;
            set_dt(3.);
            set_c_tau(1/double(20));
            set_k_av(5.);
            set_si_d(0);
        }
        void parse();
        void tco_simpleinterp();
        void tco_thinning();
        void tco_calibrate();
        void sfu_compute();
        void sfu_compute(std::string _fname);
        ~p1727();
};

class p22m : public txtfile {
    private:

    public:
        p22m(std::string _fname) {
            this->fname = _fname;
            set_dt(3.);
            set_c_tau(1/double(20));
            set_k_av(5.);
            set_si_d(0);
        }
        void parse();
        void tco_simpleinterp();
        void tco_thinning();
        void tco_calibrate();
        void sfu_compute();
        void sfu_compute(std::string _fname);
        ~p22m();
};

class raf : public txtfile {
    private:

    public:
        raf(std::string _fname) {
            this->fname = _fname;
            set_dt(3.);
            set_c_tau(1/double(20));
            set_k_av(5.);
            set_si_d(0);
        }
        void parse();
        void tco_simpleinterp();
        void tco_thinning();
        void tco_calibrate();
        void sfu_compute();
        void sfu_compute(std::string _fname);
        ~raf();
};

class f17 : public txtfile {
    private:

        void shift();

    public:
        f17(std::string _fname) {
            this->fname = _fname;
            set_dt(8.);
            set_c_tau(1/double(20));
            set_k_av(5.);
            set_si_d(3.);
        }
        void parse();
        session* tco_getshift();
        void tco_simpleinterp();
        void tco_thinning();
        void tco_calibrate();
        void sfu_compute();
        void sfu_compute(std::string _fname);
        ~f17();
};

class thtp : public txtfile {
    private:

        void shift();

    public:
        thtp(std::string _fname) {
            this->fname = _fname;
            set_dt(8.);
            set_c_tau(1/double(20));
            set_k_av(5.);
            set_si_d(3.);
        }
        void parse();
        session* tco_getshift();
        void tco_simpleinterp();
        void tco_thinning();
        void tco_calibrate();
        void sfu_compute();
        void sfu_compute(std::string _fname);
        ~thtp();
};

class ffactory {
    private:
        txtfile* file;
    public:

        txtfile* produce(std::string _fname, Source _source) {
            std::cout << "Класс файла: ";
            switch (_source) {
                case (Source::p1727):
                    file = new p1727(_fname);
                    std::cout << "p1727" << std::endl;
                    break;
                case (Source::p22m):
                    file = new p22m(_fname);
                    std::cout << "p22m" << std::endl;
                    break;
                case (Source::raf):
                    file = new raf(_fname);
                    std::cout << "raf" << std::endl;
                    break;
                case (Source::f17):
                    file = new f17(_fname);
                    std::cout << "f17" << std::endl;
                    break;
                case (Source::thtp):
                    file = new thtp(_fname);
                    std::cout << "thtp" << std::endl;
                    break;
                default:
                    file = new f17(_fname);
                    std::cout << "f17" << std::endl;
                    break;
            }
            return file;
        }
};

#endif // TXTFILE_H
