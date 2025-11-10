#define _CRT_SECURE_NO_WARNINGS
#include "../include/readBMP.h"
#include "../include/coding.h"

void ReadBMPFile() {
	//read .wav .bmp
	//const char* filename_read = "C:\\Users\\DRF\\Desktop\\Temp\\colorWRGB.bmp";
	const char* filename_read = "C:\\Users\\Xinyu\\Desktop\\Temp\\color.bmp";

	struct tagBITMAPFILEHEADER head;
	struct tagBITMAPINFOHEADER info;
	//struct tagRGBQUAD  color;

	//读取文件
	FILE* rbmp = fopen(filename_read, "rb");
	if (rbmp == NULL)
	{
		printf("file is NULL");
		return;
	}

	//读指针后移
	//fgetc(rbmp);

	//读取文件头
	fread(&head.bfType, 1, 2, rbmp);
	fread(&head.bfSize, 1, 4, rbmp);
	fread(&head.bfReserved1, 1, 2, rbmp);
	fread(&head.bfReserved2, 1, 2, rbmp);
	fread(&head.bfOffBits, 1, 4, rbmp);

	//读取文件信息
	fread(&info.biSize, 1, 4, rbmp);
	fread(&info.biWidth, 1, 4, rbmp);
	fread(&info.biHeight, 1, 4, rbmp);
	fread(&info.biPlanes, 1, 2, rbmp);
	fread(&info.biBitCount, 1, 2, rbmp);
	fread(&info.biCompression, 1, 4, rbmp);
	fread(&info.biSizeImage, 1, 4, rbmp);
	fread(&info.biXPelsPerMeter, 1, 4, rbmp);
	fread(&info.biYPelsPerMeter, 1, 4, rbmp);
	fread(&info.biClrUsed, 1, 4, rbmp);
	fread(&info.biClrImportant, 1, 4, rbmp);

	printf("\ninfo.biBitCount : %d\n ", info.biBitCount);
	printf("\ninfo.biWidth : %d \n", info.biWidth);
	printf("\ninfo.biHeight : %d \n", info.biHeight);
	//根据位数据生成对应count
	unsigned char count = 0;
	switch (info.biBitCount)
	{
	case 24:count = info.biBitCount / 8;
		break;
	case 32:count = info.biBitCount / 8;
		break;
	default:
		break;
	}

	//需要考虑行列对齐
	uint8_t* bgrcolors = (uint8_t*)malloc(info.biWidth * info.biHeight * count);

	for (int i = 0; i < info.biWidth * info.biHeight * count; i++)
	{
		fread(&bgrcolors[i], sizeof(uint8_t), 1, rbmp);
	}
	for (size_t i = 0; i < info.biHeight; i++)
	{
		printf("\n");
		for (int j = 0; j < info.biWidth; j++) {
			int pixel_index = (i * info.biWidth + j) * count;

			printf("[r:%d,", bgrcolors[pixel_index + 2]);
			printf("g:%d,", bgrcolors[pixel_index + 1]);
			printf("b:%d,", bgrcolors[pixel_index + 0]);
			printf("]");
		}
	}

	CollectData(bgrcolors, info.biWidth, info.biHeight, info.biWidth * info.biHeight * count);
}


