#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<math.h>
#include<QGraphicsEllipseItem>
#include<iostream>
#include <QDebug>
#include <algorithm>

#define movex 373
#define movey 174
#define M_PI_DIV180 0.01745329251994329576

using namespace std;

struct posicion{
    int x;
    int y;
};

int poli[4][3];
int arco[2][3];
int cubo[8][3];
int p_rec[8][3];
int p_tri[6][3];
int cono[4][3];
//int radio = 20;

int figuraActual=0;
int transActual=0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);    
    ui->lineEdit->setVisible(false);
    ui->lineEdit_2->setVisible(false);
    ui->radioButton->setVisible(false);
    ui->radioButton_2->setVisible(false);
    resetMatrixValues();
    scene = new QGraphicsScene;
    scene->setSceneRect(0,0,747,349);
    scene->addLine(0,174,747,174,QPen(Qt::gray));
    scene->addLine(373,0,373,349,QPen(Qt::gray));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

void MainWindow::resetMatrixValues(){
    int t_poli[4][3] = {{-20,20,1},{20,20,1},{20,-20,1},{-20,-20,1}};
    int t_arco[2][3] = {{0,0,1},{40,0,1}};
    int t_cubo[8][3] = {{-20,20,1},{20,20,1},{20,-20,1},{-20,-20,1},{-40,0,1},{0,0,1},{0,-40,1},{-40,-40,1}};
    int t_p_rec[8][3] = {{-20,30,1},{20,30,1},{20,-30,1},{-20,-30,1},{-40,10,1},{0,10,1},{0,-50,1},{-40,-50,1}};
    int t_p_tri[6][3] = {{-20,30,1},{20,30,1},{0,10,1},{-20,-30,1},{20,-30,1},{0,-50,1}};
    int t_cono[4][3] = {{0,30,1},{-20,-40,1},{20,-40,1},{0,-40,1}};
    copy(&t_poli[0][0],&t_poli[0][0]+12,&poli[0][0]);
    copy(&t_arco[0][0],&t_arco[0][0]+6,&arco[0][0]);
    copy(&t_cubo[0][0],&t_cubo[0][0]+24,&cubo[0][0]);
    copy(&t_p_rec[0][0],&t_p_rec[0][0]+24,&p_rec[0][0]);
    copy(&t_p_tri[0][0],&t_p_tri[0][0]+18,&p_tri[0][0]);
    copy(&t_cono[0][0],&t_cono[0][0]+12,&cono[0][0]);
}

void MainWindow::imp_pol(int arr[4][3]){
    //QGraphicsScene *scene = new QGraphicsScene;
    //scene->setSceneRect(0,0,747,349);
    for(int i=0;i<4;i++){
        if(i<3)
            scene->addLine((arr[i][0]+movex),(arr[i][1]+movey),(arr[i+1][0]+movex),(arr[i+1][1]+movey));
        else
            scene->addLine(arr[i][0]+movex,arr[i][1]+movey,arr[0][0]+movex,arr[0][1]+movey);
    }
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

void MainWindow::imp_arco(int arr[2][3]){
    int radio = arr[1][0];
    QGraphicsEllipseItem* item = new QGraphicsEllipseItem(arr[0][0]+movex-radio,arr[0][1]+movey-radio, radio*2,radio*2);

    item->setStartAngle(arr[1][1]*16); item->setSpanAngle((60)*16);
    scene->addItem(item);
}

void MainWindow::imp_cubo(int arr[8][3]){
    //QGraphicsScene *scene = new QGraphicsScene;
    //scene->setSceneRect(0,0,747,349);
    for(int i=0;i<4;i++)
        if(i<3)
            scene->addLine(arr[i][0]+movex,arr[i][1]+movey,arr[i+1][0]+movex,arr[i+1][1]+movey);
        else
            scene->addLine(arr[i][0]+movex,arr[i][1]+movey,arr[0][0]+movex,arr[0][1]+movey);
    for(int i=4;i<8;i++)
        if(i<7)
            scene->addLine(arr[i][0]+movex,arr[i][1]+movey,arr[i+1][0]+movex,arr[i+1][1]+movey);
        else
            scene->addLine(arr[i][0]+movex,arr[i][1]+movey,arr[4][0]+movex,arr[4][1]+movey);
    for(int i=0;i<4;i++)
        scene->addLine(arr[i][0]+movex,arr[i][1]+movey,arr[i+4][0]+movex,arr[i+4][1]+movey);
        //else
          //  scene->addLine(arr[i][0]+movex,arr[i][1]+movey,arr[4][0]+movex,arr[4][1]+movey);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

void MainWindow::imp_p_tri(int arr[6][3]){
    //QGraphicsScene *scene = new QGraphicsScene;
    //scene->setSceneRect(0,0,747,349);
    for(int i=0;i<3;i++)
        if(i<2)
            scene->addLine(arr[i][0]+movex,arr[i][1]+movey,arr[i+1][0]+movex,arr[i+1][1]+movey);
        else
            scene->addLine(arr[i][0]+movex,arr[i][1]+movey,arr[0][0]+movex,arr[0][1]+movey);
    for(int i=3;i<6;i++)
        if(i<5)
            scene->addLine(arr[i][0]+movex,arr[i][1]+movey,arr[i+1][0]+movex,arr[i+1][1]+movey);
        else
            scene->addLine(arr[i][0]+movex,arr[i][1]+movey,arr[3][0]+movex,arr[3][1]+movey);
    for(int i=0;i<3;i++)
        scene->addLine(arr[i][0]+movex,arr[i][1]+movey,arr[i+3][0]+movex,arr[i+3][1]+movey);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

void MainWindow::imp_cono(int arr[4][3]){
    int a = abs(arr[2][0]-arr[3][0]);
    int b = abs(arr[2][1]-arr[3][1]);
    double radio = sqrt(a*a+b*b);
    scene->addLine(arr[0][0]+movex,arr[0][1]+movey,arr[1][0]+movex,arr[1][1]+movey);
    scene->addLine(arr[0][0]+movex,arr[0][1]+movey,arr[2][0]+movex,arr[2][1]+movey);
    scene->addEllipse(arr[3][0]-radio+movex,arr[3][1]-radio+movey,radio*2,radio*2);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if(figuraActual!=index){
        scene->clear();
        scene->addLine(0,174,747,174,QPen(Qt::gray));
        scene->addLine(373,0,373,349,QPen(Qt::gray));
        resetMatrixValues();
        switch(index){
            case 0:
                figuraActual=0;
            break;
            case 1:imp_pol(poli);
                figuraActual=1;
            break;
            case 2:imp_arco(arco);
                figuraActual=2;
            break;
            case 3:imp_cubo(cubo);
                figuraActual=3;
            break;
            case 4:imp_cubo(p_rec);
                figuraActual=4;
            break;
            case 5:imp_p_tri(p_tri);
                figuraActual=5;
            break;
            case 6:imp_cono(cono);
                figuraActual=6;
            break;
        }
    }
}

void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    if(transActual!=index){
        ui->lineEdit->setVisible(false);
        ui->lineEdit_2->setVisible(false);
        ui->radioButton->setVisible(false);
        ui->radioButton_2->setVisible(false);
        switch(index){
            case 0:
            transActual = 0;
            break;
            case 1:
            ui->lineEdit->setVisible(true);
            ui->lineEdit->setPlaceholderText("Grados a rotar");
            transActual=1;
            break;
            case 2:
            ui->lineEdit->setVisible(true);
            ui->lineEdit->setPlaceholderText("Trasladar en X");
            ui->lineEdit_2->setVisible(true);
            ui->lineEdit_2->setPlaceholderText("Trasladar en Y");
            transActual=2;
            break;
            case 3:
            ui->radioButton->setVisible(true);
            ui->radioButton->setText("Proyeccion X");
            ui->radioButton_2->setVisible(true);
            ui->radioButton_2->setText("Proyeccion Y");
            transActual=3;
            break;
            case 4:
            ui->lineEdit->setVisible(true);
            ui->lineEdit->setPlaceholderText("Escalar X");
            ui->lineEdit_2->setVisible(true);
            ui->lineEdit_2->setPlaceholderText("Escalar Y");
            ui->radioButton->setText("Zoom X");
            ui->radioButton->setVisible(true);
            ui->radioButton_2->setVisible(true);
            ui->radioButton_2->setText("Zoom Y");
            transActual=4;
            break;
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    if(transActual!=0 && figuraActual!=0){
        double mat_transf[3][3] = {{1,0,0},{0,1,0},{0,0,1}};
        switch(transActual){
            case 1:
                mat_transf[0][0] = cos(ui->lineEdit->text().toDouble()*M_PI_DIV180);
                mat_transf[0][1] = -sin(ui->lineEdit->text().toDouble()*M_PI_DIV180);
                mat_transf[1][0] = sin(ui->lineEdit->text().toDouble()*M_PI_DIV180);
                mat_transf[1][1] = cos(ui->lineEdit->text().toDouble()*M_PI_DIV180);                
            break;
            case 2:
                mat_transf[0][2] = ui->lineEdit->text().toInt();
                mat_transf[1][2] = ui->lineEdit_2->text().toInt();                
            break;
            case 3:
                if(ui->radioButton_2->isChecked()) mat_transf[0][0]=-1;
                if(ui->radioButton->isChecked()) mat_transf[1][1]=-1;
            break;
            case 4:
                if(!ui->lineEdit->text().isEmpty())
                mat_transf[0][0] = ui->lineEdit->text().toDouble();
                if(!ui->lineEdit_2->text().isEmpty())
                mat_transf[1][1] = ui->lineEdit_2->text().toDouble();
            break;

        }
        switch (figuraActual){
        posicion pos;
        pos.x=0;
        pos.y=0;
        case 1:            
            for(int i = 0;i<4;i++){
                pos.x=0;
                pos.y=0;
                for(int j = 0;j<3;j++){
                    pos.x += mat_transf[0][j]*poli[i][j];                    
                    pos.y += mat_transf[1][j]*poli[i][j];
                }
                poli[i][0] = pos.x;
                poli[i][1] = pos.y;
            }

            imp_pol(poli);
        break;
        case 2:
            pos.x=0;
            pos.y=0;
            for(int j = 0;j<3;j++){
                pos.x += mat_transf[0][j]*arco[0][j];
                pos.y += mat_transf[1][j]*arco[0][j];
            }
            arco[1][0] = pos.x;
            arco[1][1] = pos.y;
            if(transActual==1)
                arco[1][1]+=ui->lineEdit->text().toInt()%360;
            if(transActual==4)
                arco[1][0]*=ui->lineEdit->text().toDouble();

            imp_arco(arco);
        break;
        case 3:
            for(int i = 0;i<8;i++){
                pos.x=0;
                pos.y=0;
                for(int j = 0;j<3;j++){
                    pos.x += mat_transf[0][j]*cubo[i][j];
                    pos.y += mat_transf[1][j]*cubo[i][j];
                }
                cubo[i][0] = pos.x;
                cubo[i][1] = pos.y;
            }
            imp_cubo(cubo);
        break;
        case 4:
            for(int i = 0;i<8;i++){
                pos.x=0;
                pos.y=0;
                for(int j = 0;j<3;j++){
                    pos.x += mat_transf[0][j]*p_rec[i][j];
                    pos.y += mat_transf[1][j]*p_rec[i][j];
                }
                p_rec[i][0] = pos.x;
                p_rec[i][1] = pos.y;
            }
            imp_cubo(cubo);
            imp_cubo(p_rec);
        break;
        case 5:
            for(int i = 0;i<6;i++){
                pos.x=0;
                pos.y=0;
                for(int j = 0;j<3;j++){
                    pos.x += mat_transf[0][j]*p_tri[i][j];
                    pos.y += mat_transf[1][j]*p_tri[i][j];
                }
                p_tri[i][0] = pos.x;
                p_tri[i][1] = pos.y;
            }
            imp_p_tri(p_tri);
        break;
        case 6:
            for(int i = 0;i<4;i++){
                pos.x=0;
                pos.y=0;
                for(int j = 0;j<3;j++){
                    pos.x += mat_transf[0][j]*cono[i][j];
                    pos.y += mat_transf[1][j]*cono[i][j];
                }                
                cono[i][0] = pos.x;               
                cono[i][1] = pos.y;
            }
            imp_cono(cono);
        break;
        }
    }
}

