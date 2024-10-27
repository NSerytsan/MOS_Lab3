#include <stdlib.h>
#include <string.h>

#include "common.h"

size_t *generate_indexes(size_t array_sz)
{
    size_t *indexes = malloc(array_sz * sizeof(size_t));
    if (indexes == NULL)
        return NULL;

    memset(indexes, 0, array_sz * sizeof(size_t));
    for (size_t i = 0; i < array_sz; i++)
    {
        indexes[i] = rand() % array_sz;
    }

    return indexes;
}

int main(int argc, char **argv)
{
    bench_args args;
    get_bench_args(&args, argc, argv);

    auto array = init_array(args.array_sz, 1);
    if (array == NULL)
        sys_error("Error allocating array");

    size_t *random_indexes = generate_indexes(args.array_sz);
    if (random_indexes == NULL)
        sys_error("Error allocating indexes");

    bench_results results;
    results.sum = 0;
    results.start = now_us();

    for (size_t i = 0; i < args.array_sz; i++)
    {
        results.sum += array[random_indexes[i]];
    }

    results.end = now_us();
    evaluate_benchmark(&results, &args, NULL);

    free(array);

    return 0;
}