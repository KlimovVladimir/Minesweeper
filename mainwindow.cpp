#include "mainwindow.h"
#include "ui_mainwindow.h"

//#define DEBUG 1
#ifdef DEBUG
#include <QDebug>
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    m_Instance = this;
    ui->setupUi(this);
    isFirstClick = true;
    isGameOver = false;
    fieldWidht = 9;
    fieldHeight = 9;
    fieldMines = 10;
    flagCount = 0;
    timerCount = 0;

    gridLayout = new QGridLayout();
    gridLayout->setSpacing(0);

    lcdNumberFlags = new QLCDNumber();
    lcdNumberFlags->setMaximumWidth(50);
    lcdNumberFlags->setSegmentStyle(QLCDNumber::Flat);
    lcdNumberFlags->setStyleSheet("QLCDNumber{ color: red;}");
    lcdNumberFlags->display(fieldMines);

    lcdNumberTime = new QLCDNumber();
    lcdNumberTime->setMaximumWidth(50);
    lcdNumberTime->setSegmentStyle(QLCDNumber::Flat);
    lcdNumberTime->setStyleSheet("QLCDNumber{ color: red;}");
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTick()));

    smileButton = new QPushButton();
    smileButton->setIcon(QIcon(":/svg/svg/smile.svg"));
    smileButton->setIconSize(QSize(30, 30));
    smileButton->setMinimumSize(QSize(30, 30));
    smileButton->setMaximumSize(QSize(30, 30));
    smileButton->resize(30, 30);
    connect(smileButton, SIGNAL(clicked()), this, SLOT(restartGame()));
    //ui->centralwidget->setLayout(gridLayout);
    generateField();
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow *MainWindow::getInstance()
{
    return m_Instance;
}

bool MainWindow::getIsFirstClick() const
{
    return isFirstClick;
}

void MainWindow::setIsFirstClick(bool value)
{
    isFirstClick = value;
}

int MainWindow::getFieldWidht() const
{
    return fieldWidht;
}

void MainWindow::setFieldWidht(int value)
{
    fieldWidht = value;
}

int MainWindow::getFieldHeight() const
{
    return fieldHeight;
}

void MainWindow::setFieldHeight(int value)
{
    fieldHeight = value;
}

int MainWindow::getFieldMines() const
{
    return fieldMines;
}

void MainWindow::setFieldMines(int value)
{
    fieldMines = value;
}

int MainWindow::getFlagCount() const
{
    return flagCount;
}

void MainWindow::setFlagCount(int value)
{
    flagCount = value;
}

void MainWindow::setLcdNumber(int value)
{
    lcdNumberFlags->display(value);
}

void MainWindow::generateField()
{
    QWidget * wdg = new QWidget(this);
    QVBoxLayout* vLayout = new QVBoxLayout(wdg);
    QHBoxLayout* topLayout = new QHBoxLayout();

    gridLayout = new QGridLayout();
    gridLayout->setSpacing(0);

    buttons2DVector.clear();
    buttons2DVector.resize(fieldWidht);
    for (int i = 0; i < fieldWidht; i++) {
        buttons2DVector[i].resize(fieldHeight);

        for (int j = 0; j < fieldHeight; j++) {
            FieldButton *button = new FieldButton(i, j);
            connect(button, SIGNAL(fieldRevealed(int, int)), this, SLOT(openField(int, int)));
            connect(button, SIGNAL(boom(int, int)), this, SLOT(gameOverBoom(int, int)));
            connect(button, SIGNAL(setFlag()), this, SLOT(flagCounterPlus()));
            connect(button, SIGNAL(unsetFlag()), this, SLOT(flagCounterMinus()));
            gridLayout->addWidget(button, i, j);
            buttons2DVector[i][j] = button;
        }
    }

    //wdg->setLayout(gridLayout);

    topLayout->addWidget(lcdNumberTime, Qt::AlignLeft);
    topLayout->addWidget(smileButton, Qt::AlignCenter);
    topLayout->addWidget(lcdNumberFlags, Qt::AlignRight);
    vLayout->addLayout(topLayout);
    vLayout->addLayout(gridLayout);

    setCentralWidget(wdg);
    resize(sizeHint());
    adjustSize();
    setMinimumSize(sizeHint());
    setMaximumSize(sizeHint());
}

void MainWindow::placeMines(int x_first, int y_first) {
    srand((unsigned) time(NULL));
    int i = 0;
    while(i < fieldMines) {
        int x = rand() % fieldWidht;
        int y = rand() % fieldHeight;
        if(buttons2DVector[x][y]->getIsMine() || (x == x_first && y == y_first)) continue;
        buttons2DVector[x][y]->setIsMine(true);
        i++;
    }
}

void MainWindow::clearMines() {
    for (int i = 0; i < fieldWidht; i++) {
        for (int j = 0; j < fieldHeight; j++) {
            buttons2DVector[i][j]->reset();
        }
    }
}

bool MainWindow::outBounds(int x, int y){
  return x < 0 || y < 0 || x >= fieldWidht || y >= fieldHeight;
}

int MainWindow::calcNear(int x, int y) {
    int i = 0;
    for (int offsetX = -1; offsetX <= 1; offsetX++) {
        for (int offsetY = -1; offsetY <= 1; offsetY++) {
            if (outBounds(offsetX + x, offsetY + y)) continue;
            if (buttons2DVector[offsetX+x][offsetY+y]->getIsMine())
                i += 1;
        }
    }
    return i;
}

void MainWindow::openField(int x, int y) {
#ifdef DEBUG
    qInfo() << "x: " << x << "y: " << y;
#endif
    curr_x = x;
    curr_y = y;
    if (isFirstClick) {
        isFirstClick = false;
        placeMines(x, y);
        for (int i = 0; i < fieldWidht; i++) {
            for (int j = 0; j < fieldHeight; j++) {
                buttons2DVector[i][j]->setCountMines(calcNear(i, j));
            }
        }
        timer->start(1000);
    }
    reveal(x, y);
    gameOverComplete();
}

void MainWindow::flagCounterPlus() {
    flagCount++;
    setLcdNumber(fieldMines - flagCount);
}

void MainWindow::flagCounterMinus() {
    flagCount--;
    setLcdNumber(fieldMines - flagCount);
}

void MainWindow::restartGame() {
    this->setEnabled(true);
    clearMines();
    isFirstClick = true;
    isGameOver = false;
    timer->stop();
    timerCount = 0;
    lcdNumberTime->display(timerCount);
    setLcdNumber(fieldMines);
    smileButton->setIcon(QIcon(":/svg/svg/smile.svg"));
}

void MainWindow::timerTick() {
    if (isGameOver) {
        timer->stop();
        return;
    }
    timerCount++;
    lcdNumberTime->display(timerCount);
}

void MainWindow::gameOverBoom(int x, int y) {
    curr_x = x;
    curr_y = y;
    for (int i = 0; i < fieldWidht; i++) {
        for (int j = 0; j < fieldHeight; j++) {
            if (buttons2DVector[i][j]->getIsMine() || buttons2DVector[i][j]->getIsFlag())
                buttons2DVector[i][j]->setIsOpened(true);
            buttons2DVector[i][j]->setEnabled(false);
        }
    }
    isGameOver = true;
    smileButton->setIcon(QIcon(":/svg/svg/explosion.svg"));
}

void MainWindow::gameOverComplete() {
    int count = 0;
    flagCount = 0;
    for (int i = 0; i < fieldWidht; i++) {
        for (int j = 0; j < fieldHeight; j++) {
            if (!buttons2DVector[i][j]->getIsMine() && buttons2DVector[i][j]->getIsOpened())
                count++;
            if (buttons2DVector[i][j]->getIsFlag())
                flagCount++;
        }
    }
    setLcdNumber(fieldMines - flagCount);

    if (count == (fieldWidht * fieldHeight - fieldMines)) {
        for (int i = 0; i < fieldWidht; i++) {
            for (int j = 0; j < fieldHeight; j++) {
                if (buttons2DVector[i][j]->getIsMine()) {
                    buttons2DVector[i][j]->setFlagIcon();
                }
            }
        }
        isGameOver = true;
        QMessageBox Msgbox;
        Msgbox.setText("You win!");
        Msgbox.exec();
    }
}

void MainWindow::reveal(int x, int y) {
#ifdef DEBUG
  qInfo() << "reveal " << "x: " << x << "y: " << y;
#endif
  if (outBounds(x, y)) return;
  if (x == curr_x && y == curr_y)
      ;
  else
    if (buttons2DVector[x][y]->getIsOpened()) return;
  buttons2DVector[x][y]->setIsOpened(false);
  if (calcNear(x, y) != 0) return;
  reveal(x-1, y-1);
  reveal(x-1, y+1);
  reveal(x+1, y-1);
  reveal(x+1, y+1);
  reveal(x-1 ,y);
  reveal(x+1, y);
  reveal(x, y-1);
  reveal(x, y+1);
}

void MainWindow::showDifficultSelector()
{
    window = new ChangeDifficult(this);
    window->exec();
}

void MainWindow::on_actionRestart_triggered()
{
    this->setEnabled(true);
    clearMines();
    isFirstClick = true;
    isGameOver = false;
    timer->stop();
    timerCount = 0;
    lcdNumberTime->display(timerCount);
    setLcdNumber(fieldMines);
    smileButton->setIcon(QIcon(":/svg/svg/smile.svg"));
}

void MainWindow::on_actionChange_level_triggered()
{
   showDifficultSelector();
}
