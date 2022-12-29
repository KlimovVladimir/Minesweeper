#include "fieldbutton.h"

FieldButton::FieldButton(int x, int y) : QPushButton("", NULL)
{
    this->setMinimumSize(QSize(20, 20));
    this->setMaximumSize(QSize(20, 20));
    this->resize(20, 20);
    this->x = x;
    this->y = y;
    isMine = false;
    isOpened = false;
    isFlag = false;
    countMines = 0;

    connect(this, SIGNAL(clicked()), this, SLOT(openField()));
    connect(this, SIGNAL(rightClicked()), this, SLOT(setFlagField()));
}

void FieldButton::openField()
{
    if (isFlag)
        return;
    isOpened = true;
    this->setEnabled(false);
    if (isMine) {
        this->setIcon(QIcon(":/svg/svg/naval-mine.svg"));
        this->setStyleSheet("background-color: rgba(255, 0, 0, 0.4); border: none;");
        emit boom(x, y);
        return;
    }
    else if (countMines > 0)
        this->setText(QString::number(countMines));
    emit fieldRevealed(x, y);
}

void FieldButton::setFlagField()
{
    if (!isFlag) {
        isFlag = true;
        this->setIcon(QIcon(":/svg/svg/red-flag.svg"));
        emit setFlag();
    }
    else {
        isFlag = false;
        this->setIcon(QIcon());
        emit unsetFlag();
    }
}

void FieldButton::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
        emit clicked();
    else if (e->button() == Qt::RightButton)
        emit rightClicked();
}

bool FieldButton::getIsMine() const
{
    return isMine;
}

void FieldButton::setIsMine(bool value)
{
    isMine = value;
}

int FieldButton::getCountMines() const
{
    return countMines;
}

void FieldButton::setCountMines(int value)
{
    countMines = value;
}

bool FieldButton::getIsOpened() const
{
    return isOpened;
}

void FieldButton::reset()
{
    isMine = false;
    isOpened = false;
    isFlag = false;
    countMines = 0;
    this->setEnabled(true);
    this->setIcon(QIcon());
    this->setText("");
    this->setStyleSheet("");
}

bool FieldButton::getIsFlag() const
{
    return isFlag;
}

void FieldButton::setIsFlag(bool value)
{
    isFlag = value;
}


void FieldButton::setIsOpened(bool isGameOver)
{
    isOpened = true;
    if (!isGameOver)
        isFlag = false;
    this->setEnabled(false);
    this->setIcon(QIcon());
    this->setText("");
    if (!isMine && isFlag && isGameOver)
        this->setIcon(QIcon(":/svg/svg/naval-mine-cross.svg"));
    else if (isMine)
        this->setIcon(QIcon(":/svg/svg/naval-mine.svg"));
    else if (countMines > 0)
        this->setText(QString::number(countMines));
}

void FieldButton::setFlagIcon()
{
    this->setEnabled(false);
    this->setIcon(QIcon(":/svg/svg/red-flag.svg"));
}
