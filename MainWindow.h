#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

class StartWidget;
class GameWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showGame();
    void showIntro();

private:
    QStackedWidget* m_stackedWidget;
    StartWidget* m_startWidget;
    GameWidget* m_gameWidget;
};

#endif