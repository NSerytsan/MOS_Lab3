#include <stdlib.h>
#include <string.h>

#include "common.h"
int main(int argc, char **argv)
{
    bench_args args;
    get_bench_args(&args, argc, argv);

    array_t array = init_array(args.array_sz, 1);
    if (array == NULL)
        sys_error("Error allocating array");

    bench_results results;

    volatile size_t sum = 0;
    results.start = now_us();

    for (size_t i = 0; i < args.array_sz; ++i)
    {
        sum += array[i];
    }

    results.end = now_us();
    results.sum = sum;
    evaluate_benchmark(&results, &args, NULL);

    free(array);

    return 0;
}