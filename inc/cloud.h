#ifndef CLOUD_H
#define CLOUD_H

#include "cache.h"

// L2 CLOUD
// #define L2_PF_DEBUG_PRINT
#ifdef L2_PF_DEBUG_PRINT
#define L2_PF_DEBUG(x) x
#else
#define L2_PF_DEBUG(x)
#endif

#define MAX_PREFETCH_DIST 3
#define DELTA_SIZE 8
#define BLOCKS_PER_PAGE 64
#define NUM_DHB_REGIONS 64
#define NUM_PT_ENTRIES 64
#define NUM_PF_ENTRIES 512
#define NUM_BLOOM_ENTRIES 4096
#define PREF_ERROR 0xFFFF
#define IP_REGION_SIZE 0

class DELTA_HISTORY_BUFFER {
	public:
		uint64_t valid,
			ip_region,
			last_addr,
			num_access,
			last_pref_dpt_level,
			page_num,
			count,
			lru;
		int64_t last_4_deltas[20],
				ips[20],
				pages[20],
				offsets[20];

	DELTA_HISTORY_BUFFER() {
		valid = 0;
		ip_region = 0;
		last_addr = 0;
		num_access = 0;
		last_pref_dpt_level = 1;
		page_num = 0;
		count = 0;
		lru = 0;
		// first_hit = 0;
		for (int i=0; i<20; i++){
			last_4_deltas[i] = 0;
			pages[i] = 0;
			offsets[i] = 0;
			ips[i] = 0;}
	};
};

class DELTA_HISTORY_BUFFER_PAGE {
	public:
		uint64_t valid,
			ip_region,
			last_addr,
			num_access,
			last_pref_dpt_level,
			page_num,
			count,
			lru;
		int64_t last_4_deltas[20],
				ips[20],
				pages[20],
				offsets[20];

	DELTA_HISTORY_BUFFER_PAGE() {
		valid = 0;
		ip_region = 0;
		last_addr = 0;
		num_access = 0;
		last_pref_dpt_level = 1;
		page_num = 0;
		count = 0;
		lru = 0;
		// first_hit = 0;
		for (int i=0; i<20; i++){
			last_4_deltas[i] = 0;
			pages[i] = 0;
			offsets[i] = 0;
			ips[i] = 0;}
	};
};

class PATTERN_TABLE {
	public:
		int64_t deltas[3],
			pred_delta,
			accuracy,
			lru;
	PATTERN_TABLE(){
		for(int i=0; i<3; i++)
			deltas[i] = 0;
		pred_delta = 0;
		accuracy = 0;
		lru = 0;
	};
};

class BLOOM_FILTER {
	public:
		int b_filter[NUM_BLOOM_ENTRIES],
			a_filter[NUM_BLOOM_ENTRIES],
			pref_degree;
			uint64_t pollution_avg, 
					demand_avg, 
					pollution_tot, 
					demand_tot, 
					evictions,

					misses,
					prefetches_avg,
					used_avg,
					prefetches_tot,
					used_tot;
	BLOOM_FILTER(){
		for(int i=0; i<NUM_BLOOM_ENTRIES; i++){
			b_filter[i] = 0;
			a_filter[i] = 0;
		}
		pref_degree = 15;
		pollution_avg = 0;
		demand_avg = 0;
		pollution_tot = 0;
		demand_tot = 0;
		evictions = 0;

		misses = 0;
		prefetches_avg = 0;
		used_avg = 0;
		prefetches_tot = 0;
		used_tot = 0;
	};
};

class PREFETCH_FILTER {
	public:
		int64_t tag,
			valid;
	PREFETCH_FILTER(){
		tag = 0;
		valid = 0;
	};
};

typedef struct 
{
    int delta;
    int accuracy;
    int dpt;
} delta_and_acc;

extern DELTA_HISTORY_BUFFER L2_DHB[NUM_CPUS][NUM_DHB_REGIONS];
extern DELTA_HISTORY_BUFFER_PAGE L2_DHBP[NUM_CPUS][NUM_DHB_REGIONS];
extern PATTERN_TABLE L2_PT_1[NUM_CPUS][NUM_PT_ENTRIES];
extern PATTERN_TABLE L2_PT_2[NUM_CPUS][NUM_PT_ENTRIES];
extern PATTERN_TABLE L2_PT_3[NUM_CPUS][NUM_PT_ENTRIES];
extern BLOOM_FILTER L2_BF[NUM_CPUS];
// extern PREFETCH_FILTER L2_PF[NUM_CPUS][NUM_PF_ENTRIES];

int L2_DHB_update(uint32_t cpu,uint64_t addr, uint64_t ip);
void L2_DPT_update(uint32_t cpu,uint64_t addr, int entry);
delta_and_acc L2_DPT_check(uint32_t cpu, int *delta, int entry);

// DELTA_HISTORY_BUFFER L2_DHB[NUM_CPUS][NUM_DHB_REGIONS];
// PATTERN_TABLE L2_PT[NUM_CPUS][NUM_PT_ENTRIES];
// PREFETCH_FILTER L2_PF[NUM_CPUS][NUM_PF_ENTRIES];

#endif




