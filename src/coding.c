#include "coding.h"

void GenerateCode(Node* nodes, Node* node, uint32_t bit, Code* codes, Code c, uint32_t indent) {
	indent++;
	//叶节点
	c.len = c.len + 1;
	//从树节点的上到下 位序从低到高
	c.code |= bit << (c.len - 1);
	if (node->type == 0) {
		codes[node->data] = c;
		return;
	}
	else {
		Node* child1 = nodes + node->childIndex;
		Node* child2 = nodes + node->childIndex - 1;
		GenerateCode(nodes, child2, 0, codes, c, indent);
		GenerateCode(nodes, child1, 1, codes, c, indent);
	}
}

void PrintTree(Node* nodes, Node* node, uint32_t indent) {
	indent++;
	printf("\n");
	for (size_t i = 0; i < indent; i++)
	{
		printf("   ");
	}
	printf("index:%d ,Cindex:%d ,data: %x , count：%d ,type:%d", node->parentIndex, node->childIndex, node->data, node->frequcey, node->type);

	//叶节点 打印叶子
	if (node->type == 0) {
		return;
	}
	else {
		Node* child1 = nodes + node->childIndex;
		Node* child2 = nodes + node->childIndex - 1;
		PrintTree(nodes, child2, indent);
		PrintTree(nodes, child1, indent);
	}
}

struct bitArray Coding(const uint8_t* content, uint32_t inDataLen) {
	const uint8_t* datas = content;
	/*不重复的数组元素*/
	uint32_t data[datasize] = { 0 };

	/*内容下标*/
	uint32_t index;
	for (uint32_t i = 0; i < inDataLen; i++) {
		/*用内容当下标，重复值当频率内容*/
		index = datas[i];
		data[index]++;
	}

	/*统计非空数据量*/
	uint32_t no_empty_size = 0;
	for (uint32_t i = 0; i < datasize; i++) {
		if (data[i] >= 1) {
			no_empty_size++;
		}
	}

	//构建链表
	printf("非空数据大小 %d   --- Len: %d\n", no_empty_size, inDataLen);
	struct LinkList list = CreateList(no_empty_size);
	Node* nodes = (Node*)calloc(sizeof(Node) * no_empty_size * 2, 1);
	Node* node = NULL;
	uint32_t nodeNum = 0;

	/*对非空数据排序 按频率升序写入units*/
	uint32_t unit_index = 0;
	uint32_t minsize = UINT32_MAX;

	uint8_t value = 0;
	uint32_t count = 0;
	bool isContinue = false;
	while (true) {
		value = 0;
		isContinue = false;
		//下标即为值（0~255）
		for (uint32_t j = 0; j < datasize; j++) {
			count = data[j];
			if (count != 0 && minsize >= count) {
				value = (uint8_t)j;
				minsize = count;
				isContinue = true;
			}
		}
		if (isContinue) {
			struct ListUnit* u = CreateListUnit(&list, minsize, value, 0);
			InsertListUnitToEnd(&list, u);
			//将原始数据清空 数据值往新数组迁移
			data[value] = 0;
			minsize = UINT32_MAX;
		}
		else {
			break;
		}
	}

	//合并插入到原链表
	struct ListUnit* first = list.firstunit;//链表头元素
	struct ListUnit* currentUnit = NULL;
	struct ListUnit* u1 = NULL;//链表第一个元素
	struct ListUnit* u2 = NULL;//链表第二个元素
	struct ListUnit* last = NULL; //链表最后一个元素
	struct ListUnit* merge = NULL;
	//合并元素属性
	uint32_t newCount = 0;
	uint32_t numOfUnits = no_empty_size;

	printf("\nnumOfUnits %d\n", numOfUnits);
	//MultiPrintList(&list);
	while (numOfUnits > 1) {
		//printf("first unit data -- %c ,count:%d\n", first->data, first->count);
		u1 = first;
		u2 = first->next;
		if (u1->next != NULL) {
		}
		first = u2->next;
		if (u2->next != NULL) {
		}
		newCount = u1->count + u2->count;

		//先移除链表前两个元素，空出位置放入合并的新元素
		node = nodes + nodeNum;
		node->frequcey = u1->count;
		node->type = u1->type;
		node->parentIndex = nodeNum;
		//合并节点的子节点设置
		if (node->type == 1) {
			node->data = 0;
			node->childIndex = u1->data;
		}
		else {
			node->data = u1->data;
		}
		++nodeNum;
		//第二个节点处理
		node = nodes + nodeNum;
		node->type = u2->type;
		node->frequcey = u2->count;
		node->parentIndex = nodeNum;
		//合并节点的子节点设置
		if (node->type == 1) {
			node->data = 0;
			node->childIndex = u2->data;
		}
		else {
			node->data = u2->data;
		}
		++nodeNum;
		//从原链表移除
		RemoveListUnit(&list, u1); numOfUnits--;
		RemoveListUnit(&list, u2); numOfUnits--;
		//合并的元素
		//创建新的组合单元并插入到单元集合中，并标记单元类型为组合单元（type=1），data中存的是指向成员单元的索引（因为两个成员单元的索引是相邻的所以只要储存一个就可以）
		merge = CreateListUnit(&list, newCount, nodeNum - 1, 1);
		currentUnit = first;
		while (currentUnit != NULL) {
			if (currentUnit->count > merge->count) {
				if (IsFirstListUnit(currentUnit)) {
					first = merge;
				}
				InsertListUnitPreview(&list, currentUnit, merge);
				++numOfUnits;
				break;
			}
			if (IsLastListUnit(currentUnit)) {
				last = currentUnit;
			}
			currentUnit = currentUnit->next;
		}
		//插入到最后一个
		if (last != NULL) {
			InsertListUnitToEnd(&list, merge);
			++numOfUnits;
		}
		//MultiPrintList(&list);
	}

	Code codes[256] = { 0 };
	Node* tempNode = nodes + nodeNum - 1;
	//printf("\n------------- 打印树结构 Start -------------\n");
	/*PrintTree(nodes, tempNode, 0, 1, 1);
	PrintTree(nodes, tempNode - 1, 0, 0, 1);*/
	//printf("\n------------- 打印树结构 End -------------\n");

	//编码的左右头节点
	Code c0 = { .code = 0,.len = 0 };
	Code c1 = { .code = 1,.len = 0 };

	/*递归编码*/
	GenerateCode(nodes, tempNode, 1, &codes, c1, 0);
	GenerateCode(nodes, tempNode - 1, 0, &codes, c0, 0);

	uint32_t contentBitsLen = 0;
	//统计原文数据位长度
	for (uint32_t i = 0; i < inDataLen; i++)
	{
		contentBitsLen += codes[datas[i]].len;
	}
	struct DataHeader header = { .nodesNum = nodeNum,.byteCount = inDataLen };
	uint32_t header_byteCount = sizeof(header.byteCount);
	uint32_t nodeBitsNum = 9;

	uint32_t totalBits = nodeBitsNum + nodeNum * 10 + header_byteCount * 8 + contentBitsLen;
	//用10个位装每个node节点的数据，1位装节点类型，9位装数据，类型 0 叶节点 data则为数据，类型 1 合并节点 data为子节点索引
	//文件字节数
	uint32_t fileBytes = (uint32_t)ceilf((float)totalBits / 8.0f);

	printf("totalBits :%d ,fileBytes :%d \n", totalBits, fileBytes);
	struct bitArray arr = { .data = (uint8_t*)malloc(fileBytes),.max = fileBytes,.len = 0,.bitlen = 0 };
	struct bitArray* bitArr = &arr;
	uint32_t bitsBuf = 0;
	node = NULL;

	/*将头信息压入位数组*/
	BitArrayPush(bitArr, header.nodesNum, 9);//节点数 9 位 最大 510 9位足够装
	BitArrayPush(bitArr, header.byteCount, header_byteCount * 8);

	printf("nodeNum:%d -- header.byteCount:%d -- contentBitsLen:%d\n", nodeNum, header.byteCount, contentBitsLen);


	/*将树信息压入位数组*/
	for (uint32_t i = 0; i < nodeNum; i++)
	{
		node = nodes + i;
		BitArrayPush(bitArr, node->type, 1);
		//printf("\nnode[%d],type:%d,data:%x[", i, node->type, node->data);

		//printBits(node->type, 1);
		//9位存储节点数据 type在高1位，data在低9位
		if (node->type == 0) {
			//叶节点 位数据即data值
			BitArrayPush(bitArr, node->data, 9);
			//printBits(node->data, 9);
		}
		else {
			//合并节点的数据是子节点索引
			BitArrayPush(bitArr, node->childIndex, 9);
			//printBits(node->childIndex, 9);
		}
		//printf("]");
	}

	//printf("\n\n--------------- 压入content位数据 End --------------\n\n");

	bitsBuf = 0;
	//原文数据压入位数组 不定长度的位信息
	for (uint32_t i = 0; i < inDataLen; i++)
	{
		bitsBuf = codes[datas[i]].code;
		BitArrayPush(bitArr, bitsBuf, codes[datas[i]].len);
		/*printf("\nlen[%d]:code:%d value:%x[", i, bitsBuf, datas[i]);
		printBits(bitsBuf, codes[datas[i]].len);
		printf("]");*/
	}

	//printf("\n--------------- 打印位串 --------------\n");
	//printf("bitArr len: %d\n", bitArr->len);
	//for (size_t i = 0; i < bitArr->max; i++)
	//{
	//	printBits(bitArr->data[i], 8);
	//}

	free(nodes);
	free(list.units);
	return arr;
}

/// <summary>
/// 按位解码数据
/// </summary>
/// <param name="inNodes"></param>
/// <param name="nodesNum"></param>
/// <param name="bitArr"></param>
/// <param name="inOffset"></param>
/// <param name="inContentBitLens"></param>
void _DecodeContentData_Context(Node* inNodes, uint16_t nodesNum, struct bitArray* bitArr, uint32_t inOffset, uint32_t bytesCount, uint8_t* outData) {
	uint8_t readbit = 0;
	Node* nodes = inNodes;
	uint32_t offset = inOffset;
	uint32_t itemCount = 0;
	Node* n0 = &inNodes[nodesNum - 2];//靠左 0
	Node* n1 = &inNodes[nodesNum - 1];//靠右 1
	Node* currentNode = NULL;

	//第一个位 0 靠左 ，1 靠右
	while (true) {
		readbit = (uint8_t)BitArrayPop(bitArr, 1, offset);
		offset += 1;
		if (readbit == 0) {
			currentNode = n0;
		}
		else
		{
			currentNode = n1;
		}

		while (currentNode != NULL && currentNode->type == 1) {
			//非叶节点 读子数据
			readbit = (uint8_t)BitArrayPop(bitArr, 1, offset);
			offset += 1;
			if (readbit == 0) {
				//左分支
				currentNode = &nodes[currentNode->childIndex - 1];
			}
			else {
				//右分支
				currentNode = &nodes[currentNode->childIndex];
			}
		}

		if (currentNode != NULL && currentNode->type == 0) {
			outData[itemCount] = currentNode->data;
			itemCount++;
			//printf("%x,  ", currentNode->data);
		}

		if (itemCount >= bytesCount)
		{
			break;
		}
	}

}

uint8_t* Decoding(struct bitArray* bitArr) {
	//内容中读取数据
	//printf("\n\n-------------------------------- 内存中读取数据  Start -------------------------------------");
	struct DataHeader header_read = { .nodesNum = 0,.byteCount = 0 };
	uint32_t offset = 0;
	uint32_t buf = 0;
	uint8_t type = 0;
	uint16_t outdata = 0;

	//读取头数据
	header_read.nodesNum = (uint16_t)BitArrayPop(bitArr, 9, offset); offset += 9;
	//printf("\nheader_read.nodesNum：%d\n", header_read.nodesNum);

	header_read.byteCount = BitArrayPop(bitArr, sizeof(header_read.byteCount) * 8, offset);
	offset += sizeof(header_read.byteCount) * 8;
	//printf("\nheader_read.byteCount：%d\n", header_read.byteCount);

	//printf("current offset：%d\n", offset);

	Node* readNodes = (Node*)malloc(header_read.nodesNum * sizeof(Node));
	for (uint32_t i = 0; i < header_read.nodesNum; i++)
	{
		//按9位取数据
		type = BitArrayPop(bitArr, 1, offset); offset += 1;
		readNodes[i].type = type;

		//叶节点
		if (type == 0) {
			readNodes[i].data = BitArrayPop(bitArr, 9, offset); offset += 9;
			readNodes[i].childIndex = 0;
		}
		else {
			readNodes[i].childIndex = BitArrayPop(bitArr, 9, offset); offset += 9;
			readNodes[i].data = 0;
		}
		//printf("outdata %x \n", outdata);
	}
	/*printf("\noffset：%d\n", offset);
	printf("\nheader_read.nodesNum：%d\n", header_read.nodesNum);
	printf("\nheader_read.byteCount：%d\n", header_read.byteCount);*/

	uint8_t* outData = (uint8_t*)malloc(header_read.byteCount);

	//内存中数据解析
	_DecodeContentData_Context(readNodes, header_read.nodesNum, bitArr, offset, header_read.byteCount, outData);

	free(readNodes);
	return outData;

}
