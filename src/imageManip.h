/* Author: Justin Proffitt
 * Date: August 23 2011
 * 
 * ImageManip.h
 *
 * Header for functions that will manipulate the images within QT.
 */
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
