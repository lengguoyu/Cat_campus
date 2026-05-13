#ifndef POETRYGAME_H
#define POETRYGAME_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QButtonGroup>
#include <QStringList>

class PoetryGame : public QDialog
{
    Q_OBJECT

public:
    explicit PoetryGame(QWidget *parent = nullptr);
    ~PoetryGame();

signals:
    void gameFinished(int correctCount, int wrongCount);

private slots:
    void onNextQuestion();

private:
    struct Question {
        QString text;
        QStringList options;
        int correctIndex;
    };

    QList<Question> questions;
    int currentIndex;
    int correctAnswers;
    int wrongAnswers;
    QLabel *questionLabel;
    QButtonGroup *optionGroup;
    QList<QRadioButton*> radioBtns;
    QPushButton *nextBtn;

    void showCurrentQuestion();
    void finishGame();
};

#endif