<<<<<<< HEAD
#include "game_main_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameMainWindow w;
    w.show();

    return a.exec();
=======
#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
>>>>>>> 0d38c3f4cbd64d8d99e73da83a3369d255c33053
}