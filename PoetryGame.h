#ifndef POETRYGAME_H
#define POETRYGAME_H

#include <QWidget>
#include <QList>
#include <QRadioButton>
#include <QButtonGroup>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

struct PoetryQuestion {
    QString question;
    QStringList options;
    int correctIndex;
};

class PoetryGame : public QWidget
{
    Q_OBJECT

public:
    explicit PoetryGame(QWidget *parent = nullptr);

signals:
    void gameFinished(int correctCount);

private slots:
    void onNextQuestion();

private:
    void loadQuestions();
    void showQuestion(int index);
    void finishGame();

private:
    QList<PoetryQuestion> m_questions;
    int m_currentIndex = 0;
    int m_correctCount = 0;

    QLabel* m_questionLabel;
    QList<QRadioButton*> m_optionButtons;
    QButtonGroup* m_optionGroup;
    QPushButton* m_nextButton;
    QLabel* m_progressLabel;
};

#endif