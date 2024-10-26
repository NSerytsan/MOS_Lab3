#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>

#define DEFAULT_CACHE_SZ 4096
#define DEFAULT_ARRAY_SZ 1024
#define THREADS_NUM 2

typedef struct bench_results
{
    double start;
    double end;

} bench_results;

typedef struct bench_args
{
    size_t cache_sz;
    size_t array_sz;
    size_t threads_num;

} bench_args;

void get_bench_args(bench_args *args, int argc, char **argv);

void sys_error(const char *msg);

double now_us();
void evaluate_benchmark(bench_results *bench, bench_args *args, FILE *fp);


#endif