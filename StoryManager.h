#ifndef STORYMANAGER_H
#define STORYMANAGER_H

#include <QObject>
#include <QMap>
#include <QList>
#include <QPair>
#include <functional>

struct StoryNode {
    int id;
    QString sceneId;
    QString text;
    QString imagePath;
    QList<QPair<QString, std::function<void()>>> options;
    bool isEnding = false;
    QString endingId;
};

class StoryManager : public QObject
{
    Q_OBJECT

public:
    static StoryManager& getInstance();

    void buildStoryTree();
    StoryNode getNode(int id) const;
    int getCurrentNodeId() const { return m_currentNodeId; }
    void setCurrentNodeId(int id) { m_currentNodeId = id; }

    void setFirstActChoice(int choice) { m_firstActChoice = choice; }
    void setSecondActChoice(int choice) { m_secondActChoice = choice; }
    void setIsDiarrhea(bool isDiarrhea) { m_isDiarrhea = isDiarrhea; }

    int getFirstActChoice() const { return m_firstActChoice; }
    int getSecondActChoice() const { return m_secondActChoice; }
    bool getIsDiarrhea() const { return m_isDiarrhea; }

    void setFlag(const QString& flag, bool value);
    bool getFlag(const QString& flag) const;

    void setPoetryCorrectCount(int count) { m_poetryCorrectCount = count; }
    int getPoetryCorrectCount() const { return m_poetryCorrectCount; }

private:
    StoryManager() = default;
    void addNode(const StoryNode& node);

private:
    QMap<int, StoryNode> m_nodes;
    int m_currentNodeId = 0;

    int m_firstActChoice = -1;
    int m_secondActChoice = -1;
    bool m_isDiarrhea = false;
    int m_poetryCorrectCount = 0;

    QMap<QString, bool> m_flags;
};

#endif