// rgbTyuv_table.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Y_table.h"
#include "U_table.h"
#include "V_table.h"
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

inline void  RGB2YUV(unsigned char * RgbBuf, unsigned char * yuvBuf, const int  nWidth, const int  nHeight )
{
	unsigned char *bufY, *bufU, *bufV, *bufRGB, *bufYuv;
	int len = nWidth * nHeight;

	bufY = yuvBuf;
	bufU = yuvBuf + nWidth * nHeight;
	bufV = bufU + (nWidth * nHeight * 1 / 4);
	unsigned char y, u, v, r, g, b, testu, testv;
	unsigned int ylen = nWidth * nHeight;
	unsigned int ulen = (nWidth * nHeight) / 4;
	unsigned int vlen = (nWidth * nHeight) / 4;

	for (int i = 0; i < len; ++i)
	{
		r = *(RgbBuf++);
		g = *(RgbBuf++);
		b = *(RgbBuf++);
		y = (unsigned char)((66 * r + 129 * g + 25 * b + 128) >> 8) + 16;
		u = (unsigned char)((-38 * r - 74 * g + 112 * b + 128) >> 8) + 128;
		v = (unsigned char)((112 * r - 94 * g - 18 * b + 128) >> 8) + 128;
		*(bufY++) = max(0, min(y, 255));
		if (i % 2 == 0 && (i + len) % 2 == 0)
		{
			if (u > 255)
			{
				u = 255;
			}
			if (u < 0)
			{
				u = 0;
			}
			*(bufU++) = u;
			//存u分量
		}
		else
		{
			//存v分量
			if (i % 2 == 0)
			{
				if (v > 255)
				{
					v = 255;
				}
				if (v < 0)
				{
					v = 0;
				}
				*(bufV++) = v;
			}
		}
	}
	len = nWidth * nHeight + (nWidth * nHeight) / 2;
	fwrite(yuvBuf, len, 1, des_file);
}


inline void rgbTyuv(unsigned char *RGB, unsigned char *YUV, const int wid, const int higt)
{
	const int IMGSIZE = wid * higt;

	for (int i = 0; i < IMGSIZE; i+=1)
	{	
		int r = *(RGB++),g = *(RGB++),b = *(RGB++);
		YUV[i]                = Y_R[r]    + Y_G[g]	  + Y_B[b]; //Y
		YUV[i +  1 * IMGSIZE]  = U_B[b]	  - U_R[r]    - U_G[g]; //U
		YUV[i +  2 *IMGSIZE + IMGSIZE]  = V_R[r]	  - V_G[g]    - V_B[b]; //V
	}

	fwrite(YUV, IMGSIZE * 3 / 2, 1, des_file);
}


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

bool ConvertBGR2YUV420P(int w, int h, unsigned char *bgr, unsigned char *yuv)
{
	unsigned char *u, *v, *y, *uu, *vv;
	unsigned char *pu1, *pu2, *pu3, *pu4;
	unsigned char *pv1, *pv2, *pv3, *pv4;
	unsigned char *b, *g, *r;

	uu = new unsigned char[w * h];
	vv = new unsigned char[w * h];

	if (uu == NULL || vv == NULL)
	{
		return false;
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
	fwrite(yuv, w *h  * 3/ 2, 1, des_file);

	delete[] uu;
	delete[] vv;

	return true;
}


int main()
{
	fopen_s(&src_file, "1920x1080.rgb", "rb");
	fopen_s(&des_file, "1920x1080.yuv", "wb");

	int len1 = src_w * src_h * 3;
	int len2 = src_w * src_h * 3 /2;
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

	double start, end, cost;
	read_image_data(src_file, image_in);

	RGB2YUV(image_in, image_out, src_w, src_h);

	/*while (true)
	{
		printf("%d\n", GetTickCount());
		RGB2YUV(image_in, image_out, src_w, src_h);
		Sleep(50);
	}*/
	
	//InitBGR2YUV420PTable();
	/*while (true)
	{
		printf("%d\n", GetTickCount());
		RGB2YUV(image_in, image_out, src_w, src_h);
		//ConvertBGR2YUV420P(src_w, src_h, image_in, image_out);
		Sleep(50);
	}*/
	

	delete[]image_in;
	delete[]image_out;

	fclose(src_file);
	fclose(des_file);
	cout << "Over!" << endl;
    return 0;
}

