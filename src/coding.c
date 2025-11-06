#include "../include/coding.h"

void GenerateCode(Node* nodes, Node* node, uint32_t bit, Code* codes, Code c, uint32_t indent) {
	indent++;
	//叶节点
	c.len = c.len + 1;
	//从树节点的上到下 位序从低到高
	c.code |= bit << (c.len - 1);

	printf("\n");
	for (size_t i = 0; i < indent; i++)
	{
		printf("  ");
	}
	if (node->type == 0) {
		printf("index:%d ,data: %d , count：%d ,type:%d  ", node->parentIndex, node->data, node->frequcey, node->type);
		for (size_t i = 0; i < indent; i++)
		{
			printf("  ");
		}
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
	printf("Pindex:%d ,Cindex:%d ,data: %x , count：%d ,type:%d", node->parentIndex,node->childIndex, node->data, node->frequcey, node->type);

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

void CollectData(const uint8_t* content, uint32_t width, uint32_t height, uint32_t len) {
	//const char* content = "AACDEEGFDEGHKBK";
	//const char* content = "Robust Programming The following conditions may cause an exception: The path is not valid for one of the following reasons: it is a zero-length string, it contains only white space, it contains invalid characters, or it is a device path (starts with \.\) (ArgumentException). The path is not valid because it is Nothing (ArgumentNullException). destinationFileName is Nothing or an empty string (ArgumentNullException). The source file is not valid or does not exist (FileNotFoundException). The combined path points to an existing directory, the destination file exists and overwrite is set to False, a file in the target directory with the same name is in use, or the user does not have sufficient permissions to access the file (IOException). A file or directory name in the path contains a colon (:) or is in an invalid format (NotSupportedException). showUI is set to True, onUserCancel is set to ThrowException, and either the user has cancelled the operation or an unspecified I/O error occurs (OperationCanceledException). The path exceeds the system-defined maximum length (PathTooLongException). The user lacks necessary permissions to view the path (SecurityException). The user does not have required permission (UnauthorizedAccessException). See also MoveFile How to: Rename a File How to: Create a Copy of a File in a Different Directory How to: Parse File Paths Collaborate with us on GitHub The source for this content can be found on GitHub, where you can also create and review issues and pull requests. For more information, see our contributor guide. .NET feedback .NET is an open source project. Select a link to provide feedback: Open a documentation issue Provide product feedback Additional resources Documentation How to: Rename a File - Visual Basic Learn about how to rename a file with the Visual Basic Runtime Library or the .NET base class library. How to: Parse File Paths - Visual Basic Learn more about: How to: Parse File Paths in Visual Basic How to: Delete a File - Visual Basic Learn more about: How to: Delete a File in Visual Basic Show 2 more";
	//const char* content = "Robust Programming The following conditions may cause an exception: ";
	//const char* content = "在本章中，我们将开始探索位图（Bitmap，简称BMP）文件的内部结构。BMP格式作为一种常见的图像文件格式，它的简单性使其成为学习图像文件处理的良好起点。我们将从基础的文件结构开始，逐步深入到BMP文件头、图像数据存储以及文件头信息对图像处理的影响。首先，理解BMP文件格式的基本结构是至关重要的。BMP文件由文件头、信息头、调色板（对于24位图像可选）和实际的位图数据构成。通过拆解这些组成部分，我们可以清晰地看到图像数据是如何在文件中排列的。我们还将探索文件头中的关键字段，如 BITMAPFILEHEADER 和BITMAPINFOHEADER ，它们分别记录了文件的元数据和位图的宽度、高度、颜色深度等关键信息。这些信息对于图像的正确读取和显示至关重要，也是图像处理软件中不可或缺的部分";
	//uint32_t len = strlen(content);
	/*char 数组转uint8 数组*/
	//const uint8_t* datas = (const uint8_t*)content;
	const uint8_t* datas = content;
	/*不重复的数组元素*/
	uint8_t data[datasize] = { 0 };
	printf("\ncontent len:%d\n", len);
	for (size_t i = 0; i < len; i++)
	{
		if (i%8==0) {
			printf("\n");
		}
		printf("%x ",datas[i]);
	}

	/*内容下标*/
	uint32_t index;
	for (uint32_t i = 0; i < len; i++) {
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
	printf("\n-----------------------  构建链表 Start -----------------------\n");
	//构建链表
	printf("非空数据大小 %d   --- Len: %d\n", no_empty_size, len);
	

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

	printf("\n-----------------------  构建链表 End -----------------------\n");

	printf("\n-----------------------  合并节点 Start -----------------------\n");

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
		MultiPrintList(&list);
	}
	printf("\n-----------------------  合并节点 End -----------------------\n");

	printf("\n\n------- 打印node 节点 nodeNum:%d -------------\n", nodeNum);
	for (uint32_t i = 0; i < nodeNum; i++) {
		//printf("\nnode[%d] count: %d(child:%d)  ,type:%d,  data:%d \n", i, (nodes + i)->frequcey, (nodes + i)->childIndex, (nodes + i)->type, (nodes + i)->data);
	}
	//编码
	Coding(nodes, nodeNum, len, datas, width, height);
}

void Coding(Node* nodes, uint32_t nodeNum, uint32_t len, const uint8_t* datas, uint32_t width, uint32_t height) {

	Code codes[256] = { 0 };
	Node* tempNode = nodes + nodeNum - 1;
	printf("\n------------- 打印树结构 Start -------------\n");
	PrintTree(nodes, tempNode, 0, 1, 1);
	PrintTree(nodes, tempNode - 1, 0, 0, 1);
	printf("\n------------- 打印树结构 End -------------\n");
	//编码的左右头节点
	Code c0 = { .code = 0,.len = 0 };
	Code c1 = { .code = 1,.len = 0 };

	printf("\n");
	printf("\n ------------- 递归编码 Start -------------\n");
	GenerateCode(nodes, tempNode, 1, &codes, c1, 0);
	GenerateCode(nodes, tempNode - 1, 0, &codes, c0, 0);
	printf("\n ------------- 打印编码  End -------------\n");
	printf("\n");


	printf("\n--------------- 压入位数据 Start --------------\n\n");
	uint32_t contentBitsLen = 0;
	//统计原文数据位长度
	for (uint32_t i = 0; i < len; i++)
	{
		contentBitsLen += codes[datas[i]].len;
	}
	printf("nodeNum:%d -- contentBitsLen:%d\n", nodeNum, contentBitsLen);

	struct DataHeader header = { .nodesNum = nodeNum,.contentCodeLen = contentBitsLen,.width = width,.height = height };
	uint32_t header_nodesNum_bytes = sizeof(header.nodesNum);
	uint32_t header_contentCodeLen_bytes = sizeof(header.contentCodeLen);
	uint32_t header_width_bytes = sizeof(header.width);
	uint32_t header_height_bytes = sizeof(header.height);
	printf("header_nodesNum_bytes:%d -- header_contentCodeLen_bytes:%d,header_width_bytes:%d,header_height_bytes:%d\n", header_nodesNum_bytes, header_contentCodeLen_bytes, header_width_bytes, header_height_bytes);
	
	uint32_t totalBits = nodeNum * 9 + contentBitsLen + header_nodesNum_bytes * 8 + header_contentCodeLen_bytes * 8 + header_width_bytes * 8 + header_height_bytes * 8;

	//用9个位装每个node节点的数据，1位装节点类型，8位装数据，类型 0 叶节点 data则为数据，类型 1 合并节点 data为子节点索引
	//文件字节数
	uint32_t fileBytes = (uint32_t)ceilf((float)totalBits / 8.0f);
	printf("totalBits :%d ,fileBytes :%d \n", totalBits, fileBytes);
	struct bitArray arr = { .data = (uint8_t*)malloc(fileBytes),.max = fileBytes,.len = 0,.bitlen = 0 };
	struct bitArray* bitArr = &arr;
	uint32_t bitsBuf = 0;
	Node* node = NULL;

	//将头信息压入位数组
	BitArrayPush(bitArr, header.nodesNum, header_nodesNum_bytes * 8);
	BitArrayPush(bitArr, header.contentCodeLen, header_contentCodeLen_bytes * 8);
	BitArrayPush(bitArr, header.width, header_width_bytes * 8);
	BitArrayPush(bitArr, header.height, header_height_bytes * 8);

	printf("\nheaderPush over\n");


	//将树信息压入位数组
	for (uint32_t i = 0; i < nodeNum; i++)
	{
		node = nodes + i;
		bitsBuf = 0;
		if (node->type == 0) {
			//叶节点 位数据即data值
			bitsBuf |= (uint32_t)node->data;
		}
		else {
			//合并节点的数据是子节点索引
			bitsBuf |= (uint32_t)node->childIndex;
		}
		//9位存储节点数据 type在高1位，data在低8位
		bitsBuf |= (((uint32_t)node->type) << 8);
		BitArrayPush(bitArr, bitsBuf, 9);
		printf("\nnode[%d],type:%d,data:%d,char:%x [", i, node->type, node->data, node->data);
		printBits(bitsBuf, 9);
		printf("]");
	}
	

	printf("\n\n--------------- 压入content位数据 End --------------\n\n");

	bitsBuf = 0;
	//原文数据压入位数组 不定长度的位信息
	for (uint32_t i = 0; i < len; i++)
	{
		bitsBuf = codes[datas[i]].code;
		BitArrayPush(bitArr, bitsBuf, codes[datas[i]].len);
		//printf("\nlen[%d]:bitsBuf/code:%d", i, bitsBuf);
		printf("\nlen[%d]:bitsBuf/code:%d[", i, bitsBuf);
		printBits(bitsBuf, codes[datas[i]].len);
		printf("]");

	}
	printf("\n\n--------------- 压入位数据 End --------------\n\n");


	//从内存中读取数据并写出到文件
	ReadAndSaveDataFromContext(bitArr);
}

/// <summary>
/// 按位解码数据
/// </summary>
/// <param name="inNodes"></param>
/// <param name="nodesNum"></param>
/// <param name="bitArr"></param>
/// <param name="inOffset"></param>
/// <param name="inContentBitLens"></param>
void DecodeContentData_Context(Node* inNodes, uint16_t nodesNum, struct bitArray* bitArr, uint32_t inOffset, uint32_t inContentBitLens) {
	uint8_t readbit = 0;
	Node* nodes = inNodes;
	uint32_t offset = inOffset;
	uint32_t contentBitLens = inContentBitLens;
	Node* n0 = &inNodes[nodesNum - 2];//靠左 0
	Node* n1 = &inNodes[nodesNum - 1];//靠右 1
	Node* currentNode = NULL;

	//第一个位 0 靠左 ，1 靠右
	while (contentBitLens > 0) {
		readbit = (uint8_t)BitArrayPop(bitArr, 1, offset);
		offset += 1;
		contentBitLens--;
		if (readbit == 0) {
			currentNode = n0;
		}
		else
		{
			currentNode = n1;
		}

		while (currentNode != NULL && currentNode->type == 1 && contentBitLens > 0) {
			//非叶节点 读子数据
			readbit = (uint8_t)BitArrayPop(bitArr, 1, offset);
			offset += 1;
			contentBitLens--;
			if (readbit == 0) {
				//左分支
				if ((currentNode->data) - 1 > 0) {

					currentNode = &nodes[currentNode->data - 1];
				}
				else {
					break;
				}
			}
			else {
				//右分支
				if ((currentNode->data) > 0) {
					currentNode = &nodes[currentNode->data];
				}
				else
				{
					break;
				}
			}
		}

		if (currentNode != NULL && currentNode->type == 0) {
			printf("data : %d  --  char: %c\n", currentNode->data, currentNode->data);
		}
	}

}

void ReadAndSaveDataFromContext(struct bitArray* bitArr) {
	//内容中读取数据
	printf("\n\n-------------------------------- 内存中读取数据  Start -------------------------------------");
	struct DataHeader header_read = { .nodesNum = 0,.contentCodeLen = 0,.width = 0,.height = 0 };
	uint32_t offset = 0;
	uint32_t buf = 0;
	uint8_t type = 0;
	uint8_t outdata = 0;

	printf("\nsizeof(header_read.nodesNum): %d \n", sizeof(header_read.nodesNum));
	//读取头数据
	header_read.nodesNum = (uint16_t)BitArrayPop(bitArr, sizeof(header_read.nodesNum) * 8, offset);
	offset += sizeof(header_read.nodesNum) * 8;
	printf("\nheader_read.nodesNum：%d\n", header_read.nodesNum);
	

	header_read.contentCodeLen = BitArrayPop(bitArr, sizeof(header_read.contentCodeLen) * 8, offset);
	offset += sizeof(header_read.contentCodeLen) * 8;
	printf("\nheader_read.contentCodeLen：%d\n", header_read.contentCodeLen);

	header_read.width = BitArrayPop(bitArr, sizeof(header_read.width) * 8, offset);
	offset += sizeof(header_read.width) * 8;
	printf("\nheader_read.width：%d\n", header_read.width);

	header_read.height = BitArrayPop(bitArr, sizeof(header_read.height) * 8, offset);
	offset += sizeof(header_read.height) * 8;
	printf("\nheader_read.width：%d\n", header_read.height);


	uint32_t totalBits = header_read.nodesNum * 9 + header_read.contentCodeLen + sizeof(header_read.nodesNum) * 8 + sizeof(header_read.contentCodeLen) * 8 + sizeof(header_read.width) * 8 + sizeof(header_read.height) * 8;
	printf("\ntotalBits：%d\n", totalBits);
	uint32_t fileBytes = (uint32_t)ceilf((float)totalBits / 8.0f);
	printf("\nfileBytes：%d\n", fileBytes);
	
	printf("current offset：%d\n",offset);
	
	Node* readNodes = (Node*)malloc(header_read.nodesNum * sizeof(Node));
	for (uint32_t i = 0; i < header_read.nodesNum; i++)
	{
		//按9位取数据
		buf = BitArrayPop(bitArr, 9, offset);
		outdata = (uint8_t)(buf & 0b11111111);
		type = (uint8_t)((buf >> 8) & 0b00000001);
		offset += 9;

		readNodes[i].type = type;
		(readNodes + i)->data = outdata;
	}
	printf("\noffset：%d\n", offset);
	printf("\nheader_read.contentCodeLen：%d\n", header_read.contentCodeLen);
	printf("\nheader_read.nodesNum：%d\n", header_read.nodesNum);
	printf("\nheader_read.width：%d\n", header_read.width);
	printf("\nheader_read.height：%d\n", header_read.height);

	//DecodeContentData_Context(readNodes, header_read.nodesNum, bitArr, offset, header_read.contentCodeLen);
	//写入数据到指定文件
	const char* filename = "C:\\Users\\Xinyu\\Desktop\\test2.express";
	printf("\n写出文件到 %s:\n", filename);
	FILE* writeStream = fopen(filename, "wb");
	fwrite(bitArr->data, sizeof(uint8_t), fileBytes, writeStream);
	fclose(writeStream);
	printf("\n\n-------------------------------- 文件中写出数据  End -----------------------------------");

	printf("\n\n-------------------------------- 内存中读取数据  End -----------------------------------");

}

uint32_t pixelCount = 0;
void ReadContentData_Infile(Node* inNodes, uint16_t nodesNum, uint8_t* data, uint32_t inOffset, uint32_t inContentBitLens, uint8_t* pixels) {
	uint8_t readbit = 0;
	Node* nodes = inNodes;
	uint32_t offset = inOffset;
	uint32_t contentBitLens = inContentBitLens;
	Node* n0 = &inNodes[nodesNum - 2];//靠左 0
	Node* n1 = &inNodes[nodesNum - 1];//靠右 1
	Node* currentNode = NULL;

	printf("offset:%d\n",offset);
	//第一个位 0 靠左 ，1 靠右
	while (contentBitLens > 0) {
		readbit = (uint8_t)BitPop(data, 1, offset);
		offset += 1;
		contentBitLens--;
		if (readbit == 0) {
			currentNode = n0;
		}
		else
		{
			currentNode = n1;
		}

		while (currentNode != NULL && currentNode->type == 1 && contentBitLens > 0) {
			//非叶节点 读子数据
			readbit = (uint8_t)BitPop(data, 1, offset);
			offset += 1;
			contentBitLens--;
			if (readbit == 0) {
				//左分支
				if ((currentNode->data) - 1 > 0) {

					currentNode = &nodes[currentNode->data - 1];
				}
				else {
					break;
				}
			}
			else {
				//右分支
				if ((currentNode->data) > 0) {
					currentNode = &nodes[currentNode->data];
				}
				else
				{
					break;
				}
			}
		}

		if (currentNode != NULL && currentNode->type == 0) {
			//printf("data : %d  --  char: %c\n", currentNode->data, currentNode->data);
			//printf("%c", currentNode->data);

			pixels[pixelCount] = currentNode->data;
			//printf("pixelCount:%d\n", pixelCount);
			pixelCount++;
		}
	}
}

void DecodeFromFile() {

	printf("\n\n-------------------------------- 文件中读取数据  Start -----------------------------------");
	const char* filename = "C:\\Users\\Xinyu\\Desktop\\test2.express";
	struct DataHeader header_read_file = { .nodesNum = 0,.contentCodeLen = 0,.width = 0,.height = 0 };
	//读取文件
	FILE* readStream_file = fopen(filename, "rb");
	if (readStream_file == NULL) {
		printf("\nreadStream is NULL\n");
	}


	//读取文件头文件
	fread(&header_read_file.nodesNum, sizeof(header_read_file.nodesNum), 1, readStream_file);
	fread(&header_read_file.contentCodeLen, sizeof(header_read_file.contentCodeLen), 1, readStream_file);
	fread(&header_read_file.width, sizeof(header_read_file.width), 1, readStream_file);
	fread(&header_read_file.height, sizeof(header_read_file.height), 1, readStream_file);



	//节点数组数据指针
	Node* readNodes_read_file = (Node*)malloc(header_read_file.nodesNum * sizeof(Node));
	//总字节数
	uint32_t totalBits_file = header_read_file.nodesNum * 9 + header_read_file.contentCodeLen + sizeof(header_read_file.nodesNum) * 8 + sizeof(header_read_file.contentCodeLen) * 8 + sizeof(header_read_file.width) * 8 + sizeof(header_read_file.height) * 8;
	uint32_t read_fileBytes = (uint32_t)ceilf((float)totalBits_file / 8.0f);


	printf("\nheader_read_file.nodesNum:%d\n", header_read_file.nodesNum);
	printf("\nheader_read_file.contentCodeLen:%d\n", header_read_file.contentCodeLen);
	printf("\nheader_read_file.width:%d\n", header_read_file.width);
	printf("\nheader_read_file.height:%d\n", header_read_file.height);
	printf("\nhearead_fileBytes:%d\n", read_fileBytes);
	
	uint32_t contentBytes = read_fileBytes - sizeof(header_read_file.nodesNum) - sizeof(header_read_file.contentCodeLen) - sizeof(header_read_file.width) - sizeof(header_read_file.height);
	printf("\contentBytes:%d\n", contentBytes);

	//总数据指针
	uint8_t* read_file_data = (uint8_t*)malloc(read_fileBytes - sizeof(header_read_file.nodesNum) - sizeof(header_read_file.contentCodeLen) - sizeof(header_read_file.width) - sizeof(header_read_file.height));
	uint32_t contentCount = fread(read_file_data, sizeof(uint8_t), contentBytes, readStream_file);
	uint32_t buf = 0;
	uint32_t offset = 0;
	uint8_t type = 0;
	uint8_t outdata = 0;

	for (uint32_t i = 0; i < header_read_file.nodesNum; i++)
	{

		//按9位取数据
		buf = BitPop(read_file_data, 9, offset);
		outdata = (uint8_t)(buf & 0b11111111);
		type = (uint8_t)((buf >> 8) & 0b00000001);
		offset += 9;

		readNodes_read_file[i].type = type;
		(readNodes_read_file + i)->data = outdata;
	}

	uint8_t* bgrcolors = (uint8_t*)malloc(header_read_file.width * header_read_file.height * 3);
	ReadContentData_Infile(readNodes_read_file, header_read_file.nodesNum, read_file_data, offset, header_read_file.contentCodeLen, bgrcolors);

	for (size_t i = 0; i < header_read_file.width * header_read_file.height * 3; i++)
	{
		if (i % 8 == 0) {
			printf("\n");
		}
		printf("%x ", bgrcolors[i]);
	}

	//读取像素值
	/*for (size_t i = 0; i < header_read_file.height; i++)
	{
		printf("\n");
		for (int j = 0; j < header_read_file.width; j++) {
			int pixel_index = (i * header_read_file.width + j) * 3;

			printf("[r:%d,", bgrcolors[pixel_index + 2]);
			printf("g:%d,", bgrcolors[pixel_index + 1]);
			printf("b:%d,", bgrcolors[pixel_index + 0]);
			printf("]");
		}
	}*/
	//const char* content = (const char*)read_file_data;
	//printf("content:%s",content);
}

void TestCoding() {
	/*CollectData();*/
	DecodeFromFile();
}