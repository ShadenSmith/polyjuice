#include <QtGui>
#include <QApplication>
#include <QWidget>
#include "PolyGui.h"
using namespace std;
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	PolyGui *G = new PolyGui();

	return app.exec();
}
