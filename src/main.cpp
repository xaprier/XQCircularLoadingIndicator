#include <QApplication>

#include "MainWindow.hpp"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    auto *window = MainWindow::Instance();
    window->show();
    return a.exec();
}
