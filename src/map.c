#include "map.h"


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
				temp->value = NULL;
				temp = NULL;
				//printf("\n free temp[%d]:", i);
			}
			free(e->value);
			free(e);
			e->value = NULL;
			e = NULL;
		}
	}
	free(map->data);
	map->mapLen = 0;
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
	//printf("key:%d\n", key);
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

uint32_t GetMapKeys(Map* map, uint32_t* mapKeys) {
	//Element count
	uint32_t index = 0;
	for (size_t i = 0; i < SlotNum; i++)
	{
		MapElement* e = map->data[i];
		while (e)
		{
			*(mapKeys + index) = e->key;
			e = e->next;
			index++;
		}
	}
	return index;
}

uint32_t GetMapValues(Map* map, void* mapValues) {
	uint8_t* values = (uint8_t*)mapValues;
	uint32_t index = 0;
	for (size_t i = 0; i < SlotNum; i++)
	{
		MapElement* e = map->data[i];
		while (e)
		{
			memcpy(values + (index * map->valueSize), e->value, map->valueSize);
			e = e->next;
			index++;
		}
	}
	return index;
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
			MapElement* eNext = e->next;
			while (eNext)
			{
				printf(" [%d,%d]", eNext->key, *((uint32_t*)(eNext->value)));
				eNext = eNext->next;
			}
		}
	}
}

void testLifeTime() {
	for (size_t i = 0; i < 10000000; i++)
	{
		Map map = CreateMap(4);
		uint32_t e0 = 60000;
		uint32_t e1 = 61000;
		uint32_t e2 = 62000;
		uint32_t e3 = 33333;
		uint32_t e4 = 44444;
		uint32_t e5 = 55555;
		uint32_t e6 = 11556;
		uint32_t e7 = 44332;
		uint32_t e8 = 12345;

		AddMapElement(&map, "mnbv", &e0);
		AddMapElement(&map, "abcd", &e1);
		AddMapElement(&map, "geok", &e2);
		AddMapElement(&map, "ffdd", &e3);
		AddMapElement(&map, "test", &e4);
		AddMapElement(&map, "next", &e5);
		AddMapElement(&map, "prev", &e6);
		AddMapElement(&map, "1155", &e7);
		AddMapElement(&map, "uiyo", &e8);

		PrintMap(&map);
		ReleaseMap(&map);
	}
}

void testRand() {

	for (size_t i = 0; i < 100000; i++)
	{
		srand(time(NULL));
		Map map = CreateMap(4);
		for (size_t n = 0; n < 20; n++)
		{
			uint32_t v = (uint32_t)rand();
			char skey[5] = "1234";
			skey[0] = (char)(rand() % 25 + 65);
			skey[1] = (char)(rand() % 25 + 65);
			skey[2] = (char)(rand() % 25 + 65);
			skey[3] = (char)(rand() % 25 + 65);
			skey[4] = 0;

			printf("[char:%s,", skey);
			printf("v:%d ] \n ", v);
			AddMapElement(&map, skey, &v);
		}

		/*for (size_t n = 0; n < 2; n++)
		{
			uint32_t value = rand();
			for (int i = 2; i < 10; i++) {
				char* skey = (char*)malloc(sizeof(char) * i);
				for (size_t k = 0; k < i; k++)
				{
					skey[k] = (char)(rand() % 95 + 32);;
				}
				skey[i - 1] = 0;
				printf("char:%s  ", skey);
				AddMapElement(&map, skey, &value);
				free(skey);
			}
		}*/

		PrintMap(&map);
		uint32_t mapLen = GetMapLength(&map);

		uint32_t* keys = (uint32_t*)calloc(mapLen, sizeof(uint32_t));
		uint32_t keysCount = GetMapKeys(&map, keys);
		printf("keysCount:%d\n", keysCount);

		uint32_t* mapValues = calloc(mapLen, sizeof(mapValues));
		uint32_t valueCount = (uint32_t*)GetMapValues(&map, mapValues);
		printf("valueCount:%d\n", valueCount);

		printf("\n");
		for (size_t i = 0; i < valueCount; i++)
		{
			printf("values[%d]:%d\n", i, mapValues[i]);
		}
		for (size_t i = 0; i < keysCount; i++)
		{
			printf("keys[%d]:%d\n", i, keys[i]);
		}

		ReleaseMap(&map);

		free(keys);
		keys = NULL;
		free(mapValues);
		mapValues = NULL;

	}
}


void MapTest() {

	//testLifeTime();

	testRand();
}