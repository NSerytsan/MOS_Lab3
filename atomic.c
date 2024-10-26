#include <stdlib.h>
#include <string.h>
#include <stdatomic.h>
#include <threads.h>

#include "common.h"

atomic_int sum = 0;

int f_sum(void *arg)
{
    thread_args *thr_args = (thread_args *)arg;
    for (size_t i = 0; i < thr_args->array_sz; i++)
    {
        atomic_fetch_add_explicit(&sum, thr_args->array[i], memory_order_relaxed);
    }

    return 0;
}

int main(int argc, char **argv)
{
    bench_args args;
    get_bench_args(&args, argc, argv);

    auto array = init_array(args.array_sz, 1);
    if (array == NULL)
        sys_error("Error allocating array");

    thread_args thr_args;
    thr_args.array = array;
    bench_results results;

    thr_args.array_sz = args.array_sz / args.threads_num;
    thrd_t *threads = malloc(args.threads_num * sizeof(thrd_t));
    results.start = now_us();
    for (size_t i = 0; i < args.threads_num; i++)
    {
        thrd_create(&threads[i], f_sum, (void *)&thr_args);
        if (thrd_join(threads[i], NULL) != thrd_success)
        {
            sys_error("Error joining thread");
        }
    }

    results.end = now_us();
    results.sum = sum;
    evaluate_benchmark(&results, &args, NULL);

    free(array);

    return 0;
}