#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <fstream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->widget->clearPlottables();
    QString filename = QFileDialog::getOpenFileName(this, tr("Open source file"));
    ui->lineEdit->setText(filename);

    if (loadData() == 0) {
        ui->pushButton_2->setEnabled(true);
    } else {
        ui->pushButton_2->setEnabled(false);
    }

    ui->radioButton->setEnabled(true);
    ui->radioButton_2->setEnabled(true);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->radioButton->setEnabled(false);
    ui->radioButton_2->setEnabled(false);

    draw(sliderPosition());
}

void MainWindow::draw(long double pos) {
    if (ui->radioButton->isChecked()) {
        long double maxVal = dy * (onX.size() - 1);
        long double curVal = maxVal * pos;
        int pp = int(curVal / dy + 0.5);
        while (pp < 0) pp++;
        while (pp >= (int)onX.size()) pp--;
        draw(onX[pp], dx);
    } else {
        long double maxVal = dx * (onY.size() - 1);
        long double curVal = maxVal * pos;
        int pp = int(curVal / dx + 0.5);
        while (pp < 0) pp++;
        while (pp >= (int)onY.size()) pp--;
        draw(onY[pp], dy);
    }
}

void MainWindow::draw(const std::vector<long double> &a, long double d) {
    QVector<double> x(a.size()), y(a.size());
    for (int i = 0; i < (int)a.size(); ++i) {
        x[i] = d * i;
        y[i] = a[i];
    }
    ui->widget->clearGraphs();
    QCPGraph *gr = ui->widget->addGraph();
    gr->setData(x, y);
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");
    gr->rescaleAxes();
    ui->widget->replot();
}

long double MainWindow::sliderPosition() {
    int position = ui->horizontalSlider->value();
    long double pos = (long double)(position - ui->horizontalSlider->minimum()) / (ui->horizontalSlider->maximum() - ui->horizontalSlider->minimum());
    return pos;
}

int MainWindow::loadData() {
    QString file = ui->lineEdit->text();
    std::fstream in;
    in.open(file.toStdString().c_str(), std::ios_base::in);
    if (!in.is_open()) {
        return 1;
    }
    try {
        in >> Nx >> dx >> Ny >> dy;
        onX.assign(Ny, std::vector<long double>(Nx, 0.0L));
        onY.assign(Nx, std::vector<long double>(Ny, 0.0L));
        for (int i = 0; i < Ny; ++i) {
            for (int j = 0; j < Nx; ++j) {
                in >> onX[i][j];
                onY[j][i] = onX[i][j];
            }
        }
    } catch (...) {
        return 1;
    }
    return 0;
}

void MainWindow::on_horizontalSlider_sliderMoved(int /*position*/)
{
    draw(sliderPosition());
}
