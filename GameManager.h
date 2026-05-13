#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include "StoryManager.h"

class GameManager : public QObject
{
    Q_OBJECT

public:
    static GameManager& getInstance();

    void startGame();
    void makeChoice(int index);

    QString getCurrentText() const;
    QString getCurrentImage() const;
    QString getCurrentSceneId() const;
    QList<QString> getCurrentOptionsText() const;

    void notifyStoryUpdate();

    void triggerPoetryGame();
    void triggerBadmintonGame();

    void onPoetryGameFinished(int correctCount);
    void onBadmintonGameFinished(bool isVictory);

    void evaluateEnding();

signals:
    void storyUpdated();
    void gameEnded(const QString& endingId);

private:
    GameManager() = default;

private:
    StoryManager& m_storyManager = StoryManager::getInstance();
};

#endif