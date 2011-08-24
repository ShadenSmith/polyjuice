/* Author: Justin Proffitt
 * Date: August 23 2011
 *
 * ImageManip.cc
 * Contains the functionality to manipulate a QImage object from QT by
 * reading/changing the least significant bits of each pixel.
 */
#include <std::string>
#include <vector>
#include <iostream>
#include <QImage>

#include "imageManip.h"

/* adjustPixel
 *
 * Function that modifies the least significant bit of an integer.
 * 
 * Args:
 *	int value: integer to modify
 *	bool in: determines how the integer should be modified.
 * Returns:
 *	int - the integer with the LSB modified.
 */
int adjustPixel(int value, bool in)
{
	if(in)
		value |= 0x0001; // Swap the last bit to a 1
	else
		value &= 0xFFFE; // Swap the last bit to a 0
	return value;
}

/* injectImage
 *
 * Function that iterates over a QImage and modifies encodes the pixels of
 * the image to contain the passed in message.
 *
 * Args:
 *	QImage img: QT Image object to encode image into.
 *	std::string message: ASCII message to be encoded.
 */
void injectImage(QImage img, std::string message)
{
	int iterations = message.length() / 3;
	int remainder = message.length() % 3;
	QRgb value;
	int color;
	bool stopFlag = false;
	int cnt = 0;
	bool *msg;

	//Convert the vector of '0' and '1' chars into a vector of bools.
	msg = new bool[message.length()];
	for(int i = 0; i < message.length(); i += 1)
	{
		if(message[i] == '1') msg[i] = true;
		else msg[i] = false;
	}

	/* Iterate over the pixels of the image and write the message into their
	 * lowest bits.
	 */
	for(int i = 0; i < img.height(); i += 1)
	{
		for(int j = 0; j < img.width(); j += 1)
		{
			color = img.pixel(i,j);
			value = qRgba(
				adjustPixel(qRed(color), msg[cnt]),
				adjustPixel(qGreen(color), msg[cnt+1]),
				adjustPixel(qBlue(color), msg[cnt+2]),
				qAlpha(color)
				);
			img.setPixel(i,j,value);
			cnt += 3;
			if(cnt == iterations)
			{
				stopFlag = true;
				if(remainder > 0)
				{
					int red, green;
					color = img.pixel(i+1, j);
					red = adjustPixel(qRed(color), msg[cnt]);
					if(remainder > 1)
						green = adjustPixel(qGreen(color), msg[cnt+1]);
					else
						green = qGreen(color);
					value = qRgba(red, green, qBlue(color), qAlpha(color));
				}
				break;
			}
		}
		if(stopFlag) break;
	}
	delete[] msg;
}

/* extractPixel
 * 
 * Function to extract the value of the least significant bit from an int.
 * 
 * Args:
 *	int value: Value to extract from.
 *
 * Returns:
 *	bool - false if LSB is 0, 1 if LSB is true.
 */
bool extractPixel(int value)
{
	value &= 0x0001;
	if(value == 0) return false;
	else return true;
}

/* extractMessage
 *
 * Function to extract the encoded string from a QImage.
 *
 * Args:
 *	QImage img: Image containing encoded string.
 *	int cnt: not used...
 *
 * Returns:
 *	std::string - ASCII string containing '0' and '1's
 */
std::string extractMessage(QImage img, int cnt)
{
	int currCnt = 0;
	vector<bool> msgString;
	int color;
	bool rBit, gBit, bBit;
	for(int i = 0; i < img.height(); i += 1)
	{
		for(int j = 0; j < img.width(); j += 1)
		{
			color = img.pixel(i,j);
			rBit = extractPixel(qRed(color));
			gBit = extractPixel(qGreen(color));
			bBit = extractPixel(qBlue(color));
			if(currCnt < cnt && rBit)
			{
				msgString.push_back(rBit);
				currCnt += 1;
			}
			else if(currCnt < cnt && !rBit)
			{
				msgString.push_back(rBit);
				currCnt = 0;
			}
			if(currCnt < cnt && gBit)
			{
				msgString.push_back(gBit);
				currCnt += 1;
			}
			else if(currCnt < cnt && !gBit)
			{
				msgString.push_back(gBit);
				currCnt = 0;
			}
			if(currCnt < cnt && bBit)
			{
				msgString.push_back(bBit);
				currCnt += 1;
			}
			else if(currCnt < cnt && !bBit)
			{
				msgString.push_back(bBit);
				currCnt = 0;
			}
			if(currCnt == 200)
			{
				std::string message;
				for(int a = 0; a < msgString.size() - 200; a += 1)
				{
					if(msgString[a]) message += '1';
					else message += '0';
				}
				return message;
			}
		}
	}
	return "";
}
