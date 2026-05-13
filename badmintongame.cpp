#include "badmintongame.h"
#include <QPainter>
#include <QMessageBox>
#include <QKeyEvent>

const int BadmintonGame::WIDTH;
const int BadmintonGame::HEIGHT;
const int BadmintonGame::PADDLE_WIDTH;
const int BadmintonGame::PADDLE_HEIGHT;
const int BadmintonGame::BALL_SIZE;
const int BadmintonGame::AI_SPEED;

BadmintonGame::BadmintonGame(QWidget *parent)
    : QWidget(parent), playerX(WIDTH/2 - PADDLE_WIDTH/2), aiX(WIDTH/2 - PADDLE_WIDTH/2),
    playerScore(0), aiScore(0), gameState(0)
{
    setFixedSize(WIDTH, HEIGHT);
    setWindowTitle("小猫羽毛球对决");
    setFocusPolicy(Qt::StrongFocus);

    scoreLabel = new QLabel("0 : 0", this);
    scoreLabel->setAlignment(Qt::AlignCenter);
    scoreLabel->setGeometry(WIDTH/2 - 30, 20, 60, 30);
    scoreLabel->setStyleSheet("font-size: 16px; font-weight: bold; background: rgba(0,0,0,0.5); color: white;");

    resetBall();
    timerId = startTimer(16);
}

BadmintonGame::~BadmintonGame()
{
    killTimer(timerId);
}

void BadmintonGame::resetBall()
{
    ballX = WIDTH/2;
    ballY = HEIGHT/2;
    ballVx = (rand() % 2 == 0) ? 3 : -3;
    ballVy = 3;
}

void BadmintonGame::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setBrush(Qt::darkGreen);
    painter.drawRect(0, 0, WIDTH, HEIGHT);
    painter.setBrush(Qt::white);
    painter.drawRect(playerX, HEIGHT - 30, PADDLE_WIDTH, PADDLE_HEIGHT);
    painter.drawRect(aiX, 20, PADDLE_WIDTH, PADDLE_HEIGHT);
    painter.setBrush(Qt::yellow);
    painter.drawEllipse(ballX - BALL_SIZE/2, ballY - BALL_SIZE/2, BALL_SIZE, BALL_SIZE);
}

void BadmintonGame::keyPressEvent(QKeyEvent *event)
{
    if (gameState != 0) return;
    if (event->key() == Qt::Key_Left) {
        playerX = qMax(0, playerX - 15);
    } else if (event->key() == Qt::Key_Right) {
        playerX = qMin(WIDTH - PADDLE_WIDTH, playerX + 15);
    }
}

void BadmintonGame::timerEvent(QTimerEvent *)
{
    if (gameState != 0) return;

    ballX += ballVx;
    ballY += ballVy;

    if (ballX <= 0 || ballX >= WIDTH) {
        ballVx = -ballVx;
        ballX = qBound(0, ballX, WIDTH);
    }

    if (aiX + PADDLE_WIDTH/2 < ballX) {
        aiX = qMin(WIDTH - PADDLE_WIDTH, aiX + AI_SPEED);
    } else {
        aiX = qMax(0, aiX - AI_SPEED);
    }

    if (ballY + BALL_SIZE/2 >= HEIGHT - 30 && ballY - BALL_SIZE/2 <= HEIGHT - 30 + PADDLE_HEIGHT &&
        ballX + BALL_SIZE/2 >= playerX && ballX - BALL_SIZE/2 <= playerX + PADDLE_WIDTH) {
        int hitPos = ballX - (playerX + PADDLE_WIDTH/2);
        ballVx += hitPos / 10;
        ballVy = -ballVy;
        ballY = HEIGHT - 30 - BALL_SIZE/2;
    }
    else if (ballY - BALL_SIZE/2 <= 20 + PADDLE_HEIGHT && ballY + BALL_SIZE/2 >= 20 &&
             ballX + BALL_SIZE/2 >= aiX && ballX - BALL_SIZE/2 <= aiX + PADDLE_WIDTH) {
        ballVy = -ballVy;
        ballY = 20 + PADDLE_HEIGHT + BALL_SIZE/2;
    }

    if (ballY > HEIGHT) {
        aiScore++;
        scoreLabel->setText(QString("%1 : %2").arg(playerScore).arg(aiScore));
        resetBall();
        checkScoreAndFinish();
    } else if (ballY < 0) {
        playerScore++;
        scoreLabel->setText(QString("%1 : %2").arg(playerScore).arg(aiScore));
        resetBall();
        checkScoreAndFinish();
    }

    if (ballVx > 8) ballVx = 8;
    if (ballVx < -8) ballVx = -8;
    if (ballVy > 6) ballVy = 6;
    if (ballVy < -6) ballVy = -6;

    update();
}

void BadmintonGame::checkScoreAndFinish()
{
    if (playerScore >= 5) {
        gameState = 1;
        killTimer(timerId);
        QMessageBox::information(this, "比赛结束", "你赢得了羽毛球比赛！");
        emit gameFinished(true);
        close();
    } else if (aiScore >= 5) {
        gameState = 2;
        killTimer(timerId);
        QMessageBox::information(this, "比赛结束", "你输掉了羽毛球比赛...");
        emit gameFinished(false);
        close();
    }
}