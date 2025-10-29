#include "../include/containers.h"


/// <summary>
/// 创建数组
/// </summary>
/// <param name="elementSize"></param>
/// <returns></returns>
Array ArrayCreate(uint32_t elementSize) {
	size_t count = 100000;
	Array arr = { .data = (uint8_t*)malloc(elementSize * count),.dataTemp = (uint8_t*)malloc(elementSize * 1),.elementSize = elementSize,.length = 0,.size = count * elementSize };
	return arr;
}

/// <summary>
/// 数组释放
/// </summary>
/// <param name="arr"></param>
void ArrayRelease(Array* arr) {

	arr->length = 0;
	arr->size = 0;
	free(arr->data);
	arr->data = NULL;
}

/// <summary>
/// 数组扩容
/// </summary>
/// <param name="arr">源数组</param>
/// <returns>扩容后的数组</returns>
Array* ArrayResize(Array* arr) {
	uint8_t* newContainer = (uint8_t*)malloc(arr->size * 2);
	memcpy(newContainer, arr->data, arr->size);
	free(arr->data);
	arr->data = newContainer;
	arr->size = arr->size * 2;
	return arr;
}

/// <summary>
/// 数组打印
/// </summary>
/// <param name="arr"></param>
void PrintArray(Array* arr) {

	printf("\nContainer size:%d , length:%d, elementSize:%dB,useByte:%dB,totalByte:%dB\n", arr->size, arr->length, arr->elementSize, arr->length * arr->elementSize, arr->size * arr->elementSize);
	printf("Elements:");
	for (uint32_t i = 0; i < arr->length; i++)
	{
		printf("   ");
		uint8_t* element = arr->data + (i * arr->elementSize);
		for (uint32_t j = 0; j < arr->elementSize; j++) {
			printf("%x", element[j]);
		}
	}
}

/// <summary>
/// 在数组末尾新增元素
/// </summary>
/// <param name="arr">源数组</param>
/// <param name="element">新增的元素</param>
void ArrayPush(Array* arr, void* element) {
	if (((arr->length + 1) * arr->elementSize > arr->size)) {
		//元素占用总空间 > 容器总空间 需要扩容
		//uint8_t* newContainer = (uint8_t*)malloc(arr->size * 2);/
		//逐字节拷贝
		//for (uint32_t i = 0; i < arr->length; i++)
		//{
		//	for (uint32_t j = 0; j < arr->elementSize; j++)
		//	{
		//		newContainer[i * arr->elementSize + j] = arr->data[i * arr->elementSize + j];
		//	}
		//}
		//arr->size = arr->size * 2;
		arr = ArrayResize(arr);
	}

	memcpy(arr->data + (arr->length * arr->elementSize), element, arr->elementSize);
	/*uint8_t* temp = (uint8_t*)element;
	for (uint32_t i = 0; i < arr->elementSize; i++)
	{
		arr->data[arr->length * arr->elementSize + i] = temp[i];
	}*/
	arr->length = arr->length + 1;
}

/// <summary>
/// 获取数组元素
/// </summary>
/// <param name="arr">源数组</param>
/// <param name="index">元素下标</param>
/// <returns></returns>
uint8_t* GetArrayElementByIndex(Array* arr, uint32_t index) {

	return arr->data + (index * arr->elementSize);
}

/// <summary>
/// 插入数组元素
/// </summary>
/// <param name="arr">源数组</param>
/// <param name="element">插入的元素</param>
/// <param name="index">插入的位置</param>
void ArrayInsert(Array* arr, void* element, uint32_t index) {
	if (((arr->length + 1) * arr->elementSize > arr->size)) {
		//元素占用总空间 > 容器总空间 需要扩容
		arr = ArrayResize(arr);
	}
	//从数组最后一个元素开始挪动
	for (uint32_t i = arr->length; i > index; i--)
	{
		memcpy(arr->data + (i * arr->elementSize), arr->data + ((i - 1) * arr->elementSize), arr->elementSize);
	}
	memcpy(arr->data + (index * arr->elementSize), element, arr->elementSize);
	arr->length = arr->length + 1;
	//逐字节拷贝
	//if (((arr->length + 1) * arr->elementSize < arr->size)) {
	//	//不需要扩容
	//	arr->length = arr->length + 1;
	//	for (uint32_t i = arr->length - 1; i > index; i--)
	//	{
	//		uint8_t* moveElement = arr->data + ((i - 1) * arr->elementSize);
	//		for (uint32_t j = 0; j < arr->elementSize; j++)
	//		{
	//			arr->data[i * arr->elementSize + j] = moveElement[j];
	//		}
	//	}

	//	uint8_t* insertElement = (uint8_t*)element;
	//	for (uint32_t i = 0; i < arr->elementSize; i++)
	//	{
	//		arr->data[index * arr->elementSize + i] = insertElement[i];
	//	}
	//}
}

/// <summary>
/// 删除数组元素
/// </summary>
/// <param name="arr">源数组</param>
/// <param name="index">删除的元素下标</param>
void ArrayDelete(Array* arr, uint32_t index) {

	/*for (uint32_t i = index; i < arr->length; i++)
	{
		uint8_t* moveElement = arr->data + ((i + 1) * arr->elementSize);
		for (uint32_t j = 0; j < arr->elementSize; j++)
		{
			arr->data[i * arr->elementSize + j] = moveElement[j];
		}
	}*/
	for (uint32_t i = index; i < arr->length; i++) {

		memcpy(arr->data + (i * arr->elementSize), arr->data + ((i + 1) * arr->elementSize), arr->elementSize);
	}
	arr->length = arr->length - 1;
}

/// <summary>
/// 获取数组元素数量
/// </summary>
/// <param name="arr"></param>
/// <returns></returns>
uint32_t GetArrayElementCount(Array* arr) {

	return arr->length;
}

/// <summary>
/// 交换数组元素
/// </summary>
/// <param name="arr"></param>
/// <param name="index1"></param>
/// <param name="index2"></param>
void ArrayExchange(Array* arr, int32_t index1, int32_t index2) {
	//uint8_t* temp = (uint8_t*)malloc(sizeof(uint8_t) * arr->elementSize);
	uint8_t* temp = arr->dataTemp;
	memcpy(temp, arr->data + (index1 * arr->elementSize), arr->elementSize);
	memcpy(arr->data + (index1 * arr->elementSize), arr->data + (index2 * arr->elementSize), arr->elementSize);
	memcpy(arr->data + (index2 * arr->elementSize), temp, arr->elementSize);
	//free(temp);
}

/// <summary>
/// 数组分区
/// </summary>
/// <param name="arr"></param>
/// <param name="startIndex"></param>
/// <param name="endIndex"></param>
/// <param name="compareFunc"></param>
/// <returns></returns>
int32_t ArrayPartition(Array* arr, int32_t startIndex, int32_t endIndex, bool (*compareFunc)(void*, void*)) {
	//数组最后一个元素 基准值
	uint8_t* x = arr->data + (endIndex * arr->elementSize);
	uint8_t* valj;
	int32_t i = startIndex - 1;
	for (int32_t j = startIndex; j < endIndex; j++)
	{
		valj = arr->data + (j * arr->elementSize);
		if (compareFunc(valj, x)) {

			i++;
			ArrayExchange(arr, i, j);
		}
	}
	i++;
	ArrayExchange(arr, i, endIndex);
	return i;
}

/// <summary>
/// 数组快速排序
/// </summary>
/// <param name="arr"></param>
/// <param name="startIndex"></param>
/// <param name="endIndex"></param>
/// <param name="compareFunc"></param>
void ArrayQuickSort(Array* arr, int32_t startIndex, int32_t endIndex, bool (*compareFunc)(void*, void*)) {

	if (startIndex >= endIndex)return;
	int32_t q = ArrayPartition(arr, startIndex, endIndex, compareFunc);
	ArrayQuickSort(arr, startIndex, (q - 1), compareFunc);
	ArrayQuickSort(arr, (q + 1), endIndex, compareFunc);
}

/// <summary>
/// 普通数据类型的交换
/// </summary>
/// <param name="arr"></param>
/// <param name="index1"></param>
/// <param name="index2"></param>
void Exchange(uint32_t* arr, int32_t index1, int32_t index2) {
	uint32_t temp = arr[index1];
	arr[index1] = arr[index2];
	arr[index2] = temp;
}

/// <summary>
/// 普通数组数据类型分区
/// </summary>
/// <param name="arr"></param>
/// <param name="p"></param>
/// <param name="r"></param>
/// <returns></returns>
int32_t Partition(uint32_t* arr, int32_t p, int32_t r) {

	int32_t x = arr[r];
	int32_t i = p - 1;
	for (int32_t j = p; j < r; j++)
	{
		if (arr[j] <= x) {

			i++;
			Exchange(arr, i, j);
		}
	}

	i++;
	Exchange(arr, i, r);
	return i;
}

/// <summary>
/// 快速排序算法
/// </summary>
/// <param name="arr"></param>
/// <param name="p"></param>
/// <param name="r"></param>
void QuickSort(uint32_t* arr, int32_t p, int32_t r) {

	if (p >= r)return;
	int32_t q = Partition(arr, p, r);
	QuickSort(arr, p, (q - 1));
	QuickSort(arr, (q + 1), r);
}