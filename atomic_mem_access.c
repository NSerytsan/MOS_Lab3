#include <stdlib.h>
#include <string.h>
#include <stdatomic.h>
#include <threads.h>

#include "common.h"

atomic_int sum = 0;

int f_sum(void *arg)
{
    thread_args *thr_args = (thread_args *)arg;
    thr_args->results.start = now_us();

    for (size_t i = 0; i < thr_args->array_sz; i++)
    {
        atomic_fetch_add_explicit(&sum, thr_args->array[i], memory_order_relaxed);
    }

    thr_args->results.end = now_us();

    return 0;
}

int main(int argc, char **argv)
{
    bench_args args;
    get_bench_args(&args, argc, argv);

    auto array = init_array(args.array_sz, 1);
    if (array == NULL)
        sys_error("Error allocating array");

    thread_args *thr_args = malloc(args.threads_num * sizeof(thread_args));
    if (thr_args == NULL)
        sys_error("Error allocating memory");

    thrd_t *threads = malloc(args.threads_num * sizeof(thrd_t));
    if (threads == NULL)
        sys_error("Error allocating memory");

    for (size_t i = 0; i < args.threads_num; i++)
    {
        thr_args[i].array_sz = args.array_sz / args.threads_num;
        thr_args[i].array = array;
        if (thrd_create(&threads[i], f_sum, (void *)&thr_args[i]) != thrd_success)
        {
            sys_error("Error creating thread");
        }
    }

    for (size_t i = 0; i < args.threads_num; i++)
    {
        if (thrd_join(threads[i], NULL) != thrd_success)
        {
            sys_error("Error joining thread");
        }
    }

    bench_results results;
    results.start = thr_args[0].results.start;
    results.end = thr_args[0].results.end;
    for (size_t i = 0; i < args.threads_num; i++)
    {
        if (results.start > thr_args[i].results.start)
            results.start = thr_args->results.start;
        if (results.end < thr_args->results.end)
            results.end = thr_args->results.end;
    }

    results.sum = sum;
    evaluate_benchmark(&results, &args, NULL);

    free(array);
    free(thr_args);
    free(threads);

    return 0;
}