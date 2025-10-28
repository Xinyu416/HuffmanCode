#include "HuffmanCode.h"
#include "linklist.h"

/*打印链表*/
void PrintList(Unit* head) {
	Unit* current = head;

	if (current == NULL) {
		printf("链表为空\n");
		return;
	}
	while (current != NULL) {
		printf("printList %c -- %d\n", (char)current->data, current->frequency);
		current = current->next;
	}
	printf("NULL\n");
}

bool IsLastUnit(Unit* u) {
	return u->next == NULL;
}

bool IsFirstUnit(Unit* u) {
	return u->preview == NULL;
}

Unit* CreateUnit(Unit* units, uint8_t len, uint8_t frequecy, uint8_t data, uint8_t type) {
	Unit* u = NULL;
	for (size_t i = 0; i < len; i++) {
		if (units[i].frequency == 0) {
			units->frequency = frequecy;
			units->data = data;
			units->type = type;
			u = &units[i];
			break;
		}
	}
	return u;
}

void InsertUnitPreview(Unit* current, Unit* target) {
	/*插入到的元素是第一个*/
	if (IsFirstUnit(target)) {
		target->preview = current;
		current->next = target;
		current->preview = NULL;
	}
	else {
		target->preview->next = current;
		current->preview = target->preview;
		target->preview = current;
		current->next = target;
	}
}

void InsertUnitNext(Unit* current, Unit* target) {
	/*插入到的元素是最后一个*/
	if (IsLastUnit(target)) {
		target->next = current;
		current->preview = target;
		current->next = NULL;
	}
	else {
		target->next->preview = current;
		current->next = target->next;
		target->next = current;
		current->preview = target;
	}
}

void RemoveUnit(Unit* unit) {
	unit->next->preview = NULL;
	unit->next = NULL;
}

void ResetUnit(Unit* unit) {
	memset(unit, 0, 1);
	/*unit->next->preview = NULL;
	unit->next = NULL;
	unit->data = 0;
	unit->frequency = 0;
	unit->childIndex = 0;*/
}

uint8_t GetEmptyUnit(Unit* units, uint8_t len) {
	for (size_t i = 0; i < len; i++) {
		if (units[i].frequency == 0) {
			return i;
		}
	}
}


void generateList(Unit* units, uint8_t no_empty_size) {
	/*Unit* u = CreateUnit(units,no_empty_size,);
	for (size_t i = 0; i < no_empty_size; i++) {
		if (newUnit->frequency < units[i].frequency) {
			units[i].preview = newUnit;
			units[i - 1].next = newUnit;
			newUnit->next = &units[i];
			newUnit->preview = &units[i - 1];
			printf("merged -- [insert] %c:%d -- [merged] %d\n", (char)units[i].data, units[i].frequency, newUnit->frequency);
			break;
		}
	}*/
}

void UnitSort(Unit* units, uint32_t data[]) {
	/*对非空数据排序 按频率升序写入units*/
	uint32_t unit_index = 0;
	uint32_t minsize = UINT32_MAX;

	uint8_t value = 0;
	uint32_t count = 0;
	while (true) {
		value = 0;
		for (uint32_t j = 0; j < datasize; j++) {
			count = data[j];
			if (count != 0 && minsize >= count) {
				value = (uint8_t)j;
				minsize = count;
			}
		}
		if (value != 0) {
			units[unit_index].frequency = minsize;
			units[unit_index].data = value;
			units[unit_index].childIndex = unit_index;
			units[unit_index].preview = NULL;
			units[unit_index].next = NULL;
			unit_index++;
			data[value] = 0;
			printf("UnitSort:: %c -- %d\n", value, minsize);
			minsize = UINT32_MAX;
		}
		else {
			break;
		}
	}
}


void GetUnitPushToNode(Unit* unit, Node* node) {
	node->childIndex = unit->childIndex;
	node->data = unit->data;
	node->frequcey = unit->frequency;
}

int main_()
{
	const char* content = "AACDEEGFDEGHKBK";
	uint8_t len = strlen(content);

	/*char 数组转uint8 数组*/
	const uint8_t* datas = (const uint8_t*)content;

	/*不重复的数组元素*/
	uint32_t data[datasize] = { 0 };
	/*内容下标*/
	uint32_t index;
	for (uint32_t i = 0; i < len; i++) {
		/*用内容当下标，重复值当频率内容*/
		index = (uint8_t)datas[i];
		data[index]++;
	}

	/*统计非空数据量*/
	uint32_t no_empty_size = 0;
	for (uint32_t i = 0; i < datasize; i++) {
		if (data[i] >= 1) {
			no_empty_size++;
		}
	}

	printf("非空数据大小 %d \n", no_empty_size);
	Unit* units = (Unit*)calloc(sizeof(Unit) * no_empty_size, 1);
	Node* nodes = (Node*)calloc(sizeof(Node) * no_empty_size * 2, 1);

	/*对非空数据排序 按频率升序写入units*/
	UnitSort(units, data);

	/*建立units链*/
	for (uint32_t i = 0; i < no_empty_size; i++) {
		printf("units -- %c -- %d\n", (char)units[i].data, units[i].frequency);
		if (i > 0) {
			units[i].preview = &units[i - 1];
		}
		if (i < no_empty_size - 1) {
			units[i].next = &units[i + 1];
		}
	}

}
