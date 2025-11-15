#define _CRT_SECURE_NO_WARNINGS

#include "linklist.h"
#include <math.h>
#include <time.h> 
#include "bitoperate.h"
#include "containers.h"
#include "coding.h"
#include "map.h"
#include "readBMP.h"
#include "fileRead.h"

int main() {
	printf("test main");

	const char* file = "C:\\Users\\DRF\\Desktop\\Temp\\test.xx";
	//doCompress(file);
	doDeCompress(file);
	//FileReadTest();
}
