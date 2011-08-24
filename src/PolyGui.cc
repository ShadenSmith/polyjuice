/* Author: Justin Proffitt
 * Date: August 23 2011
 *
 * PolyGui.cc
 * Class implementation of the GUI used for PolyJuice
 *
 */
#include <QObject>
#include <iostream>
#include <QtGui>
#include <QApplication>
#include <QMainWindow>
#include <QWidget>

#include "PolyGui.h"
#include "imageManip.h"

/* Constructor for PolyGui class. Initializes the QT GUI components
 * and adds them to the proper layouts and connects the proper signals to
 * the proper slots.
 */
PolyGui::PolyGui()
{
	//Set the title, create the layout, and create the button objects.
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

	//Add each button to the innermost layout.
	buttonlayout->addWidget(loadImg);
	buttonlayout->addWidget(loadMsg);
	buttonlayout->addWidget(genFreq);
	buttonlayout->addWidget(loadFreq);
	buttonlayout->addWidget(saveImg);

	//Add the button layout and imageLabels to the outer layout. 
	layout->addLayout(buttonlayout);
	layout->addWidget(imageLabel1);
	layout->addWidget(imageLabel2);

	window.setLayout(layout);

	//Connect each signal to the proper slot.
	QObject::connect(loadFreq, SIGNAL(clicked()), this, SLOT(loadFreqFile()));
	QObject::connect(genFreq, SIGNAL(clicked()), this, SLOT(generateFreq()));
	QObject::connect(loadImg, SIGNAL(clicked()), this, SLOT(loadImage()));
	QObject::connect(saveImg, SIGNAL(clicked()), this, SLOT(saveImage()));
	QObject::connect(loadMsg, SIGNAL(clicked()), this, SLOT(loadMessage()));

	window.show();
}

/* 
 *
 *
 */
void PolyGui::resizeWindow()
{
}

/* loadFreqFile()
 * Opens a file selection dialogue to allow a non-default frequency file to
 * be used for encoding or decoding.
 */
void PolyGui::loadFreqFile()
{
	std::cout << "loadFreqFile()" << endl;
}

/* generateFreq()
 * Generates a frequency file from the currently loaded message file.
 */
void PolyGui::generateFreq()
{
	std::cout << "generateFreq()" << endl;
}

/* saveImage()
 * Encodes the Message into the currently loaded image and then saves the 
 * newly 'stegonagraphied' image.
 */
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

	std::cout << "saveImage()" << endl;
}

/* loadMessage()
 * Loads a file encoded in ascii to allow a Huffman coding to be generated 
 * and from that encoding the message to be placed inside the image.
 *
 */
void PolyGui::loadMessage()
{
	std::cout << "loadMessage()" << endl;
}

/* loadImage()
 * Loads an image that will either have a message injected or extracted
 * from its pixels. 
 */
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
	std::cout << "loadImage()" << endl;
}
