#include <QtGui>
#include <string>
#include <list>
#include <sqlite3>
#include "conversion.h"
#include <iostream>         // Are the two stream headers necessary here?
#include <fstream>

//include a bunch of qt stuff
#include <QCoreApplication>
#include <QDeclarativeEngine>
#include <QDeclarativeComponent>
#include <QDebug>

using namespace std;

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  QDeclarativeView view;

  view.setSource(QUrl::fromLocalFile("main.qml"));
     view.show();

  return app.exec();

}
