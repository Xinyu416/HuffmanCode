#define _CRT_SECURE_NO_WARNINGS

#include "linklist.h"
#include "HuffmanCode.h"
#include <math.h>
#include <time.h> 
#include "bitoperate.h"
#include "include/containers.h"
#include "include/coding.h"
#include "include/map.h"
#include "include/readBMP.h"


void TestQuickSort() {
	//快速排序一般数据类型测试
	//uint32_t testArr[] = { 8,6,7,4,1,3,9,5,2 };
	//uint32_t* testArr = (uint32_t*)malloc(sizeof(uint32_t) * 8);
	clock_t t = clock();
	uint32_t* testArr = (uint32_t*)malloc(sizeof(uint32_t) * 10000000);
	testArr[0] = 2;
	testArr[1] = 8;
	testArr[2] = 7;
	testArr[3] = 1;
	testArr[4] = 3;
	testArr[5] = 5;
	testArr[6] = 6;
	testArr[7] = 4;
	for (size_t i = 0; i < 10000000; i++)
	{
		testArr[i] = rand();
	}
	int32_t p = 0;
	int32_t r = 10000000 - 1;

	/*数组创建计时*/
	t = clock() - t;
	printf("\n ArrayCreate Time: %d clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);
	QuickSort(testArr, p, r);

	t = clock() - t;
	printf("\n ArraySort Time: %d clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);
	printf("\n");
	for (size_t k = 0; k < 10000000; k++)
	{
		printf("%d,", testArr[k]);
	}
	free(testArr);
}

/// <summary>
/// 比较自定义类型函数
/// </summary>
/// <param name="e1"></param>
/// <param name="e2"></param>
/// <returns></returns>
bool myCompareFuncUint16(void* e1, void* e2) {
	uint16_t e1val = *((uint16_t*)e1);
	uint16_t e2val = *((uint16_t*)e2);
	//printf("\ne1val：%d,e2val:%d\n", e1val, e2val);
	return e1val <= e2val;
}
bool myCompareSize_t(void* e1, void* e2) {
	size_t e1val = *((size_t*)e1);
	size_t  e2val = *((size_t*)e2);
	//printf("\ne1val：%d,e2val:%d\n", e1val, e2val);
	return e1val <= e2val;
}
bool myCompareTestContainer(void* e1, void* e2) {
	TestContainer e1val = *((TestContainer*)e1);
	TestContainer  e2val = *((TestContainer*)e2);
	//printf("\ne1val：%d,e2val:%d\n", e1val, e2val);
	return e1val.number0 <= e2val.number0;
}

void TestFuncPtr() {
	/*函数指针类型测试*/
	/*声明myFunction 函数变量*/
	bool (*myFunction)(void*, void*) = myCompareFuncUint16;
	/*通过函数变量形式调用函数*/
	myFunction(123, 567);
}

void TestCustomArray() {
	Array arr = ArrayCreate(2);
	PrintArray(&arr);
	uint16_t e0 = 0xddff;
	uint16_t e1 = 0xeeee;
	uint16_t e2 = 0xe59d;
	uint16_t e3 = 0xaaaa;
	uint16_t e4 = 0xbbbb;
	uint16_t e5 = 0xcccc;
	uint16_t e6 = 0xdddd;
	uint16_t e7 = 0xabcd;
	uint16_t e8 = 0xaabb;
	uint16_t e9 = 0xccdd;
	uint16_t e10 = 0xffff;
	ArrayPush(&arr, &e0);
	ArrayPush(&arr, &e1);
	ArrayPush(&arr, &e2);
	ArrayPush(&arr, &e3);
	ArrayPush(&arr, &e4);
	ArrayInsert(&arr, &e5, 0);
	ArrayInsert(&arr, &e6, 5);
	PrintArray(&arr);

	/*uint16_t* e3 = (uint16_t*)GetArrayElementByIndex(&arr,0);
	printf("e3:%x\n",*e3);*/

	uint16_t* insertElement1 = 0x3333;
	ArrayInsert(&arr, &insertElement1, 1);
	PrintArray(&arr);

	ArrayDelete(&arr, 1);
	PrintArray(&arr);

	uint16_t* insertElement2 = 0xffff;
	ArrayInsert(&arr, &insertElement2, 1);
	PrintArray(&arr);

	ArrayDelete(&arr, 2);
	PrintArray(&arr);

	/*ArrayExchange(&arr, 0, 1);
	PrintArray(&arr);*/

	/*用快速排序重排数组*/
	//ArrayPartition(&arr,0, GetArrayElementCount(&arr)-1, myCompareFunc);
	ArrayQuickSort(&arr, 0, GetArrayElementCount(&arr) - 1, myCompareFuncUint16);
	PrintArray(&arr);

	ArrayRelease(&arr);
}


void TestCustomArray2() {
	Array arr = ArrayCreate(sizeof(size_t));
	size_t randomNumber = 0;
	size_t e = 0;
	clock_t t = clock();
	for (size_t i = 0; i < 10000000; i++)
	{
		e = rand();
		ArrayPush(&arr, &e);
	}
	/*数组创建计时*/
	t = clock() - t;
	printf("\n ArrayCreate Time: %d clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);
	ArrayQuickSort(&arr, 0, GetArrayElementCount(&arr) - 1, myCompareSize_t);

	t = clock() - t;
	printf("\nArrayQuickSort Time: %d clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);
	ArrayRelease(&arr);
}


void TestCustomArrayTestContainer() {
	printf("sizeof(TestContainer):%d\n", sizeof(TestContainer));
	Array arr = ArrayCreate(sizeof(TestContainer));
	size_t randomNumber = 0;
	TestContainer e = { 0 };
	clock_t t = clock();
	for (size_t i = 0; i < 10000000; i++)
	{
		e.number0 = rand();
		ArrayPush(&arr, &e);
	}
	t = clock() - t;
	printf("\nIt took me %d clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);

	ArrayQuickSort(&arr, 0, GetArrayElementCount(&arr) - 1, myCompareTestContainer);
	t = clock() - t;
	printf("\nIt took me %d clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);
	ArrayRelease(&arr);
}

int main() {
	/*编解码 霍夫曼code*/
	//Codec();
	//TestQuickSort();
	/*TestCustomArray();
	TestCustomArray2();*/
	//TestCustomArrayTestContainer();
	// 编解码测试
	//printf("entry");
	//MapTest();

	ReadBMPFile();
	TestCoding();
}
