#pragma once
#include"linklist.h"

struct LinkList CreateList(const uint32_t maxsize) {
	struct LinkList list = { .firstunit = NULL,.endunit = NULL,.len = 0,.maxSize = maxsize,.idmax = 1 };
	list.units = (struct ListUnit*)calloc(maxsize, sizeof(struct ListUnit));
	return list;
}

struct ListUnit* CreateListUnit(struct LinkList* list, uint32_t count, uint8_t data, uint8_t type) {
	struct ListUnit* u = NULL;
	for (uint32_t i = 0; i < list->maxSize; i++) {
		u = list->units + i;
		if (u->id == 0) {
			u->count = count;
			u->data = data;
			u->type = type;
			list->len++;
			u->id = list->idmax++;
			u->preview = u->next = NULL;
			//printf("create -- %d \n ", u->id);
			return u;
		}
	}
	return NULL;
}

void RemoveListUnit(struct LinkList* list, struct ListUnit* unit) {
	if (unit == NULL) return;

	if (IsFirstListUnit(unit)) {

		list->firstunit = unit->next;
		unit->next->preview = NULL;
	}
	if (IsLastListUnit(unit)) {
		list->endunit = unit->preview;
		unit->preview->next = NULL;
	}
	if (unit->preview != NULL && unit->next != NULL)
	{
		unit->preview->next = unit->next;
		unit->preview = unit->next = NULL;
	}

	unit->id = 0;
	list->len--;
}

void InsertListUnitToHead(struct LinkList* list, struct ListUnit* unit) {
	if (unit == NULL) return;
	if (list->firstunit == NULL) {
		//第一个元素 既是头也是尾
		list->firstunit = unit;
		list->endunit = unit;
		unit->preview = unit->next = NULL;
	}
	else {
		//printf("Head is Not NULL--\n  ");
		list->firstunit->preview = unit;
		unit->next = list->firstunit;
		list->firstunit = unit;
		unit->preview = NULL;
	}
}

void InsertListUnitToEnd(struct LinkList* list, struct ListUnit* unit) {
	if (unit == NULL) return;
	if (list->endunit == NULL)
	{	//第一个元素 既是头也是尾
		//printf("End Is NULL");
		list->firstunit = unit;
		list->endunit = unit;
	}
	else {
		//printf("unit %d , endunit %d\n", unit->data, list->endunit->data);
		unit->preview = list->endunit;
		list->endunit->next = unit;
		list->endunit = unit;
		unit->next = NULL;
	}
}

void InsertListUnitPreview(struct LinkList* list, struct ListUnit* target, struct ListUnit* unit) {
	if (unit == NULL || target == NULL)return;

	if (IsFirstListUnit(target)) {
		//没有前一个，队头
		InsertListUnitToHead(list, unit);
	}
	else
	{
		target->preview->next = unit;
		unit->next = target;
		unit->preview = target->preview;
		target->preview = unit;
	}

}

void InsertListUnitNext(struct LinkList* list, struct ListUnit* target, struct ListUnit* unit) {
	if (unit == NULL || target == NULL)return;
	//如果是最后一个
	if (IsLastListUnit(target)) {
		//printf("Insert to end");
		InsertListUnitToEnd(list, unit);
	}
	else {
		target->next->preview = unit;
		unit->next = target->next;
		target->next = unit;
		unit->preview = target;
	}
}

bool IsFirstListUnit(struct ListUnit* unit) {
	return unit != NULL && unit->preview == NULL && unit->next != NULL;
}

bool IsLastListUnit(struct ListUnit* unit) {
	bool islast = (unit != NULL && unit->next == NULL && unit->preview != NULL);
	//printf("is last: %d -- %c \n", islast, unit->data);
	return (unit != NULL && unit->next == NULL && unit->preview != NULL);
}

void MultiPrintList(struct LinkList* list) {
	//printf("first: %c -- last:%c \n", list->firstunit->data, list->endunit->data);
	struct ListUnit* u = NULL;
	printf("\narray:");
	for (uint32_t i = 0; i < list->maxSize; ++i) {
		u = list->units + i;
		printf("%d,", u->id);
	}
	printf("\n data:");
	u = list->firstunit;
	while (u != NULL) {
		//printf("unit -- count: %d -- data: %c -- type: %d", u->count, u->data, u->type, u->id);
		printf("%c/%d(%d),", u->data, u->data, u->count);
		u = u->next;
	}
}

void test() {

	//创建
	struct LinkList list = CreateList(10);
	//printf("size:%d\n", sizeof(struct ListUnit));

	struct ListUnit* u1 = CreateListUnit(&list, 3, 'A', 1);
	InsertListUnitToHead(&list, u1);

	struct ListUnit* u2 = CreateListUnit(&list, 4, 'B', 1);
	InsertListUnitToHead(&list, u2);

	struct ListUnit* u3 = CreateListUnit(&list, 5, 'C', 1);
	InsertListUnitToHead(&list, u3);

	struct ListUnit* u4 = CreateListUnit(&list, 6, 'D', 1);
	InsertListUnitPreview(&list, u1, u4);

	struct ListUnit* u5 = CreateListUnit(&list, 7, 'E', 1);
	InsertListUnitToEnd(&list, u5);

	/*RemoveListUnit(&list,u2);
	RemoveListUnit(&list, u3);
	RemoveListUnit(&list, u5);*/

	MultiPrintList(&list);

}