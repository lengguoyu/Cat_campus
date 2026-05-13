#include "MainWindow.h"
#include "StartWidget.h"
#include "GameWidget.h"
#include "ResultDialog.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("小猫校园模拟器");
    setFixedSize(900, 650);

    m_stackedWidget = new QStackedWidget(this);
    setCentralWidget(m_stackedWidget);

    m_startWidget = new StartWidget(this);
    m_gameWidget = new GameWidget(this);

    m_stackedWidget->addWidget(m_startWidget);
    m_stackedWidget->addWidget(m_gameWidget);

    connect(m_startWidget, &StartWidget::startGameRequested, this, &MainWindow::showGame);
    connect(m_startWidget, &StartWidget::introRequested, this, &MainWindow::showIntro);

    m_stackedWidget->setCurrentWidget(m_startWidget);
}

MainWindow::~MainWindow() {}

void MainWindow::showGame()
{
    m_gameWidget->startGame();
    m_stackedWidget->setCurrentWidget(m_gameWidget);
}

void MainWindow::showIntro()
{
    QMessageBox::information(this, "游戏介绍",
                             "🐱 欢迎来到小猫校园模拟器！🐱\n\n"
                             "你将扮演小猫63度过完整校园日常，不同选择会触发分支剧情与属性变化。\n\n"
                             "📚 内置古诗答题小游戏\n"
                             "🏸 羽毛球对战小游戏\n\n"
                             "积累属性即可解锁多重专属结局！\n\n"
                             "祝你玩得开心~");
}