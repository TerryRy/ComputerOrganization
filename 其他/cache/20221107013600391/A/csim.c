#include "cachelab.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <getopt.h>
#include <string.h>

int h,v,s,E,b,S; // ���������ģ��Ĳ�����Ϊ�˷����ں�������ã����ó�ȫ��

int hit_count , 
    miss_count , 
    eviction_count;  // ������ printSummary �����еĲ�������Ҫ���ϸ���
	
char t[1000]; // �� getopt ��ѡ�����ݣ���ʾ������֤����ʹ�õ�trace�ļ���

typedef struct{
    int valid_bits;
    int tag;
    int stamp;
}cache_line, *cache_asso, **cache;  // cache ģ�����Ľṹ���ɺϷ�λ�����λ��ʱ������

cache _cache_ = NULL;  // ����һ���յĽṹ�����Ͷ�ά����

// ��ӡ helper ���ݵĺ�����-h ����ʹ�ã����ݿ��Զ���
void printUsage()
{
    printf("Usage: ./csim-ref [-hv] -s <num> -E <num> -b <num> -t <file>\n"
            "Options:\n"
            "  -h         Print this help message.\n"
            "  -v         Optional verbose flag.\n"
            "  -s <num>   Number of set index bits.\n"
            "  -E <num>   Number of lines per set.\n"
            "  -b <num>   Number of block offset bits.\n"
            "  -t <file>  Trace file.\n\n"
            "Examples:\n"
            "  linux>  ./csim-ref -s 4 -E 1 -b 4 -t traces/yi.trace\n"
            "  linux>  ./csim-ref -v -s 8 -E 2 -b 4 -t traces/yi.trace\n");
}

// ��ʼ��cache�ĺ���
void init_cache()
{
	//��ά����Ŀ���Ҫһ����malloc
        _cache_ = (cache)malloc(sizeof(cache_asso) * S); 
	int i = 0;
	int j = 0;
	for(i = 0; i < S; i++)
	{
		_cache_[i] = (cache_asso)malloc(sizeof(cache_line) * E);
		for(j = 0; j < E; ++j)
		{
			_cache_[i][j].valid_bits = 0;
			_cache_[i][j].tag = -1;
			_cache_[i][j].stamp = -1;
		}
	}
}



void update(unsigned int address)
{
	// ������ַλ������λ���㣬-1U�����������64����Ϊ�ҵ�����64λ
        int setindex_add = (address >> b) & ((-1U) >> (64 - s));
	int tag_add = address >> (b + s);
	
	int max_stamp = INT_MIN;
	int max_stamp_index = -1;

	for(int i = 0; i < E; ++i) //���tag��ͬ����hit������ʱ���
	{
		if(_cache_[setindex_add][i].tag == tag_add)
		{
			_cache_[setindex_add][i].stamp = 0;
			++hit_count;
			return ;
		}
	}
	
	for(int i = 0; i < E; ++i) // �鿴��û�п���
	{
		if(_cache_[setindex_add][i].valid_bits == 0)
		{
			_cache_[setindex_add][i].valid_bits = 1;
			_cache_[setindex_add][i].tag = tag_add;
			_cache_[setindex_add][i].stamp = 0;
			++miss_count;
			return ;
		}
	}
	// û�п�����û��hit����Ҫ�滻��
	++eviction_count;
	++miss_count;
	
	for(int i = 0; i < E; ++i)
	{
		if(_cache_[setindex_add][i].stamp > max_stamp)
		{
			max_stamp = _cache_[setindex_add][i].stamp;
			max_stamp_index = i;
		}
	}
	_cache_[setindex_add][max_stamp_index].tag = tag_add;
	_cache_[setindex_add][max_stamp_index].stamp = 0;
	return ;
}


void update_stamp()
{
	for(int i = 0; i < S; ++i)
		for(int j = 0; j < E; ++j)
			if(_cache_[i][j].valid_bits == 1)
				++_cache_[i][j].stamp;
}


void parse_trace()
{
	FILE* fp = fopen(t, "r"); // ��ȡ�ļ���
	if(fp == NULL)
	{
		printf("open error");
		exit(-1);
	}
	
	char operation;         // ���ͷ�� I L M S
	unsigned int address;   // ��ַ����
	int size;               // ��С
	while(fscanf(fp, " %c %xu,%d\n", &operation, &address, &size) > 0)
	{
		
		switch(operation)
		{
			//case 'I': continue;	   // ����д���� I ���ж�Ҳ����
			case 'L':
				update(address);
				break;
			case 'M':
				update(address);  // miss�Ļ���Ҫ����һ��storage
			case 'S':
				update(address);
		}
		update_stamp();	//����ʱ���
	}
	
	fclose(fp);
	for(int i = 0; i < S; ++i)
		free(_cache_[i]);
	free(_cache_);            // malloc ��Ҫ�ǵ� free ���ҹ��ļ�
	
}

//===============================================================

int main(int argc, char* argv[])
{
	h = 0; 
	v = 0; 
	hit_count = miss_count = eviction_count = 0;
	int opt; // ����getopt�ķ���ֵ
        
        // getopt �����������У�����ʡ�Ե�ѡ���ַ���Ҫ��ð�ţ�����h��v��ʡ��
	while(-1 != (opt = (getopt(argc, argv, "hvs:E:b:t:"))))
	{
		switch(opt)
		{
			case 'h':
				h = 1;
				printUsage();
				break;
			case 'v':
				v = 1;
				printUsage();
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
			default:
				printUsage();
				break;
		}
	}
	
	if(s<=0 || E<=0 || b<=0 || t==NULL) // ���ѡ��������ϸ���˳�
	        return -1;
	S = 1 << s;                // S=2^s
	
	FILE* fp = fopen(t, "r");
	if(fp == NULL)
	{
		printf("open error");
		exit(-1);
	}
	
	init_cache();  // ��ʼ��cache
	parse_trace(); // �������յ���������

    printSummary(hit_count, miss_count, eviction_count);
    
    return 0;
}
