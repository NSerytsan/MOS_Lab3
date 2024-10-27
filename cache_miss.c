#include <stdlib.h>
#include <string.h>

#include "common.h"
int main(int argc, char **argv)
{
    bench_args args;
    get_bench_args(&args, argc, argv);

    auto array = init_array(args.array_sz * args.cache_line_sz, 1);
    if (array == NULL)
        sys_error("Error allocating array");

    bench_results results;
    results.sum = 0;
    results.start = now_us();

    size_t step = args.cache_line_sz / sizeof(array_element_t);
    size_t array_sz = args.array_sz * step;
    for (size_t i = 0; i < array_sz; i += step)
    {
        results.sum += array[i];
    }

    results.end = now_us();
    evaluate_benchmark(&results, &args, NULL);

    free(array);

    return 0;
}