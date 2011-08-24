#include <QtGui>
#include <QApplication>
#include <QWidget>

#include "PolyGui.h"
#include "Huffman.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	// create our GUI object
	PolyGui G;

	Huffman h;
	h.readFreqFile();

	return app.exec();
}
