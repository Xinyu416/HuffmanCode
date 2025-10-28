#include "fileRead.h"

//void ReadFile() {
//
//	const char* filename = "C:\\Users\\DRF\\Desktop\\test.express";
//	uint32_t offset = 0;
//	uint32_t buf = 0;
//	uint8_t type = 0;
//	uint8_t outdata = 0;
//
//	printf("\n\n-------------------------------- 文件中读取数据  Start -----------------------------------");
//	struct DataHeader header_read_file = { .nodesNum = 0,.contentCodeLen = 0 };
//	//读取文件
//	FILE* readStream_file = fopen(filename, "rb");
//	if (readStream_file == NULL) {
//		printf("readStream is NULL");
//		return;
//	}
//
//	//读取文件头文件
//	fread(&header_read_file.nodesNum, sizeof(header_read_file.nodesNum), 1, readStream_file);
//	fread(&header_read_file.contentCodeLen, sizeof(header_read_file.contentCodeLen), 1, readStream_file);
//
//
//	//节点数组数据指针
//	Node* readNodes_read_file = (Node*)malloc(header_read_file.nodesNum * sizeof(Node));
//	//总字节数
//	uint32_t totalBits_file = header_read_file.nodesNum * 9 + header_read_file.contentCodeLen + sizeof(header_read_file.nodesNum) * 8 + sizeof(header_read_file.contentCodeLen) * 8;
//	uint32_t read_fileBytes = (uint32_t)ceilf((float)totalBits_file / 8.0f);
//
//	//总数据指针
//	uint8_t* read_file_data = (uint8_t*)malloc(read_fileBytes - sizeof(header_read_file.nodesNum) - sizeof(header_read_file.contentCodeLen));
//	uint32_t contentCount = fread(read_file_data, sizeof(uint8_t), read_fileBytes, readStream_file);
//	//offset = sizeof(header_read_file.nodesNum) * 8 + sizeof(header_read_file.contentCodeLen) * 8;
//	buf = 0;
//	offset = 0;
//
//	for (uint32_t i = 0; i < header_read_file.nodesNum; i++)
//	{
//		//按8+1位取数据
//		/*buf = BitPop(read_file_data, 8, offset);
//		offset += 8;
//		printf("\ndata: %d", buf);
//		buf = BitPop(read_file_data, 1, offset);
//		offset += 1;
//		printf("\n---type:%d\n", buf);*/
//
//		//按9位取数据
//		printf("\n----------- %d -----------\n", i);
//		buf = BitPop(read_file_data, 9, offset);
//		//printBits(buf, 32);
//		outdata = (uint8_t)(buf & 0b11111111);
//		printf("\ndata: %d", outdata);
//		type = (uint8_t)((buf >> 8) & 0b00000001);
//		printf("\n---type:%d\n", type);
//		offset += 9;
//
//		readNodes_read_file[i].type = type;
//		(readNodes_read_file + i)->data = outdata;
//	}
//
//	ReadContentData_Infile(readNodes_read_file, header_read_file.nodesNum, read_file_data, offset, header_read_file.contentCodeLen);
//
//	fclose(readStream_file);
//	printf("\n\n-------------------------------- 文件中读取数据  End -----------------------------------");
//}