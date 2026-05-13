#include "PoetryGame.h"
#include <QHBoxLayout>
#include <QMessageBox>

PoetryGame::PoetryGame(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("古诗词问答挑战");
    setFixedSize(600, 450);
    setWindowFlags(Qt::Dialog);

    setStyleSheet(R"(
        QWidget {
            background-color: rgba(0,0,0,0.85);
            border-radius: 15px;
        }
        QLabel {
            color: #ffd700;
            font-size: 18px;
            font-weight: bold;
            background-color: rgba(0,0,0,0.6);
            border-radius: 10px;
            padding: 10px;
        }
        QRadioButton {
            color: white;
            font-size: 15px;
            background-color: rgba(0,0,0,0.5);
            border-radius: 8px;
            padding: 10px;
            margin: 3px;
        }
        QRadioButton::indicator {
            width: 16px;
            height: 16px;
        }
        QPushButton {
            background-color: #ff8c00;
            color: white;
            font-size: 16px;
            font-weight: bold;
            border: none;
            border-radius: 10px;
            padding: 10px 25px;
        }
        QPushButton:hover {
            background-color: #ff6a00;
        }
    )");

    loadQuestions();

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(15);

    m_progressLabel = new QLabel(this);
    m_progressLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(m_progressLabel);

    m_questionLabel = new QLabel(this);
    m_questionLabel->setWordWrap(true);
    m_questionLabel->setAlignment(Qt::AlignCenter);
    m_questionLabel->setMinimumHeight(80);
    mainLayout->addWidget(m_questionLabel);

    QVBoxLayout* optionsLayout = new QVBoxLayout();
    m_optionGroup = new QButtonGroup(this);

    for (int i = 0; i < 4; i++) {
        QRadioButton* rb = new QRadioButton(this);
        m_optionButtons.append(rb);
        optionsLayout->addWidget(rb);
        m_optionGroup->addButton(rb, i);
    }
    mainLayout->addLayout(optionsLayout);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    m_nextButton = new QPushButton("下一题", this);
    connect(m_nextButton, &QPushButton::clicked, this, &PoetryGame::onNextQuestion);
    buttonLayout->addWidget(m_nextButton);
    buttonLayout->addStretch();
    mainLayout->addLayout(buttonLayout);

    showQuestion(0);
}

void PoetryGame::loadQuestions()
{
    m_questions = {
        {"\"床前明月光，________。\" 请补充下一句。",
         {"低头思故乡", "疑是地上霜", "处处闻啼鸟", "粒粒皆辛苦"}, 1},
        {"下列哪句诗出自杜甫的《春望》？",
         {"天生我材必有用", "烽火连三月", "大漠孤烟直", "采菊东篱下"}, 1},
        {"\"欲穷千里目，更上一层楼。\" 的作者是？",
         {"李白", "杜甫", "王之涣", "王维"}, 2},
        {"下列哪句诗描写的是春天？",
         {"接天莲叶无穷碧", "霜叶红于二月花", "草长莺飞二月天", "千山鸟飞绝"}, 2},
        {"\"海内存知己，天涯若比邻。\" 出自王勃的哪首诗？",
         {"滕王阁序", "送杜少府之任蜀州", "凉州词", "出塞"}, 1}
    };
}

void PoetryGame::showQuestion(int index)
{
    if (index >= m_questions.size()) {
        finishGame();
        return;
    }

    m_progressLabel->setText(QString("📖 第 %1 / %2 题 📖").arg(index + 1).arg(m_questions.size()));

    const PoetryQuestion& q = m_questions[index];
    m_questionLabel->setText(q.question);

    for (int i = 0; i < m_optionButtons.size(); i++) {
        if (i < q.options.size()) {
            m_optionButtons[i]->setText(QString("%1. %2").arg(QChar('A' + i)).arg(q.options[i]));
            m_optionButtons[i]->setVisible(true);
        } else {
            m_optionButtons[i]->setVisible(false);
        }
    }

    m_optionGroup->setExclusive(false);
    for (QAbstractButton* btn : m_optionGroup->buttons()) {
        btn->setChecked(false);
    }
    m_optionGroup->setExclusive(true);
}

void PoetryGame::onNextQuestion()
{
    QAbstractButton* selected = m_optionGroup->checkedButton();
    if (!selected) {
        QMessageBox::information(this, "提示", "请选择一个答案！");
        return;
    }

    int selectedIndex = m_optionGroup->id(selected);
    const PoetryQuestion& q = m_questions[m_currentIndex];

    bool isCorrect = (selectedIndex == q.correctIndex);
    if (isCorrect) {
        m_correctCount++;
        QMessageBox::information(this, "结果", "✓ 回答正确！ +5智慧");
    } else {
        QString correctAnswer = q.options[q.correctIndex];
        QMessageBox::information(this, "结果", QString("✗ 回答错误\n正确答案是：%1").arg(correctAnswer));
    }

    m_currentIndex++;

    if (m_currentIndex >= m_questions.size()) {
        finishGame();
    } else {
        showQuestion(m_currentIndex);
    }
}

void PoetryGame::finishGame()
{
    int total = m_questions.size();
    int correct = m_correctCount;

    QMessageBox::information(this, "答题结束",
                             QString("🎉 你答对了 %1 / %2 道题 🎉\n\n获得 %3 点智慧值！")
                                 .arg(correct).arg(total).arg(correct * 5));

    emit gameFinished(correct);
    close();
}