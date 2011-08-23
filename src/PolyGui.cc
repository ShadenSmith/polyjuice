#include <QObject>
#include <iostream>
#include <QtGui>
#include <QApplication>
#include <QMainWindow>
#include <QWidget>

using namespace std;

#include "PolyGui.h"
#include "imageManip.h"
PolyGui::PolyGui()
{
	window.setWindowTitle(
		QApplication::translate("toplevel", "PolyJuice!"));
	buttonlayout = new QVBoxLayout();
	layout = new QHBoxLayout();
	loadFreq = new QPushButton(
		QApplication::translate("childwidget", "Load Frequency"), &window);
	loadImg = new QPushButton(
		QApplication::translate("childwidget", "Load Image"), &window);
	loadMsg = new QPushButton(
		QApplication::translate("childwidget", "Load Message"), &window);
	genFreq = new QPushButton(
		QApplication::translate("childwidget", 
								"Generate Frequency"), &window);
	saveImg = new QPushButton(
		QApplication::translate("childwidget", "Save Image"), &window);

	imageLabel1 = new QLabel;
	imageLabel2 = new QLabel;

	buttonlayout->addWidget(loadImg);
	buttonlayout->addWidget(loadMsg);
	buttonlayout->addWidget(genFreq);
	buttonlayout->addWidget(loadFreq);
	buttonlayout->addWidget(saveImg);

	layout->addLayout(buttonlayout);
	layout->addWidget(imageLabel1);
	layout->addWidget(imageLabel2);

	window.setLayout(layout);
	QObject::connect(loadFreq, SIGNAL(clicked()), this, SLOT(loadFreqFile()));
	QObject::connect(genFreq, SIGNAL(clicked()), this, SLOT(generateFreq()));
	QObject::connect(loadImg, SIGNAL(clicked()), this, SLOT(loadImage()));
	QObject::connect(saveImg, SIGNAL(clicked()), this, SLOT(saveImage()));
	QObject::connect(loadMsg, SIGNAL(clicked()), this, SLOT(loadMessage()));

	window.show();
}
void PolyGui::resizeWindow()
{
}
void PolyGui::loadFreqFile()
{
	cout << "loadFreqFile()" << endl;
}
void PolyGui::generateFreq()
{
	cout << "generateFreq()" << endl;
}
void PolyGui::saveImage()
{

	QRgb value;
	for(int i = 0; i < image2.width(); i += 1)
	{
		for(int j = 0; j < image2.height(); j += 1)
		{
			int color = image2.pixel(i,j);
			value = qRgba(qRed(color)+20, qGreen(color), qBlue(color), qAlpha(color));
			image2.setPixel(i,j, value);
		}
	}

	imageLabel2->setPixmap(QPixmap::fromImage(image2));

	cout << "saveImage()" << endl;
}
void PolyGui::loadMessage()
{
	cout << "loadMessage()" << endl;
}
void PolyGui::loadImage()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open File"), QDir::currentPath());
	if (!fileName.isEmpty())
	{
		QImage tempImage(fileName);
		if (tempImage.isNull())
		{
			QMessageBox::information(this, tr("Image Viewer"),
				tr("Cannot load %1.").arg(fileName));
			return;
		}
		QImage tempImage2(fileName);
		image1 = tempImage;
		image2 = tempImage2;
		imageLabel1->setPixmap(QPixmap::fromImage(image1));
		imageLabel2->setPixmap(QPixmap::fromImage(image2));
	}
	cout << "loadImage()" << endl;
}
