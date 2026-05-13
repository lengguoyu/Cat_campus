#ifndef BADMINTONGAME_H
#define BADMINTONGAME_H

#include <QWidget>
#include <QLabel>

class BadmintonGame : public QWidget
{
    Q_OBJECT

public:
    explicit BadmintonGame(QWidget *parent = nullptr);
    ~BadmintonGame();

signals:
    void gameFinished(bool victory);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

private:
    int playerX, ballX, ballY, ballVx, ballVy, aiX;
    int playerScore, aiScore, gameState, timerId;
    QLabel *scoreLabel;

    static const int WIDTH = 600;
    static const int HEIGHT = 400;
    static const int PADDLE_WIDTH = 80;
    static const int PADDLE_HEIGHT = 10;
    static const int BALL_SIZE = 10;
    static const int AI_SPEED = 5;

    void resetBall();
    void checkScoreAndFinish();
};

#endif