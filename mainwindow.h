#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_horizontalSlider_sliderMoved(int);

    void on_MainWindow_iconSizeChanged(const QSize &iconSize);

private:
    Ui::MainWindow *ui;
    int loadData();
    void draw(long double pos);
    long double sliderPosition();
    void draw(const std::vector<long double> &a, long double d);

private:
    std::vector<std::vector<long double> > onX;
    std::vector<std::vector<long double> > onY;
    int Nx;
    int Ny;
    long double dx, dy;
};

#endif // MAINWINDOW_H
