#include "cachelab.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <getopt.h>
#include <string.h>

#define ll long long

int h,v,E,b,r; // 这个是我们模拟的参数，为了方便在函数里调用，设置成全局
ll s, S;

int hit_count , 
    miss_count , 
    eviction_count;  // 三个在 printSummary 函数中的参数，需要不断更新
	
char t[1000]; // 存 getopt 中选项内容，表示的是验证中需使用的trace文件名

typedef struct{
    int valid_bits;
    ll tag;
    int stamp;
}cache_line, *cache_asso, **cache;  // cache 模拟器的结构。由合法位、标记位和时间戳组成

cache _cache_ = NULL;  // 声明一个空的结构体类型二维数组

// 打印 helper 内容的函数，-h 命令使用，内容可自定义
// void printUsage()
// {
//     printf("Usage: ./csim-ref [-hv] -s <num> -E <num> -b <num> -t <file>\n"
//             "Options:\n"
//             "  -h         Print this help message.\n"
//             "  -v         Optional verbose flag.\n"
//             "  -s <num>   Number of set index bits.\n"
//             "  -E <num>   Number of lines per set.\n"
//             "  -b <num>   Number of block offset bits.\n"
//             "  -t <file>  Trace file.\n\n"
//             "Examples:\n"
//             "  linux>  ./csim-ref -s 4 -E 1 -b 4 -t traces/yi.trace\n"
//             "  linux>  ./csim-ref -v -s 8 -E 2 -b 4 -t traces/yi.trace\n");
// }

// 初始化cache的函数
void init_cache()
{
	//多维数组的开辟要一行行malloc
        _cache_ = (cache)malloc(sizeof(cache_asso) * S); 
	for(int i = 0; i < S; ++i)
	{
		_cache_[i] = (cache_asso)malloc(sizeof(cache_line) * E);
		for(int j = 0; j < E; ++j)
		{
			_cache_[i][j].valid_bits = 0;
			_cache_[i][j].tag = -1;
			_cache_[i][j].stamp = 0;
		}
	}
}

void update_stamp(int op, int k, int setindex_add)
{
    if(op == 1) {
		    for(int j = 0; j < E; ++j)
				++_cache_[setindex_add][j].stamp;
    } else {
        for(int i = 0; i < E; i ++) {
            if (_cache_[setindex_add][i].stamp < _cache_[setindex_add][k].stamp) {
                _cache_[setindex_add][i].stamp ++;
            }
        }
    }
	return;
}

void update_fifo(ll setindex_add) {
    for(int j = 0; j < E; ++j)
		++_cache_[setindex_add][j].stamp;
}

void fifo(ll address) {
    ll setindex_add = (address >> b) & ((1 << s) - 1);
	ll tag_add = (address >> b) >> s;

    int max_stamp = INT_MIN;
	int max_stamp_index = -1;

    for(int i = 0; i < E; ++i) //如果tag相同，就hit，重置时间戳
	{
		if(_cache_[setindex_add][i].tag == tag_add && _cache_[setindex_add][i].valid_bits == 1)
		{
            update_fifo(setindex_add);	//更新时间戳
            _cache_[setindex_add][i].stamp = 0;
			++hit_count;
            printf(" hit");
			return ;
		}
	}
    ++ miss_count;
    printf(" miss");
	for(int i = 0; i < E; ++i)
	{
		if(_cache_[setindex_add][i].stamp > max_stamp)
		{
            max_stamp = _cache_[setindex_add][i].stamp;
			max_stamp_index = i;
		}    
	}
    if (_cache_[setindex_add][max_stamp_index].valid_bits == 0) {
        _cache_[setindex_add][max_stamp_index].valid_bits = 1;
    }
    else {
        ++ eviction_count;
        printf(" eviction");
    }
    update_fifo(setindex_add);	//更新时间戳
	_cache_[setindex_add][max_stamp_index].tag = tag_add;
	_cache_[setindex_add][max_stamp_index].stamp = 0;
	return ;
}

void update(ll address) {
	// 索引地址位可以用位运算，-1U是最大整数，64是因为我电脑是64位
    ll setindex_add = (address >> b) & ((1 << s) - 1);
	ll tag_add = (address >> b) >> s;
	
	int max_stamp = INT_MIN;
	int max_stamp_index = -1;

	for(int i = 0; i < E; ++i) //如果tag相同，就hit，重置时间戳
	{
		if(_cache_[setindex_add][i].tag == tag_add && _cache_[setindex_add][i].valid_bits == 1)
		{
            update_stamp(0, i, setindex_add);	//更新时间戳
            _cache_[setindex_add][i].stamp = 0;
			++hit_count;
            printf(" hit");
			return ;
		}
	}
	
	// for(int i = 0; i < E; ++i) // 查看有没有空行
	// {
	// 	if(_cache_[setindex_add][i].valid_bits == 0)
	// 	{
    //         update_stamp(1, i, setindex_add);	//更新时间戳
	// 		_cache_[setindex_add][i].valid_bits = 1;
	// 		_cache_[setindex_add][i].tag = tag_add;
	// 		_cache_[setindex_add][i].stamp = 0;
	// 		++miss_count;
    //         printf(" miss");
	// 		return ;
	// 	}
	// }
	// // 没有空行又没有hit就是要替换了
	// ++eviction_count;
	// ++miss_count;
    // printf(" miss eviction");
	
    ++ miss_count;
    printf(" miss");
	for(int i = 0; i < E; ++i)
	{
		if(_cache_[setindex_add][i].stamp > max_stamp)
		{
            max_stamp = _cache_[setindex_add][i].stamp;
			max_stamp_index = i;
		}    
	}
    if (_cache_[setindex_add][max_stamp_index].valid_bits == 0) {
        _cache_[setindex_add][max_stamp_index].valid_bits = 1;
    }
    else {
        ++ eviction_count;
        printf(" eviction");
    }
    update_stamp(1, max_stamp_index, setindex_add);	//更新时间戳
	_cache_[setindex_add][max_stamp_index].tag = tag_add;
	_cache_[setindex_add][max_stamp_index].stamp = 0;
	return ;
}

void printop(char opration, ll adresse, int size) {
    printf("%c %llx,%d", opration, adresse, size);
    return;
}

void parse_trace(int r)
{
	FILE* fp = fopen(t, "r"); // 读取文件名
	if(fp == NULL)
	{
		printf("open error");
		exit(-1);
	}
	
	char operation;         // 命令开头的 I L M S
	ll address;   // 地址参数
	int size;               // 大小
	while(fscanf(fp, " %c %llx,%d\n", &operation, &address, &size) > 0)
	{
		
		switch(operation)
		{
			case 'I': {
                if (v == 1) {
                    printop(operation, address, size);
                    printf("\n");
                }
                break;
            }	   // 不用写关于 I 的判断也可以
			case 'L':
                {
                    if (v == 1) {
                        printop(operation, address, size);
                    }
                    if(r == 0) {
                        update(address);
                    }
                    else {
                        fifo(address);
                    }
                    printf("\n");
                    break;
                }
			case 'M':
                {
                    if (v == 1) {
                        printop(operation, address, size);
                    }
	    			if(r == 0) {
                        update(address);  // miss的话还要进行一次storage
                        update(address);
                    }
                    else {
                        fifo(address);
                        fifo(address);
                    }
                    printf("\n");
                    break;
                }
			case 'S':
                {
                    if (v == 1)
                    {
                        printop(operation, address, size);
                    }
                    if(r == 0) {
                        update(address);
                    }
                    else {
                        fifo(address);
                    }
                    printf("\n");
                    break;
                }
				
		}
		
	}
	
	fclose(fp);
	for(int i = 0; i < S; ++i)
		free(_cache_[i]);
	free(_cache_);            // malloc 完要记得 free 并且关文件
	
}

//===============================================================

int main(int argc, char* argv[])
{
	h = 0; 
	v = 0; 
    r = 0;
	hit_count = miss_count = eviction_count = 0;
	int opt; // 接收getopt的返回值
        
        // getopt 第三个参数中，不可省略的选项字符后要跟冒号，这里h和v可省略
	while(-1 != (opt = (getopt(argc, argv, "hvs:E:b:t:r:"))))
	{
		switch(opt)
		{
			case 'h':
				h = 1;
				// printUsage();
				break;
			case 'v':
				v = 1;
				// printUsage();
				break;
			case 's':
				s = atoi(optarg);
				break;
			case 'E':
				E = atoi(optarg);
				break;
			case 'b':
				b = atoi(optarg);
				break;
			case 't':
				strcpy(t, optarg);
				break;
            case 'r':
                r = atoi(optarg);
			default:
				break;
		}
	}
	
	if(s<=0 || E<=0 || b<=0 || t==NULL) // 如果选项参数不合格就退出
	        return -1;
	S = 1 << s;                // S=2^s
	
	FILE* fp = fopen(t, "r");
	if(fp == NULL)
	{
		printf("open error");
		exit(-1);
	}
	
	init_cache();  // 初始化cache
	parse_trace(r); // 更新最终的三个参数

    printSummary(hit_count, miss_count, eviction_count);
    
    return 0;
}