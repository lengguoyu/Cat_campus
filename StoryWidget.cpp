#include "StoryWidget.h"

StoryWidget::StoryWidget(QWidget *parent)
    : QTextEdit(parent)
{
    setReadOnly(true);
    setFrameStyle(QFrame::NoFrame);

    setStyleSheet(R"(
        QTextEdit {
            background-color: transparent;
            color: #ffffff;
            font-size: 19px;
            font-family: "Microsoft YaHei", "SimHei", "PingFang SC";
            font-weight: bold;
            border: none;
        }
    )");

    document()->setDocumentMargin(25);
}

void StoryWidget::setStoryText(const QString& text)
{
    setPlainText(text);
    QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::Start);
    setTextCursor(cursor);
}