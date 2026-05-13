#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QVariant>
#include <QList>

class PoetryGame;
class BadmintonGame;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onOptionClicked();
    void onPoetryFinished(int correctCount, int wrongCount);
    void onBadmintonFinished(bool victory);

private:
    enum EventStep {
        STEP_BREAKFAST, STEP_POETRY, STEP_LUNCH, STEP_NAP,
        STEP_MATH, STEP_GOSSIP, STEP_SUNSET, STEP_BADMINTON_CHOICE,
        STEP_BADMINTON_GAME, STEP_DINNER, STEP_ENDING
    };
    EventStep currentStep;

    int wisdom;
    int warmth;
    int sleep;

    QLabel *wisdomLabel;
    QLabel *warmthLabel;
    QLabel *sleepLabel;
    QLabel *eventDescLabel;
    QWidget *buttonWidget;
    QVBoxLayout *buttonLayout;
    QList<QPushButton*> optionButtons;

    void updateAttributeLabels();
    void showEventByStep();
    void clearOptions();
    void addOption(const QString &text, const QVariant &data);
    void applyAttributeChange(int deltaWisdom, int deltaWarmth, int deltaSleep);
    void showEndingAndAchievement();
    void triggerPoetryGame();
    void triggerBadmintonGame();
    void handleMathQuestion(const QString &question, int gainOnCorrect, int lossOnWrong);
};

#endif