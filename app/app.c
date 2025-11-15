#include "codec.h"
#include "stdio.h"

void apptest() {
	printf("app test");
}

void Help() {
	printf("------ 压缩或解压文件 ------\n");
	printf("-h				-- 显示此帮助信息\n");
	printf("-v				-- 显示版本号\n");
	printf("-zip filename			-- 压缩输入的文件，压缩文件放在同级目录下,最大支持530MB\n");
	printf("-unzip filename			-- 解压输入的文件，解压文件放在同级目录下\n");
}

int main(int argc, char** argv) {
	//argc 参数个数 argv 参数数组 第一个固定位程序路径
	//printf("app start\n");
	/*run help*/
	if ((argc < 2) || strcmp(argv[1], "-h") == 0) {
		Help();
		return;
	}
	/*version*/
	if (strcmp(argv[1], "-v") == 0) {
		//printf("%s", APP_VERSION);
		return 0;
	}

	/*compress*/
	if (strcmp(argv[1], "-zip") == 0) {
		if (argc < 3) {
			Help();
			return;
		}
		printf("run compress mode");
		Compress(argv[2]);
		return 0;
	}

	/*uncompress*/
	if (strcmp(argv[1], "-unzip") == 0) {
		if (argc < 3) {
			Help();
			return;
		}
		printf("run uncompress mode");
		UnCompress(argv[2]);
		return 0;
	}
	Help();
	return;
}