#ifndef RESULTDIALOG_H
#define RESULTDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>

class ResultDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResultDialog(const QString& endingId, QWidget *parent = nullptr);

signals:
    void restartGame();
    void backToMenu();

private:
    QString getEndingTitle(const QString& endingId) const;
    QString getEndingDescription(const QString& endingId) const;
    QString getEndingIcon(const QString& endingId) const;

private:
    QLabel* m_titleLabel;
    QLabel* m_descLabel;
    QPushButton* m_restartButton;
    QPushButton* m_menuButton;
};

#endif