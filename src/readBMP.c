#define _CRT_SECURE_NO_WARNINGS
#include "../include/readBMP.h"
#include "../include/coding.h"

void ReadBMPFile() {
	//read .wav .bmp
	//const char* filename_read = "C:\\Users\\Xinyu\\Desktop\\Temp\\color.bmp";
	const char* filename_read = "../assets/color.bmp";

	if (filename_read == NULL)
	{
		printf("file is NULL");
		return;
	}
	struct tagBITMAPFILEHEADER head;
	struct tagBITMAPINFOHEADER info;
	//struct tagRGBQUAD  color;


	//读取文件
	FILE* rbmp = fopen(filename_read, "rb");


	//读指针后移
	//fgetc(rbmp);

	//读取文件头
	fread(&head.bfType, 1, 2, rbmp);
	fread(&head.bfSize, 1, 4, rbmp);
	fread(&head.bfReserved1, 1, 2, rbmp);
	fread(&head.bfReserved2, 1, 2, rbmp);
	fread(&head.bfOffBits, 1, 4, rbmp);

	//读取文件信息
	fread(&info.biSize, 1, 4, rbmp);
	fread(&info.biWidth, 1, 4, rbmp);
	fread(&info.biHeight, 1, 4, rbmp);
	fread(&info.biPlanes, 1, 2, rbmp);
	fread(&info.biBitCount, 1, 2, rbmp);
	fread(&info.biCompression, 1, 4, rbmp);
	fread(&info.biSizeImage, 1, 4, rbmp);
	fread(&info.biXPelsPerMeter, 1, 4, rbmp);
	fread(&info.biYPelsPerMeter, 1, 4, rbmp);
	fread(&info.biClrUsed, 1, 4, rbmp);
	fread(&info.biClrImportant, 1, 4, rbmp);

	printf("\ninfo.biBitCount : %d\n ", info.biBitCount);
	printf("\ninfo.biWidth : %d \n", info.biWidth);
	printf("\ninfo.biHeight : %d \n", info.biHeight);
	//根据位数据生成对应count
	unsigned char count = 0;
	switch (info.biBitCount)
	{
	case 24:count = info.biBitCount / 8;
		break;
	case 32:count = info.biBitCount / 8;
		break;
	default:
		break;
	}

	//需要考虑行列对齐
	//struct BGRCOLOR bgrcolor[3072] = { 0 };

	struct BGRCOLOR* bgrcolor = (struct BGRCOLOR*)malloc(sizeof(struct BGRCOLOR) * (info.biWidth * info.biHeight));
	printf("sizeof(struct BGRCOLOR:%d\n", sizeof(struct BGRCOLOR));
	for (int i = 0; i < info.biWidth * info.biHeight; i++)
	{
		fread(&bgrcolor[i], sizeof(struct BGRCOLOR), 1, rbmp);
		/*fread(&bgrcolor[i].b, 1, 1, rbmp);
		fread(&bgrcolor[i].g, 1, 1, rbmp);
		fread(&bgrcolor[i].r, 1, 1, rbmp);*/
	}
	for (size_t i = 0; i < info.biHeight; i++)
	{
		printf("\n");
		for (int j = 0; j < info.biWidth; j++) {

			printf("num:[%d][r:%d,g:%d,b:%d],", (j + i * info.biWidth), bgrcolor[j + i * info.biWidth].r, bgrcolor[j + i * info.biWidth].g, bgrcolor[j + i * info.biWidth].b);
		}
	}
	const char* content = "Robust Programming The following conditions may cause an exception: The path is not valid for one of the following reasons: it is a zero-length string, it contains only white space, it contains invalid characters, or it is a device path (starts with \.\) (ArgumentException). The path is not valid because it is Nothing (ArgumentNullException). destinationFileName is Nothing or an empty string (ArgumentNullException). The source file is not valid or does not exist (FileNotFoundException). The combined path points to an existing directory, the destination file exists and overwrite is set to False, a file in the target directory with the same name is in use, or the user does not have sufficient permissions to access the file (IOException). A file or directory name in the path contains a colon (:) or is in an invalid format (NotSupportedException). showUI is set to True, onUserCancel is set to ThrowException, and either the user has cancelled the operation or an unspecified I/O error occurs (OperationCanceledException). The path exceeds the system-defined maximum length (PathTooLongException). The user lacks necessary permissions to view the path (SecurityException). The user does not have required permission (UnauthorizedAccessException). See also MoveFile How to: Rename a File How to: Create a Copy of a File in a Different Directory How to: Parse File Paths Collaborate with us on GitHub The source for this content can be found on GitHub, where you can also create and review issues and pull requests. For more information, see our contributor guide. .NET feedback .NET is an open source project. Select a link to provide feedback: Open a documentation issue Provide product feedback Additional resources Documentation How to: Rename a File - Visual Basic Learn about how to rename a file with the Visual Basic Runtime Library or the .NET base class library. How to: Parse File Paths - Visual Basic Learn more about: How to: Parse File Paths in Visual Basic How to: Delete a File - Visual Basic Learn more about: How to: Delete a File in Visual Basic Show 2 more";

	//const char* content = (const char*)bgrcolor;
	//CollectData(content,info.biWidth,info.biHeight);
}


