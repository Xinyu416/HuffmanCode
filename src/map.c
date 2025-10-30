#include "../include/map.h"


void TestMultipHash() {
	//乘法散列函数
	//h(k) = m(kA mod 1)
	int m = 10;
	int k = 0;
	float A = ((sqrtf(5) - 1)) / 2;
	int h = 0;
	//floorf(m * (fmodf(k * A, 1)));
	for (size_t i = 0; i < 1000; i++)
	{
		if ((i % 10) == 0)printf("\n");
		k = i;
		h = floorf(m * (fmodf(k * A, 1)));
		printf("(%d,%d),", k, h);
	}
	printf("\nA:%f\n", A);
	/*k = 1334887048;
	h = floorf(m * (fmodf(k * A, 1)));

	printf("\nh:%d\n",h);*/

	//除法散列
	//h(k) = k mod m

	/*const char* str = "abcd test skdfjas";
	uint32_t s2n = BKDRHash(str);
	printf("\ns2n:%d\n", s2n);*/

}

void UniversalHashing() {
	//全域散列函数
	//h(a,b)(k) = ((a*k+b)mod p)mod m

	int a = 3;
	int b = 4;
	int k = 8;
	int m = 1000;
	int p = 1111;
	int h = 0;
	// fmodf(fmodf((a * k + b), p), m);

	for (size_t i = 1; i < 1000; i++)
	{
		if ((i % 10) == 0)printf("\n");
		k = i;
		h = fmodf(fmodf((a * k + b), p), m);
		printf("(%d, %d),", i, h);
	}
}

Map CreateMap(uint32_t valueSize) {
	Map map = { .mapLen = 0, .valueSize = valueSize,.data = (MapElement**)calloc(SlotNum,sizeof(MapElement*)) };
	return map;
}

void ReleaseMap(Map* map) {
	for (size_t i = 0; i < SlotNum; i++)
	{
		MapElement* e = map->data[i];
		if (e != NULL) {
			MapElement* eNext = e->next;
			MapElement* temp = NULL;
			while (eNext != NULL)
			{
				temp = eNext;
				eNext = eNext->next;
				free(temp->value);
				free(temp);
				printf("\n free temp[%d]:", i);
			}
		}
		printf("\n free e [%d]:", i);
		free(e);
	}
	printf("\n free map.data");
	free(map->data);
}

void AddMapElement(Map* map, const char* skey, void* value) {
	//(key,value) 元素是否存在 
	//用skey 转换成 int key 再用int key 转换成index
	uint32_t ikey = BKDRHash(skey);
	uint32_t mapIndex = GenerateMapIndex(map, ikey);

	//查找key是否存在
	MapElement* findEle = __ContainsMapElement(map, ikey);
	if (findEle) {
		//替换key值
		memcpy(findEle->value, value, map->valueSize);
	}
	else {

		if (map->data[mapIndex] == NULL) {
			//不存在任何元素 添加
			MapElement* e = (MapElement*)calloc(1, sizeof(MapElement));
			e->value = (uint8_t*)malloc(map->valueSize);
			memcpy(e->value, value, map->valueSize);
			e->key = ikey;
			e->next = NULL;
			map->data[mapIndex] = e;
			//printf("\n %s %d : 第一个槽位为空 添加元素\n", skey, e->key);
		}
		else
		{
			//没有相同键值元素 新增元素
			MapElement* e = (MapElement*)calloc(1, sizeof(MapElement));
			e->key = ikey;
			e->next = NULL;
			e->value = (uint8_t*)malloc(map->valueSize);
			memcpy(e->value, value, map->valueSize);

			MapElement* temp = map->data[mapIndex];
			e->next = temp;
			map->data[mapIndex] = e;
			//printf("\n [%d][%s,%d] :槽位头有元素 添加到槽位头\n", mapIndex, skey, e->key);
		}
		map->mapLen++;
	}

	////第一个元素为空
	//if (map->data[mapIndex] == NULL) {
	//	//不存在 添加
	//	MapElement* e = (MapElement*)calloc(1, sizeof(MapElement));
	//	e->value = (uint8_t*)malloc(map->valueSize);
	//	memcpy(e->value, value, map->valueSize);
	//	e->key = ikey;
	//	e->next = NULL;
	//	map->data[mapIndex] = e;
	//	map->mapLen++;
	//	printf("\n %s %d : 第一个槽位为空 添加元素\n", skey, e->key);
	//}
	//else {
	//	bool isReplace = false;
	//	//槽位有元素存在 判断元素内容是否重复 从头元素往下找
	//	MapElement* current = map->data[mapIndex];
	//	while (current != NULL) {
	//		if (current->key == ikey) {

	//			//键相同 替换值
	//			memcpy(current->value, value, map->valueSize);
	//			printf("\n %s :键相同 替换值\n", skey);
	//			isReplace = true;
	//			break;
	//		}
	//		current = current->next;
	//	}

	//	if (!isReplace) {
	//		//没有相同键值元素 新增元素
	//		MapElement* e = (MapElement*)calloc(1, sizeof(MapElement));
	//		e->key = ikey;
	//		e->next = NULL;
	//		e->value = (uint8_t*)malloc(map->valueSize);
	//		memcpy(e->value, value, map->valueSize);

	//		MapElement* temp = map->data[mapIndex];
	//		e->next = temp;
	//		map->data[mapIndex] = e;
	//		printf("\n [%d][%s,%d] :槽位头有元素 添加到槽位头\n", mapIndex, skey, e->key);
	//	}
	//}
}

bool RemoveMapElement(Map* map, const char* skey) {
	uint32_t key = BKDRHash(skey);
	for (size_t i = 0; i < SlotNum; i++)
	{
		MapElement* e = map->data[i];
		MapElement* pre = NULL;

		while (e)
		{
			if (e->key == key) {
				if (pre) {
					//如果有前一个 连接前一个的下一个元素的引用
					pre->next = e->next;
				}
				else {
					//删除首元素时重新指定元素头
					map->data[i] = e->next;
				}
				free(e->value);
				free(e);
				return true;
			}
			pre = e;
			e = e->next;
		}
	}
	return false;
}

MapElement* __ContainsMapElement(Map* map, uint32_t key) {
	for (size_t i = 0; i < SlotNum; i++)
	{
		MapElement* e = map->data[i];
		while (e)
		{
			if (e->key == key) {
				return e;
			}
			e = e->next;
		}
	}
	return NULL;
}

MapElement* FindMapElement(Map* map, const char* skey) {

	uint32_t key = BKDRHash(skey);
	printf("key:%d\n", key);
	for (size_t i = 0; i < SlotNum; i++)
	{
		MapElement* e = map->data[i];
		while (e)
		{
			if (e->key == key) {
				return e;
			}
			e = e->next;
		}
	}
	return NULL;
}

uint32_t* GetMapKeys(Map* map) {
	uint32_t* keys = (uint32_t*)malloc(map->mapLen);
	uint32_t index = 0;
	for (size_t i = 0; i < SlotNum; i++)
	{
		MapElement* e = map->data[i];
		while (e)
		{
			printf("\nkey:%d\n", e->key);
			keys[index] = e->key;
			e = e->next;
			index++;
		}
	}
	return keys;
}

void* GetMapValues(Map* map) {
	uint8_t* values = (uint8_t*)malloc(map->mapLen * map->valueSize);
	uint32_t index = 0;
	for (size_t i = 0; i < SlotNum; i++)
	{
		MapElement* e = map->data[i];
		while (e)
		{
			//memcpy(values[index*(map->valueSize)], e->value, map->valueSize);
			e = e->next;
			index++;
		}
	}
	return values;
}


uint32_t GetMapLength(Map* map) {
	return map->mapLen;
}

uint32_t GenerateMapIndex(Map* map, uint32_t key) {
	//通过key值算出index值
	float A = ((sqrtf(5) - 1)) / 2;
	uint32_t hIndex = (uint32_t)floorf(SlotNum * (fmodf(key * A, 1)));
	return hIndex;
}

void PrintMap(Map* map) {
	for (size_t i = 0; i < SlotNum; i++)
	{
		MapElement* e = map->data[i];
		printf("\n[%d]:", i);
		if (e) {
			printf(" [%d,%d]", e->key, *((uint32_t*)(e->value)));
			//printf("[%d]", e->key);
			MapElement* eNext = e->next;
			while (eNext)
			{
				printf(" [%d,%d]", eNext->key, *((uint32_t*)(eNext->value)));
				eNext = eNext->next;
			}
		}
	}
}

void MapTest() {

	//TestMultipHash();
	Map map = CreateMap(4);
	uint32_t e0 = 60000;
	uint32_t e1 = 61000;
	uint32_t e2 = 62000;
	uint32_t e3 = 33333;
	uint32_t e4 = 33333;
	uint32_t e5 = 33333;
	uint32_t e6 = 33333;
	uint32_t e7 = 33333;


	int index = 0;
	for (size_t n = 0; n < 5; n++)
	{
		uint32_t value = rand();
		for (int i = 2; i < 10; i++) {
			char* skey = (char*)malloc(sizeof(char) * i);
			for (size_t k = 0; k < i; k++)
			{
				skey[k] = (char)(rand() % 95 + 32);;
			}
			skey[i] = 0;
			printf("\nchar:%s\n", skey);
			index++;
			AddMapElement(&map, skey, &value);
		}
	}

	//PrintMap(&map);
	AddMapElement(&map, "a", &e0);
	AddMapElement(&map, "abcdef", &e1);
	AddMapElement(&map, "gedsafd", &e2);
	AddMapElement(&map, "a", &e3);
	RemoveMapElement(&map, "gedsafd");

	PrintMap(&map);
	printf("\nindex:%d", index);
	printf("\n map len:%d\n", GetMapLength(&map));

	uint32_t* keys = (uint32_t*)malloc(GetMapLength(&map));
	uint32_t* values = (uint32_t*)malloc(GetMapLength(&map));
	keys = (uint32_t*)GetMapKeys(&map);
	values = (uint32_t*)GetMapValues(&map);

	for (size_t i = 0; i < GetMapLength(&map); i++)
	{
		printf("values[%d]:%d\n",i,values[i]);
	}

	/*MapElement* findElement = FindMapElement(&map, "a");
	printf("\nfind value:%d", *(uint32_t*)(findElement->value));*/

	//ReleaseMap(&map);
}