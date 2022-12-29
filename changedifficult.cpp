#include "changedifficult.h"
#include "mainwindow.h"
#include "ui_changedifficult.h"

ChangeDifficult::ChangeDifficult(QMainWindow *parent) :
    QDialog(parent),
    ui(new Ui::ChangeDifficult)
{
    ui->setupUi(this);
}

ChangeDifficult::~ChangeDifficult()
{
    delete ui;
}

void ChangeDifficult::on_pushButton_clicked()
{
    MainWindow* pMainWindow = qobject_cast<MainWindow*>(parent());

    if (ui->radioButton_begginer->isChecked()) {
        pMainWindow->setFieldWidht(9);
        pMainWindow->setFieldHeight(9);
        pMainWindow->setFieldMines(10);
        pMainWindow->setLcdNumber(10);
        pMainWindow->setIsFirstClick(true);
        pMainWindow->setFlagCount(0);
        pMainWindow->generateField();
        close();
    }
    else if (ui->radioButton_intermediate->isChecked()) {
        pMainWindow->setFieldWidht(16);
        pMainWindow->setFieldHeight(16);
        pMainWindow->setFieldMines(40);
        pMainWindow->setLcdNumber(40);
        pMainWindow->setIsFirstClick(true);
        pMainWindow->setFlagCount(0);
        pMainWindow->generateField();
        close();
    }
    else if (ui->radioButton_expert->isChecked()) {
        pMainWindow->setFieldWidht(16);
        pMainWindow->setFieldHeight(30);
        pMainWindow->setFieldMines(99);
        pMainWindow->setLcdNumber(99);
        pMainWindow->setIsFirstClick(true);
        pMainWindow->setFlagCount(0);
        pMainWindow->generateField();
        close();
    }
    else if (ui->radioButton_custom->isChecked()) {
        pMainWindow->setFieldWidht(ui->widhtEdit->text().toInt());
        pMainWindow->setFieldHeight(ui->heightEdit->text().toInt());
        pMainWindow->setFieldMines(ui->minesEdit->text().toInt());
        pMainWindow->setLcdNumber(99);
        pMainWindow->setIsFirstClick(true);
        pMainWindow->setFlagCount(0);
        pMainWindow->generateField();
        close();
    }
}
