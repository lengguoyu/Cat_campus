#include "GameWidget.h"
#include "GameManager.h"
#include "AttributeManager.h"
#include "StoryWidget.h"
#include "OptionWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFile>

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(25, 20, 25, 20);

    QHBoxLayout* topLayout = new QHBoxLayout();
    topLayout->addStretch();
    m_attrLabel = new QLabel(this);
    m_attrLabel->setStyleSheet(R"(
        QLabel {
            color: white;
            font-size: 14px;
            font-weight: bold;
            background-color: rgba(0,0,0,0.6);
            border-radius: 20px;
            padding: 8px 18px;
        }
    )");
    topLayout->addWidget(m_attrLabel);
    mainLayout->addLayout(topLayout);

    m_storyWidget = new StoryWidget(this);
    mainLayout->addWidget(m_storyWidget, 1);

    m_optionWidget = new OptionWidget(this);
    mainLayout->addWidget(m_optionWidget);

    connect(&GameManager::getInstance(), &GameManager::storyUpdated,
            this, &GameWidget::onStoryUpdated);
    connect(&AttributeManager::getInstance(), &AttributeManager::attributesChanged,
            this, &GameWidget::onAttributesChanged);
    connect(m_optionWidget, &OptionWidget::optionSelected,
            this, &GameWidget::onOptionSelected);

    setStyleSheet("GameWidget { background-color: #2c3e50; }");
}

void GameWidget::startGame()
{
    GameManager::getInstance().startGame();
    onAttributesChanged(0, 0, 0);
}

void GameWidget::onStoryUpdated()
{
    updateUI();
}

void GameWidget::updateUI()
{
    GameManager& gm = GameManager::getInstance();
    m_storyWidget->setStoryText(gm.getCurrentText());
    m_optionWidget->setOptions(gm.getCurrentOptionsText());

    QString sceneId = gm.getCurrentSceneId();
    QString imagePath = getImagePathForScene(sceneId);

    if (!imagePath.isEmpty() && QFile::exists(":" + imagePath)) {
        setStyleSheet(QString("GameWidget { background-image: url(%1); background-position: center; background-repeat: no-repeat; background-size: cover; }").arg(imagePath));
    }
}

QString GameWidget::getImagePathForScene(const QString& sceneId) const
{
    if (sceneId == "bedroom") return ":/images/bedroom.jpg";
    if (sceneId == "living_room") return ":/images/living_room.jpg";
    if (sceneId == "classroom") return ":/images/classroom.jpg";
    if (sceneId == "canteen") return ":/images/canteen.jpg";
    if (sceneId == "free_time") return ":/images/free_time.jpg";
    if (sceneId == "sunset") return ":/images/sunset.jpg";
    if (sceneId == "night_classroom") return ":/images/night_classroom.jpg";
    if (sceneId == "bedroom_night") return ":/images/bedroom_night.jpg";
    if (sceneId == "library") return ":/images/library.jpg";
    if (sceneId == "piano_room") return ":/images/piano_room.jpg";
    if (sceneId == "night_market") return ":/images/night_market.jpg";
    if (sceneId == "shaomai") return ":/images/shaomai.jpg";
    if (sceneId == "lamb_noodles") return ":/images/lamb_noodles.jpg";
    if (sceneId == "stir_fry") return ":/images/stir_fry.jpg";
    if (sceneId == "guandongzhu") return ":/images/guandongzhu.jpg";
    if (sceneId == "tiebodoufu") return ":/images/tiebodoufu.jpg";

    return "";
}

void GameWidget::onOptionSelected(int index)
{
    GameManager::getInstance().makeChoice(index);
}

void GameWidget::onAttributesChanged(int sleep, int wisdom, int warmth)
{
    m_attrLabel->setText(QString("😴 睡眠: %1    📚 智慧: %2    💖 暖心: %3")
                             .arg(sleep).arg(wisdom).arg(warmth));
}