#include "GameManager.h"
#include "AttributeManager.h"
#include "PoetryGame.h"
#include "BadmintonGame.h"

GameManager& GameManager::getInstance()
{
    static GameManager instance;
    return instance;
}

void GameManager::startGame()
{
    AttributeManager::getInstance().reset();
    m_storyManager.buildStoryTree();
    m_storyManager.setCurrentNodeId(0);
    emit storyUpdated();
}

void GameManager::makeChoice(int index)
{
    StoryNode currentNode = m_storyManager.getNode(m_storyManager.getCurrentNodeId());
    if (index >= 0 && index < currentNode.options.size()) {
        currentNode.options[index].second();
    }
}

QString GameManager::getCurrentText() const
{
    StoryNode node = m_storyManager.getNode(m_storyManager.getCurrentNodeId());
    return node.text;
}

QString GameManager::getCurrentImage() const
{
    StoryNode node = m_storyManager.getNode(m_storyManager.getCurrentNodeId());
    return node.imagePath;
}

QString GameManager::getCurrentSceneId() const
{
    StoryNode node = m_storyManager.getNode(m_storyManager.getCurrentNodeId());
    return node.sceneId;
}

QList<QString> GameManager::getCurrentOptionsText() const
{
    QList<QString> texts;
    StoryNode node = m_storyManager.getNode(m_storyManager.getCurrentNodeId());
    for (const auto& opt : node.options) {
        texts.append(opt.first);
    }
    return texts;
}

void GameManager::notifyStoryUpdate()
{
    emit storyUpdated();
}

void GameManager::triggerPoetryGame()
{
    PoetryGame* game = new PoetryGame();
    QObject::connect(game, &PoetryGame::gameFinished, [this](int correctCount) {
        onPoetryGameFinished(correctCount);
    });
    game->setAttribute(Qt::WA_DeleteOnClose);
    game->show();
}

void GameManager::triggerBadmintonGame()
{
    BadmintonGame* game = new BadmintonGame();
    QObject::connect(game, &BadmintonGame::gameFinished, [this](bool isVictory) {
        onBadmintonGameFinished(isVictory);
    });
    game->setAttribute(Qt::WA_DeleteOnClose);
    game->show();
}

void GameManager::onPoetryGameFinished(int correctCount)
{
    m_storyManager.setPoetryCorrectCount(correctCount);
    int wisdomGain = correctCount * 5;
    if (wisdomGain > 0) {
        AttributeManager::getInstance().addWisdom(wisdomGain);
    }

    m_storyManager.setCurrentNodeId(5);
    emit storyUpdated();
}

void GameManager::onBadmintonGameFinished(bool isVictory)
{
    AttributeManager::getInstance().addWarmth(10);
    if (isVictory) {
        AttributeManager::getInstance().addWarmth(10);
        AttributeManager::getInstance().addWisdom(15);
    } else {
        AttributeManager::getInstance().addWarmth(-5);
    }

    m_storyManager.setCurrentNodeId(17);
    emit storyUpdated();
}

void GameManager::evaluateEnding()
{
    AttributeManager& attr = AttributeManager::getInstance();

    if (attr.getWisdom() >= 90) {
        emit gameEnded("ending_scholar");
        return;
    }

    if (attr.getWarmth() >= 120) {
        emit gameEnded("ending_sunshine");
        return;
    }

    if (attr.getSleep() >= 70 && attr.getWarmth() >= 60 && attr.getWisdom() >= 50) {
        emit gameEnded("ending_peaceful");
        return;
    }

    if (attr.getWisdom() <= 30 && attr.getSleep() >= 60) {
        emit gameEnded("ending_sleepy");
        return;
    }

    if (m_storyManager.getFlag("called_police") && attr.getWarmth() >= 100) {
        emit gameEnded("ending_hero");
        return;
    }

    if (m_storyManager.getFlag("closed_piano_door") && m_storyManager.getFlag("wrote_poem")) {
        emit gameEnded("ending_artist");
        return;
    }

    emit gameEnded("ending_normal");
}