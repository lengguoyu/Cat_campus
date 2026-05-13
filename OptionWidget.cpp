#include "OptionWidget.h"
#include <QPushButton>
#include <QVBoxLayout>

OptionWidget::OptionWidget(QWidget *parent)
    : QWidget(parent)
{
    m_layout = new QVBoxLayout(this);
    m_layout->setSpacing(12);
    m_layout->setContentsMargins(20, 10, 20, 20);

    setStyleSheet(R"(
        QPushButton {
            background-color: rgba(0,0,0,0.55);
            color: white;
            font-size: 16px;
            font-weight: bold;
            border: 2px solid rgba(255,255,255,0.3);
            border-radius: 30px;
            padding: 12px 20px;
            text-align: left;
        }
        QPushButton:hover {
            background-color: rgba(0,0,0,0.75);
            border-color: #ff8c00;
        }
    )");
}

void OptionWidget::setOptions(const QList<QString>& options)
{
    clearButtons();

    for (int i = 0; i < options.size(); i++) {
        QPushButton* btn = new QPushButton(QString("%1. %2").arg(i + 1).arg(options[i]), this);
        btn->setProperty("index", i);
        connect(btn, &QPushButton::clicked, this, &OptionWidget::onButtonClicked);
        m_buttons.append(btn);
        m_layout->addWidget(btn);
    }

    m_layout->addStretch();
}

void OptionWidget::clearButtons()
{
    for (QPushButton* btn : m_buttons) {
        m_layout->removeWidget(btn);
        delete btn;
    }
    m_buttons.clear();
}

void OptionWidget::onButtonClicked()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (btn) {
        int index = btn->property("index").toInt();
        emit optionSelected(index);
    }
}