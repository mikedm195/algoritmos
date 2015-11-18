#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void imp_pol(int arr[4][3]);
    void imp_arco(int arr[2][3]);
    void imp_cubo(int arr[8][3]);
    void imp_p_rec(int arr[8][3]);
    void imp_p_tri(int arr[6][3]);
    void imp_cono(int arr[4][3]);
    void resetMatrixValues();
    ~MainWindow();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_2_currentIndexChanged(int index);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene = new QGraphicsScene;
};

#endif // MAINWINDOW_H
