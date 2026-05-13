#include "mainwindow.h"
#include "poetrygame.h"
#include "badmintongame.h"
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), currentStep(STEP_BREAKFAST), wisdom(0), warmth(0), sleep(40)
{
    setWindowTitle("小猫的校园模拟");
    resize(600, 500);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    QHBoxLayout *statsLayout = new QHBoxLayout();
    wisdomLabel = new QLabel(QString("智慧: %1").arg(wisdom), this);
    warmthLabel = new QLabel(QString("暖心: %1").arg(warmth), this);
    sleepLabel = new QLabel(QString("睡眠: %1").arg(sleep), this);
    statsLayout->addWidget(wisdomLabel);
    statsLayout->addWidget(warmthLabel);
    statsLayout->addWidget(sleepLabel);
    mainLayout->addLayout(statsLayout);

    eventDescLabel = new QLabel(this);
    eventDescLabel->setWordWrap(true);
    eventDescLabel->setMinimumHeight(100);
    mainLayout->addWidget(eventDescLabel);

    buttonWidget = new QWidget(this);
    buttonLayout = new QVBoxLayout(buttonWidget);
    mainLayout->addWidget(buttonWidget);

    showEventByStep();
}

MainWindow::~MainWindow() {}

void MainWindow::updateAttributeLabels()
{
    wisdomLabel->setText(QString("智慧: %1").arg(wisdom));
    warmthLabel->setText(QString("暖心: %1").arg(warmth));
    sleepLabel->setText(QString("睡眠: %1").arg(sleep));
}

void MainWindow::clearOptions()
{
    qDeleteAll(optionButtons);
    optionButtons.clear();
    QLayoutItem *item;
    while ((item = buttonLayout->takeAt(0)) != nullptr) {
        delete item;
    }
}

void MainWindow::addOption(const QString &text, const QVariant &data)
{
    QPushButton *btn = new QPushButton(text, this);
    btn->setProperty("optionData", data);
    connect(btn, &QPushButton::clicked, this, &MainWindow::onOptionClicked);
    buttonLayout->addWidget(btn);
    optionButtons.append(btn);
}

void MainWindow::applyAttributeChange(int deltaWisdom, int deltaWarmth, int deltaSleep)
{
    wisdom += deltaWisdom;
    warmth += deltaWarmth;
    sleep += deltaSleep;
    updateAttributeLabels();
}

void MainWindow::showEventByStep()
{
    clearOptions();
    switch (currentStep) {
    case STEP_BREAKFAST:
        eventDescLabel->setText("【清晨】小猫63从睡梦中醒来，该吃早餐了！\n请选择：");
        addOption("楼下烧麦 + 酸奶 (睡眠+10)", QVariant::fromValue(QList<int>{0, 0, 10}));
        addOption("猫妈妈小霞做的面条 (暖心+10)", QVariant::fromValue(QList<int>{0, 10, 0}));
        break;
    case STEP_POETRY:
        eventDescLabel->setText("【语文课】古诗词知识竞赛开始啦！");
        triggerPoetryGame();
        break;
    case STEP_LUNCH:
        eventDescLabel->setText("【午餐时间】肚子饿了，吃什么好呢？");
        addOption("羊肉粉 (暖心+5, 睡眠+10)", QVariant::fromValue(QList<int>{0, 5, 10}));
        addOption("小炒 (睡眠-10, 暖心+10)", QVariant::fromValue(QList<int>{0, 10, -10}));
        break;
    case STEP_NAP:
        eventDescLabel->setText("午觉过后，做了一个好梦，睡眠值+20");
        applyAttributeChange(0, 0, 20);
        currentStep = STEP_MATH;
        showEventByStep();
        return;
    case STEP_MATH:
        eventDescLabel->setText("【数学课】老师提问，请选择一个知识点回答：");
        addOption("圆锥曲线", "conic");
        addOption("立体几何", "geometry");
        addOption("导数", "derivative");
        addOption("交集并集", "sets");
        break;
    case STEP_GOSSIP:
        eventDescLabel->setText("【课间闲聊】小猫17分享了八卦消息：");
        addOption("隔壁班小马和小鹿在一起了！(暖心+10, 智慧-5)", QVariant::fromValue(QList<int>{-5, 10, 0}));
        addOption("老马班主任喝醉了！(暖心+20, 智慧-5)", QVariant::fromValue(QList<int>{-5, 20, 0}));
        break;
    case STEP_SUNSET:
        eventDescLabel->setText("【傍晚】看到美丽的晚霞，你决定：");
        addOption("写诗赞美 (智慧+10)", QVariant::fromValue(QList<int>{10, 0, 0}));
        addOption("努力干饭 (暖心+10)", QVariant::fromValue(QList<int>{0, 10, 0}));
        addOption("大喊一声: 我去好美！(智慧-1, 暖心+15)", QVariant::fromValue(QList<int>{-1, 15, 0}));
        break;
    case STEP_BADMINTON_CHOICE:
        eventDescLabel->setText("同学发来羽毛球竞技邀请，是否接受？");
        addOption("接受挑战", "accept");
        addOption("拒绝 (智慧+5)", QVariant::fromValue(QList<int>{5, 0, 0}));
        break;
    case STEP_BADMINTON_GAME:
        eventDescLabel->setText("【羽毛球对决】开始！");
        triggerBadmintonGame();
        break;
    case STEP_DINNER:
        eventDescLabel->setText("【晚餐时间】晚上吃点什么呢？");
        addOption("关东煮 (智慧-5, 暖心+15)", QVariant::fromValue(QList<int>{-5, 15, 0}));
        addOption("铁板豆腐 (智慧-2, 暖心+10)", QVariant::fromValue(QList<int>{-2, 10, 0}));
        break;
    case STEP_ENDING:
        showEndingAndAchievement();
        break;
    default:
        break;
    }
}

void MainWindow::onOptionClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;
    QVariant data = btn->property("optionData");

    switch (currentStep) {
    case STEP_BREAKFAST: {
        QList<int> deltas = data.value<QList<int>>();
        if (deltas.size() == 3) applyAttributeChange(deltas[0], deltas[1], deltas[2]);
        currentStep = STEP_POETRY;
        showEventByStep();
        break;
    }
    case STEP_LUNCH: {
        QList<int> deltas = data.value<QList<int>>();
        if (deltas.size() == 3) applyAttributeChange(deltas[0], deltas[1], deltas[2]);
        currentStep = STEP_NAP;
        showEventByStep();
        break;
    }
    case STEP_MATH: {
        QString topic = data.toString();
        if (topic == "conic") handleMathQuestion("圆锥曲线：椭圆的标准方程是 x^2/a^2 + y^2/b^2 = 1 (a>b>0)，其中焦距c满足？", 30, -10);
        else if (topic == "geometry") handleMathQuestion("立体几何：若一条直线平行于平面内的一条直线，则这条直线与平面的位置关系是？", 30, -10);
        else if (topic == "derivative") handleMathQuestion("导数：函数 f(x)=x^2 的导数是？", 30, -10);
        else if (topic == "sets") handleMathQuestion("交集并集：若集合A={1,2,3}, B={2,3,4}，则A∩B = ?", 10, -20);
        break;
    }
    case STEP_GOSSIP: {
        QList<int> deltas = data.value<QList<int>>();
        if (deltas.size() == 3) applyAttributeChange(deltas[0], deltas[1], deltas[2]);
        currentStep = STEP_SUNSET;
        showEventByStep();
        break;
    }
    case STEP_SUNSET: {
        QList<int> deltas = data.value<QList<int>>();
        if (deltas.size() == 3) applyAttributeChange(deltas[0], deltas[1], deltas[2]);
        currentStep = STEP_BADMINTON_CHOICE;
        showEventByStep();
        break;
    }
    case STEP_BADMINTON_CHOICE: {
        if (data.toString() == "accept") {
            currentStep = STEP_BADMINTON_GAME;
            showEventByStep();
        } else {
            QList<int> deltas = data.value<QList<int>>();
            if (deltas.size() == 3) applyAttributeChange(deltas[0], deltas[1], deltas[2]);
            currentStep = STEP_DINNER;
            showEventByStep();
        }
        break;
    }
    case STEP_DINNER: {
        QList<int> deltas = data.value<QList<int>>();
        if (deltas.size() == 3) applyAttributeChange(deltas[0], deltas[1], deltas[2]);
        currentStep = STEP_ENDING;
        showEventByStep();
        break;
    }
    default:
        break;
    }
}

void MainWindow::triggerPoetryGame()
{
    PoetryGame *poetry = new PoetryGame(this);
    connect(poetry, &PoetryGame::gameFinished, this, &MainWindow::onPoetryFinished);
    poetry->setModal(true);
    poetry->show();
}

void MainWindow::onPoetryFinished(int correctCount, int wrongCount)
{
    int deltaWisdom = correctCount * 5;
    int deltaWarmth = -wrongCount;
    applyAttributeChange(deltaWisdom, deltaWarmth, 0);
    QMessageBox::information(this, "语文课结束", QString("古诗词竞赛结束！\n答对%1题，智慧+%2\n答错%3题，暖心%4")
                                                     .arg(correctCount).arg(deltaWisdom).arg(wrongCount).arg(deltaWarmth));
    currentStep = STEP_LUNCH;
    showEventByStep();
}

void MainWindow::handleMathQuestion(const QString &question, int gainOnCorrect, int lossOnWrong)
{
    bool ok;
    QString answer = QInputDialog::getText(this, "数学提问", question, QLineEdit::Normal, "", &ok);
    if (!ok) {
        applyAttributeChange(lossOnWrong, 0, 0);
        QMessageBox::information(this, "结果", "回答取消，视为错误！智慧值变化：" + QString::number(lossOnWrong));
    } else {
        bool correct = false;
        if (question.contains("椭圆") && answer.trimmed().toLower() == "c^2=a^2-b^2") correct = true;
        else if (question.contains("平行") && answer.trimmed().toLower() == "平行") correct = true;
        else if (question.contains("导数") && answer.trimmed().toLower() == "2x") correct = true;
        else if (question.contains("A∩B") && answer.trimmed() == "{2,3}") correct = true;

        if (correct) {
            applyAttributeChange(gainOnCorrect, 0, 0);
            QMessageBox::information(this, "结果", "回答正确！智慧值 +" + QString::number(gainOnCorrect));
        } else {
            applyAttributeChange(lossOnWrong, 0, 0);
            QMessageBox::information(this, "结果", "回答错误！智慧值变化：" + QString::number(lossOnWrong));
        }
    }
    currentStep = STEP_GOSSIP;
    showEventByStep();
}

void MainWindow::triggerBadmintonGame()
{
    BadmintonGame *game = new BadmintonGame(this);
    connect(game, &BadmintonGame::gameFinished, this, &MainWindow::onBadmintonFinished);
    game->show();
}

void MainWindow::onBadmintonFinished(bool victory)
{
    if (victory) {
        applyAttributeChange(15, 10, 0);
        QMessageBox::information(this, "羽毛球赛", "胜利！智慧+15，暖心+10");
    } else {
        applyAttributeChange(0, -5, 0);
        QMessageBox::information(this, "羽毛球赛", "失败...暖心-5");
    }
    currentStep = STEP_DINNER;
    showEventByStep();
}

void MainWindow::showEndingAndAchievement()
{
    eventDescLabel->setText("小猫63进入梦乡，做了一个好梦~\n校园生活告一段落...");
    clearOptions();

    QString achievement;
    if (wisdom >= 50 && warmth >= 30 && sleep >= 40) {
        achievement = "完美小猫！智慧、暖心、睡眠全面发展，校园之星！";
    } else if (wisdom >= 40) {
        achievement = "学霸猫猫：智勇双全，学术巅峰！";
    } else if (warmth >= 40) {
        achievement = "暖心天使：你温暖了整个校园！";
    } else if (sleep >= 60) {
        achievement = "睡神小猫：永远精力充沛！";
    } else if (wisdom < 10 && warmth < 10) {
        achievement = "糊涂小猫…… 要加油哦！";
    } else {
        achievement = "普通校园小猫，平凡的一天~";
    }

    QString endingText = QString("【最终属性】\n智慧: %1\n暖心: %2\n睡眠: %3\n\n成就达成：%4")
                             .arg(wisdom).arg(warmth).arg(sleep).arg(achievement);
    QMessageBox::information(this, "游戏结局", endingText);

    QPushButton *closeBtn = new QPushButton("结束游戏", this);
    connect(closeBtn, &QPushButton::clicked, this, &MainWindow::close);
    buttonLayout->addWidget(closeBtn);
}