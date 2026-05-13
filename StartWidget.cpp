#include "StartWidget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

StartWidget::StartWidget(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet(R"(
        StartWidget {
            background-image: url(:/images/campus.jpg);
            background-position: center;
            background-repeat: no-repeat;
            background-size: cover;
        }
        QPushButton {
            background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 #ff8c00, stop:1 #ff4500);
            color: white;
            font-size: 20px;
            font-weight: bold;
            font-family: "Microsoft YaHei";
            border: none;
            border-radius: 30px;
            padding: 15px 40px;
            min-width: 200px;
        }
        QPushButton:hover {
            background-color: #ff6a00;
        }
    )");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addStretch();

    QLabel* titleLabel = new QLabel("🐱 小猫校园模拟器 🐱", this);
    titleLabel->setStyleSheet("color: #ffd700; font-size: 36px; font-weight: bold; background-color: rgba(0,0,0,0.5); border-radius: 20px; padding: 10px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel, 0, Qt::AlignCenter);

    layout->addStretch();

    m_startButton = new QPushButton("✨ 开始游戏 ✨", this);
    m_introButton = new QPushButton("📖 游戏介绍 📖", this);

    connect(m_startButton, &QPushButton::clicked, this, &StartWidget::startGameRequested);
    connect(m_introButton, &QPushButton::clicked, this, &StartWidget::introRequested);

    layout->addWidget(m_startButton, 0, Qt::AlignCenter);
    layout->addSpacing(20);
    layout->addWidget(m_introButton, 0, Qt::AlignCenter);
    layout->addStretch();
}