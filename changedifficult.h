#ifndef CHANGEDIFFICULT_H
#define CHANGEDIFFICULT_H

#include <QDialog>
#include <QMainWindow>

namespace Ui {
class ChangeDifficult;
}

class ChangeDifficult : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeDifficult(QMainWindow *parent = nullptr);
    ~ChangeDifficult();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ChangeDifficult *ui;
};

#endif // CHANGEDIFFICULT_H
