#include <stdio.h>
#include "acc_user.h"

int count = 1;
int benchmark_pli(){
    int arg1;
    int arg2;
    int arg3;
    
    acc_initialize();
    
    arg1 = acc_fetch_tfarg_int(1);
    arg2 = acc_fetch_tfarg_int(2);
    arg3 = acc_fetch_tfarg_int(3);
    
    int res = arg1 * arg2 * count / arg3;

    if(!(count % 1000)){
        printf("Benchmark PLI: count: %d, result: %d\n", count, res);
    }

    acc_close();

}
