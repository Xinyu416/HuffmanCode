#define _CRT_SECURE_NO_WARNINGS
#include "linklist.h"
#include "HuffmanCode.h"
#include <math.h>
#include <time.h> 
#include "bitoperate.h"
//#include "fileRead.h"
#include "include/containers.h"
#include "include/coding.h"

//uint32_t CodesNum = 0;
//void CreateCode(Node* nodes, Node* node, uint32_t bit, uint32_t code, uint32_t bitlen, Code* codes) {
//	//叶节点
//	if (node->type == 0) {
//		(codes + CodesNum)->code = code;
//		(codes + CodesNum)->len = bitlen;
//		++CodesNum;
//		printf("\n index:%d ,data: %d , count：%d ,type:%d \n", node->parentIndex, node->data, node->frequcey, node->type);
//		return;
//	}
//	else {
//		Node* child1 = nodes + node->childIndex;
//		Node* child2 = nodes + node->childIndex - 1;
//		CreateCode(nodes, child1, 1, (code << 1) | 1, bitlen + 1, codes);
//		CreateCode(nodes, child2, 0, (code << 1) | 0, bitlen + 1, codes);
//	}
//}
//
//void ReadContentData_Context(Node* inNodes, uint16_t nodesNum, struct bitArray* bitArr, uint32_t inOffset, uint32_t inContentBitLens) {
//	uint8_t readbit = 0;
//	Node* nodes = inNodes;
//	uint8_t offset = inOffset;
//	uint32_t contentBitLens = inContentBitLens;
//	Node* n0 = &inNodes[nodesNum - 2];//靠左 0
//	Node* n1 = &inNodes[nodesNum - 1];//靠右 1
//	Node* currentNode = NULL;
//
//	//第一个位 0 靠左 ，1 靠右
//	while (contentBitLens > 0) {
//		readbit = (uint8_t)BitArrayPop(bitArr, 1, offset);
//		offset += 1;
//		contentBitLens--;
//		if (readbit == 0) {
//			currentNode = n0;
//		}
//		else
//		{
//			currentNode = n1;
//		}
//
//		while (currentNode != NULL && currentNode->type == 1 && contentBitLens > 0) {
//			//非叶节点 读子数据
//			readbit = (uint8_t)BitArrayPop(bitArr, 1, offset);
//			offset += 1;
//			contentBitLens--;
//			if (readbit == 0) {
//				//左分支
//				if ((currentNode->data) - 1 > 0) {
//
//					currentNode = &nodes[currentNode->data - 1];
//				}
//				else {
//					break;
//				}
//			}
//			else {
//				//右分支
//				if ((currentNode->data) > 0) {
//					currentNode = &nodes[currentNode->data];
//				}
//				else
//				{
//					break;
//				}
//			}
//		}
//
//		if (currentNode != NULL && currentNode->type == 0) {
//			//printf("data : %d  --  char: %c\n", currentNode->data, currentNode->data);
//		}
//	}
//}
//
//void ReadContentData_Infile(Node* inNodes, uint16_t nodesNum, uint8_t* data, uint32_t inOffset, uint32_t inContentBitLens) {
//	uint8_t readbit = 0;
//	Node* nodes = inNodes;
//	uint8_t offset = inOffset;
//	uint32_t contentBitLens = inContentBitLens;
//	Node* n0 = &inNodes[nodesNum - 2];//靠左 0
//	Node* n1 = &inNodes[nodesNum - 1];//靠右 1
//	Node* currentNode = NULL;
//	//printf("n0 type: %d,data:%d \n", n0->type, n0->data);
//	//printf("n1 type: %d,data:%d \n", n1->type, n1->data);
//	//printf("\n\n readbit:%d ,contentBitLens %d  nodesNum %d\n", readbit, contentBitLens, nodesNum);
//
//
//	//第一个位 0 靠左 ，1 靠右
//
//	while (contentBitLens > 0) {
//		readbit = (uint8_t)BitPop(data, 1, offset);
//		offset += 1;
//		contentBitLens--;
//		if (readbit == 0) {
//			currentNode = n0;
//		}
//		else
//		{
//			currentNode = n1;
//		}
//
//		while (currentNode != NULL && currentNode->type == 1 && contentBitLens > 0) {
//			//非叶节点 读子数据
//			readbit = (uint8_t)BitPop(data, 1, offset);
//			offset += 1;
//			contentBitLens--;
//			if (readbit == 0) {
//				//左分支
//				if ((currentNode->data) - 1 > 0) {
//
//					currentNode = &nodes[currentNode->data - 1];
//				}
//				else {
//					break;
//				}
//			}
//			else {
//				//右分支
//				if ((currentNode->data) > 0) {
//					currentNode = &nodes[currentNode->data];
//				}
//				else
//				{
//					break;
//				}
//			}
//		}
//
//		if (currentNode != NULL && currentNode->type == 0) {
//			printf("data : %d  --  char: %c\n", currentNode->data, currentNode->data);
//		}
//	}
//}
//
//void GenerateCode(Node* nodes, Node* node, uint32_t bit, Code* codes, Code c, uint32_t indent) {
//	indent++;
//	//叶节点
//	c.len = c.len + 1;
//	//从树节点的上到下 位序从低到高
//	c.code |= bit << (c.len - 1);
//
//	printf("\n");
//	for (size_t i = 0; i < indent; i++)
//	{
//		printf("  ");
//	}
//	if (node->type == 0) {
//		printf("index:%d ,data: %d , count：%d ,type:%d  ", node->parentIndex, node->data, node->frequcey, node->type);
//		for (size_t i = 0; i < indent; i++)
//		{
//			printf("  ");
//		}
//		codes[node->data] = c;
//		return;
//	}
//	else {
//		Node* child1 = nodes + node->childIndex;
//		Node* child2 = nodes + node->childIndex - 1;
//		GenerateCode(nodes, child2, 0, codes, c, indent);
//		GenerateCode(nodes, child1, 1, codes, c, indent);
//	}
//}
//
//void PrintTree(Node* nodes, Node* node, uint32_t indent) {
//	indent++;
//	printf("\n");
//	for (size_t i = 0; i < indent; i++)
//	{
//		printf("   ");
//	}
//	printf("index:%d ,data: %d , count：%d ,type:%d", node->parentIndex, node->data, node->frequcey, node->type);
//
//	//叶节点 打印叶子
//	if (node->type == 0) {
//		return;
//	}
//	else {
//		Node* child1 = nodes + node->childIndex;
//		Node* child2 = nodes + node->childIndex - 1;
//		PrintTree(nodes, child2, indent);
//		PrintTree(nodes, child1, indent);
//	}
//}
//
//void Codec() {
//	//const char* content = "AACDEEGFDEGHKBK  AACDEEGFDEGHKBK 1155665 4433221 adfsksldfjsdf2io33-23049543-sdjdfjslaf;-32203432045 52 sfsdf2hhkjhkjyu AACDEEGFDEGHKBK  AACDEEGFDEGHKBK 1155665 4433221 adfsksldfjsdf2io33-23049543-sdjdfjslaf;-32203432045 52 sfsdf2hhkjhkjyu";
//	const char* content = "Robust Programming The following conditions may cause an exception: The path is not valid for one of the following reasons: it is a zero-length string, it contains only white space, it contains invalid characters, or it is a device path (starts with \.\) (ArgumentException). The path is not valid because it is Nothing (ArgumentNullException). destinationFileName is Nothing or an empty string (ArgumentNullException). The source file is not valid or does not exist (FileNotFoundException). The combined path points to an existing directory, the destination file exists and overwrite is set to False, a file in the target directory with the same name is in use, or the user does not have sufficient permissions to access the file (IOException). A file or directory name in the path contains a colon (:) or is in an invalid format (NotSupportedException). showUI is set to True, onUserCancel is set to ThrowException, and either the user has cancelled the operation or an unspecified I/O error occurs (OperationCanceledException). The path exceeds the system-defined maximum length (PathTooLongException). The user lacks necessary permissions to view the path (SecurityException). The user does not have required permission (UnauthorizedAccessException). See also MoveFile How to: Rename a File How to: Create a Copy of a File in a Different Directory How to: Parse File Paths Collaborate with us on GitHub The source for this content can be found on GitHub, where you can also create and review issues and pull requests. For more information, see our contributor guide. .NET feedback .NET is an open source project. Select a link to provide feedback: Open a documentation issue Provide product feedback Additional resources Documentation How to: Rename a File - Visual Basic Learn about how to rename a file with the Visual Basic Runtime Library or the .NET base class library. How to: Parse File Paths - Visual Basic Learn more about: How to: Parse File Paths in Visual Basic How to: Delete a File - Visual Basic Learn more about: How to: Delete a File in Visual Basic Show 2 more";
//	//const char* content = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";
//	uint32_t len = strlen(content);
//
//	/*char 数组转uint8 数组*/
//	const uint8_t* datas = (const uint8_t*)content;
//
//	/*不重复的数组元素*/
//	uint32_t data[datasize] = { 0 };
//	/*内容下标*/
//	uint32_t index;
//	for (uint32_t i = 0; i < len; i++) {
//		/*用内容当下标，重复值当频率内容*/
//		index = (uint8_t)datas[i];
//		data[index]++;
//	}
//
//	/*统计非空数据量*/
//	uint32_t no_empty_size = 0;
//	for (uint32_t i = 0; i < datasize; i++) {
//		if (data[i] >= 1) {
//			no_empty_size++;
//		}
//	}
//	printf("\n-----------------------  构建链表 Start -----------------------\n");
//	//构建链表
//	printf("非空数据大小 %d   --- Len: %d\n", no_empty_size, len);
//
//	struct LinkList list = CreateList(no_empty_size);
//	Node* nodes = (Node*)calloc(sizeof(Node) * no_empty_size * 2, 1);
//
//	Node* node = NULL;
//	uint32_t nodeNum = 0;
//	Node* nodeChild1 = NULL;
//	Node* nodeChild2 = NULL;
//
//	/*对非空数据排序 按频率升序写入units*/
//	uint32_t unit_index = 0;
//	uint32_t minsize = UINT32_MAX;
//
//	uint8_t value = 0;
//	uint32_t count = 0;
//	while (true) {
//		value = 0;
//		for (uint32_t j = 0; j < datasize; j++) {
//			count = data[j];
//			if (count != 0 && minsize >= count) {
//				value = (uint8_t)j;
//				minsize = count;
//			}
//		}
//		if (value != 0) {
//			struct ListUnit* u = CreateListUnit(&list, minsize, value, 0);
//			InsertListUnitToEnd(&list, u);
//			data[value] = 0;
//			minsize = UINT32_MAX;
//		}
//		else {
//			break;
//		}
//	}
//
//	printf("\n-----------------------  构建链表 End -----------------------\n");
//
//	printf("\n-----------------------  合并节点 Start -----------------------\n");
//
//	//合并插入到原链表
//	struct ListUnit* first = list.firstunit;//链表头元素
//	struct ListUnit* currentUnit = NULL;
//	struct ListUnit* u1 = NULL;//链表第一个元素
//	struct ListUnit* u2 = NULL;//链表第二个元素
//	struct ListUnit* last = NULL; //链表最后一个元素
//	struct ListUnit* merge = NULL;
//	//合并元素属性
//	uint32_t newCount = 0;
//	uint32_t numOfUnits = no_empty_size;
//
//	printf("\nnumOfUnits %d\n", numOfUnits);
//	MultiPrintList(&list);
//
//	while (numOfUnits > 1) {
//		//printf("first unit data -- %c ,count:%d\n", first->data, first->count);
//		u1 = first;
//		u2 = first->next;
//		if (u1->next != NULL) {
//		}
//		first = u2->next;
//		if (u2->next != NULL) {
//		}
//		newCount = u1->count + u2->count;
//
//		//先移除链表前两个元素，空出位置放入合并的新元素
//		node = nodes + nodeNum;
//		node->frequcey = u1->count;
//		node->type = u1->type;
//		node->parentIndex = nodeNum;
//		//合并节点的子节点设置
//		if (node->type == 1) {
//			node->data = 0;
//			node->childIndex = u1->data;
//			/*nodeChild1 = nodes + node->childIndex - 1;
//			nodeChild2 = nodes + node->childIndex - 0;
//			nodeChild1->parentIndex = nodeNum;
//			nodeChild2->parentIndex = nodeNum;*/
//		}
//		else {
//			node->data = u1->data;
//		}
//		++nodeNum;
//		//第二个节点处理
//		node = nodes + nodeNum;
//		node->type = u2->type;
//		node->frequcey = u2->count;
//		node->parentIndex = nodeNum;
//		//合并节点的子节点设置
//		if (node->type == 1) {
//			node->data = 0;
//			node->childIndex = u2->data;
//			/*nodeChild1 = nodes + node->childIndex - 1;
//			nodeChild2 = nodes + node->childIndex - 0;
//			nodeChild1->parentIndex = nodeNum;
//			nodeChild2->parentIndex = nodeNum;*/
//		}
//		else {
//			node->data = u2->data;
//		}
//		++nodeNum;
//		//从原链表移除
//		RemoveListUnit(&list, u1); numOfUnits--;
//		RemoveListUnit(&list, u2); numOfUnits--;
//		//合并的元素
//		merge = CreateListUnit(&list, newCount, nodeNum - 1, 1);
//		currentUnit = first;
//		while (currentUnit != NULL) {
//			if (currentUnit->count > merge->count) {
//				if (IsFirstListUnit(currentUnit)) {
//					first = merge;
//				}
//				InsertListUnitPreview(&list, currentUnit, merge);
//				++numOfUnits;
//				break;
//			}
//			if (IsLastListUnit(currentUnit)) {
//				last = currentUnit;
//			}
//			currentUnit = currentUnit->next;
//		}
//		//插入到最后一个
//		if (last != NULL) {
//			InsertListUnitToEnd(&list, merge);
//			++numOfUnits;
//		}
//		MultiPrintList(&list);
//	}
//	printf("\n-----------------------  合并节点 End -----------------------\n");
//
//
//	printf("\n\n------- 打印node 节点 nodeNum:%d -------------\n", nodeNum);
//	for (uint32_t i = 0; i < nodeNum; i++) {
//		//printf("\nnode[%d] count: %d(child:%d)  ,type:%d,  data:%d \n", i, (nodes + i)->frequcey, (nodes + i)->childIndex, (nodes + i)->type, (nodes + i)->data);
//	}
//
//
//
//	Code codes[256] = { 0 };
//	Node* tempNode = nodes + nodeNum - 1;
//	printf("\n------------- 打印树结构 Start -------------\n");
//	PrintTree(nodes, tempNode, 0, 1, 1);
//	PrintTree(nodes, tempNode - 1, 0, 0, 1);
//	printf("\n------------- 打印树结构 End -------------\n");
//	//编码的左右头节点
//	Code c0 = { .code = 0,.len = 0 };
//	Code c1 = { .code = 1,.len = 0 };
//
//	printf("\n");
//	printf("\n ------------- 递归编码 Start -------------\n");
//	GenerateCode(nodes, tempNode, 1, &codes, c1, 0);
//	GenerateCode(nodes, tempNode - 1, 0, &codes, c0, 0);
//	printf("\n ------------- 打印编码  End -------------\n");
//	printf("\n");
//
//	//所有编码的长度 位数据
//	uint32_t codesLen = 0;
//	printf("\n-------------- print codeLens --------------\n\n");
//	for (uint32_t i = 0; i < 256; i++) {
//		codesLen += (codes + i)->len;
//		if ((codes + i)->len != 0)
//		{
//			//printf("codes[%d] : code: %d, len:%d\n", i, codes[i].code, codes[i].len);
//		}
//	}
//	printf("codeLen:%d\n", codesLen);
//	printf("\n-------------- print codeLens end --------------\n\n");
//	printf("\n--------------- 压入位数据 Start --------------\n\n");
//	uint32_t contentBitsLen = 0;
//	printf("len:%d\n", len);
//	//统计原文数据位长度
//	for (uint32_t i = 0; i < len; i++)
//	{
//		contentBitsLen += codes[datas[i]].len;
//	}
//	printf("contentBitsLen:%d\n", contentBitsLen);
//
//	struct DataHeader header = { .nodesNum = nodeNum,.contentCodeLen = contentBitsLen };
//	uint32_t totalBits = nodeNum * 9 + contentBitsLen + sizeof(header.nodesNum) * 8 + sizeof(header.contentCodeLen) * 8;
//
//	//用9个位装每个node节点的数据，1位装节点类型，8位装数据，类型 0 叶节点 data则为数据，类型 1 合并节点 data为子节点索引
//	//文件字节数
//	uint32_t fileBytes = (uint32_t)ceilf((float)totalBits / 8.0f);
//
//	printf("totalBits :%d ,fileBytes :%d \n", totalBits, fileBytes);
//
//
//	struct bitArray arr = { .data = (uint8_t*)malloc(fileBytes),.max = fileBytes,.len = 0,.bitlen = 0 };
//	struct bitArray* bitArr = &arr;
//
//	//将头信息压入位数组
//	BitArrayPush(bitArr, header.nodesNum, sizeof(header.nodesNum) * 8);
//	BitArrayPush(bitArr, header.contentCodeLen, sizeof(header.contentCodeLen) * 8);
//	printf("nodesNum:%d , contentCodeLen %d\n", header.nodesNum, header.contentCodeLen);
//
//	//将树信息压入位数组
//	uint32_t bitsBuf = 0;
//	node = NULL;
//	for (uint32_t i = 0; i < nodeNum; i++)
//	{
//		node = nodes + i;
//		bitsBuf = 0;
//		//printf("\n");
//		//printf("node(%d):", node->type);
//		if (node->type == 0) {
//			bitsBuf |= (uint32_t)node->data;
//			//printf("data:%d ", node->data);
//		}
//		else {
//			bitsBuf |= (uint32_t)node->childIndex;
//			//printf("childindex:%d ", node->childIndex);
//		}
//
//		bitsBuf |= (((uint32_t)node->type) << 8);
//		/*printf("type:%d", (uint32_t)node->type);
//		printf("bitsBuf code:");
//		printBits(bitsBuf, 9);*/
//		BitArrayPush(bitArr, bitsBuf, 9);
//	}
//	printf("\n\n--------------- 压入content位数据 End --------------\n\n");
//	bitsBuf = 0;
//	//原文数据压入位数组 不定长度的位信息
//	for (uint32_t i = 0; i < len; i++)
//	{
//		bitsBuf = codes[datas[i]].code;
//		//printf("char:%c -- %d  -- ", datas[i], datas[i]);
//		//printf("charCodeLen:%d\n", codes[datas[i]].len);
//		BitArrayPush(bitArr, bitsBuf, codes[datas[i]].len);
//	}
//	printf("bitArrBitsLen:%d\n", bitArr->len);
//
//	printf("\n\n--------------- 压入位数据 End --------------\n\n");
//
//	for (uint32_t i = 0; i < fileBytes; i++) {
//		/*printf("\ncontainerArr[%d],code:", i);
//		printBits_8(bitArr->data[i], 8);*/
//	}
//
//	//BitsArrayTest();
//
//	//内容中读取数据
//	printf("\n\n-------------------------------- 内存中读取数据  Start -------------------------------------");
//	struct DataHeader header_read = { .nodesNum = 0,.contentCodeLen = 0 };
//	uint32_t offset = 0;
//	uint32_t buf = 0;
//	uint8_t type = 0;
//	uint8_t outdata = 0;
//
//	//读取头数据
//	header_read.nodesNum = BitArrayPop(bitArr, sizeof(header_read.nodesNum) * 8, offset);
//	offset += sizeof(header_read.nodesNum) * 8;
//	header_read.contentCodeLen = BitArrayPop(bitArr, sizeof(header_read.contentCodeLen) * 8, offset);
//	offset += sizeof(header_read.contentCodeLen) * 8;
//
//	printf("\n\n sizeof(header_read.nodesNum) %d , sizeof(header_read.contentCodeLen) %d\n", sizeof(header_read.nodesNum), sizeof(header_read.contentCodeLen));
//
//	printf("header_read.nodesNum:%d , header_read.contentCodeLen:%d\n", header_read.nodesNum, header.contentCodeLen);
//
//	Node* readNodes = (Node*)malloc(header_read.nodesNum * sizeof(Node));
//	for (uint32_t i = 0; i < header_read.nodesNum; i++)
//	{
//		//按8+1位取数据
//		/*buf = BitArrayPop(bitArr, 8, offset);
//		offset += 8;
//		printf("\ndata: %d", buf);
//		buf = BitArrayPop(bitArr, 1, offset);
//		offset += 1;
//		printf("\n---type:%d\n", buf);*/
//
//		//按9位取数据
//		//printf("\n----------- %d -----------\n", i);
//		buf = BitArrayPop(bitArr, 9, offset);
//		//printBits(buf, 32);
//		outdata = (uint8_t)(buf & 0b11111111);
//		//printf("\ndata: %d", outdata);
//		type = (uint8_t)((buf >> 8) & 0b00000001);
//		//printf("\n---type:%d\n", type);
//		offset += 9;
//
//		readNodes[i].type = type;
//		(readNodes + i)->data = outdata;
//	}
//
//	ReadContentData_Context(readNodes, header_read.nodesNum, bitArr, offset, header.contentCodeLen);
//
//
//	printf("\n\n-------------------------------- 内存中读取数据  End -----------------------------------");
//
//	printf("\n\n-------------------------------- 文件中写出数据  Start -----------------------------------");
//
//	//写入数据到指定文件
//	const char* filename = "C:\\Users\\Xinyu\\Desktop\\test.express";
//	printf("\n写出文件到 %s:\n", filename);
//	FILE* writeStream = fopen(filename, "w+");
//	fwrite(bitArr->data, sizeof(uint8_t), fileBytes, writeStream);
//	fclose(writeStream);
//	printf("\n\n-------------------------------- 文件中写出数据  End -----------------------------------");
//
//
//	printf("\n\n-------------------------------- 文件中读取数据  Start -----------------------------------");
//	struct DataHeader header_read_file = { .nodesNum = 0,.contentCodeLen = 0 };
//	//读取文件
//	FILE* readStream_file = fopen(filename, "rb");
//	if (readStream_file == NULL) {
//		printf("readStream is NULL");
//	}
//
//	//读取文件头文件
//	fread(&header_read_file.nodesNum, sizeof(header_read_file.nodesNum), 1, readStream_file);
//	fread(&header_read_file.contentCodeLen, sizeof(header_read_file.contentCodeLen), 1, readStream_file);
//
//
//	//节点数组数据指针
//	Node* readNodes_read_file = (Node*)malloc(header_read_file.nodesNum * sizeof(Node));
//	//总字节数
//	uint32_t totalBits_file = header_read_file.nodesNum * 9 + header_read_file.contentCodeLen + sizeof(header_read_file.nodesNum) * 8 + sizeof(header_read_file.contentCodeLen) * 8;
//	uint32_t read_fileBytes = (uint32_t)ceilf((float)totalBits_file / 8.0f);
//
//	//总数据指针
//	uint8_t* read_file_data = (uint8_t*)malloc(read_fileBytes - sizeof(header_read_file.nodesNum) - sizeof(header_read_file.contentCodeLen));
//	uint32_t contentCount = fread(read_file_data, sizeof(uint8_t), read_fileBytes, readStream_file);
//	//offset = sizeof(header_read_file.nodesNum) * 8 + sizeof(header_read_file.contentCodeLen) * 8;
//	buf = 0;
//	offset = 0;
//	printf("header_read_file.nodesNum:%d\n", header_read_file.nodesNum);
//	for (uint32_t i = 0; i < header_read_file.nodesNum; i++)
//	{
//		//按8+1位取数据
//		/*buf = BitPop(read_file_data, 8, offset);
//		offset += 8;
//		printf("\ndata: %d", buf);
//		buf = BitPop(read_file_data, 1, offset);
//		offset += 1;
//		printf("\n---type:%d\n", buf);*/
//
//		//按9位取数据
//		//printf("\n----------- %d -----------\n", i);
//		buf = BitPop(read_file_data, 9, offset);
//		//printBits(buf, 32);
//		outdata = (uint8_t)(buf & 0b11111111);
//		//printf("\ndata: %d", outdata);
//		type = (uint8_t)((buf >> 8) & 0b00000001);
//		//printf("\n---type:%d\n", type);
//		offset += 9;
//
//		readNodes_read_file[i].type = type;
//		(readNodes_read_file + i)->data = outdata;
//	}
//
//	ReadContentData_Infile(readNodes_read_file, header_read_file.nodesNum, read_file_data, offset, header_read_file.contentCodeLen);
//
//
//	printf("\nheader_read_file.nodesNum:%d\n", header_read_file.nodesNum);
//	printf("header_read_file.contentCodeLen:%d\n", header_read_file.contentCodeLen);
//
//	fclose(readStream_file);
//	printf("\n\n-------------------------------- 文件中读取数据  End -----------------------------------");
//	free(readNodes_read_file);
//	free(arr.data);
//	free(read_file_data);
//	free(nodes);
//	free(readNodes);
//}

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
	int32_t r = 10000000-1;

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
	TestContainer e = {0};
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
	TestCoding();
	//printf("entry");
}
