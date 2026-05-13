#ifndef STORYWIDGET_H
#define STORYWIDGET_H

#include <QTextEdit>

class StoryWidget : public QTextEdit
{
    Q_OBJECT

public:
    explicit StoryWidget(QWidget *parent = nullptr);
    void setStoryText(const QString& text);
};

#endif