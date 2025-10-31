#include "bitoperate.h"
#include <math.h>
#include "HuffmanCode.h"

void printBits(uint32_t data, uint32_t bitlen) {
	for (uint32_t i = 0; i < bitlen; i++) {
		printf("%d,", (data >> i) & 1);
	}
}

void printBits_8(uint8_t data, uint8_t bitlen) {
	for (uint8_t i = 0; i < bitlen; i++) {
		printf("%d,", (data >> i) & 1);
	}
}

//11 0000 00 container
//1111 0000  data
void moveBitsToContainer(uint8_t data, uint8_t dataStart, uint8_t dataLen, uint8_t container, uint8_t containerLen) {
	uint8_t newdata = 0;
	//掩码 注意高低位信息 手敲字高位在左
	uint8_t maskslowtoHight[9] = { 0b11111111,0b11111110,0b11111100,0b11111000,0b11110000,0b11100000,0b11000000,0b10000000,0b00000000 };
	uint8_t maskshighttoLow[9] = { 0b11111111,0b01111111,0b00111111,0b00011111,0b00001111,0b00000111,0b00000011,0b00000001,0b00000000 };
	//对齐数据
	uint8_t dataUnuse = 8 - dataLen;

	//移到需要补位的位置
	data = data << containerLen;
	data = data & maskshighttoLow[8 - dataLen - containerLen];
	data = data & maskslowtoHight[containerLen];
	newdata = container | data;
}

void moveBitsToContainerMulti() {
	uint8_t maskslowtoHight[9] = { 0b11111111,0b11111110,0b11111100,0b11111000,0b11110000,0b11100000,0b11000000,0b10000000,0b00000000 };
	uint8_t maskshighttoLow[9] = { 0b11111111,0b01111111,0b00111111,0b00011111,0b00001111,0b00000111,0b00000011,0b00000001,0b00000000 };

	uint16_t data = 0b0000000101001101;
	uint8_t dataLen = 9;//考虑字节数据

	//容器长度 字节
	uint8_t containerMax = 2;
	uint8_t container[2] = { 0b00001111 ,0b00000000 };
	//当前容器总使用位长度
	uint8_t containerLen = 4;
	//单个字节当前用的位
	uint8_t bitUseLen = 0;
	//单个字节剩余的可用位
	uint8_t bitLeaveLen = 0;

	while (dataLen > 0)
	{
		//当前字节占用位信息
		bitUseLen = containerLen % 8;
		printf("bitUseLen: %d\n", bitUseLen);
		//当前字节剩余位信息
		bitLeaveLen = 8 - bitUseLen;
		printf("bitLeaveLen: %d\n", bitLeaveLen);

		//比较小的数据内容块 决定要移动的数据
		uint8_t min = dataLen < bitLeaveLen ? dataLen : bitLeaveLen;

		//临时变量赋值
		uint8_t temp = (uint8_t)data;
		temp = (temp << bitUseLen) & maskslowtoHight[bitUseLen];

		//当前字节数据
		uint8_t currentIndex = containerLen / 8;
		container[currentIndex] |= temp;
		//更新数据
		containerLen += min;
		data >>= min;
		dataLen -= min;

	}
}

void BitArrayPush(struct bitArray* containerArr, uint32_t inData, uint8_t inDataLen) {
	//printf("\n\n---------------- BitArrayPush ----------------\n\n");
	uint8_t maskslowtoHight[9] = { 0b11111111,0b11111110,0b11111100,0b11111000,0b11110000,0b11100000,0b11000000,0b10000000,0b00000000 };
	uint8_t maskshighttoLow[9] = { 0b11111111,0b01111111,0b00111111,0b00011111,0b00001111,0b00000111,0b00000011,0b00000001,0b00000000 };

	uint32_t data = inData;
	uint8_t dataLen = inDataLen;
	//容器
	uint32_t containerMax = containerArr->max;
	uint32_t containerLen = containerArr->len;
	uint8_t bitUseLen = 0;
	uint8_t bitLeaveLen = 0;

	while (dataLen > 0)
	{
		//当前字节占用位信息
		bitUseLen = containerLen % 8;
		//当前字节剩余位信息
		bitLeaveLen = 8 - bitUseLen;

		//比较小的数据内容块 决定要移动的数据
		uint8_t min = dataLen < bitLeaveLen ? dataLen : bitLeaveLen;

		//临时变量赋值
		uint8_t temp = (uint8_t)data;
		temp = (temp << bitUseLen) & maskslowtoHight[bitUseLen];

		//当前字节数据
		uint8_t currentIndex = containerLen / 8;
		//清除原先的数据
		containerArr->data[currentIndex] &= maskshighttoLow[bitLeaveLen];
		//塞入数据
		containerArr->data[currentIndex] |= temp;
		//总数据长度更新
		containerLen += min;
		//更新数据
		data >>= min;
		//当前数据长度更新
		dataLen -= min;
	}
	containerArr->len += inDataLen;
	//printf("---------------- BitArrayPush ----------------\n\n");
}

uint32_t BitArrayPop(struct bitArray* arr, uint8_t getDataLen, uint32_t offset) {
	//printf("\n\n---------------- BitArrayPop ----------------\n\n");
	uint8_t maskslowtoHight[9] = { 0b11111111,0b11111110,0b11111100,0b11111000,0b11110000,0b11100000,0b11000000,0b10000000,0b00000000 };
	uint8_t maskshighttoLow[9] = { 0b11111111,0b01111111,0b00111111,0b00011111,0b00001111,0b00000111,0b00000011,0b00000001,0b00000000 };

	uint32_t outData = 0;
	uint8_t currentWriteLen = 0;
	//当前字节（数组index）
	uint8_t currentBytes = 0;
	//当前字节使用的位
	uint8_t A = 0;
	//当前字节剩余的位
	uint8_t B = 0;
	//L和B中小的部分
	uint8_t D = 0;
	uint8_t L = getDataLen;
	uint32_t O = offset;
	uint32_t temp = 0;
	uint8_t tempBlock = 0;

	while (L > 0) {
		currentBytes = O / 8;
		A = O % 8;
		//printf("\nA:%d\n", A);
		B = 8 - A;
		//printf("\nB:%d\n", B);
		//复制到block当中向低位移除A的部分
		tempBlock = arr->data[currentBytes];
		/*	printf("\ntempBlock\n");
			printBits(tempBlock, 8);*/
		tempBlock = tempBlock >> A;
		/*printf("\ntempBlock >> A %d\n",A);
		printBits(tempBlock, 8);*/

		//取L和B中小的部分
		D = L < B ? L : B;
		//printf("\nD:%d\n", D);
		//掩掉高位D以外的部分
		tempBlock &= maskshighttoLow[8 - D];
		/*printf("\ntempBlock &= mask %d\n", (8 - D));
		printBits(tempBlock, 8);*/
		//用32位容器装8位容器数据
		temp = (uint32_t)tempBlock;
		//数据往高位移动
		temp <<= currentWriteLen;
		/*printf("\ temp <<= currentWriteLen %d\n", currentWriteLen);
		printBits(tempBlock, 32);*/
		//合并数据
		outData |= temp;
		/*printf("\noutdata |= \n");
		printBits(outData, 32);*/
		L -= D;
		O += D;
		currentWriteLen += D;
	}

	//while (L > 0) {
	//printf("\n offset:%d\n",offset);
	//	currentBytes = O / 8;
	//	printf("\ncurrentBytes:%d", currentBytes);

	//	currentUseBit = O % 8;
	//	printf("\ncurrentUseBit:%d", currentUseBit);

	//	currentleaveBit = 8 - currentUseBit;
	//	printf("\ncurrentleaveBit:%d", currentleaveBit);

	//	//取出来要处理的8位块数据
	//	uint8_t blockData = 0;
	//	//往低位移动取出需要的数据
	//	blockData = (arr->data[currentBytes]) >> currentUseBit;
	//	printf("\n       bbbbb bbbData       ");
	//	//printBits_8(blockData, currentleaveBit);
	//	printBits_8(blockData, 32);

	//	//取小的部分数据量
	//	min = currentleaveBit > L ? L : currentleaveBit;
	//	//需要将高位数据掩码
	//	blockData &= maskshighttoLow[8-min];

	//	printf("\n       print bbbData&      ");
	//	printBits_8(blockData, 32);

	//	printf("\nmin:%d\n", min);
	//	L -= min;
	//	O += min;
	//	//输出的数据 需要考虑前面已读的数据长度，从低位往高位写
	//	blockData <<= currentWriteLen;
	//	printf("writeLen:%d",currentWriteLen);
	//	printf("\n       print bbbData<      ");
	//	printBits(blockData, 32);

	//	outData |= blockData;

	//	currentWriteLen += min;
	//	printf("\n       print outData|      ");
	//	printBits(outData, 32);
	//	//printBits(outData, currentWriteLen);
	//}
	////printf("\n\n---------------- BitArrayPop ----------------\n\n");
	//printf("\n       print outData       ");
	//printf("\n------ outData: %d\n", outData);
	//printBits(outData, 32);
	return outData;
}

uint32_t BitPop(uint8_t* data, uint8_t getDataLen, uint32_t offset) {
	uint8_t maskslowtoHight[9] = { 0b11111111,0b11111110,0b11111100,0b11111000,0b11110000,0b11100000,0b11000000,0b10000000,0b00000000 };
	uint8_t maskshighttoLow[9] = { 0b11111111,0b01111111,0b00111111,0b00011111,0b00001111,0b00000111,0b00000011,0b00000001,0b00000000 };

	uint32_t outData = 0;
	uint32_t currentWriteLen = 0;
	//当前字节（数组index）
	uint32_t currentBytes = 0;
	//当前字节使用的位
	uint8_t A = 0;
	//当前字节剩余的位
	uint8_t B = 0;
	//L和B中小的部分
	uint8_t D = 0;
	uint8_t L = getDataLen;
	uint32_t O = offset;
	uint32_t temp = 0;
	uint8_t tempBlock = 0;

	while (L > 0) {
		currentBytes = O / 8;
		A = O % 8;
		B = 8 - A;
		//复制到block当中向低位移除A的部分
		tempBlock = data[currentBytes];
		tempBlock = tempBlock >> A;

		//取L和B中小的部分
		D = L < B ? L : B;
		//掩掉高位D以外的部分
		tempBlock &= maskshighttoLow[8 - D];
		//用32位容器装8位容器数据
		temp = tempBlock;
		//数据往高位移动
		temp <<= currentWriteLen;
		//合并数据
		outData |= temp;
		L -= D;
		O += D;
		currentWriteLen += D;
	}
	return outData;
}

void BitsArrayTest() {
	printf("\n\n----------- print getbits -----------\n\n");

	uint32_t testSize = 4;
	struct bitArray testArr = { .data = (uint8_t*)malloc(testSize),.max = testSize,.len = 0,.bitlen = 0 };
	struct bitArray* bitTestArr = &testArr;
	bitTestArr->data[0] = 0b11001100;
	bitTestArr->data[1] = 0b10101011;
	bitTestArr->data[2] = 0b11100111;
	bitTestArr->data[3] = 0b11000111;

	BitArrayPop(bitTestArr, 9, 1);
	printf("\n\n----------- print getbits -----------\n\n");
}