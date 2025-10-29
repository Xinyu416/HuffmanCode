#include "../include/map.h"


void TestMultipHash() {
	//乘法散列函数
	//h(k) = m(kA mod 1)
	int m = 30;
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

Map CreateMap(uint32_t slotNum) {
	Map map = { .slotNum = slotNum,.data = (uint8_t*)malloc(sizeof(uint8_t*) * slotNum) };
	return map;
}

void ReleaseMap(Map* map) {
	for (size_t i = 0; i < map->slotNum; i++)
	{
		free(map->data + i);
		*(map->data + i) = NULL;
	}
}

uint32_t GenerateK(Map* map, const char* str) {
	//文字转int值 当做元素key值 设置到元素上
	uint32_t k = BKDRHash(str);
	printf("\nk:%d\n",k);
	float A = ((sqrtf(5) - 1)) / 2;

	printf("\nmap->slotNum:%d\n", map->slotNum);
	//临时算出index值
	uint32_t hIndex = floorf(map->slotNum * (fmodf(k * A, 1)));
	printf("\nhKey:%d\n", hIndex);
	return hIndex;
}

void MapSet(Map* map, MapElement* e) {

}


void PrintMap(Map* map) {
	for (size_t i = 0; i < map->slotNum; i++)
	{
		printf("\n[%d],[%p]", i, map->data + i);
	}
}


void MapTest() {

	//TestMultipHash();
	Map map = CreateMap(10);
	PrintMap(&map);
	//ReleaseMap(&map);
	MapElement e0 = { 0 };
	uint16_t e0value = 65000;

	e0.value = (uint16_t*)malloc(sizeof(uint16_t));
	e0.value = e0value;
	uint32_t key = GenerateK(&map, "abc");
	e0.key = key;

	printf("\n[key:%d,value:%d]\n", e0.key,e0.value);
}