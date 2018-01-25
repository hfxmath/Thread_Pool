// rgbTyuv_table.cpp: 定义控制台应用程序的入口点。
unsigned short Y_R[256] = { 0, 0, 0, 0, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 10, 10, 10, 11, 11, 11, 11, 12, 12, 12, 13, 13, 13, 14, 14, 14, 14, 15, 15, 15, 16, 16, 16, 17, 17, 17, 17, 18, 18, 18, 19, 19, 19, 20, 20, 20, 20, 21, 21, 21, 22, 22, 22, 23, 23, 23, 23, 24, 24, 24, 25, 25, 25, 25, 26, 26, 26, 27, 27, 27, 28, 28, 28, 28, 29, 29, 29, 30, 30, 30, 31, 31, 31, 31, 32, 32, 32, 33, 33, 33, 34, 34, 34, 34, 35, 35, 35, 36, 36, 36, 37, 37, 37, 37, 38, 38, 38, 39, 39, 39, 40, 40, 40, 40, 41, 41, 41, 42, 42, 42, 43, 43, 43, 43, 44, 44, 44, 45, 45, 45, 46, 46, 46, 46, 47, 47, 47, 48, 48, 48, 49, 49, 49, 49, 50, 50, 50, 51, 51, 51, 51, 52, 52, 52, 53, 53, 53, 54, 54, 54, 54, 55, 55, 55, 56, 56, 56, 57, 57, 57, 57, 58, 58, 58, 59, 59, 59, 60, 60, 60, 60, 61, 61, 61, 62, 62, 62, 63, 63, 63, 63, 64, 64, 64, 65, 65, 65, 66, 66, 66, 66, 67, 67, 67, 68, 68, 68, 69, 69, 69, 69, 70, 70, 70, 71, 71, 71, 72, 72, 72, 72, 73, 73, 73, 74, 74, 74, 75, 75, 75, 75, 76 }
;
unsigned short Y_G[256] = { 0, 0, 1, 1, 2, 2, 3, 4, 4, 5, 5, 6, 7, 7, 8, 8, 9, 9, 10, 11, 11, 12, 12, 13, 14, 14, 15, 15, 16, 17, 17, 18, 18, 19, 19, 20, 21, 21, 22, 22, 23, 24, 24, 25, 25, 26, 26, 27, 28, 28, 29, 29, 30, 31, 31, 32, 32, 33, 34, 34, 35, 35, 36, 36, 37, 38, 38, 39, 39, 40, 41, 41, 42, 42, 43, 44, 44, 45, 45, 46, 46, 47, 48, 48, 49, 49, 50, 51, 51, 52, 52, 53, 53, 54, 55, 55, 56, 56, 57, 58, 58, 59, 59, 60, 61, 61, 62, 62, 63, 63, 64, 65, 65, 66, 66, 67, 68, 68, 69, 69, 70, 71, 71, 72, 72, 73, 73, 74, 75, 75, 76, 76, 77, 78, 78, 79, 79, 80, 80, 81, 82, 82, 83, 83, 84, 85, 85, 86, 86, 87, 88, 88, 89, 89, 90, 90, 91, 92, 92, 93, 93, 94, 95, 95, 96, 96, 97, 98, 98, 99, 99, 100, 100, 101, 102, 102, 103, 103, 104, 105, 105, 106, 106, 107, 107, 108, 109, 109, 110, 110, 111, 112, 112, 113, 113, 114, 115, 115, 116, 116, 117, 117, 118, 119, 119, 120, 120, 121, 122, 122, 123, 123, 124, 125, 125, 126, 126, 127, 127, 128, 129, 129, 130, 130, 131, 132, 132, 133, 133, 134, 134, 135, 136, 136, 137, 137, 138, 139, 139, 140, 140, 141, 142, 142, 143, 143, 144, 144, 145, 146, 146, 147, 147, 148, 149, 149 }
;
unsigned short Y_B[256] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 19, 19, 19, 19, 20, 20, 20, 20, 20, 20, 20, 20, 20, 21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 23, 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26, 26, 26, 27, 27, 27, 27, 27, 27, 27, 27, 27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 29 }
;
//U = - 0.169R - 0.331G + 0.5B;
unsigned short U_R[256] = { 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 19, 20, 20, 20, 20, 20, 20, 21, 21, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 24, 24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26, 27, 27, 27, 27, 27, 27, 28, 28, 28, 28, 28, 28, 29, 29, 29, 29, 29, 29, 30, 30, 30, 30, 30, 30, 31, 31, 31, 31, 31, 31, 32, 32, 32, 32, 32, 32, 33, 33, 33, 33, 33, 33, 34, 34, 34, 34, 34, 34, 35, 35, 35, 35, 35, 35, 36, 36, 36, 36, 36, 36, 37, 37, 37, 37, 37, 38, 38, 38, 38, 38, 38, 39, 39, 39, 39, 39, 39, 40, 40, 40, 40, 40, 40, 41, 41, 41, 41, 41, 41, 42, 42, 42, 42, 42, 42, 43 }
;
unsigned short U_G[256] = { 0, 0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 10, 11, 11, 11, 12, 12, 12, 13, 13, 13, 14, 14, 14, 15, 15, 15, 16, 16, 16, 17, 17, 17, 18, 18, 18, 19, 19, 19, 20, 20, 20, 21, 21, 21, 22, 22, 22, 23, 23, 23, 24, 24, 24, 25, 25, 25, 26, 26, 26, 27, 27, 27, 28, 28, 28, 29, 29, 29, 30, 30, 30, 31, 31, 31, 32, 32, 32, 33, 33, 33, 34, 34, 34, 35, 35, 35, 36, 36, 36, 37, 37, 37, 38, 38, 38, 39, 39, 39, 40, 40, 40, 41, 41, 41, 42, 42, 42, 43, 43, 43, 44, 44, 44, 45, 45, 45, 46, 46, 46, 47, 47, 47, 48, 48, 48, 48, 49, 49, 49, 50, 50, 50, 51, 51, 51, 52, 52, 52, 53, 53, 53, 54, 54, 54, 55, 55, 55, 56, 56, 56, 57, 57, 57, 58, 58, 58, 59, 59, 59, 60, 60, 60, 61, 61, 61, 62, 62, 62, 63, 63, 63, 64, 64, 64, 65, 65, 65, 66, 66, 66, 67, 67, 67, 68, 68, 68, 69, 69, 69, 70, 70, 70, 71, 71, 71, 72, 72, 72, 73, 73, 73, 74, 74, 74, 75, 75, 75, 76, 76, 76, 77, 77, 77, 78, 78, 78, 79, 79, 79, 80, 80, 80, 81, 81, 81, 82, 82, 82, 83, 83, 83, 84, 84 }
;
unsigned short U_B[256] = { 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32, 32, 33, 33, 34, 34, 35, 35, 36, 36, 37, 37, 38, 38, 39, 39, 40, 40, 41, 41, 42, 42, 43, 43, 44, 44, 45, 45, 46, 46, 47, 47, 48, 48, 49, 49, 50, 50, 51, 51, 52, 52, 53, 53, 54, 54, 55, 55, 56, 56, 57, 57, 58, 58, 59, 59, 60, 60, 61, 61, 62, 62, 63, 63, 64, 64, 65, 65, 66, 66, 67, 67, 68, 68, 69, 69, 70, 70, 71, 71, 72, 72, 73, 73, 74, 74, 75, 75, 76, 76, 77, 77, 78, 78, 79, 79, 80, 80, 81, 81, 82, 82, 83, 83, 84, 84, 85, 85, 86, 86, 87, 87, 88, 88, 89, 89, 90, 90, 91, 91, 92, 92, 93, 93, 94, 94, 95, 95, 96, 96, 97, 97, 98, 98, 99, 99, 100, 100, 101, 101, 102, 102, 103, 103, 104, 104, 105, 105, 106, 106, 107, 107, 108, 108, 109, 109, 110, 110, 111, 111, 112, 112, 113, 113, 114, 114, 115, 115, 116, 116, 117, 117, 118, 118, 119, 119, 120, 120, 121, 121, 122, 122, 123, 123, 124, 124, 125, 125, 126, 126, 127, 127 }
;
//V = 0.5R - 0.419G - 0.081B;
unsigned short V_R[256] = { 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32, 32, 33, 33, 34, 34, 35, 35, 36, 36, 37, 37, 38, 38, 39, 39, 40, 40, 41, 41, 42, 42, 43, 43, 44, 44, 45, 45, 46, 46, 47, 47, 48, 48, 49, 49, 50, 50, 51, 51, 52, 52, 53, 53, 54, 54, 55, 55, 56, 56, 57, 57, 58, 58, 59, 59, 60, 60, 61, 61, 62, 62, 63, 63, 64, 64, 65, 65, 66, 66, 67, 67, 68, 68, 69, 69, 70, 70, 71, 71, 72, 72, 73, 73, 74, 74, 75, 75, 76, 76, 77, 77, 78, 78, 79, 79, 80, 80, 81, 81, 82, 82, 83, 83, 84, 84, 85, 85, 86, 86, 87, 87, 88, 88, 89, 89, 90, 90, 91, 91, 92, 92, 93, 93, 94, 94, 95, 95, 96, 96, 97, 97, 98, 98, 99, 99, 100, 100, 101, 101, 102, 102, 103, 103, 104, 104, 105, 105, 106, 106, 107, 107, 108, 108, 109, 109, 110, 110, 111, 111, 112, 112, 113, 113, 114, 114, 115, 115, 116, 116, 117, 117, 118, 118, 119, 119, 120, 120, 121, 121, 122, 122, 123, 123, 124, 124, 125, 125, 126, 126, 127, 127 }
;
unsigned short V_G[256] = { 0, 0, 0, 1, 1, 2, 2, 2, 3, 3, 4, 4, 5, 5, 5, 6, 6, 7, 7, 7, 8, 8, 9, 9, 10, 10, 10, 11, 11, 12, 12, 12, 13, 13, 14, 14, 15, 15, 15, 16, 16, 17, 17, 18, 18, 18, 19, 19, 20, 20, 20, 21, 21, 22, 22, 23, 23, 23, 24, 24, 25, 25, 25, 26, 26, 27, 27, 28, 28, 28, 29, 29, 30, 30, 31, 31, 31, 32, 32, 33, 33, 33, 34, 34, 35, 35, 36, 36, 36, 37, 37, 38, 38, 38, 39, 39, 40, 40, 41, 41, 41, 42, 42, 43, 43, 43, 44, 44, 45, 45, 46, 46, 46, 47, 47, 48, 48, 49, 49, 49, 50, 50, 51, 51, 51, 52, 52, 53, 53, 54, 54, 54, 55, 55, 56, 56, 56, 57, 57, 58, 58, 59, 59, 59, 60, 60, 61, 61, 62, 62, 62, 63, 63, 64, 64, 64, 65, 65, 66, 66, 67, 67, 67, 68, 68, 69, 69, 69, 70, 70, 71, 71, 72, 72, 72, 73, 73, 74, 74, 74, 75, 75, 76, 76, 77, 77, 77, 78, 78, 79, 79, 80, 80, 80, 81, 81, 82, 82, 82, 83, 83, 84, 84, 85, 85, 85, 86, 86, 87, 87, 87, 88, 88, 89, 89, 90, 90, 90, 91, 91, 92, 92, 93, 93, 93, 94, 94, 95, 95, 95, 96, 96, 97, 97, 98, 98, 98, 99, 99, 100, 100, 100, 101, 101, 102, 102, 103, 103, 103, 104, 104, 105, 105, 105, 106, 106 }
;
unsigned short V_B[256] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 20, 20, 20, 20, 20, 20, 20, 20, 20 }
;

#include "stdafx.h"
#include <iostream>
#include <memory>
#include <time.h>
#include <windows.h> 
using namespace std;

const int src_w = 1920, src_h = 1080;
static FILE *src_file = NULL;
static FILE *des_file = NULL;

void read_image_data(FILE *fp, unsigned char *image_in)
{
	if (fp == NULL)
	{
		return;
	}
	int i = 0;
	unsigned char temp = 0;
	for (i = 0; i < src_h * src_w * 3; i++)
	{
		fscanf(fp, "%c", &temp);
		image_in[i] = temp;
	}
}
/*
void table_init()
{
	for (int i = 0; i < SIZE; i++)
	{
		//Y = 0.299R + 0.587G + 0.114B;
		Y_R[i] = (i * 1224) >> 12; //Y对应的查表数组
		Y_G[i] = (i * 2404) >> 12;
		Y_B[i] = (i * 467) >> 12;

		//U = -0.147R - 0.289G + 0.436B;
		U_R[i] = (i * 602) >> 12; //U对应的查表数组
		U_G[i] = (i * 1183) >> 12;
		U_B[i] = (i * 1785) >> 12;

		//V = 0.615R - 0.515G - 0.100B;
		V_R[i] = (i * 2519) >> 12; //V对应的查表数组
		V_G[i] = (i * 2109) >> 12;
		V_B[i] = (i * 409) >> 12;
	}
}*/
static int BGR2YUV_YR[256];
static int BGR2YUV_YG[256];
static int BGR2YUV_YB[256];
static int BGR2YUV_UR[256];
static int BGR2YUV_UG[256];
static int BGR2YUV_UBVR[256];
static int BGR2YUV_VG[256];
static int BGR2YUV_VB[256];

void InitBGR2YUV420PTable()
{
	for (int i = 0; i < 256; ++i)
	{
		BGR2YUV_YR[i] = (float)65.481  * (i << 8);
		BGR2YUV_YG[i] = (float)128.553 * (i << 8);
		BGR2YUV_YB[i] = (float)24.966  * (i << 8);
		BGR2YUV_UR[i] = (float)37.797  * (i << 8);
		BGR2YUV_UG[i] = (float)74.203  * (i << 8);
		BGR2YUV_VG[i] = (float)93.786  * (i << 8);
		BGR2YUV_VB[i] = (float)18.214  * (i << 8);
		BGR2YUV_UBVR[i] = (float)112 * (i << 8);
	}
}

void ConvertBGR2YUV420P(unsigned char *bgr, unsigned char *yuv,int w, int h)
{

	unsigned char *u, *v, *y, *uu, *vv;
	unsigned char *pu1, *pu2, *pu3, *pu4;
	unsigned char *pv1, *pv2, *pv3, *pv4;
	unsigned char *b, *g, *r;

	uu = new unsigned char[w * h];
	vv = new unsigned char[w * h];

	if (uu == NULL || vv == NULL)
	{
		return;
	}

	y = yuv;
	v = uu;
	u = vv;

	r = bgr;
	g = bgr + 1;
	b = bgr + 2;

	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			*y++ = (BGR2YUV_YR[*b] + BGR2YUV_YG[*g] + BGR2YUV_YB[*r] + 1048576) >> 16;
			*u++ = (-BGR2YUV_UR[*b] - BGR2YUV_UG[*g] + BGR2YUV_UBVR[*r] + 8388608) >> 16;
			*v++ = (BGR2YUV_UBVR[*b] - BGR2YUV_VG[*g] - BGR2YUV_VB[*r] + 8388608) >> 16;
			b += 3;
			g += 3;
			r += 3;
		}

	}

	u = yuv + w * h;
	v = u + (w * h) / 4;

	pu1 = uu;
	pu2 = pu1 + 1;
	pu3 = pu1 + w;
	pu4 = pu3 + 1;

	pv1 = vv;
	pv2 = pv1 + 1;
	pv3 = pv1 + w;
	pv4 = pv3 + 1;

	for (int i = 0; i < h; i += 2)
	{
		for (int j = 0; j < w; j += 2)
		{
			*u++ = (*pu1 + *pu2 + *pu3 + *pu4) >> 2;
			*v++ = (*pv1 + *pv2 + *pv3 + *pv4) >> 2;

			pu1 += 2;
			pu2 += 2;
			pu3 += 2;
			pu4 += 2;

			pv1 += 2;
			pv2 += 2;
			pv3 += 2;
			pv4 += 2;
		}

		pu1 += w;
		pu2 += w;
		pu3 += w;
		pu4 += w;

		pv1 += w;
		pv2 += w;
		pv3 += w;
		pv4 += w;

	}

	delete[] uu;
	delete[] vv;
	fwrite(yuv, w*h*3/2, 1, des_file);
	return;
}
inline void  RGB2YUV(unsigned char *RgbBuf, unsigned char *yuvBuf, const int  nWidth, const int  nHeight )
{
	int len = nWidth * nHeight;

	unsigned char *bufY = yuvBuf;
	unsigned char *bufU = yuvBuf + nWidth * nHeight;
	unsigned char *bufV = bufU + (nWidth * nHeight * 1 / 4);
	
	unsigned char y, u, v, r, g, b;

	for (int i = 0; i < len; ++i)
	{
		r = *(RgbBuf++);
		g = *(RgbBuf++);
		b = *(RgbBuf++);
		y = (unsigned char)((66 * r + 129 * g + 25 * b + 128) >> 8) + 16;
		u = (unsigned char)((-38 * r - 74 * g + 112 * b + 128) >> 8) + 128;
		v = (unsigned char)((112 * r - 94 * g - 18 * b + 128) >> 8) + 128;

		//printf("%u \t %u \t %u \n", y, u, v);

		*(bufY++) = max(0, min(y, 255));
		if (i % 2 == 0 && (i + len) % 2 == 0)
		{
			*(bufU++) = max(0, min(u, 255));
		}
		else
		{
			if (i % 2 == 0)
			{
				*(bufV++) = max(0, min(v, 255));
			}
		}
	}
	len = nWidth * nHeight + (nWidth * nHeight) / 2;
	fwrite(yuvBuf, len, 1, des_file);
}
 inline void rgbTyuv111(unsigned char *RGB, unsigned char *YUV, const int wid, const int higt)
{
	const int IMGSIZE = wid * higt;
	unsigned char *bufY = YUV;
	unsigned char *bufU = bufY + IMGSIZE;
	unsigned char *bufV = bufU + (IMGSIZE >> 2);

	/*for (int i = 0; i < IMGSIZE; i+=2)
	{
		int b = *(RGB++), g = *(RGB++), r = *(RGB++);
		*(bufY++) = Y_R[r] + Y_G[g] + Y_B[b];

		b = *(RGB++), g = *(RGB++), r = *(RGB++);
		*(bufY++) = Y_R[r] + Y_G[g] + Y_B[b];
	}*/
	
	for (int i = 0; i < higt; i ++)
	{
		for (int j = 0; j < wid; j ++)
		{
			int b = *(RGB++), g = *(RGB++), r = *(RGB++);
			b = 90, g = 0, r = 0;
			*(bufY++) = Y_R[r] + Y_G[g] + Y_B[b];
			if (i % 2== 0 && j % 2==0)
			{
				*(bufU++) = U_B[b] - U_R[r] - U_G[g] + 128;
				*(bufV++) = V_R[r] - V_G[g] - V_B[b] + 128;
			}
		}
	}
	//fwrite(YUV, wid * higt * 3 / 2, 1, des_file);
}
inline void rgbTyuv(unsigned char *RGB, unsigned char *YUV, const int wid, const int higt)
{
	const int IMGSIZE = wid * higt;
	unsigned char *bufY = YUV;
	unsigned char *bufU = bufY + IMGSIZE;
	unsigned char *bufV = bufU + (IMGSIZE >> 2);

	for (int i = 0; i < higt; ++i)
	{
		bool isU = false;
		if (i & 1)
		{
			isU = true;
		}
		for (int j = 0; j < wid; ++j)
		{
			int r = *(RGB++), g = *(RGB++), b = *(RGB++);

			*(bufY++) = Y_R[r] + Y_G[g] + Y_B[b];
			
			if (isU)
			{
				if (j & 1)
				{
					*(bufU++) = U_B[b] - U_R[r] - U_G[g] + 128;
					*(bufV++) = V_R[r] - V_G[g] - V_B[b] + 128;
				}
			}
		}
	}
	//fwrite(YUV, IMGSIZE * 3 / 2, 1, des_file);
}

int main()
{
	fopen_s(&src_file, "1920x1080.rgb", "rb");
	fopen_s(&des_file, "1920x1080.yuv", "wb");

	int len1 = src_w * src_h * 3;
	int len2 = src_w * src_h * 3 / 2;
	unsigned char *image_in = new unsigned char[len1];
	if (image_in == NULL)
	{
		delete[]image_in;
		return -1;
	}
	unsigned char *image_out = new unsigned char[len2];
	if (image_out == NULL)
	{
		delete[]image_out;
		return -1;
	}

	read_image_data(src_file, image_in);

	//RGB2YUV(image_in, image_out, src_w, src_h);
	rgbTyuv(image_in, image_out, src_w, src_h);
/*
	InitBGR2YUV420PTable();
	ConvertBGR2YUV420P(image_in, image_out, src_w, src_h);
	while (true)
	{
		printf("%d\n", GetTickCount());
		rgbTyuv(image_in, image_out, src_w, src_h);
		//RGB2YUV(image_in, image_out, src_w, src_h);
		//ConvertBGR2YUV420P(image_in, image_out, src_w, src_h);
		Sleep(50);
	}*/
	
	delete[]image_in;
	delete[]image_out;

	fclose(src_file);
	fclose(des_file);
	cout << "Over!" << endl;
    return 0;
}

