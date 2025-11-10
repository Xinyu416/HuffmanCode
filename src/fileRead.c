#define _CRT_SECURE_NO_WARNINGS
#include "../include/fileRead.h"

void FileReadTest() {
	const char* filename = "C:\\Users\\DRF\\Desktop\\Temp\\test.mp4";

	//╤ах║нд╪Ч
	FILE* f = fopen(filename, "rb");

	if (fseek(f, 0, SEEK_END) != 0) {
		return;
	}
	long size = ftell(f);
	printf("size:%d\n",size);
}
