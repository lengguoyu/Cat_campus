#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <QWidget>

class QPushButton;

class StartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StartWidget(QWidget *parent = nullptr);

signals:
    void startGameRequested();
    void introRequested();

private:
    QPushButton* m_startButton;
    QPushButton* m_introButton;
};

#endif