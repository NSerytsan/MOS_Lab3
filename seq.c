#include <stdlib.h>
#include <string.h>

#include "common.h"
int main(int argc, char **argv)
{
    bench_args args;
    get_bench_args(&args, argc, argv);

    int *memory = malloc(args.memory_sz * sizeof(int));
    if (memory == NULL)
        sys_error("Error allocating memory");

    for (size_t i = 0; i < args.memory_sz; i++)
    {
        memory[i] = 1;
    }

    bench_results results;
    results.sum = 0;
    results.start = now_us();

    for (size_t i = 0; i < args.memory_sz; i++)
    {
        results.sum += memory[i];
    }

    results.end = now_us();
    evaluate_benchmark(&results, &args, NULL);

    free(memory);

    return 0;
}