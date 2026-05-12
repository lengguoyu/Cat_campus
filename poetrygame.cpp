#include "poetrygame.h"
#include <QMessageBox>

PoetryGame::PoetryGame(QWidget *parent)
    : QDialog(parent), currentIndex(0), correctAnswers(0), wrongAnswers(0)
{
    setWindowTitle("古诗词填空");
    setModal(true);
    resize(400, 300);

    Question q1 = {"\"床前____光，疑是地上霜。\" 填入正确的字？", {"明", "月", "亮", "白"}, 0};
    Question q2 = {"\"春眠不觉晓，处处闻啼____。\"", {"鸟", "鸣", "叫", "唱"}, 0};
    Question q3 = {"\"欲穷千里目，更上一____楼。\"", {"层", "座", "栋", "个"}, 0};
    Question q4 = {"\"明月几时有，把酒问____天。\"", {"青", "苍", "蓝", "碧"}, 0};
    Question q5 = {"\"小荷才露尖尖角，早有蜻蜓____上头。\"", {"立", "站", "落", "停"}, 0};

    questions.append(q1);
    questions.append(q2);
    questions.append(q3);
    questions.append(q4);
    questions.append(q5);

    QVBoxLayout *layout = new QVBoxLayout(this);
    questionLabel = new QLabel(this);
    questionLabel->setWordWrap(true);
    layout->addWidget(questionLabel);

    QHBoxLayout *radioLayout = new QHBoxLayout();
    optionGroup = new QButtonGroup(this);
    for (int i = 0; i < 4; ++i) {
        QRadioButton *rb = new QRadioButton(this);
        radioBtns.append(rb);
        optionGroup->addButton(rb, i);
        radioLayout->addWidget(rb);
    }
    layout->addLayout(radioLayout);

    nextBtn = new QPushButton("下一题", this);
    connect(nextBtn, &QPushButton::clicked, this, &PoetryGame::onNextQuestion);
    layout->addWidget(nextBtn);

    showCurrentQuestion();
}

PoetryGame::~PoetryGame() {}

void PoetryGame::showCurrentQuestion()
{
    if (currentIndex >= questions.size()) {
        finishGame();
        return;
    }
    const Question &q = questions[currentIndex];
    questionLabel->setText(q.text);
    for (int i = 0; i < radioBtns.size(); ++i) {
        radioBtns[i]->setText(q.options[i]);
        radioBtns[i]->setChecked(false);
    }
}

void PoetryGame::onNextQuestion()
{
    int selected = optionGroup->checkedId();
    if (selected == -1) {
        QMessageBox::warning(this, "提示", "请选择一个答案！");
        return;
    }
    const Question &q = questions[currentIndex];
    if (selected == q.correctIndex) {
        correctAnswers++;
    } else {
        wrongAnswers++;
    }
    currentIndex++;
    if (currentIndex < questions.size()) {
        showCurrentQuestion();
    } else {
        finishGame();
    }
}

void PoetryGame::finishGame()
{
    emit gameFinished(correctAnswers, wrongAnswers);
    accept();
}