#pragma once
#ifndef __READBMP__
#define __READBMP__

#include "stdio.h"
#include "windows.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
struct BGRCOLOR
{
	uint8_t b;
	uint8_t g;
	uint8_t r;
};

void ReadBMPFile();
#endif 