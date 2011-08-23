#ifndef POLYGUI_H
#define POLYGUI_H
#include <QtGui>
#include <QObject>
#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include "imageManip.h"

class PolyGui : public QMainWindow
{
	Q_OBJECT

	public:
	PolyGui();

	public slots:
	void loadFreqFile();
	void loadImage();
	void generateFreq();
	void saveImage();
	void loadMessage();


	private:
	void resizeWindow();
	QWidget window;

	QPushButton *loadFreq;
	QPushButton *loadImg;
	QPushButton *genFreq;
	QPushButton *saveImg;
	QPushButton *loadMsg;
	QHBoxLayout *layout;
	QVBoxLayout *buttonlayout;

	QImage image1;
	QImage image2;
	QLabel *imageLabel1;
	QLabel *imageLabel2;
};
#endif
