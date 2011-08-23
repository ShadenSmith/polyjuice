#include <string>
#include <vector>
#include <iostream>
#include <QImage>
using namespace std;
#include "imageManip.h"

int adjustPixel(int value, bool in)
{
	if(in)
		value &= 0xFFFF;
	else
		value &= 0xFFFE;
	return value;
}

void injectImage(QImage img, string message)
{
	int iterations = message.length() / 3;
	int remainder = message.length() % 3;
	QRgb value;
	int color;
	bool stopFlag = false;
	int cnt = 0;
	bool *msg;
	msg = new bool[message.length()];
	for(int i = 0; i < message.length(); i += 1)
	{
		if(message[i] == '1') msg[i] = true;
		else msg[i] = false;
	}
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
bool extractPixel(int value)
{
	value &= 0x0001;
	if(value == 0) return false;
	else return true;
}
string extractMessage(QImage img, int cnt)
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
				string message;
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
/*
int main()
{
	for(int i = 0; i < 256; i += 1)
	{
		cout << "i = " << i << "\t" << "adjusted(f) = " << adjustPixel(i, false) << endl;
		cout << "i = " << i << "\t" << "adjusted(t) = " << adjustPixel(i, true) << endl;
	}
	return 0;
}
*/
