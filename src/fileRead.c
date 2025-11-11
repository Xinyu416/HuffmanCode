#define _CRT_SECURE_NO_WARNINGS
#include "../include/fileRead.h"
#include "../include/coding.h"

void FileReadTest() {
	//const char* filename = "C:\\Users\\Xinyu\\Desktop\\Temp\\test.mp4";
	//const char* filename = "C:\\Users\\DRF\\Desktop\\Temp\\test.mp4";
	//const char* filename = "C:\\Users\\DRF\\Desktop\\Temp\\colorWRGB.bmp";
	const char* filename = "C:\\Users\\DRF\\Desktop\\Temp\\HoloKnight.jpg";
	//const char* filename = "C:\\Users\\DRF\\Desktop\\Temp\\shine_zl.png";

	//读取文件
	FILE* f = fopen(filename, "rb");

	if (fseek(f, 0, SEEK_END) != 0) {
		return;
	}
	long size = ftell(f);
	printf("size:%d\n", size);

	//重新回到文件头
	/*rewind(f);
	uint8_t* datas = (uint8_t*)malloc(size);

	fread(datas, 1, size, f);
	fclose(f);*/
	size = 20;
	uint8_t* datas = (uint8_t*)malloc(size);
	srand(time(NULL));
	for (size_t i = 0; i < size; i++)
	{
		datas[i] = (uint8_t)(rand() % 255);
		printf("data[%d]:%x\n",i,datas[i]);
	}

	CollectData(datas, size);

	//uint8_t* readDatas = DecodeFromFile();
	//printf("size:%d\n", size);
	//for (size_t i = 0; i < size; i++)
	//{
	//	//printf("比对数据 %d\n", i);
	//	if (datas[i] != readDatas[i]) {
	//		printf("index = %d\n", i);
	//		printf("origin : %x , read : %x \n", datas[i], readDatas[i]);
	//		break;
	//	}
	//}
	//printf("比对完成");

}
