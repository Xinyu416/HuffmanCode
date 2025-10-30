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
	uint8_t* v = NULL;

	//第一个元素为空
	if (map->data[mapIndex] == NULL) {
		//不存在 添加
		MapElement* e = (MapElement*)calloc(1, sizeof(MapElement));

		e->value = (uint8_t*)malloc(map->valueSize);
		memcpy(e->value, value, map->valueSize);
		e->key = ikey;
		e->next = NULL;
		map->data[mapIndex] = e;
		map->mapLen++;
		printf("\n %s %d : 第一个槽位为空 添加元素\n", skey, e->key);
	}
	else {
		bool isReplace = false;
		//槽位有元素存在 判断元素内容是否重复 从头元素往下找
		MapElement* current = map->data[mapIndex];
		while (current != NULL) {
			if (current->key == ikey) {

				//键相同 替换值
				memcpy(current->value, value, map->valueSize);
				printf("\n %s :键相同 替换值\n", skey);
				isReplace = true;
				break;
			}
			current = current->next;
		}

		if (!isReplace) {
			//没有相同键值元素 新增元素
			MapElement* e = (MapElement*)calloc(1, sizeof(MapElement));
			e->key = ikey;
			e->next = NULL;
			e->value = (uint8_t*)malloc(map->valueSize);
			memcpy(e->value, value, map->valueSize);

			MapElement* temp = map->data[mapIndex];
			e->next = temp;
			map->data[mapIndex] = e;
			printf("\n [%d][%s,%d] :槽位头有元素 添加到槽位头\n", mapIndex, skey, e->key);
		}
	}
}

bool RemoveMapElement(const char* skey) {

	return false;
}

MapElement* FindMapElement(const char* skey) {

	return NULL;
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
		if (e != NULL) {
			printf(" [%d,%d]", e->key, *((uint32_t*)(e->value)));
			//printf("[%d]", e->key);
			MapElement* eNext = e->next;
			while (eNext != NULL)
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
	//PrintMap(&map);
	AddMapElement(&map, "a", &e0);
	AddMapElement(&map, "abcdef", &e1);
	AddMapElement(&map, "gedsafd", &e2);
	PrintMap(&map);

	/*MapElement e0 = { 0 };
	MapElement e1 = { .key = 89454,.value = 60000 };
	uint16_t e0value = 65000;

	e0.value = (uint16_t*)malloc(sizeof(uint16_t));
	e0.value = e0value;
	ConvertKey(&e0, "abc");
	uint32_t index = GenerateMapIndex(&map, e0.key);

	map.data[index] = &e0;
	map.data[index]->next = &e1;
	printf("\nmap.data[index]->value:%d\n", map.data[index]->value);
	printf("\nmap.data[index] next:%d\n", map.data[index]->next->value);

	printf("\nindex:%d -- [key:%d,value:%d]\n", index, e0.key, e0.value);*/
	ReleaseMap(&map);
}