#include "veriuser.h"
#include "vxl_veriuser.h"

extern int benchmark_pli();

p_tfcell bootstrap() {
    s_tfcell veriusertfs[] = {
    //  {userfunction|usertask, data, checktf(), sizetf(), calltf(),        misctf(), "$tfname",        forwref},
        {usertask,              0,    0,         0,        benchmark_pli,   0,        "$benchmark_pli",       1},
        {0}  // last entry must be 0
    };
    return veriusertfs;
}

