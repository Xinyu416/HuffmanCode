#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

struct bitArray {
	uint8_t* data;
	uint32_t max;
	uint32_t len;
	uint8_t  bitlen;
	uint8_t  block[3];
};

struct DataHeader {
	uint16_t nodesNum;
	uint32_t contentCodeLen;
};

/// <summary>
/// 打印位信息
/// </summary>
/// <param name="data"></param>
/// <param name="bitlen"></param>
void printBits(uint32_t data, uint32_t bitlen);

/// <summary>
/// 打印8个位信息
/// </summary>
/// <param name="data"></param>
/// <param name="bitlen"></param>
void printBits_8(uint8_t data, uint8_t bitlen);

/// <summary>
/// 向目标容器移动单个位数据
/// </summary>
/// <param name="data"></param>
/// <param name="dataStart"></param>
/// <param name="dataLen"></param>
/// <param name="container"></param>
/// <param name="containerStart"></param>
void moveBitsToContainer(uint8_t data, uint8_t dataStart,uint8_t dataLen,uint8_t container,uint8_t containerStart);

/// <summary>
/// 向目标容器移动多个字节位数据
/// </summary>
void moveBitsToContainerMulti();

//压入数据
void BitArrayPush(struct bitArray* containerArr, uint32_t inData, uint8_t inDataLen);

uint32_t BitArrayPop(struct bitArray* containerArr, uint8_t getDataLen,uint32_t offset);

uint32_t BitPop(uint8_t* data, uint8_t getDataLen, uint32_t offset);
