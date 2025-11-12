#define _CRT_SECURE_NO_WARNINGS
#include "../include/fileRead.h"
#include "../include/coding.h"

void doCompress(const char* path) {

	//读取文件
	FILE* f = fopen(path, "rb");

	if (fseek(f, 0, SEEK_END) != 0) {
		return;
	}
	long originSize = ftell(f);
	printf("originSize:%d\n", originSize);

	//文件大小有限制
	if (originSize>XXDATAMAX)
	{
		printf("filesize out of limit");
		fclose(f);
		return;
	}

	//重新回到文件头
	rewind(f);
	uint8_t* data = (uint8_t*)malloc(originSize);
	fread(data, 1, originSize, f);

	//压缩数据
	struct bitArray inDatas = Coding(data, originSize);

	//写出
	struct FileHeader fheader = { .type = 0x4e4e,.compressSize = inDatas.max,.originSize = originSize };
	printf("压缩比：%f\n", ((float)fheader.compressSize / (float)fheader.originSize));
	const char* outPath = "C:\\Users\\DRF\\Desktop\\Temp\\fCoding.xx";
	FILE* writeStream = fopen(outPath, "wb");

	fwrite(&fheader, sizeof(struct FileHeader), 1, writeStream);
	fwrite(inDatas.data, 1, inDatas.max, writeStream);
	fclose(writeStream);

	free(data);
}

void doDeCompress() {
	//读文件
	const char* inPath = "C:\\Users\\DRF\\Desktop\\Temp\\fcoding.xx";
	FILE* readStream = fopen(inPath, "rb");
	struct FileHeader fheader = { .type = 0,.compressSize = 0,.originSize = 0 };
	fread(&fheader,sizeof(struct FileHeader),1,readStream);
	printf("file header:: type:%x,compressSize:%d,originSize:%d\n",fheader.type,fheader.compressSize,fheader.originSize);

	if (fheader.type!= 0x4e4e)
	{
		fclose(readStream);
		printf("file type is not match!");
		return;
	}
	uint8_t* inData = (uint8_t*)malloc(fheader.compressSize);
	fread(inData, fheader.compressSize, 1, readStream);
	//解压文件
	uint8_t* outData = Decoding(&inData);

	//写出数据
	const char* outPath = "C:\\Users\\DRF\\Desktop\\Temp\\fDecoding.xx";
	FILE* writeStream = fopen(outPath, "wb");
	fwrite(outData, fheader.originSize, 1, writeStream);

	fclose(writeStream);
	free(inData);
}

void FileReadTest() {

	const char* file = "C:\\Users\\DRF\\Desktop\\Temp\\Angelique.bin";
	//const char* file = "C:\\Users\\DRF\\Desktop\\Temp\\A Boy and His Blob.wbfs";
	FILE* f = fopen(file, "rb");
	if (fseek(f, 0, SEEK_END) != 0) {
		return;
	}
	long originSize = ftell(f);
	printf("originSize:%d\n", originSize);

	//文件大小有限制
	if (originSize > XXDATAMAX)
	{
		printf("filesize out of limit");
		fclose(f);
		return;
	}

	//重新回到文件头
	rewind(f);
	uint8_t* datas = (uint8_t*)malloc(originSize);
	fread(datas, 1, originSize, f);

	//测试
	//for (size_t i = 0; i < 10000000; i++)
	{
		//srand(time(NULL));
		//long  originSize = rand();
		//uint8_t* datas = (uint8_t*)malloc(originSize);
		//for (size_t i = 0; i < originSize; i++)
		//{
		//	datas[i] = (uint8_t)(rand() % 255);
		//	//printf("%x,  ", datas[i]);
		//}
		struct bitArray inDatas = Coding(datas, originSize);

		uint8_t* outDatas = Decoding(&inDatas);

		printf("\nCodingSize:%d\n", inDatas.max);
		printf("\ninDataSize:%d\n", originSize);

		printf("ratio:%.2f\n", ((float)inDatas.max / (float)originSize));
		for (size_t i = 0; i < originSize; i++)
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
