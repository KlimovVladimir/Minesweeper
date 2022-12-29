#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFrame>
#include <QLabel>
#include <QLCDNumber>
#include <QTimer>
#include "fieldbutton.h"
#include "changedifficult.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    MainWindow *getInstance();
    void generateField();
    int calcNear(int x, int y);
    void placeMines(int x, int y);
    void clearMines();
    bool outBounds(int x, int y);
    void reveal(int x, int y);
    void gameOverComplete();
    void showDifficultSelector();

    bool getIsFirstClick() const;
    void setIsFirstClick(bool value);

    int getFieldWidht() const;
    void setFieldWidht(int value);

    int getFieldHeight() const;
    void setFieldHeight(int value);

    int getFieldMines() const;
    void setFieldMines(int value);

    int getFlagCount() const;
    void setFlagCount(int value);

    void setLcdNumber(int value);

private:
    bool isFirstClick;
    bool isGameOver;
    int fieldWidht;
    int fieldHeight;
    int fieldMines;
    int flagCount;
    int curr_x, curr_y;
    int timerCount;
    QVector<QVector<FieldButton*>> buttons2DVector;
    ChangeDifficult* window;
    QGridLayout* gridLayout;
    QPushButton* smileButton;
    QLCDNumber* lcdNumberFlags;
    QLCDNumber* lcdNumberTime;
    QTimer *timer;

public slots:
    void openField(int x, int y);
    void gameOverBoom(int x, int y);
    void flagCounterPlus();
    void flagCounterMinus();
    void restartGame();
    void timerTick();

private slots:
    void on_actionRestart_triggered();
    void on_actionChange_level_triggered();

private:
    Ui::MainWindow *ui;
    MainWindow* m_Instance;
};
#endif // MAINWINDOW_H
