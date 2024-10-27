#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>

#define DEFAULT_CACHE_LINE_SZ 64
#define DEFAULT_ARRAY_SZ 1000
#define THREADS_NUM 2

#ifndef VOLATILE 
#define VOLATILE
#endif

typedef int array_element_t;
typedef array_element_t *array_t;

typedef struct bench_results
{
    double start;
    double end;
    size_t sum;
} bench_results;

typedef struct bench_args
{
    size_t cache_line_sz;
    size_t array_sz;
    size_t threads_num;
} bench_args;

typedef struct thread_args
{
    array_t array;
    size_t array_sz;
    bench_results results;
} thread_args;

void get_bench_args(bench_args *args, int argc, char **argv);

void sys_error(const char *msg);

double now_us();
void evaluate_benchmark(bench_results *bench, bench_args *args, FILE *fp);

VOLATILE array_t init_array(size_t array_sz, array_element_t default_value);

#endif