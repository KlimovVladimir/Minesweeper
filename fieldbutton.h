#ifndef FIELDBUTTON_H
#define FIELDBUTTON_H
#include <QPushButton>
#include <QMouseEvent>


class FieldButton : public QPushButton
{
    Q_OBJECT
public:
    FieldButton(int x, int y);

    bool getIsMine() const;
    void setIsMine(bool value);

    int getCountMines() const;
    void setCountMines(int value);

    bool getIsOpened() const;
    void setIsOpened(bool isGameOver);

    void reset();

    bool getIsFlag() const;
    void setIsFlag(bool value);

    void setFlagIcon();
private:
    int x, y;
    bool isMine;
    int countMines;
    bool isOpened;
    bool isFlag;

public slots:
    void openField();
    void setFlagField();
    void mousePressEvent(QMouseEvent *event);

signals:
    void rightClicked();
    void fieldRevealed(int x, int y);
    void boom(int x, int y);
    void setFlag();
    void unsetFlag();
};

#endif // FIELDBUTTON_H
