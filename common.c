#include <stdlib.h>
#include "common.h"

void sys_error(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}