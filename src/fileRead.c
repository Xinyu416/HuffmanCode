#define _CRT_SECURE_NO_WARNINGS
#include "../include/fileRead.h"
#include "../include/coding.h"

void FileReadTest() {
	const char* filename = "C:\\Users\\Xinyu\\Desktop\\Temp\\test.mp4";

	//读取文件
	FILE* f = fopen(filename, "rb");

	if (fseek(f, 0, SEEK_END) != 0) {
		return;
	}
	long size = ftell(f);
	printf("size:%d\n",size);

	rewind(f);
	uint8_t* datas = (uint8_t*)malloc(size);
	fread(datas,1,size,f);
	fclose(f);

	CollectData(datas, 255, 255, size);

	//写入数据到指定文件
	//const char* fw = "C:\\Users\\Xinyu\\Desktop\\Temp\\test2.xx";
	//printf("\n写出文件到: %s\n", fw);
	//FILE* writeStream = fopen(fw, "wb");

	//fwrite(datas,1,size, writeStream);


	
}
