#include <stdio.h>
#include "acc_user.h"

int benchmark_pli(){
    int message;

    acc_initialize();
    message = acc_fetch_tfarg_int(1);
    printf("Benchmark PLI: %d", message);
    acc_close();

}
