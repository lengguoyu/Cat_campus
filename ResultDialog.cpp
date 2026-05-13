#include "ResultDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

ResultDialog::ResultDialog(const QString& endingId, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("结局");
    setFixedSize(550, 380);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setModal(true);

    setStyleSheet(R"(
        QDialog {
            background-color: #1a1a2e;
            border-radius: 25px;
            border: 2px solid #ffd700;
        }
        QLabel#title {
            color: #ffd700;
            font-size: 26px;
            font-weight: bold;
        }
        QLabel#desc {
            color: #e0e0e0;
            font-size: 16px;
        }
        QPushButton {
            background-color: #ff8c00;
            color: white;
            font-size: 15px;
            font-weight: bold;
            border: none;
            border-radius: 12px;
            padding: 10px 25px;
            min-width: 120px;
        }
        QPushButton:hover {
            background-color: #ff6a00;
        }
    )");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);

    QString icon = getEndingIcon(endingId);
    m_titleLabel = new QLabel(QString("%1 %2 %1").arg(icon).arg(getEndingTitle(endingId)), this);
    m_titleLabel->setObjectName("title");
    m_titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(m_titleLabel);

    m_descLabel = new QLabel(getEndingDescription(endingId), this);
    m_descLabel->setObjectName("desc");
    m_descLabel->setWordWrap(true);
    m_descLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(m_descLabel);

    mainLayout->addStretch();

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();

    m_restartButton = new QPushButton("🔄 重新开始", this);
    m_menuButton = new QPushButton("🏠 返回菜单", this);

    connect(m_restartButton, &QPushButton::clicked, [this]() {
        emit restartGame();
        accept();
    });
    connect(m_menuButton, &QPushButton::clicked, [this]() {
        emit backToMenu();
        accept();
    });

    buttonLayout->addWidget(m_restartButton);
    buttonLayout->addSpacing(20);
    buttonLayout->addWidget(m_menuButton);
    buttonLayout->addStretch();

    mainLayout->addLayout(buttonLayout);
}

QString ResultDialog::getEndingIcon(const QString& endingId) const
{
    if (endingId == "ending_scholar") return "🏆";
    if (endingId == "ending_sunshine") return "☀️";
    if (endingId == "ending_peaceful") return "🌸";
    if (endingId == "ending_sleepy") return "😴";
    if (endingId == "ending_hero") return "🦸";
    if (endingId == "ending_artist") return "🎨";
    return "✨";
}

QString ResultDialog::getEndingTitle(const QString& endingId) const
{
    if (endingId == "ending_scholar") return "学霸金榜结局";
    if (endingId == "ending_sunshine") return "温柔小太阳结局";
    if (endingId == "ending_peaceful") return "安稳幸福结局";
    if (endingId == "ending_sleepy") return "迷糊可爱结局";
    if (endingId == "ending_hero") return "勇敢英雄结局";
    if (endingId == "ending_artist") return "艺术文艺结局";
    return "普通结局";
}

QString ResultDialog::getEndingDescription(const QString& endingId) const
{
    if (endingId == "ending_scholar") {
        return "成绩稳居前列，老师夸奖，作文常被朗读，未来可期！\n\n解锁称号：语文之星 ⭐";
    }
    if (endingId == "ending_sunshine") {
        return "人缘超好，朋友信赖，善良勇敢，是大家的小温暖！\n\n解锁称号：校园小天使 👼";
    }
    if (endingId == "ending_peaceful") {
        return "平凡又治愈，每天开心安稳，没有烦恼！\n\n解锁称号：平凡小美好 🌼";
    }
    if (endingId == "ending_sleepy") {
        return "有点迷糊但超可爱，每天开开心心，人缘很好！\n\n解锁称号：瞌睡小猫 🐱💤";
    }
    if (endingId == "ending_hero") {
        return "冷静勇敢，救下学妹，被学校表扬，成为校园榜样！\n\n解锁称号：正义小猫 🦸‍♀️";
    }
    if (endingId == "ending_artist") {
        return "温柔安静，有艺术气质，被学长记住，气质独特！\n\n解锁称号：文艺小猫 🎵";
    }
    return "度过了平凡而充实的一天，期待明天的到来！";
}