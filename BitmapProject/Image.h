#pragma once
#include <Windows.h>

const double r1 = 0.2126, g1 = 0.7152, b1 = 0.0722;
const double r2 = 0.299, g2 = 0.587, b2 = 0.114;

RGBTRIPLE Gray(BYTE avg) {
	RGBTRIPLE rgb;
	rgb.rgbtRed = avg;
	rgb.rgbtGreen = avg;
	rgb.rgbtBlue = avg;
	return rgb;
}