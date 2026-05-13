#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>

class QLabel;
class StoryWidget;
class OptionWidget;

class GameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameWidget(QWidget *parent = nullptr);

    void startGame();

signals:
    void gameEnded(const QString& endingId);

private slots:
    void onStoryUpdated();
    void onOptionSelected(int index);
    void onAttributesChanged(int sleep, int wisdom, int warmth);

private:
    void updateUI();
    QString getImagePathForScene(const QString& sceneId) const;

private:
    StoryWidget* m_storyWidget;
    OptionWidget* m_optionWidget;
    QLabel* m_attrLabel;
};

#endif