#include "files.h"

#include <QtCharts/QtCharts>
#include <QWidget>

#include <QDir>
#include <QString>

#include <QDebug>

std::vector<tco*> txtfile::get_tco() { return this->tco_vec; }
std::vector<sfu*> txtfile::get_sfu() { return this->sfu_vec; }

tco* txtfile::tco_find(int _freq) {
    tco* tco1 = NULL;
    for (tco* a : this->tco_vec) {
        if (a->freq == _freq) tco1 = a;
    }
    return tco1;
}

sfu* txtfile::sfu_find(int _freq) {
    sfu* sfu1 = NULL;
    for (sfu* a : this->sfu_vec) {
        if (a->freq == _freq) sfu1 = a;
    }
    return sfu1;
}

void txtfile::tco_cut(int _from, int _to) {
    if (_to == 0) return;
    if (_from >= _to) return;
    for (tco* a: this->tco_vec) {
        std::vector<double> new_t, new_x;
        for (unsigned int i = 0; i < a->t.size(); i++) {
            if ((a->t[i] > _from) && (a->t[i] < _to)) {
                new_t.push_back(a->t[i]);
                new_x.push_back(a->x[i]);
            }
        }
        a->t = new_t;
        a->x = new_x;
    }
    this->tco_samelength();
    return;
}

void txtfile::tco_samelength() {
    this->tco_deleteshortfreq();
    unsigned int n = this->tco_vec[0]->t.size();
    for (tco* a : this->tco_vec) {
        if (a->t.size() < n) n = a->t.size();
    }
    std::cout << "Нормализация: " << n << std::endl;
    for (tco* a : this->tco_vec) {
        if (a->t.size() > n) {
            a->t.erase(a->t.begin() + n, a->t.end());
            a->x.erase(a->x.begin() + n, a->x.end());
        }
    }
    return;
}

void txtfile::tco_deleteshortfreq() {
    std::vector<tco*> n_tco;
    for (tco* a : this->tco_vec) {
        if (a->t.size() >= this->minLength1Freq) n_tco.push_back(a);
        else {
            std::cout << "Freq: " << a->freq << " - t.size() < min_length :: Deleted" << std::endl;
        }
    }
    if (n_tco.size() == 0) {
        std::cout << "Empty tco vector" << std::endl;
    }
    this->tco_vec = n_tco;
    return;
}

void txtfile::tco_delete0freq() {
    std::cout << "...Устранение неточностей.." << std::endl;
    std::vector<tco*> n_tco;
    for (unsigned int i = 0; i < this->tco_vec.size(); i++) {
        tco* a = this->tco_vec[i];
        if (a->freq != 0) {
            n_tco.push_back(a);
        } else {
            delete a;
        }
    }
    this->tco_vec = n_tco;
    std::cout << "...OK" << std::endl;
    return;
}

void txtfile::tco_elimemiss() {
//TBD
    return;
}

void txtfile::tco_smoothing() {
//TBD
    return;
}

void txtfile::tco_show() {
    QChart* chart = new QChart();
    chart->setTitle("Временной ход");
    QValueAxis *axisX = new QValueAxis;
    axisX->setTitleText("Время (сек.)");
    axisX->setTickCount(10);
    chart->addAxis(axisX, Qt::AlignBottom);
    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("Ярк. температура");
    axisY->setTickCount(10);
    chart->addAxis(axisY, Qt::AlignLeft);
    int processed = 0;
    double min = 0., max = 0.;
    for (tco* a : this->tco_vec) {
        processed++;
        QLineSeries* s = new QLineSeries();
        QPen* pen = new QPen();
        pen->setWidthF(0.5);
        DColor* col = new DColor(processed);
        QColor* color = new QColor(col->getR(), col->getG(), col->getB());
        pen->setColor(*color);
        s->setPen(*pen);

        for (unsigned int i = 0; i < a->t.size(); i++) {
            s->append(a->t[i], a->x[i]);
            if (a->x[i] < min) min = a->x[i];
            if (a->x[i] > max) max = a->x[i];
        }

        s->setName(QString::fromStdString(dtos(a->freq)));
        chart->addSeries(s);

        s->attachAxis(axisX);
        s->attachAxis(axisY);
    }
    if (processed == 0) return;
    axisY->setRange(min - 10, max + 10);
    QChartView *chartView = new QChartView(chart);
    QWidget* chartWindow = new QWidget(0);
    QVBoxLayout* layout = new QVBoxLayout(chartWindow);
    layout->addWidget(chartView);
    chartWindow->setLayout(layout);
    layout->activate();
    chartWindow->resize(800,500);
    chartWindow->show();
    return;
}

void txtfile::tco_show(std::vector<int> _freqs) {
    QChart* chart = new QChart();
    chart->setTitle("Временной ход");
    QValueAxis *axisX = new QValueAxis;
    axisX->setTitleText("Время (сек.)");
    axisX->setTickCount(10);
    chart->addAxis(axisX, Qt::AlignBottom);
    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("Ярк. температура");
    axisY->setTickCount(10);
    chart->addAxis(axisY, Qt::AlignLeft);
    int processed = 0;
    double min = 0., max = 0.;
    for (unsigned int i = 0; i < _freqs.size(); i++) {
        tco* a = this->tco_find(_freqs[i]);
        if (a == NULL) continue;
        processed++;
        QLineSeries* s = new QLineSeries();
        QPen* pen = new QPen();
        pen->setWidthF(0.5);
        DColor* col = new DColor(processed);
        QColor* color = new QColor(col->getR(), col->getG(), col->getB());
        pen->setColor(*color);
        s->setPen(*pen);

        for (unsigned int i = 0; i < a->t.size(); i++) {
            s->append(a->t[i], a->x[i]);
            if (a->x[i] < min) min = a->x[i];
            if (a->x[i] > max) max = a->x[i];
        }

        s->setName(QString::fromStdString(dtos(a->freq)));
        chart->addSeries(s);

        s->attachAxis(axisX);
        s->attachAxis(axisY);
    }
    if (processed == 0) return;
    axisY->setRange(min - 10, max + 10);
    QChartView *chartView = new QChartView(chart);
    QWidget* chartWindow = new QWidget(0);
    QVBoxLayout* layout = new QVBoxLayout(chartWindow);
    layout->addWidget(chartView);
    chartWindow->setLayout(layout);
    layout->activate();
    chartWindow->resize(800,500);
    chartWindow->show();
    return;
}

void txtfile::sfu_show() {
    QChart* chart = new QChart();
    chart->setTitle("Структурные функции");
    QValueAxis *axisX = new QValueAxis;
    axisX->setTitleText("Время (сек.)");
    axisX->setTickCount(10);
    chart->addAxis(axisX, Qt::AlignBottom);
    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("Корень из D");
    axisY->setTickCount(10);
    chart->addAxis(axisY, Qt::AlignLeft);
    int processed = 0;
    double min = 0., max = 0.;
    for (sfu* a : this->sfu_vec) {
        processed++;
        QLineSeries* s = new QLineSeries();
        QPen* pen = new QPen();
        pen->setWidthF(0.5);
        DColor* col = new DColor(processed);
        QColor* color = new QColor(col->getR(), col->getG(), col->getB());
        pen->setColor(*color);
        s->setPen(*pen);

        for (unsigned int i = 0; i < a->t.size(); i++) {
            if (a->t[i] > this->strFuncOutputLength) break;
            if (a->t[i] < this->strFuncOutputBegin) continue;
            s->append(a->t[i], a->x[i]);
            if (a->x[i] < min) min = a->x[i];
            if (a->x[i] > max) max = a->x[i];
        }

        s->setName(QString::fromStdString(dtos(a->freq)));
        chart->addSeries(s);

        s->attachAxis(axisX);
        s->attachAxis(axisY);
    }
    if (processed == 0) return;
    axisY->setRange(min - 0.05, max + 0.05);
    QChartView *chartView = new QChartView(chart);
    QWidget* chartWindow = new QWidget(0);
    QVBoxLayout* layout = new QVBoxLayout(chartWindow);
    layout->addWidget(chartView);
    chartWindow->setLayout(layout);
    layout->activate();
    chartWindow->resize(800,500);
    chartWindow->show();
    return;
}

void txtfile::sfu_show(std::vector<int> _freqs) {
    QChart* chart = new QChart();
    chart->setTitle("Структурные функции");
    QValueAxis *axisX = new QValueAxis;
    axisX->setTitleText("Время (сек.)");
    axisX->setTickCount(10);
    chart->addAxis(axisX, Qt::AlignBottom);
    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("Корень из D");
    axisY->setTickCount(10);
    chart->addAxis(axisY, Qt::AlignLeft);
    int processed = 0;
    double min = 0., max = 0.;
    for (unsigned int i = 0; i < _freqs.size(); i++) {
        sfu* a = this->sfu_find(_freqs[i]);
        if (a == NULL) continue;
        processed++;
        QLineSeries* s = new QLineSeries();
        QPen* pen = new QPen();
        pen->setWidthF(0.5);
        DColor* col = new DColor(processed);
        QColor* color = new QColor(col->getR(), col->getG(), col->getB());
        pen->setColor(*color);
        s->setPen(*pen);

        for (unsigned int i = 0; i < a->t.size(); i++) {
            if (a->t[i] > this->strFuncOutputLength) break;
            if (a->t[i] < this->strFuncOutputBegin) continue;
            s->append(a->t[i], a->x[i]);
            if (a->x[i] < min) min = a->x[i];
            if (a->x[i] > max) max = a->x[i];
        }

        s->setName(QString::fromStdString(dtos(a->freq)));
        chart->addSeries(s);

        s->attachAxis(axisX);
        s->attachAxis(axisY);
    }
    if (processed == 0) return;
    axisY->setRange(min - 0.05, max + 0.5);
    QChartView *chartView = new QChartView(chart);
    QWidget* chartWindow = new QWidget(0);
    QVBoxLayout* layout = new QVBoxLayout(chartWindow);
    layout->addWidget(chartView);
    chartWindow->setLayout(layout);
    layout->activate();
    chartWindow->resize(800,500);
    chartWindow->show();
    return;
}

void txtfile::tco_show_sc(std::vector<int> _freqs) {
    /*
    QChart* chart = new QChart();
    chart->setTitle("Временной ход");
    QValueAxis *axisX = new QValueAxis;
    axisX->setTitleText("Время (сек.)");
    axisX->setTickCount(10);
    chart->addAxis(axisX, Qt::AlignBottom);
    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("Ярк. температура");
    axisY->setTickCount(10);
    chart->addAxis(axisY, Qt::AlignLeft);
    int processed = 0;
    double min = 0., max = 0.;
    for (unsigned int i = 0; i < _freqs.size(); i++) {
        tco* a = this->tco_find(_freqs[i]);
        if (a == NULL) continue;
        processed++;
        QScatterSeries* s = new QScatterSeries();
        s->setMarkerSize(1);
        QPen* pen = new QPen();
        pen->setWidthF(0.5);
        DColor* col = new DColor(processed);
        QColor* color = new QColor(col->getR(), col->getG(), col->getB());
        pen->setColor(*color);
        s->setPen(*pen);

        for (unsigned int i = 0; i < a->t.size(); i++) {
            s->append(a->t[i], a->x[i]);
            if (a->x[i] < min) min = a->x[i];
            if (a->x[i] > max) max = a->x[i];
        }

        s->setName(QString::fromStdString(dtos(a->freq)));
        chart->addSeries(s);

        s->attachAxis(axisX);
        s->attachAxis(axisY);
    }
    if (processed == 0) return;
    axisY->setRange(min - 10, max + 10);
    QChartView *chartView = new QChartView(chart);
    QWidget* chartWindow = new QWidget(0);
    QVBoxLayout* layout = new QVBoxLayout(chartWindow);
    layout->addWidget(chartView);
    chartWindow->setLayout(layout);
    layout->activate();
    chartWindow->resize(800,500);
    chartWindow->show();
    */
    std::ofstream fout;
    std::string path = (QDir::currentPath() + "/tco.tmp").toStdString();
    fout.open(path);
    std::string write = "";
    this->tco_samelength();
    for (unsigned int j = 0; j < this->tco_vec.size(); j++) {
        write += "t" + dtos(this->tco_vec[j]->freq) + "\t" +
                dtos(this->tco_vec[j]->freq) + "\t";
    }
    write += "\n";
    fout << write;
    for (unsigned int i = 0; i < this->tco_vec[0]->t.size(); i++) {
        write = "";
        for (unsigned int j = 0; j < this->tco_vec.size(); j++) {
            write += dtos(this->tco_vec[j]->t[i]) + "\t" +
                    dtos(this->tco_vec[j]->x[i]) + "\t";
        }
        write += "\n";
        fout << write;
    }
    fout.close();

    FILE *gnuplot = popen("gnuplot -persistent", "w");
    fprintf(gnuplot, "reset\n");
    fprintf(gnuplot, "set title 'Br. temp'\n");
    fprintf(gnuplot, "set xlabel 'time'\n");
    fprintf(gnuplot, "set ylabel 'value'\n");
    std::string zapros = "plot";
    int k = 0;
    for (unsigned int n = 0; n < _freqs.size(); n++) {
        for (unsigned int j = 0; j < this->tco_vec.size(); j++) {
            if (_freqs[n] == tco_vec[j]->freq) {
                //std::cout << "found" << std::endl;
                k = j * 2;
                zapros += " '" + path + "' using " + dtos(k+1) + ":" + dtos(k+2) + " w lines " +
                        "title '" + dtos(this->tco_vec[j]->freq) + "',";
                continue;
            }
        }
    }
    zapros = zapros.replace(zapros.length() - 1, 1, "");
    zapros += "\n";
    std::cout << "~ tco_show_sc() :: ~" << std::endl;
    std::cout << zapros << std::endl;
    const char* z = zapros.c_str();
    fprintf(gnuplot, z);
    pclose(gnuplot);
    return;
}

void txtfile::tco_freqsort() {
    std::cout << "Сортировка..." << std::endl;
    int size = (int)this->tco_vec.size();
    for (int i = size - 1; i >= 0; i--) {
        for (int j = 0; j < i; j++) {
            if (this->tco_vec[j]->freq > this->tco_vec[j + 1]->freq) {
                tco* tmp = this->tco_vec[j];
                this->tco_vec[j] = this->tco_vec[j + 1];
                this->tco_vec[j + 1] = tmp;
            }
        }
    }
    std::cout << "OK" << std::endl;
    return;
}

void txtfile::spectrum_show() {
    this->tco_freqsort();

    this->tco_samelength();

    std::ofstream fout;
    std::string path = (QDir::currentPath() + "/spectrum.tmp").toStdString();
    fout.open(path);
    for (tco* a : this->tco_vec) {
        std::string write = "";
        for (unsigned int i = 0; i < a->t.size(); i++) {
            write += dtos(a->x[i] - a->x[0]) + " ";
        }
        write += "\n";
        fout << write;
    }
    fout.close();

    FILE *gnuplot = popen("gnuplot -persistent", "w");
    fprintf(gnuplot, "reset\n");
    fprintf(gnuplot, "unset key\n");
    fprintf(gnuplot, "unset colorbox\n");
    fprintf(gnuplot, "unset tics\n");
    fprintf(gnuplot, "set palette defined (0 '#352a87', 1 '#0363e1', 2 '#1485d4', 3 '#06a7c6', 4 '#38b99e', 5 '#92bf73', 6 '#d9ba56', 7 '#fcce2e', 8 '#f9fb0e')\n");
    fprintf(gnuplot, "set pm3d map\n");
    fprintf(gnuplot, "set pm3d interpolate 0,0\n");
    std::string zapros = "splot '" + path + "' matrix\n";
    const char* z = zapros.c_str();
    fprintf(gnuplot, z);
    pclose(gnuplot);
    return;
}

void txtfile::deltas_show() {
    std::ofstream fout;
    std::string path = (QDir::currentPath() + "/deltas.tmp").toStdString();
    fout.open(path);
    std::string write = "";
    for (unsigned int i = 0; i < this->sh->t.size(); i++) {
        write = dtos(this->sh->t[i]) + " " + dtos(this->sh->x[i]) + "\n";
        fout << write;
    }
    fout.close();

    FILE *gnuplot = popen("gnuplot -persistent", "w");
    fprintf(gnuplot, "reset\n");
    fprintf(gnuplot, "set title 'The shift'\n");
    fprintf(gnuplot, "set xlabel '# of spectrum'\n");
    fprintf(gnuplot, "set ylabel 'value'\n");
    std::string zapros = "plot '" + path + "' using 1:2 w lines ls 1\n";
    const char* z = zapros.c_str();
    fprintf(gnuplot, z);
    pclose(gnuplot);
    return;
}

void txtfile::setNoCloudsInterval(int _start, int _stop) {
    this->i_start = _start;
    this->i_stop = _stop;
    return;
}

void txtfile::init_dbase() {
    init_datetime();
    std::string oclock = str_datetime(this->datetime);
    DBase* d_base = new DBase();
    d_base->connect();
    d_base->datetime_select_all(oclock);
    this->d_base = d_base;
    return;
}

void txtfile::computeQW_(int freq_1 /*Mhz*/, int freq_2 /*Mhz*/) {

    session* sesQ = new session();
    session* sesW = new session();
    this->tco_samelength();
    tco* tco1 = this->tco_find(freq_1);
    tco* tco2 = this->tco_find(freq_2);
/*
    double sr1 = 0., sr2 = 0.;
    if ((this->i_start != 0) || (this->i_stop != 0)) {
        for (unsigned int j = 0; j < tco1->t.size(); j++) {
            if ((tco1->t[j] >= this->i_start) && (tco1->t[j] <= this->i_stop)) sr1 += tco1->x[j];
            if ((tco2->t[j] >= this->i_start) && (tco2->t[j] <= this->i_stop)) sr2 += tco2->x[j];
        }
        sr1 /= abs(this->i_stop - this->i_start);
        sr2 /= abs(this->i_stop - this->i_start);
    }
    if ((sr1 != 0) && (sr2 != 0)) {
        //КАЛИБРОВКА ПО БЕЗОБЛАЧНОЙ АТМ.
        double Tavg = std::stod(d_base->T) - 15; //Cels
        for (unsigned int i = 0; i < tco1->t.size(); i++) {
            double tau1 = tau(double(freq_1)/1000, d_base); //tau = gammaO*H1+gammaH2O*H2
            double tau2 = tau(double(freq_2)/1000, d_base);
            double Tya1 = (Tavg + 273) * (1 - exp(-tau1));
            double Tya2 = (Tavg + 273) * (1 - exp(-tau2));
            tco1->x[i] = Tya1 + (250 - Tya1) / (250 - sr1) * tco1->x[i];
            tco2->x[i] = Tya2 + (250 - Tya2) / (250 - sr2) * tco2->x[i];
        }

    }
*/

    /*Расчёт Q и W*/
    double T_obl = -2;
    double tauO1 = tauO2_t(double(freq_1)/1000, d_base);
    double tauO2 = tauO2_t(double(freq_2)/1000, d_base);
    for (unsigned int i = 0; i < tco1->t.size(); i++) {
        double tau1 = tau_t(tco1->x[i], d_base);
        double tau2 = tau_t(tco2->x[i], d_base);
        double c1 = tauO1 - tau1;
        double c2 = tauO2 - tau2;
        //double a1 = k_phi(double(freq_1)/1000);
        //double a2 = k_phi(double(freq_2)/1000);
        double a1 = k_phi_t(double(freq_1)/1000, d_base);
        double a2 = k_phi_t(double(freq_2)/1000, d_base);
        double b1 = k_w(double(freq_1)/1000, T_obl);
        double b2 = k_w(double(freq_2)/1000, T_obl);
        double b0, c0, Q, W;
        if (fabs(a1*b2-a2*b1)>=0.0001) {
            if (a1 != 0) {
                b0=b2-(b1/a1*a2);
                c0=-(c2-(c1/a1*a2));
                W=c0/b0;
                Q=(-c1-((b1*c0)/b0))/a1;
            }
            else {
                b0=b1-(b2/a2*a1);
                c0=-(c1-(c2/a2*a1));
                W=c0/b0;
                Q=(-c2-((b2*c0)/b0))/a2;
            }
        }
        else {
            qDebug() << "findQW :: det(sys) = 0";
        }
        sesQ->t.push_back((tco1->t[i] + tco2->t[i])/2);
        sesQ->x.push_back(Q);
        sesW->t.push_back((tco1->t[i] + tco2->t[i])/2);
        sesW->x.push_back(W);
    }

    /*
    double sredWnc = 0.; int k = 0;

    for (unsigned int j = 0; j < sesW->t.size(); j++) {
        if ((this->i_start < sesW->t[j]) && (sesW->t[j] < this->i_stop)) {
            sredWnc += sesW->x[j];
            k++;
        }
    }
    sredWnc /= k;
    */
    /*
    for (unsigned int i = 0; i < sesW->t.size(); i++) {
        sesW->x[i] -= sredWnc;
    }
    */
    /*
    for (unsigned int i = 0; i < sesQ->t.size(); i++) {
        double tau1 = tau_t(tco1->x[i], d_base);
        double tau2 = tau_t(tco2->x[i], d_base);
        //double a1 = k_phi(double(freq_1)/1000);
        //double a2 = k_phi(double(freq_2)/1000);
        double a1 = k_phi_t(double(freq_1)/1000, d_base);
        double a2 = k_phi_t(double(freq_2)/1000, d_base);
        double b1 = k_w(double(freq_1)/1000, T_obl);
        double b2 = k_w(double(freq_2)/1000, T_obl);
        double c1 = tauO1 - tau1 + b1 * sredWnc;
        double c2 = tauO2 - tau2 + b2 * sredWnc;
    /*
        double Q1 = (tau1 - tauO1 - b1*sesW->x[i]) / a1;
        double Q2 = (tau2 - tauO2 - b2*sesW->x[i]) / a2;
        double Q = (Q1 + Q2) / 2;

        sesQ->x[i] = Q;
    */
    /*
        double Q = (tau1 + tau2 - tauO1 - tauO2 -
                        (b1 + b2) * sesW->x[i])/(a1 + a2);

        sesQ->x[i] = Q;
    */
    /*
        double b0, c0, Q, W;
        if (fabs(a1*b2-a2*b1)>=0.0001) {
            if (a1 != 0) {
                b0=b2-(b1/a1*a2);
                c0=-(c2-(c1/a1*a2));
                W=c0/b0;
                Q=(-c1-((b1*c0)/b0))/a1;
            }
            else {
                b0=b1-(b2/a2*a1);
                c0=-(c1-(c2/a2*a1));
                W=c0/b0;
                Q=(-c2-((b2*c0)/b0))/a2;
            }
        }
        else {
            qDebug() << "findQW :: det(sys) = 0";
        }

        sesQ->x[i] = Q;
        sesW->x[i] = W;

    }
    */
    //this->QW.clear();
    this->QW.push_back(sesQ);
    this->QW.push_back(sesW);
    //Q_err, W_err - TBD

    return;

}
/*
void txtfile::computeQW() {
    session* sesQ = new session();
    session* sesW = new session();
    this->tco_samelength();
    tco* tco1 = this->tco_find(freq_1);
    tco* tco2 = this->tco_find(freq_2);



    return;
}
/*
void txtfile::computeQW_summar() {
    std::vector<session*> QWs;
    //1
    this->computeQW(22400, 27000);
    QWs = this->QW;
    this->QW.clear();
    //2
    this->computeQW(18600, 22400);
    for (unsigned int j = 0; j < QWs.size(); j++) {
        for (unsigned int i = 0; i < QWs[j]->t.size(); i++) {
            QWs[j]->t[i] += this->QW[j]->t[i];
            QWs[j]->x[i] += this->QW[j]->x[i];
        }
    }
    this->QW.clear();
    //3
    this->computeQW(18400, 22600);
    for (unsigned int j = 0; j < QWs.size(); j++) {
        for (unsigned int i = 0; i < QWs[j]->t.size(); i++) {
            QWs[j]->t[i] += this->QW[j]->t[i];
            QWs[j]->x[i] += this->QW[j]->x[i];
        }
    }
    //Усреднение
    for (unsigned int j = 0; j < QWs.size(); j++) {
        for (unsigned int i = 0; i < QWs[j]->t.size(); i++) {
            QWs[j]->t[i] /= 3;
            QWs[j]->x[i] /= 3;
        }
    }
    this->QW = QWs;
    return;
}
*/

void txtfile::showQW(std::vector<std::string> caption) {
    if (caption.size() != this->QW.size() / 2) {
        std::cout << "showQW() :: Error!" << std::endl;
        return;
    }
    std::ofstream foutq;
    std::string pathq = (QDir::currentPath() + "/q.tmp").toStdString();
    foutq.open(pathq);
    std::ofstream foutw;
    std::string pathw = (QDir::currentPath() + "/w.tmp").toStdString();
    foutw.open(pathw);
    std::string writeq = ""; std::string writew = "";
    unsigned int j = this->QW[0]->t.size();
    for (unsigned int k = 1; k < this->QW.size(); k++) {
        if (this->QW[k]->t.size() < j) j = this->QW[k]->t.size();
    }
    for (unsigned int i = 0; i < j; i++) {
        writeq = ""; writew = "";
        for (unsigned int k = 0; k < this->QW.size() / 2; k++) {
            writeq += dtos(this->QW[k*2]->t[i]) + " " +
                    dtos(this->QW[k*2]->x[i]) + "\t";
            writew += dtos(this->QW[k*2+1]->t[i]) + " " +
                    dtos(this->QW[k*2+1]->x[i]) + "\t";
        }
        writeq += "\n";
        writew += "\n";
        foutq << writeq;
        foutw << writew;
    }
    foutq.close();
    foutw.close();

    FILE* gnuplot = popen("gnuplot -persistent", "w");
    fprintf(gnuplot, "reset\n");
    std::string title = "set title 'Q - полная масса водяного пара'\n";
    fprintf(gnuplot, title.c_str());
    fprintf(gnuplot, "set xlabel 'Время [сек.]'\n");
    fprintf(gnuplot, "set ylabel '[г/см^2]'\n");
    std::string zapros = "plot";
    for (unsigned int k = 0; k < caption.size(); k++) {
        zapros += " '" + pathq + "' using " + dtos(k*2+1) + ":" + dtos(k*2+2) +
                " with lines title '" + caption[k] + "',";
    }
    zapros = zapros.replace(zapros.length() - 1, 1, "");
    zapros += "\n";
    const char* z = zapros.c_str();
    fprintf(gnuplot, z);
    pclose(gnuplot);

    gnuplot = popen("gnuplot -persistent", "w");
    fprintf(gnuplot, "reset\n");
    title = "set title 'W - водозапас облаков'\n";
    fprintf(gnuplot, title.c_str());
    fprintf(gnuplot, "set xlabel 'Время [сек.]'\n");
    fprintf(gnuplot, "set ylabel '[кг/м^2]'\n");
    zapros = "plot";
    for (unsigned int k = 0; k < caption.size(); k++) {
        zapros += " '" + pathw + "' using " + dtos(k*2+1) + ":" + dtos(k*2+2) +
                " with lines title '" + caption[k] + "',";
    }
    zapros = zapros.replace(zapros.length() - 1, 1, "");
    zapros += "\n";
    z = zapros.c_str();
    fprintf(gnuplot, z);
    pclose(gnuplot);
    return;
}

void txtfile::showQW(std::string caption) {
    /*
    QChart* chart = new QChart();
    chart->setTitle("Q & W");
    QValueAxis *axisX = new QValueAxis;
    axisX->setTitleText("Время (сек.)");
    axisX->setTickCount(10);
    chart->addAxis(axisX, Qt::AlignBottom);
    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("Водозапас");
    axisY->setTickCount(10);
    chart->addAxis(axisY, Qt::AlignLeft);
    int processed = 0;
    double min = 0., max = 0.;
    for (session* a : this->QW) {
        processed++;
        QLineSeries* s = new QLineSeries();
        QPen* pen = new QPen();
        pen->setWidthF(0.5);
        DColor* col = new DColor(processed);
        QColor* color = new QColor(col->getR(), col->getG(), col->getB());
        pen->setColor(*color);
        s->setPen(*pen);

        for (unsigned int i = 0; i < a->t.size(); i++) {
            s->append(a->t[i], a->x[i]);
            if (a->x[i] < min) min = a->x[i];
            if (a->x[i] > max) max = a->x[i];
        }

        if (processed == 1)
            s->setName("Q");
        else
            s->setName("W");
        chart->addSeries(s);

        s->attachAxis(axisX);
        s->attachAxis(axisY);
    }
    if (processed == 0) return;
    axisY->setRange(min - 10, max + 10);
    QChartView *chartView = new QChartView(chart);
    QWidget* chartWindow = new QWidget(0);
    QVBoxLayout* layout = new QVBoxLayout(chartWindow);
    layout->addWidget(chartView);
    chartWindow->setLayout(layout);
    layout->activate();
    chartWindow->resize(800,500);
    chartWindow->show();
    */
    std::ofstream foutq;
    std::string pathq = (QDir::currentPath() + "/q.tmp").toStdString();
    foutq.open(pathq);
    std::ofstream foutw;
    std::string pathw = (QDir::currentPath() + "/w.tmp").toStdString();
    foutw.open(pathw);
    std::string write = "";
    session* q = this->QW[0];
    session* w = this->QW[1];
    for (unsigned int i = 0; i < q->t.size(); i++) {
        write = dtos(q->t[i]) + " " + dtos(q->x[i]) + "\n";
        foutq << write;
    }
    foutq.close();
    for (unsigned int i = 0; i < w->t.size(); i++) {
        write = dtos(w->t[i]) + " " + dtos(w->x[i]) + "\n";
        foutw << write;
    }
    foutw.close();
/*
    FILE* gnuplot = popen("gnuplot -persistent", "w");
    fprintf(gnuplot, "reset\n");
    std::string title = "set title 'Q - полная масса водяного пара / " + caption + "'\n";
    fprintf(gnuplot, title.c_str());
    fprintf(gnuplot, "set xlabel 'Время [сек.]'\n");
    fprintf(gnuplot, "set ylabel '[г/см^2]'\n");
    std::string zapros = "plot '" + pathq + "' using 1:2 with lines title 'Q'\n";
    const char* z = zapros.c_str();
    fprintf(gnuplot, z);
    pclose(gnuplot);
*/
    FILE* gnuplot;
    std::string title;
    std::string zapros;
    const char* z;
    gnuplot = popen("gnuplot -persistent", "w");
    fprintf(gnuplot, "reset\n");
    title = "set title 'W - водозапас облаков / " + caption + "'\n";
    fprintf(gnuplot, title.c_str());
    fprintf(gnuplot, "set xlabel 'Время [сек.]'\n");
    fprintf(gnuplot, "set ylabel '[кг/м^2]'\n");
    zapros = "plot '" + pathw + "' using 1:2 with lines title 'W'\n";
    z = zapros.c_str();
    fprintf(gnuplot, z);
    pclose(gnuplot);
    return;
}

void txtfile::clearQW() {
    this->QW.clear();
    return;
}

void txtfile::firstderivcl() {
    std::cout << "firstderiv-Обработка..." << std::endl;

    int lvlnumb = 6;
    double eps_pipe = 3.;

    for (unsigned int j = 0; j < this->tco_vec.size(); j++) {
        tco* a = this->tco_vec[j];
        std::vector<double> deriv;
        for (unsigned int i = 0; i < a->x.size() - 1; i++) {
            deriv.push_back(a->x[i+1] - a->x[i]);
        }
        double sum = 0.;
        for (double d : deriv) sum += d;
        double sr = sum / deriv.size();
        std::cout << a->freq << " - ср. значение: " << sr << std::endl;
        tco* b = new tco(a->freq);
        for (unsigned int i = 0; i < deriv.size(); i++)
            if (fabs(deriv[i]) < fabs(sr) + eps_pipe) {
                b->t.push_back(a->t[i]);
                b->x.push_back(a->x[i]);
        }
        std::cout << " -- кол-во точек: " << a->x.size() << " -> " << b->x.size() << std::endl;
        a->~tco();
        a = b;
        this->tco_vec[j] = a;

        unsigned int i = 0;
        while (fabs(a->x[i+1] - a->x[i]) < fabs(sr) + eps_pipe) {
            i++;
            if (i + 1 == a->x.size()) break;
        }
        i++;
        if (i + 1 == a->x.size()) continue;


        std::vector<tco*> vec;
        for (int k = 1; k <= lvlnumb; k++) vec.push_back(new tco(b->freq));
        int k = 1;
        do {
            while (fabs(a->x[i+1] - a->x[i]) < fabs(sr) + eps_pipe) {
                if (a->x[i] >= 250) {
                    vec[lvlnumb-1]->x.push_back(a->x[i]);
                    vec[lvlnumb-1]->t.push_back(a->t[i]);
                } else {
                    vec[k-1]->x.push_back(a->x[i]);
                    vec[k-1]->t.push_back(a->t[i]);
                }
                i++;
                if (i + 1 == a->x.size()) break;
            }
            if (a->x[i] >= 250) {
                vec[lvlnumb-1]->x.push_back(a->x[i]);
                vec[lvlnumb-1]->t.push_back(a->t[i]);
            } else {
                vec[k-1]->x.push_back(a->x[i]);
                vec[k-1]->t.push_back(a->t[i]);
            }
            i++;
            k++;
            if (k > lvlnumb - 1) k = 1;
        } while (i + 1 < a->x.size());
        std::cout << std::endl;
    }
    return;
}

void txtfile::init_datetime() {
    this->datetime = __get_datetime(this->fname);
    return;
}
