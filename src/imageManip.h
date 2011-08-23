#ifndef IMAGEMANIP_H
#define IMAGEMANIP_H
#include <string>
#include <vector>
#include <iostream>
#include <QImage>
using namespace std;

int adjustPixel(int value, bool in);
void injectImage(QImage img, string message);
bool extractPixel(int value);
string extractMessage(QImage img, int cnt);
#endif
