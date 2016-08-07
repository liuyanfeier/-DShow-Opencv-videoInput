
#include <stdio.h>
#include <highgui.h>
#include <iostream>
#include <cstdio>
#include <fstream>

#include "camerads.h"

const char *g_szTitle = "Camera";

using namespace std;

void save(IplImage *pFrame){
	FILE *fp;
	fopen_s(&fp, "照片.bmp", "wb");
	// cout << pFrame->nChannels << ' ' << pFrame->width << ' ' << pFrame->height << endl;
	char bfType[] = { "BM" };
	int bfSize = 54 + pFrame->width * pFrame->height * pFrame->nChannels;
	short bfReserved1 = 0;
	short bfReserved2 = 0;
	unsigned int bfOffBits = 40 + 14;
	fwrite(bfType, sizeof(unsigned char), 2, fp);
	fwrite(&bfSize, sizeof(unsigned char), 4, fp);
	fwrite(&bfReserved1, sizeof(unsigned char), 2, fp);
	fwrite(&bfReserved2, sizeof(unsigned char), 2, fp);
	fwrite(&bfOffBits, sizeof(unsigned char), 4, fp);


	//head
	int biSize = 40;
	int biWidth = (pFrame->width);
	int biHeight = -(pFrame->height);
	short biPlanels = 1;
	short biBitCount = pFrame->nChannels * 8;
	int biCompressopm = 0;
	int biSizeImage = 0;
	int biXPelPerMeter = 0;
	int biYPelPerMeter = 0;
	int biClrUsed = (int)(pow(2, biBitCount) + 0.01);
	int biClrImport = biClrUsed;

	fwrite(&biSize, sizeof(unsigned char), 4, fp);
	fwrite(&biWidth, sizeof(unsigned char), 4, fp);
	fwrite(&biHeight, sizeof(unsigned char), 4, fp);
	fwrite(&biPlanels, sizeof(unsigned char), 2, fp);
	fwrite(&biBitCount, sizeof(unsigned char), 2, fp);
	fwrite(&biCompressopm, sizeof(unsigned char), 4, fp);
	fwrite(&biSizeImage, sizeof(unsigned char), 4, fp);

	fwrite(&biXPelPerMeter, sizeof(unsigned char), 4, fp);
	fwrite(&biYPelPerMeter, sizeof(unsigned char), 4, fp);
	
	fwrite(&biClrUsed, sizeof(unsigned char), 4, fp);
	fwrite(&biClrImport, sizeof(unsigned char), 4, fp);
	//	ouf << biSize << biWidth << biHeight << biPlanels << biBitCount << biCompressopm << biSizeImage << biXPelPerMeter << biYPelPerMeter << biClrUsed << biClrImport;

	char *data = (char *)malloc(pFrame->width * pFrame->height * pFrame->nChannels * sizeof(char));

	memcpy(data, pFrame->imageDataOrigin, pFrame->width * pFrame->height * pFrame->nChannels * sizeof(char));
	fwrite(data, sizeof(unsigned char), pFrame->width * pFrame->height * pFrame->nChannels, fp);

	cout << "拍照成功!!!!!!" << endl;

	//ouf.close();
	fclose(fp);
	//data

}

int main()
{
	int m_iCamCount = CCameraDS::CameraCount();

	//std::cout << "please input 't' for Taking photo!" << std::endl;
	//std::cout << "please input 'e' for Exit!" << std::endl;

	//cout << "you can enter 'p' to get a picture" << endl;
	//cout << "you can enter 'q' to quit" << endl;

	cout << "输入P拍照，输入Q退出！" << endl;

	if (m_iCamCount == 0)
	{
		return -1 ;
	}

	CCameraDS m_CamDS0;

	IplImage *pFrame0 = NULL;

	// m_CamDS0.OpenCamera(0, true, 320 * 2, 240 * 2);

	m_CamDS0.OpenCamera(0, false, 640, 480);

	cvNamedWindow("照相机");

	int num = 0;
	while (true)
	{
		
		//获取一帧
		pFrame0 = m_CamDS0.QueryFrame();
		//显示
		cvShowImage("照相机", pFrame0);
		char c = cvWaitKey(20);
		if (c == 'Q')
		{
			cout << "退出成功!!!!!!" << endl;
			break;
		}
		if (c == 'P'){
			save(pFrame0);
		}
	}
	m_CamDS0.CloseCamera(); 
	//	m_CamDS1.CloseCamera();
	cvDestroyWindow("myApp");

	return 0;
}

