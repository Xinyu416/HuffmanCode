#define _CRT_SECURE_NO_WARNINGS
#include "../include/fileRead.h"
#include "../include/coding.h"

void FileReadTest() {
	//const char* filename = "C:\\Users\\Xinyu\\Desktop\\Temp\\test.mp4";
	//const char* filename = "C:\\Users\\DRF\\Desktop\\Temp\\test.mp4";
	//const char* filename = "C:\\Users\\DRF\\Desktop\\Temp\\colorWRGB.bmp";
	//const char* filename = "C:\\Users\\DRF\\Desktop\\Temp\\HoloKnight.jpg";
	//const char* filename = "C:\\Users\\DRF\\Desktop\\Temp\\shine_zl.png";

	//读取文件
	//FILE* f = fopen(filename, "rb");

	//if (fseek(f, 0, SEEK_END) != 0) {
	//	return;
	//}
	//long size = ftell(f);
	//printf("size:%d\n", size);

	////重新回到文件头
	//rewind(f);
	//uint8_t* datas = (uint8_t*)malloc(size);

	//fread(datas, 1, size, f);
	//fclose(f);

	for (size_t i = 0; i < 100000; i++)
	{
		srand(time(NULL));
		long  size = rand();
		uint8_t* datas = (uint8_t*)malloc(size);
		for (size_t i = 0; i < size; i++)
		{
			datas[i] = (uint8_t)(rand() % 255);
			//printf("%x,  ", datas[i]);
		}


		struct bitArray inDatas = Coding(datas, size);

		uint8_t* outDatas = Decoding(&inDatas);


		printf("\nCodingSize:%d\n", inDatas.max);
		printf("\ninDataSize:%d\n", size);

		printf("ratio:%.2f\n", ((float)inDatas.max / (float)size));
		for (size_t i = 0; i < size; i++)
		{
			//printf("比对数据 %d\n", i);
			if (datas[i] != outDatas[i]) {
				printf("index = %d\n", i);
				printf("origin : %x , outDatas : %x ", datas[i], outDatas[i]);
				break;
			}
		}
		printf("比对完成");
		free(datas);
		free(outDatas);
		free(inDatas.data);
	}

}
