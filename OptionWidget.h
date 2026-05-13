#ifndef OPTIONWIDGET_H
#define OPTIONWIDGET_H

#include <QWidget>
#include <QList>

class QPushButton;
class QVBoxLayout;

class OptionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OptionWidget(QWidget *parent = nullptr);
    void setOptions(const QList<QString>& options);

signals:
    void optionSelected(int index);

private slots:
    void onButtonClicked();

private:
    void clearButtons();

private:
    QList<QPushButton*> m_buttons;
    QVBoxLayout* m_layout;
};

#endif