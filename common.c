#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <stddef.h>

#include "common.h"

void get_bench_args(bench_args *args, int argc, char **argv)
{
    if (args == NULL)
        return;
    int opt = 0;

    args->cache_sz = DEFAULT_CACHE_SZ;
    args->array_sz = DEFAULT_ARRAY_SZ;
    args->threads_num = THREADS_NUM;
    while ((opt = getopt(argc, argv, "c:a:")) != -1)
    {
        switch (opt)
        {
        case 'c':
            args->cache_sz = atoi(optarg);
            break;
        case 'a':
            args->array_sz = atoi(optarg);
            break;
        default:
            continue;
        }
    }
}

void sys_error(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

double now_us()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double)(tv.tv_sec) * 1000000.0 + (double)(tv.tv_usec);
}

void evaluate_benchmark(bench_results *bench, bench_args *args, FILE *fp)
{
    if (fp == NULL)
    {
        fp = stdout;
    }
    const double latency = (bench->end - bench->start) / 1000;
    fprintf(fp, "Sum:           %ld\n", bench->sum);
    fprintf(fp, "Latency:       %.3f\tms\n", latency);
}

array_t init_array(size_t array_sz, array_element_t default_value)
{
    array_t array = malloc(array_sz * sizeof(array_element_t));
    if (array == NULL)
        return NULL;
    for (size_t i = 0; i < array_sz; i++)
    {
        array[i] = default_value;
    }

    return array;
}