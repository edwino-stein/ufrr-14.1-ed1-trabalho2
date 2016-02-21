#if !defined _benchmark
#define _benchmark

struct benchmark{
	int time;
	int timeUnity;
	unsigned long long compareds;
	unsigned long long moves;
};

struct benchmarkResult{
	int sortType;
	struct benchmark *perFiles;
};

#endif