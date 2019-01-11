#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <vector>
#include <string>
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->factory = new ffactory();
    ui->setupUi(this);

    QDir p1727("/home/dobri/Документы/flucts3/DATA/p1727/");
    p1727.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    filesList = p1727.entryList();
    ui->listWidget->addItems(filesList);

    QDir p22m("/home/dobri/Документы/flucts3/DATA/p22m/");
    p22m.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    filesList = p22m.entryList();
    ui->listWidget_2->addItems(filesList);

    QDir raf("/home/dobri/Документы/flucts3/DATA/raf/");
    raf.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    filesList = raf.entryList();
    ui->listWidget_3->addItems(filesList);

    QDir f17("/home/dobri/Документы/flucts3/DATA/fryaz/");
    f17.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    filesList = f17.entryList();
    ui->listWidget_4->addItems(filesList);

    QDir cht("/home/dobri/Документы/flucts3/DATA/cht/");
    cht.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    filesList = cht.entryList();
    ui->listWidget_5->addItems(filesList);

    QDir thtp("/home/dobri/Документы/flucts3/DATA/thtp/");
    thtp.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    filesList = thtp.entryList();
    ui->listWidget_6->addItems(filesList);

    this->on_tabWidget_tabBarClicked(4);

    ui->groupBox->setEnabled(false);

    ui->textEdit->setText("49600");
    ui->textEdit_2->setText("60000");
    ui->textEdit_4->setText("49600");
    ui->textEdit_5->setText("50600");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString file;
    QString rootdir = "/home/dobri/Документы/flucts3/DATA";
    Source ss;
    if (ui->tabWidget->currentIndex() == 0) {
        source = "p1727";
        ss = Source::p1727;
        file = ui->listWidget->currentItem()->text();
    }
    if (ui->tabWidget->currentIndex() == 1) {
        source = "p22m";
        ss = Source::p22m;
        file = ui->listWidget_2->currentItem()->text();
    }
    if (ui->tabWidget->currentIndex() == 2) {
        source = "raf";
        ss = Source::raf;
        file = ui->listWidget_3->currentItem()->text();
    }
    if (ui->tabWidget->currentIndex() == 4) {
        source = "fryaz";
        ss = Source::f17;
        file = ui->listWidget_4->currentItem()->text();
    }
    if (ui->tabWidget->currentIndex() == 3) {
        source = "cht";
        ss = Source::f17;
        file = ui->listWidget_5->currentItem()->text();
    }
    if (ui->tabWidget->currentIndex() == 5) {
        source = "thtp";
        ss = Source::thtp;
        file = ui->listWidget_6->currentItem()->text();
    }

    if ((source == "p1727") || (source == "p22m") || (source == "raf")) {
        if (ui->checkBox_18649->isChecked()) frequencies.push_back(18649);
        if (ui->checkBox_20449->isChecked()) frequencies.push_back(20449);
        if (ui->checkBox_22249->isChecked()) frequencies.push_back(22249);
        if (ui->checkBox_24049->isChecked()) frequencies.push_back(24049);
        if (ui->checkBox_18700->isChecked()) frequencies.push_back(18700);
        if (ui->checkBox_19100->isChecked()) frequencies.push_back(19100);
        if (ui->checkBox_21100->isChecked()) frequencies.push_back(21100);
        if (ui->checkBox_21700->isChecked()) frequencies.push_back(21700);
        if (ui->checkBox_22300->isChecked()) frequencies.push_back(22300);
        if (ui->checkBox_23900->isChecked()) frequencies.push_back(23900);
        if (ui->checkBox_24100->isChecked()) frequencies.push_back(24100);
        if (ui->checkBox_25300->isChecked()) frequencies.push_back(25300);
        if (ui->checkBox_26900->isChecked()) frequencies.push_back(26900);
    }

    if ((source == "fryaz") || (source == "cht") || (source == "thtp")) {
        if (ui->checkBox_18000->isChecked()) frequencies.push_back(18000);
        if (ui->checkBox_18200->isChecked()) frequencies.push_back(18200);
        if (ui->checkBox_18400->isChecked()) frequencies.push_back(18400);
        if (ui->checkBox_18600->isChecked()) frequencies.push_back(18600);
        if (ui->checkBox_18800->isChecked()) frequencies.push_back(18800);
        if (ui->checkBox_19000->isChecked()) frequencies.push_back(19000);
        if (ui->checkBox_19200->isChecked()) frequencies.push_back(19200);
        if (ui->checkBox_19400->isChecked()) frequencies.push_back(19400);
        if (ui->checkBox_19600->isChecked()) frequencies.push_back(19600);
        if (ui->checkBox_19800->isChecked()) frequencies.push_back(19800);
        if (ui->checkBox_20000->isChecked()) frequencies.push_back(20000);
        if (ui->checkBox_20200->isChecked()) frequencies.push_back(20200);
        if (ui->checkBox_20400->isChecked()) frequencies.push_back(20400);
        if (ui->checkBox_20600->isChecked()) frequencies.push_back(20600);
        if (ui->checkBox_20800->isChecked()) frequencies.push_back(20800);
        if (ui->checkBox_21000->isChecked()) frequencies.push_back(21000);
        if (ui->checkBox_21200->isChecked()) frequencies.push_back(21200);
        if (ui->checkBox_21400->isChecked()) frequencies.push_back(21400);
        if (ui->checkBox_21600->isChecked()) frequencies.push_back(21600);
        if (ui->checkBox_21800->isChecked()) frequencies.push_back(21800);
        if (ui->checkBox_22000->isChecked()) frequencies.push_back(22000);
        if (ui->checkBox_22200->isChecked()) frequencies.push_back(22200);
        if (ui->checkBox_22400->isChecked()) frequencies.push_back(22400);
        if (ui->checkBox_22600->isChecked()) frequencies.push_back(22600);
        if (ui->checkBox_22800->isChecked()) frequencies.push_back(22800);
        if (ui->checkBox_23000->isChecked()) frequencies.push_back(23000);
        if (ui->checkBox_23200->isChecked()) frequencies.push_back(23200);
        if (ui->checkBox_23400->isChecked()) frequencies.push_back(23400);
        if (ui->checkBox_23600->isChecked()) frequencies.push_back(23600);
        if (ui->checkBox_23800->isChecked()) frequencies.push_back(23800);
        if (ui->checkBox_24000->isChecked()) frequencies.push_back(24000);
        if (ui->checkBox_24200->isChecked()) frequencies.push_back(24200);
        if (ui->checkBox_24400->isChecked()) frequencies.push_back(24400);
        if (ui->checkBox_24600->isChecked()) frequencies.push_back(24600);
        if (ui->checkBox_24800->isChecked()) frequencies.push_back(24800);
        if (ui->checkBox_25000->isChecked()) frequencies.push_back(25000);
        if (ui->checkBox_25200->isChecked()) frequencies.push_back(25200);
        if (ui->checkBox_25400->isChecked()) frequencies.push_back(25400);
        if (ui->checkBox_25600->isChecked()) frequencies.push_back(25600);
        if (ui->checkBox_25800->isChecked()) frequencies.push_back(25800);
        if (ui->checkBox_26000->isChecked()) frequencies.push_back(26000);
        if (ui->checkBox_26200->isChecked()) frequencies.push_back(26200);
        if (ui->checkBox_26400->isChecked()) frequencies.push_back(26400);
        if (ui->checkBox_26600->isChecked()) frequencies.push_back(26600);
        if (ui->checkBox_26800->isChecked()) frequencies.push_back(26800);
        if (ui->checkBox_27000->isChecked()) frequencies.push_back(27000);
        if (ui->checkBox_27200->isChecked()) frequencies.push_back(27200);
    }

    if (this->b12timesPressed) tfile->~txtfile();

    QString file_path = rootdir+"/"+source+"/"+file;
    this->tfile = this->factory->produce(file_path.toStdString(), ss);
    tfile->parse();
    //tfile->tco_calibrate();
    //tfile->tco_show(frequencies);
    tfile->tco_show_sc(frequencies);
    if (source == "thtp") {
        tfile->tco_show_sc(frequencies);
        tfile->firstderivcl();
        tfile->tco_show_sc(frequencies);
    }
    ui->groupBox->setEnabled(true);

    if (ui->deltas_checkBox->isChecked()) tfile->deltas_show();

    this->b12timesPressed = 1;

    frequencies.clear();

    tfile->init_dbase();
    QString weather = "";
    weather += file + "\n";
    if (!tfile->d_base->T.empty()) weather += "Температура воздуха (градусы Цельсия) на высоте 2 метра над поверхностью земли: " + QString::fromStdString(tfile->d_base->T) + "\n";
    weather += "\n";
    if (!tfile->d_base->Po.empty()) weather += "Атмосферное давление на уровне станции (мм. рт. ст.): " + QString::fromStdString(tfile->d_base->Po) + "\n";
    if (!tfile->d_base->P.empty()) weather += "Атмосферное давление, приведенное к среднему уровню моря (мм. рт. ст.): " + QString::fromStdString(tfile->d_base->P) + "\n";
    if (!tfile->d_base->Pa.empty()) weather +="Барическая тенденция: изменение атмосферного давления за последние три часа (мм. рт. ст.): " + QString::fromStdString(tfile->d_base->Pa) + "\n";
    weather += "\n";
    if (!tfile->d_base->U.empty()) weather += "Относительная влажность (%) на высоте 2 метра над поверхностью земли: " + QString::fromStdString(tfile->d_base->U) + "\n";
    weather += "\n";
    if (!tfile->d_base->N.empty()) weather += "Общая облачность: " + QString::fromStdString(tfile->d_base->N) + "\n\n";
    weather += "\n";
    if (!tfile->d_base->DD.empty()) weather += "Направление ветра (румбы) на высоте 10-12 метров над земной поверхностью, осредненное за 10-минутный период, непосредственно предшествовавший сроку наблюдения: " + QString::fromStdString(tfile->d_base->DD) + "\n";
    if (!tfile->d_base->Ff.empty()) weather += "Cкорость ветра на высоте 10-12 метров над земной поверхностью, осредненная за 10-минутный период, непосредственно предшествовавший сроку наблюдения (метры в секунду): " + QString::fromStdString(tfile->d_base->Ff) + "\n";
    if (!tfile->d_base->ff10.empty()) weather += "Максимальное значение порыва ветра на высоте 10-12 метров над земной поверхностью за 10-минутный период, непосредственно предшествующий сроку наблюдения (метры в секунду): " + QString::fromStdString(tfile->d_base->ff10) + "\n";
    if (!tfile->d_base->ff3.empty()) weather += "Максимальное значение порыва ветра на высоте 10-12 метров над земной поверхностью за период между сроками (метры в секунду): " + QString::fromStdString(tfile->d_base->ff3) + "\n";
    weather += "\n";
    if (!tfile->d_base->WW.empty()) weather += "Текущая погода, сообщаемая с метеорологической станции: " + QString::fromStdString(tfile->d_base->WW) + "\n";
    if (!tfile->d_base->W1.empty()) weather += "Прошедшая погода между сроками наблюдения 1: " + QString::fromStdString(tfile->d_base->W1) + "\n";
    if (!tfile->d_base->W2.empty()) weather += "Прошедшая погода между сроками наблюдения 2: " + QString::fromStdString(tfile->d_base->W2) + "\n";
    weather += "\n";
    if (!tfile->d_base->Tn.empty()) weather += "Минимальная температура воздуха (градусы Цельсия) за прошедший период (не более 12 часов): " + QString::fromStdString(tfile->d_base->Tn) + "\n";
    if (!tfile->d_base->Tx.empty()) weather += "Максимальная температура воздуха (градусы Цельсия) за прошедший период (не более 12 часов): " + QString::fromStdString(tfile->d_base->Tx) + "\n";
    weather += "\n";
    if (!tfile->d_base->Cl.empty()) weather += "Слоисто-кучевые, слоистые, кучевые и кучево-дождевые облака (Cl): " + QString::fromStdString(tfile->d_base->Cl) + "\n";
    if (!tfile->d_base->Nh.empty()) weather += "Количество всех наблюдающихся облаков Cl или, при отсутствии облаков Cl, количество всех наблюдающихся облаков Cm: " + QString::fromStdString(tfile->d_base->Nh) + "\n";
    if (!tfile->d_base->H.empty()) weather += "Высота основания самых низких облаков (м): " + QString::fromStdString(tfile->d_base->H) + "\n";
    if (!tfile->d_base->Cm.empty()) weather += "Высококучевые, высокослоистые и слоисто-дождевые облака (Cm): " + QString::fromStdString(tfile->d_base->Cm) + "\n";
    if (!tfile->d_base->Ch.empty()) weather += "Перистые, перисто-кучевые и перисто-слоистые облака (Ch): " + QString::fromStdString(tfile->d_base->Ch) + "\n";
    weather += "\n";
    if (!tfile->d_base->VV.empty()) weather += "Горизонтальная дальность видимости (км): " + QString::fromStdString(tfile->d_base->VV) + "\n";
    if (!tfile->d_base->Td.empty()) weather += "Температура точки росы на высоте 2 метра над поверхностью земли (градусы Цельсия): " + QString::fromStdString(tfile->d_base->Td) + "\n";
    if (!tfile->d_base->RRR.empty()) weather += "Количество выпавших осадков (миллиметры): " + QString::fromStdString(tfile->d_base->RRR) + "\n";
    if (!tfile->d_base->tR.empty()) weather += "Период времени, за который накоплено указанное количество осадков (часы): " + QString::fromStdString(tfile->d_base->tR) + "\n";
    if (!tfile->d_base->E.empty()) weather += "Состояние поверхности почвы без снега или измеримого ледяного покрова: " + QString::fromStdString(tfile->d_base->E) + "\n";
    if (!tfile->d_base->Tg.empty()) weather += "Минимальная температура поверхности почвы за ночь. (градусы Цельсия): " + QString::fromStdString(tfile->d_base->Tg) + "\n";
    if (!tfile->d_base->E_p.empty()) weather += "Состояние поверхности почвы со снегом или измеримым ледяным покровом: " + QString::fromStdString(tfile->d_base->E_p) + "\n";
    if (!tfile->d_base->sss.empty()) weather += "Высота снежного покрова (см): " + QString::fromStdString(tfile->d_base->sss) + "\n";
    ui->textEdit_3->setText(weather);
    return;
}

void MainWindow::on_pushButton_2_clicked()
{
    if ((source == "p1727") || (source == "p22m") || (source == "raf")) {
        if (ui->checkBox_18649->isChecked()) frequencies.push_back(18649);
        if (ui->checkBox_20449->isChecked()) frequencies.push_back(20449);
        if (ui->checkBox_22249->isChecked()) frequencies.push_back(22249);
        if (ui->checkBox_24049->isChecked()) frequencies.push_back(24049);
        if (ui->checkBox_18700->isChecked()) frequencies.push_back(18700);
        if (ui->checkBox_19100->isChecked()) frequencies.push_back(19100);
        if (ui->checkBox_21100->isChecked()) frequencies.push_back(21100);
        if (ui->checkBox_21700->isChecked()) frequencies.push_back(21700);
        if (ui->checkBox_22300->isChecked()) frequencies.push_back(22300);
        if (ui->checkBox_23900->isChecked()) frequencies.push_back(23900);
        if (ui->checkBox_24100->isChecked()) frequencies.push_back(24100);
        if (ui->checkBox_25300->isChecked()) frequencies.push_back(25300);
        if (ui->checkBox_26900->isChecked()) frequencies.push_back(26900);
    }

    if ((source == "fryaz") || (source == "cht") || (source == "thtp")) {
        if (ui->checkBox_18000->isChecked()) frequencies.push_back(18000);
        if (ui->checkBox_18200->isChecked()) frequencies.push_back(18200);
        if (ui->checkBox_18400->isChecked()) frequencies.push_back(18400);
        if (ui->checkBox_18600->isChecked()) frequencies.push_back(18600);
        if (ui->checkBox_18800->isChecked()) frequencies.push_back(18800);
        if (ui->checkBox_19000->isChecked()) frequencies.push_back(19000);
        if (ui->checkBox_19200->isChecked()) frequencies.push_back(19200);
        if (ui->checkBox_19400->isChecked()) frequencies.push_back(19400);
        if (ui->checkBox_19600->isChecked()) frequencies.push_back(19600);
        if (ui->checkBox_19800->isChecked()) frequencies.push_back(19800);
        if (ui->checkBox_20000->isChecked()) frequencies.push_back(20000);
        if (ui->checkBox_20200->isChecked()) frequencies.push_back(20200);
        if (ui->checkBox_20400->isChecked()) frequencies.push_back(20400);
        if (ui->checkBox_20600->isChecked()) frequencies.push_back(20600);
        if (ui->checkBox_20800->isChecked()) frequencies.push_back(20800);
        if (ui->checkBox_21000->isChecked()) frequencies.push_back(21000);
        if (ui->checkBox_21200->isChecked()) frequencies.push_back(21200);
        if (ui->checkBox_21400->isChecked()) frequencies.push_back(21400);
        if (ui->checkBox_21600->isChecked()) frequencies.push_back(21600);
        if (ui->checkBox_21800->isChecked()) frequencies.push_back(21800);
        if (ui->checkBox_22000->isChecked()) frequencies.push_back(22000);
        if (ui->checkBox_22200->isChecked()) frequencies.push_back(22200);
        if (ui->checkBox_22400->isChecked()) frequencies.push_back(22400);
        if (ui->checkBox_22600->isChecked()) frequencies.push_back(22600);
        if (ui->checkBox_22800->isChecked()) frequencies.push_back(22800);
        if (ui->checkBox_23000->isChecked()) frequencies.push_back(23000);
        if (ui->checkBox_23200->isChecked()) frequencies.push_back(23200);
        if (ui->checkBox_23400->isChecked()) frequencies.push_back(23400);
        if (ui->checkBox_23600->isChecked()) frequencies.push_back(23600);
        if (ui->checkBox_23800->isChecked()) frequencies.push_back(23800);
        if (ui->checkBox_24000->isChecked()) frequencies.push_back(24000);
        if (ui->checkBox_24200->isChecked()) frequencies.push_back(24200);
        if (ui->checkBox_24400->isChecked()) frequencies.push_back(24400);
        if (ui->checkBox_24600->isChecked()) frequencies.push_back(24600);
        if (ui->checkBox_24800->isChecked()) frequencies.push_back(24800);
        if (ui->checkBox_25000->isChecked()) frequencies.push_back(25000);
        if (ui->checkBox_25200->isChecked()) frequencies.push_back(25200);
        if (ui->checkBox_25400->isChecked()) frequencies.push_back(25400);
        if (ui->checkBox_25600->isChecked()) frequencies.push_back(25600);
        if (ui->checkBox_25800->isChecked()) frequencies.push_back(25800);
        if (ui->checkBox_26000->isChecked()) frequencies.push_back(26000);
        if (ui->checkBox_26200->isChecked()) frequencies.push_back(26200);
        if (ui->checkBox_26400->isChecked()) frequencies.push_back(26400);
        if (ui->checkBox_26600->isChecked()) frequencies.push_back(26600);
        if (ui->checkBox_26800->isChecked()) frequencies.push_back(26800);
        if (ui->checkBox_27000->isChecked()) frequencies.push_back(27000);
        if (ui->checkBox_27200->isChecked()) frequencies.push_back(27200);
    }

    ui->groupBox->setEnabled(false);
    this->from = ui->textEdit->toPlainText();
    this->to = ui->textEdit_2->toPlainText();

    tfile->tco_cut(from.toInt(), to.toInt());

    if (ui->spectrum_checkBox->isChecked()) tfile->spectrum_show();

    tfile->tco_simpleinterp();
    tfile->tco_thinning();

    QString start, stop;
    start = ui->textEdit_4->toPlainText();
    stop = ui->textEdit_5->toPlainText();
    if (start == "") start = "0";
    if (stop == "") stop = "0";
    tfile->setNoCloudsInterval(start.toInt(), stop.toInt());
    tfile->tco_calibrate();

    //tfile->tco_show(frequencies);
    tfile->tco_show_sc(frequencies);

    if (ui->filtration1->isChecked()) {
        QString filenameBB = QFileDialog::getOpenFileName(
                    this,
                    "Измерение по чёрному телу",
                    QDir::currentPath(),
                    "Text (*.txt)" );
        ui->label_3->setText(filenameBB);
        tfile->sfu_compute(filenameBB.toStdString());
    } else {
        tfile->sfu_compute();
    }
    tfile->sfu_show(frequencies);

    if (ui->QW_checkBox->isChecked()) {
        //tfile->computeQW_summar();

        std::vector<std::string> caption;
        if (ui->tabWidget->currentIndex() >= 3) {

            tfile->computeQW_(18000, 21000);
            caption.push_back("18000, 21000");

            tfile->computeQW_(27000, 21000);
            caption.push_back("27000, 21000");

            tfile->computeQW_(18000, 22000);
            caption.push_back("18000, 22000");

            tfile->computeQW_(27000, 22000);
            caption.push_back("27000, 22000");

            //tfile->computeQW_(18000, 27000);
            //caption.push_back("18000, 27000");
/*
            tfile->computeQW_(18800, 22000);
            caption.push_back("18800, 22000");

            tfile->computeQW_(26000, 20000);
            caption.push_back("26000, 20000");
*/
            tfile->showQW(caption);

            /*
            std::ofstream fout;
            std::string path = (QDir::currentPath() + "/www.tmp").toStdString();
            fout.open(path);
            for (int d = 3000; d <= 4000; d += 200) {
                for (int a = 18000; a <= 27000 - d; a += 200) {
                    int b = a + d;
                    tfile->clearQW();
                    tfile->computeQW_(a, b);
                    //tfile->showQW(dtos(a) + ", " + dtos(b));
                    double sr = 0.; int k = 0;
                    for (unsigned int i = 0; i < tfile->QW[1]->t.size() / 3; i++) {
                        if ((start.toInt() < tfile->QW[1]->t[i]) &&
                                (tfile->QW[1]->t[i] < stop.toInt())) {
                            sr += tfile->QW[1]->x[i];
                            k += 1;
                        }
                    }
                    sr /= k;
                    fout << dtos(a) + " " + dtos(b) + "\t" + dtos(sr) + "\n";
                }
            }
            fout.close();
*/

        }
        else
        {
            tfile->computeQW_(21100, 26900);
            tfile->showQW();
        }
        /*
        tfile->computeQW(18600, 22400);
        tfile->showQW();
        tfile->computeQW(18400, 22600);
        tfile->showQW();
        */
    }

    tfile->~txtfile();
    this->b12timesPressed = 0;
    frequencies.clear();
    return;
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    ui->checkBox_18649->setCheckable(true);
    ui->checkBox_20449->setCheckable(true);
    ui->checkBox_22249->setCheckable(true);
    ui->checkBox_24049->setCheckable(true);
    ui->checkBox_18700->setCheckable(true);
    ui->checkBox_19100->setCheckable(true);
    ui->checkBox_21100->setCheckable(true);
    ui->checkBox_21700->setCheckable(true);
    ui->checkBox_22300->setCheckable(true);
    ui->checkBox_23900->setCheckable(true);
    ui->checkBox_24100->setCheckable(true);
    ui->checkBox_25300->setCheckable(true);
    ui->checkBox_26900->setCheckable(true);

    ui->checkBox_18000->setCheckable(true);
    ui->checkBox_18200->setCheckable(true);
    ui->checkBox_18400->setCheckable(true);
    ui->checkBox_18600->setCheckable(true);
    ui->checkBox_18800->setCheckable(true);
    ui->checkBox_19000->setCheckable(true);
    ui->checkBox_19200->setCheckable(true);
    ui->checkBox_19400->setCheckable(true);
    ui->checkBox_19600->setCheckable(true);
    ui->checkBox_19800->setCheckable(true);
    ui->checkBox_20000->setCheckable(true);
    ui->checkBox_20200->setCheckable(true);
    ui->checkBox_20400->setCheckable(true);
    ui->checkBox_20600->setCheckable(true);
    ui->checkBox_20800->setCheckable(true);
    ui->checkBox_21000->setCheckable(true);
    ui->checkBox_21200->setCheckable(true);
    ui->checkBox_21400->setCheckable(true);
    ui->checkBox_21600->setCheckable(true);
    ui->checkBox_21800->setCheckable(true);
    ui->checkBox_22000->setCheckable(true);
    ui->checkBox_22200->setCheckable(true);
    ui->checkBox_22400->setCheckable(true);
    ui->checkBox_22600->setCheckable(true);
    ui->checkBox_22800->setCheckable(true);
    ui->checkBox_23000->setCheckable(true);
    ui->checkBox_23200->setCheckable(true);
    ui->checkBox_23400->setCheckable(true);
    ui->checkBox_23600->setCheckable(true);
    ui->checkBox_23800->setCheckable(true);
    ui->checkBox_24000->setCheckable(true);
    ui->checkBox_24200->setCheckable(true);
    ui->checkBox_24400->setCheckable(true);
    ui->checkBox_24600->setCheckable(true);
    ui->checkBox_24800->setCheckable(true);
    ui->checkBox_25000->setCheckable(true);
    ui->checkBox_25200->setCheckable(true);
    ui->checkBox_25400->setCheckable(true);
    ui->checkBox_25600->setCheckable(true);
    ui->checkBox_25800->setCheckable(true);
    ui->checkBox_26000->setCheckable(true);
    ui->checkBox_26200->setCheckable(true);
    ui->checkBox_26400->setCheckable(true);
    ui->checkBox_26600->setCheckable(true);
    ui->checkBox_26800->setCheckable(true);
    ui->checkBox_27000->setCheckable(true);
    ui->checkBox_27200->setCheckable(true);

    //ui->deltas_checkBox->setChecked(false);
    ui->deltas_checkBox->setEnabled(true);

    if (index == 0) {

        ui->deltas_checkBox->setChecked(false);
        ui->deltas_checkBox->setEnabled(false);

        ui->checkBox_18649->setChecked(false);
        ui->checkBox_20449->setChecked(false);
        ui->checkBox_22249->setChecked(false);
        ui->checkBox_24049->setChecked(false);
        ui->checkBox_18700->setChecked(true);
        ui->checkBox_19100->setChecked(true);
        ui->checkBox_21100->setChecked(true);
        ui->checkBox_21700->setChecked(true);
        ui->checkBox_22300->setChecked(true);
        ui->checkBox_23900->setChecked(true);
        ui->checkBox_24100->setChecked(true);
        ui->checkBox_25300->setChecked(true);
        ui->checkBox_26900->setChecked(true);

        ui->checkBox_18000->setChecked(false);
        ui->checkBox_18200->setChecked(false);
        ui->checkBox_18400->setChecked(false);
        ui->checkBox_18600->setChecked(false);
        ui->checkBox_18800->setChecked(false);
        ui->checkBox_19000->setChecked(false);
        ui->checkBox_19200->setChecked(false);
        ui->checkBox_19400->setChecked(false);
        ui->checkBox_19600->setChecked(false);
        ui->checkBox_19800->setChecked(false);
        ui->checkBox_20000->setChecked(false);
        ui->checkBox_20200->setChecked(false);
        ui->checkBox_20400->setChecked(false);
        ui->checkBox_20600->setChecked(false);
        ui->checkBox_20800->setChecked(false);
        ui->checkBox_21000->setChecked(false);
        ui->checkBox_21200->setChecked(false);
        ui->checkBox_21400->setChecked(false);
        ui->checkBox_21600->setChecked(false);
        ui->checkBox_21800->setChecked(false);
        ui->checkBox_22000->setChecked(false);
        ui->checkBox_22200->setChecked(false);
        ui->checkBox_22400->setChecked(false);
        ui->checkBox_22600->setChecked(false);
        ui->checkBox_22800->setChecked(false);
        ui->checkBox_23000->setChecked(false);
        ui->checkBox_23200->setChecked(false);
        ui->checkBox_23400->setChecked(false);
        ui->checkBox_23600->setChecked(false);
        ui->checkBox_23800->setChecked(false);
        ui->checkBox_24000->setChecked(false);
        ui->checkBox_24200->setChecked(false);
        ui->checkBox_24400->setChecked(false);
        ui->checkBox_24600->setChecked(false);
        ui->checkBox_24800->setChecked(false);
        ui->checkBox_25000->setChecked(false);
        ui->checkBox_25200->setChecked(false);
        ui->checkBox_25400->setChecked(false);
        ui->checkBox_25600->setChecked(false);
        ui->checkBox_25800->setChecked(false);
        ui->checkBox_26000->setChecked(false);
        ui->checkBox_26200->setChecked(false);
        ui->checkBox_26400->setChecked(false);
        ui->checkBox_26600->setChecked(false);
        ui->checkBox_26800->setChecked(false);
        ui->checkBox_27000->setChecked(false);
        ui->checkBox_27200->setChecked(false);

        ui->checkBox_18000->setCheckable(false);
        ui->checkBox_18200->setCheckable(false);
        ui->checkBox_18400->setCheckable(false);
        ui->checkBox_18600->setCheckable(false);
        ui->checkBox_18800->setCheckable(false);
        ui->checkBox_19000->setCheckable(false);
        ui->checkBox_19200->setCheckable(false);
        ui->checkBox_19400->setCheckable(false);
        ui->checkBox_19600->setCheckable(false);
        ui->checkBox_19800->setCheckable(false);
        ui->checkBox_20000->setCheckable(false);
        ui->checkBox_20200->setCheckable(false);
        ui->checkBox_20400->setCheckable(false);
        ui->checkBox_20600->setCheckable(false);
        ui->checkBox_20800->setCheckable(false);
        ui->checkBox_21000->setCheckable(false);
        ui->checkBox_21200->setCheckable(false);
        ui->checkBox_21400->setCheckable(false);
        ui->checkBox_21600->setCheckable(false);
        ui->checkBox_21800->setCheckable(false);
        ui->checkBox_22000->setCheckable(false);
        ui->checkBox_22200->setCheckable(false);
        ui->checkBox_22400->setCheckable(false);
        ui->checkBox_22600->setCheckable(false);
        ui->checkBox_22800->setCheckable(false);
        ui->checkBox_23000->setCheckable(false);
        ui->checkBox_23200->setCheckable(false);
        ui->checkBox_23400->setCheckable(false);
        ui->checkBox_23600->setCheckable(false);
        ui->checkBox_23800->setCheckable(false);
        ui->checkBox_24000->setCheckable(false);
        ui->checkBox_24200->setCheckable(false);
        ui->checkBox_24400->setCheckable(false);
        ui->checkBox_24600->setCheckable(false);
        ui->checkBox_24800->setCheckable(false);
        ui->checkBox_25000->setCheckable(false);
        ui->checkBox_25200->setCheckable(false);
        ui->checkBox_25400->setCheckable(false);
        ui->checkBox_25600->setCheckable(false);
        ui->checkBox_25800->setCheckable(false);
        ui->checkBox_26000->setCheckable(false);
        ui->checkBox_26200->setCheckable(false);
        ui->checkBox_26400->setCheckable(false);
        ui->checkBox_26600->setCheckable(false);
        ui->checkBox_26800->setCheckable(false);
        ui->checkBox_27000->setCheckable(false);
        ui->checkBox_27200->setCheckable(false);
    }
    if (index == 1) {

        ui->deltas_checkBox->setChecked(false);
        ui->deltas_checkBox->setEnabled(false);

        ui->checkBox_18649->setChecked(false);
        ui->checkBox_20449->setChecked(false);
        ui->checkBox_22249->setChecked(false);
        ui->checkBox_24049->setChecked(false);
        ui->checkBox_18700->setChecked(true);
        ui->checkBox_19100->setChecked(true);
        ui->checkBox_21100->setChecked(true);
        ui->checkBox_21700->setChecked(true);
        ui->checkBox_22300->setChecked(true);
        ui->checkBox_23900->setChecked(true);
        ui->checkBox_24100->setChecked(true);
        ui->checkBox_25300->setChecked(true);
        ui->checkBox_26900->setChecked(true);

        ui->checkBox_18000->setChecked(false);
        ui->checkBox_18200->setChecked(false);
        ui->checkBox_18400->setChecked(false);
        ui->checkBox_18600->setChecked(false);
        ui->checkBox_18800->setChecked(false);
        ui->checkBox_19000->setChecked(false);
        ui->checkBox_19200->setChecked(false);
        ui->checkBox_19400->setChecked(false);
        ui->checkBox_19600->setChecked(false);
        ui->checkBox_19800->setChecked(false);
        ui->checkBox_20000->setChecked(false);
        ui->checkBox_20200->setChecked(false);
        ui->checkBox_20400->setChecked(false);
        ui->checkBox_20600->setChecked(false);
        ui->checkBox_20800->setChecked(false);
        ui->checkBox_21000->setChecked(false);
        ui->checkBox_21200->setChecked(false);
        ui->checkBox_21400->setChecked(false);
        ui->checkBox_21600->setChecked(false);
        ui->checkBox_21800->setChecked(false);
        ui->checkBox_22000->setChecked(false);
        ui->checkBox_22200->setChecked(false);
        ui->checkBox_22400->setChecked(false);
        ui->checkBox_22600->setChecked(false);
        ui->checkBox_22800->setChecked(false);
        ui->checkBox_23000->setChecked(false);
        ui->checkBox_23200->setChecked(false);
        ui->checkBox_23400->setChecked(false);
        ui->checkBox_23600->setChecked(false);
        ui->checkBox_23800->setChecked(false);
        ui->checkBox_24000->setChecked(false);
        ui->checkBox_24200->setChecked(false);
        ui->checkBox_24400->setChecked(false);
        ui->checkBox_24600->setChecked(false);
        ui->checkBox_24800->setChecked(false);
        ui->checkBox_25000->setChecked(false);
        ui->checkBox_25200->setChecked(false);
        ui->checkBox_25400->setChecked(false);
        ui->checkBox_25600->setChecked(false);
        ui->checkBox_25800->setChecked(false);
        ui->checkBox_26000->setChecked(false);
        ui->checkBox_26200->setChecked(false);
        ui->checkBox_26400->setChecked(false);
        ui->checkBox_26600->setChecked(false);
        ui->checkBox_26800->setChecked(false);
        ui->checkBox_27000->setChecked(false);
        ui->checkBox_27200->setChecked(false);

        ui->checkBox_18000->setCheckable(false);
        ui->checkBox_18200->setCheckable(false);
        ui->checkBox_18400->setCheckable(false);
        ui->checkBox_18600->setCheckable(false);
        ui->checkBox_18800->setCheckable(false);
        ui->checkBox_19000->setCheckable(false);
        ui->checkBox_19200->setCheckable(false);
        ui->checkBox_19400->setCheckable(false);
        ui->checkBox_19600->setCheckable(false);
        ui->checkBox_19800->setCheckable(false);
        ui->checkBox_20000->setCheckable(false);
        ui->checkBox_20200->setCheckable(false);
        ui->checkBox_20400->setCheckable(false);
        ui->checkBox_20600->setCheckable(false);
        ui->checkBox_20800->setCheckable(false);
        ui->checkBox_21000->setCheckable(false);
        ui->checkBox_21200->setCheckable(false);
        ui->checkBox_21400->setCheckable(false);
        ui->checkBox_21600->setCheckable(false);
        ui->checkBox_21800->setCheckable(false);
        ui->checkBox_22000->setCheckable(false);
        ui->checkBox_22200->setCheckable(false);
        ui->checkBox_22400->setCheckable(false);
        ui->checkBox_22600->setCheckable(false);
        ui->checkBox_22800->setCheckable(false);
        ui->checkBox_23000->setCheckable(false);
        ui->checkBox_23200->setCheckable(false);
        ui->checkBox_23400->setCheckable(false);
        ui->checkBox_23600->setCheckable(false);
        ui->checkBox_23800->setCheckable(false);
        ui->checkBox_24000->setCheckable(false);
        ui->checkBox_24200->setCheckable(false);
        ui->checkBox_24400->setCheckable(false);
        ui->checkBox_24600->setCheckable(false);
        ui->checkBox_24800->setCheckable(false);
        ui->checkBox_25000->setCheckable(false);
        ui->checkBox_25200->setCheckable(false);
        ui->checkBox_25400->setCheckable(false);
        ui->checkBox_25600->setCheckable(false);
        ui->checkBox_25800->setCheckable(false);
        ui->checkBox_26000->setCheckable(false);
        ui->checkBox_26200->setCheckable(false);
        ui->checkBox_26400->setCheckable(false);
        ui->checkBox_26600->setCheckable(false);
        ui->checkBox_26800->setCheckable(false);
        ui->checkBox_27000->setCheckable(false);
        ui->checkBox_27200->setCheckable(false);
    }
    if (index == 2) {

        ui->deltas_checkBox->setChecked(false);
        ui->deltas_checkBox->setEnabled(false);

        ui->checkBox_18649->setChecked(true);
        ui->checkBox_20449->setChecked(true);
        ui->checkBox_22249->setChecked(true);
        ui->checkBox_24049->setChecked(true);
        ui->checkBox_18700->setChecked(false);
        ui->checkBox_19100->setChecked(false);
        ui->checkBox_21100->setChecked(false);
        ui->checkBox_21700->setChecked(false);
        ui->checkBox_22300->setChecked(false);
        ui->checkBox_23900->setChecked(false);
        ui->checkBox_24100->setChecked(false);
        ui->checkBox_25300->setChecked(false);
        ui->checkBox_26900->setChecked(false);

        ui->checkBox_18000->setChecked(false);
        ui->checkBox_18200->setChecked(false);
        ui->checkBox_18400->setChecked(false);
        ui->checkBox_18600->setChecked(false);
        ui->checkBox_18800->setChecked(false);
        ui->checkBox_19000->setChecked(false);
        ui->checkBox_19200->setChecked(false);
        ui->checkBox_19400->setChecked(false);
        ui->checkBox_19600->setChecked(false);
        ui->checkBox_19800->setChecked(false);
        ui->checkBox_20000->setChecked(false);
        ui->checkBox_20200->setChecked(false);
        ui->checkBox_20400->setChecked(false);
        ui->checkBox_20600->setChecked(false);
        ui->checkBox_20800->setChecked(false);
        ui->checkBox_21000->setChecked(false);
        ui->checkBox_21200->setChecked(false);
        ui->checkBox_21400->setChecked(false);
        ui->checkBox_21600->setChecked(false);
        ui->checkBox_21800->setChecked(false);
        ui->checkBox_22000->setChecked(false);
        ui->checkBox_22200->setChecked(false);
        ui->checkBox_22400->setChecked(false);
        ui->checkBox_22600->setChecked(false);
        ui->checkBox_22800->setChecked(false);
        ui->checkBox_23000->setChecked(false);
        ui->checkBox_23200->setChecked(false);
        ui->checkBox_23400->setChecked(false);
        ui->checkBox_23600->setChecked(false);
        ui->checkBox_23800->setChecked(false);
        ui->checkBox_24000->setChecked(false);
        ui->checkBox_24200->setChecked(false);
        ui->checkBox_24400->setChecked(false);
        ui->checkBox_24600->setChecked(false);
        ui->checkBox_24800->setChecked(false);
        ui->checkBox_25000->setChecked(false);
        ui->checkBox_25200->setChecked(false);
        ui->checkBox_25400->setChecked(false);
        ui->checkBox_25600->setChecked(false);
        ui->checkBox_25800->setChecked(false);
        ui->checkBox_26000->setChecked(false);
        ui->checkBox_26200->setChecked(false);
        ui->checkBox_26400->setChecked(false);
        ui->checkBox_26600->setChecked(false);
        ui->checkBox_26800->setChecked(false);
        ui->checkBox_27000->setChecked(false);
        ui->checkBox_27200->setChecked(false);

        ui->checkBox_18000->setCheckable(false);
        ui->checkBox_18200->setCheckable(false);
        ui->checkBox_18400->setCheckable(false);
        ui->checkBox_18600->setCheckable(false);
        ui->checkBox_18800->setCheckable(false);
        ui->checkBox_19000->setCheckable(false);
        ui->checkBox_19200->setCheckable(false);
        ui->checkBox_19400->setCheckable(false);
        ui->checkBox_19600->setCheckable(false);
        ui->checkBox_19800->setCheckable(false);
        ui->checkBox_20000->setCheckable(false);
        ui->checkBox_20200->setCheckable(false);
        ui->checkBox_20400->setCheckable(false);
        ui->checkBox_20600->setCheckable(false);
        ui->checkBox_20800->setCheckable(false);
        ui->checkBox_21000->setCheckable(false);
        ui->checkBox_21200->setCheckable(false);
        ui->checkBox_21400->setCheckable(false);
        ui->checkBox_21600->setCheckable(false);
        ui->checkBox_21800->setCheckable(false);
        ui->checkBox_22000->setCheckable(false);
        ui->checkBox_22200->setCheckable(false);
        ui->checkBox_22400->setCheckable(false);
        ui->checkBox_22600->setCheckable(false);
        ui->checkBox_22800->setCheckable(false);
        ui->checkBox_23000->setCheckable(false);
        ui->checkBox_23200->setCheckable(false);
        ui->checkBox_23400->setCheckable(false);
        ui->checkBox_23600->setCheckable(false);
        ui->checkBox_23800->setCheckable(false);
        ui->checkBox_24000->setCheckable(false);
        ui->checkBox_24200->setCheckable(false);
        ui->checkBox_24400->setCheckable(false);
        ui->checkBox_24600->setCheckable(false);
        ui->checkBox_24800->setCheckable(false);
        ui->checkBox_25000->setCheckable(false);
        ui->checkBox_25200->setCheckable(false);
        ui->checkBox_25400->setCheckable(false);
        ui->checkBox_25600->setCheckable(false);
        ui->checkBox_25800->setCheckable(false);
        ui->checkBox_26000->setCheckable(false);
        ui->checkBox_26200->setCheckable(false);
        ui->checkBox_26400->setCheckable(false);
        ui->checkBox_26600->setCheckable(false);
        ui->checkBox_26800->setCheckable(false);
        ui->checkBox_27000->setCheckable(false);
        ui->checkBox_27200->setCheckable(false);
    }
    if (index == 4) {
        ui->checkBox_18649->setChecked(false);
        ui->checkBox_20449->setChecked(false);
        ui->checkBox_22249->setChecked(false);
        ui->checkBox_24049->setChecked(false);
        ui->checkBox_18700->setChecked(false);
        ui->checkBox_19100->setChecked(false);
        ui->checkBox_21100->setChecked(false);
        ui->checkBox_21700->setChecked(false);
        ui->checkBox_22300->setChecked(false);
        ui->checkBox_23900->setChecked(false);
        ui->checkBox_24100->setChecked(false);
        ui->checkBox_25300->setChecked(false);
        ui->checkBox_26900->setChecked(false);
        ui->checkBox_18649->setCheckable(false);
        ui->checkBox_20449->setCheckable(false);
        ui->checkBox_22249->setCheckable(false);
        ui->checkBox_24049->setCheckable(false);
        ui->checkBox_18700->setCheckable(false);
        ui->checkBox_19100->setCheckable(false);
        ui->checkBox_21100->setCheckable(false);
        ui->checkBox_21700->setCheckable(false);
        ui->checkBox_22300->setCheckable(false);
        ui->checkBox_23900->setCheckable(false);
        ui->checkBox_24100->setCheckable(false);
        ui->checkBox_25300->setCheckable(false);
        ui->checkBox_26900->setCheckable(false);

        ui->checkBox_18000->setChecked(true);
        ui->checkBox_18200->setChecked(false);
        ui->checkBox_18400->setChecked(false);
        ui->checkBox_18600->setChecked(false);
        ui->checkBox_18800->setChecked(false);
        ui->checkBox_19000->setChecked(false);
        ui->checkBox_19200->setChecked(false);
        ui->checkBox_19400->setChecked(false);
        ui->checkBox_19600->setChecked(false);
        ui->checkBox_19800->setChecked(false);
        ui->checkBox_20000->setChecked(false);
        ui->checkBox_20200->setChecked(false);
        ui->checkBox_20400->setChecked(true);
        ui->checkBox_20600->setChecked(false);
        ui->checkBox_20800->setChecked(false);
        ui->checkBox_21000->setChecked(true);
        ui->checkBox_21200->setChecked(false);
        ui->checkBox_21400->setChecked(false);
        ui->checkBox_21600->setChecked(false);
        ui->checkBox_21800->setChecked(false);
        ui->checkBox_22000->setChecked(false);
        ui->checkBox_22200->setChecked(true);
        ui->checkBox_22400->setChecked(false);
        ui->checkBox_22600->setChecked(false);
        ui->checkBox_22800->setChecked(false);
        ui->checkBox_23000->setChecked(false);
        ui->checkBox_23200->setChecked(true);
        ui->checkBox_23400->setChecked(false);
        ui->checkBox_23600->setChecked(false);
        ui->checkBox_23800->setChecked(false);
        ui->checkBox_24000->setChecked(false);
        ui->checkBox_24200->setChecked(false);
        ui->checkBox_24400->setChecked(true);
        ui->checkBox_24600->setChecked(false);
        ui->checkBox_24800->setChecked(false);
        ui->checkBox_25000->setChecked(false);
        ui->checkBox_25200->setChecked(false);
        ui->checkBox_25400->setChecked(false);
        ui->checkBox_25600->setChecked(false);
        ui->checkBox_25800->setChecked(false);
        ui->checkBox_26000->setChecked(false);
        ui->checkBox_26200->setChecked(false);
        ui->checkBox_26400->setChecked(false);
        ui->checkBox_26600->setChecked(false);
        ui->checkBox_26800->setChecked(false);
        ui->checkBox_27000->setChecked(true);
        ui->checkBox_27200->setChecked(false);
    }
    if (index == 3) {
        ui->checkBox_18649->setChecked(false);
        ui->checkBox_20449->setChecked(false);
        ui->checkBox_22249->setChecked(false);
        ui->checkBox_24049->setChecked(false);
        ui->checkBox_18700->setChecked(false);
        ui->checkBox_19100->setChecked(false);
        ui->checkBox_21100->setChecked(false);
        ui->checkBox_21700->setChecked(false);
        ui->checkBox_22300->setChecked(false);
        ui->checkBox_23900->setChecked(false);
        ui->checkBox_24100->setChecked(false);
        ui->checkBox_25300->setChecked(false);
        ui->checkBox_26900->setChecked(false);
        ui->checkBox_18649->setCheckable(false);
        ui->checkBox_20449->setCheckable(false);
        ui->checkBox_22249->setCheckable(false);
        ui->checkBox_24049->setCheckable(false);
        ui->checkBox_18700->setCheckable(false);
        ui->checkBox_19100->setCheckable(false);
        ui->checkBox_21100->setCheckable(false);
        ui->checkBox_21700->setCheckable(false);
        ui->checkBox_22300->setCheckable(false);
        ui->checkBox_23900->setCheckable(false);
        ui->checkBox_24100->setCheckable(false);
        ui->checkBox_25300->setCheckable(false);
        ui->checkBox_26900->setCheckable(false);

        ui->checkBox_18000->setChecked(true);
        ui->checkBox_18200->setChecked(true);
        ui->checkBox_18400->setChecked(true);
        ui->checkBox_18600->setChecked(true);
        ui->checkBox_18800->setChecked(true);
        ui->checkBox_19000->setChecked(true);
        ui->checkBox_19200->setChecked(true);
        ui->checkBox_19400->setChecked(true);
        ui->checkBox_19600->setChecked(true);
        ui->checkBox_19800->setChecked(true);
        ui->checkBox_20000->setChecked(true);
        ui->checkBox_20200->setChecked(true);
        ui->checkBox_20400->setChecked(true);
        ui->checkBox_20600->setChecked(true);
        ui->checkBox_20800->setChecked(true);
        ui->checkBox_21000->setChecked(true);
        ui->checkBox_21200->setChecked(true);
        ui->checkBox_21400->setChecked(true);
        ui->checkBox_21600->setChecked(true);
        ui->checkBox_21800->setChecked(true);
        ui->checkBox_22000->setChecked(true);
        ui->checkBox_22200->setChecked(true);
        ui->checkBox_22400->setChecked(true);
        ui->checkBox_22600->setChecked(true);
        ui->checkBox_22800->setChecked(true);
        ui->checkBox_23000->setChecked(true);
        ui->checkBox_23200->setChecked(true);
        ui->checkBox_23400->setChecked(true);
        ui->checkBox_23600->setChecked(true);
        ui->checkBox_23800->setChecked(true);
        ui->checkBox_24000->setChecked(true);
        ui->checkBox_24200->setChecked(true);
        ui->checkBox_24400->setChecked(true);
        ui->checkBox_24600->setChecked(true);
        ui->checkBox_24800->setChecked(true);
        ui->checkBox_25000->setChecked(true);
        ui->checkBox_25200->setChecked(true);
        ui->checkBox_25400->setChecked(true);
        ui->checkBox_25600->setChecked(true);
        ui->checkBox_25800->setChecked(true);
        ui->checkBox_26000->setChecked(true);
        ui->checkBox_26200->setChecked(true);
        ui->checkBox_26400->setChecked(true);
        ui->checkBox_26600->setChecked(true);
        ui->checkBox_26800->setChecked(true);
        ui->checkBox_27000->setChecked(true);
        ui->checkBox_27200->setChecked(true);
    }
    if (index == 5) {
        ui->checkBox_18649->setChecked(false);
        ui->checkBox_20449->setChecked(false);
        ui->checkBox_22249->setChecked(false);
        ui->checkBox_24049->setChecked(false);
        ui->checkBox_18700->setChecked(false);
        ui->checkBox_19100->setChecked(false);
        ui->checkBox_21100->setChecked(false);
        ui->checkBox_21700->setChecked(false);
        ui->checkBox_22300->setChecked(false);
        ui->checkBox_23900->setChecked(false);
        ui->checkBox_24100->setChecked(false);
        ui->checkBox_25300->setChecked(false);
        ui->checkBox_26900->setChecked(false);
        ui->checkBox_18649->setCheckable(false);
        ui->checkBox_20449->setCheckable(false);
        ui->checkBox_22249->setCheckable(false);
        ui->checkBox_24049->setCheckable(false);
        ui->checkBox_18700->setCheckable(false);
        ui->checkBox_19100->setCheckable(false);
        ui->checkBox_21100->setCheckable(false);
        ui->checkBox_21700->setCheckable(false);
        ui->checkBox_22300->setCheckable(false);
        ui->checkBox_23900->setCheckable(false);
        ui->checkBox_24100->setCheckable(false);
        ui->checkBox_25300->setCheckable(false);
        ui->checkBox_26900->setCheckable(false);

        ui->checkBox_18000->setChecked(true);
        ui->checkBox_18200->setChecked(false);
        ui->checkBox_18400->setChecked(false);
        ui->checkBox_18600->setChecked(false);
        ui->checkBox_18800->setChecked(false);
        ui->checkBox_19000->setChecked(false);
        ui->checkBox_19200->setChecked(false);
        ui->checkBox_19400->setChecked(false);
        ui->checkBox_19600->setChecked(false);
        ui->checkBox_19800->setChecked(false);
        ui->checkBox_20000->setChecked(false);
        ui->checkBox_20200->setChecked(false);
        ui->checkBox_20400->setChecked(true);
        ui->checkBox_20600->setChecked(false);
        ui->checkBox_20800->setChecked(false);
        ui->checkBox_21000->setChecked(true);
        ui->checkBox_21200->setChecked(false);
        ui->checkBox_21400->setChecked(false);
        ui->checkBox_21600->setChecked(false);
        ui->checkBox_21800->setChecked(false);
        ui->checkBox_22000->setChecked(false);
        ui->checkBox_22200->setChecked(true);
        ui->checkBox_22400->setChecked(false);
        ui->checkBox_22600->setChecked(false);
        ui->checkBox_22800->setChecked(false);
        ui->checkBox_23000->setChecked(false);
        ui->checkBox_23200->setChecked(true);
        ui->checkBox_23400->setChecked(false);
        ui->checkBox_23600->setChecked(false);
        ui->checkBox_23800->setChecked(false);
        ui->checkBox_24000->setChecked(false);
        ui->checkBox_24200->setChecked(false);
        ui->checkBox_24400->setChecked(true);
        ui->checkBox_24600->setChecked(false);
        ui->checkBox_24800->setChecked(false);
        ui->checkBox_25000->setChecked(false);
        ui->checkBox_25200->setChecked(false);
        ui->checkBox_25400->setChecked(false);
        ui->checkBox_25600->setChecked(false);
        ui->checkBox_25800->setChecked(false);
        ui->checkBox_26000->setChecked(false);
        ui->checkBox_26200->setChecked(false);
        ui->checkBox_26400->setChecked(false);
        ui->checkBox_26600->setChecked(false);
        ui->checkBox_26800->setChecked(false);
        ui->checkBox_27000->setChecked(true);
        ui->checkBox_27200->setChecked(false);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->checkBox_18649->setChecked(false);
    ui->checkBox_20449->setChecked(false);
    ui->checkBox_22249->setChecked(false);
    ui->checkBox_24049->setChecked(false);
    ui->checkBox_18700->setChecked(false);
    ui->checkBox_19100->setChecked(false);
    ui->checkBox_21100->setChecked(false);
    ui->checkBox_21700->setChecked(false);
    ui->checkBox_22300->setChecked(false);
    ui->checkBox_23900->setChecked(false);
    ui->checkBox_24100->setChecked(false);
    ui->checkBox_25300->setChecked(false);
    ui->checkBox_26900->setChecked(false);

    ui->checkBox_18000->setChecked(false);
    ui->checkBox_18200->setChecked(false);
    ui->checkBox_18400->setChecked(false);
    ui->checkBox_18600->setChecked(false);
    ui->checkBox_18800->setChecked(false);
    ui->checkBox_19000->setChecked(false);
    ui->checkBox_19200->setChecked(false);
    ui->checkBox_19400->setChecked(false);
    ui->checkBox_19600->setChecked(false);
    ui->checkBox_19800->setChecked(false);
    ui->checkBox_20000->setChecked(false);
    ui->checkBox_20200->setChecked(false);
    ui->checkBox_20400->setChecked(false);
    ui->checkBox_20600->setChecked(false);
    ui->checkBox_20800->setChecked(false);
    ui->checkBox_21000->setChecked(false);
    ui->checkBox_21200->setChecked(false);
    ui->checkBox_21400->setChecked(false);
    ui->checkBox_21600->setChecked(false);
    ui->checkBox_21800->setChecked(false);
    ui->checkBox_22000->setChecked(false);
    ui->checkBox_22200->setChecked(false);
    ui->checkBox_22400->setChecked(false);
    ui->checkBox_22600->setChecked(false);
    ui->checkBox_22800->setChecked(false);
    ui->checkBox_23000->setChecked(false);
    ui->checkBox_23200->setChecked(false);
    ui->checkBox_23400->setChecked(false);
    ui->checkBox_23600->setChecked(false);
    ui->checkBox_23800->setChecked(false);
    ui->checkBox_24000->setChecked(false);
    ui->checkBox_24200->setChecked(false);
    ui->checkBox_24400->setChecked(false);
    ui->checkBox_24600->setChecked(false);
    ui->checkBox_24800->setChecked(false);
    ui->checkBox_25000->setChecked(false);
    ui->checkBox_25200->setChecked(false);
    ui->checkBox_25400->setChecked(false);
    ui->checkBox_25600->setChecked(false);
    ui->checkBox_25800->setChecked(false);
    ui->checkBox_26000->setChecked(false);
    ui->checkBox_26200->setChecked(false);
    ui->checkBox_26400->setChecked(false);
    ui->checkBox_26600->setChecked(false);
    ui->checkBox_26800->setChecked(false);
    ui->checkBox_27000->setChecked(false);
    ui->checkBox_27200->setChecked(false);
}

void MainWindow::on_pushButton_4_clicked()
{
    std::string text = "";
    QString weather = ui->textEdit_3->toPlainText();
    QStringList W = weather.split("\n");
    text += W[0].toStdString() + "\n";
    text += "Выбрано:   от " + ui->textEdit->toPlainText().toStdString() +
            "  до " + ui->textEdit_2->toPlainText().toStdString() + "\n";
    text += "Участок безобл. погоды: " + ui->textEdit_4->toPlainText().toStdString() +
            " - " + ui->textEdit_5->toPlainText().toStdString() + "\n\n";
    for (int i = 1; i < W.size(); i++) {
        text += W[i].toStdString();
    }
    std::ofstream fout;
    QString save_file = QFileDialog::getSaveFileName(this,"choose a path to save the file","",
                                             "txt (*.txt)");
    fout.open(save_file.toStdString());
    fout << text;
    fout.close();
}
