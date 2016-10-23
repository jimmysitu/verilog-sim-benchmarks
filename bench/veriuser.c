#include "veriuser.h"

#ifdef NC
    #include "vxl_veriuser.h"
#endif

#ifdef CVC
    #include "cv_veriuser.h"
#endif

extern int benchmark_pli();

s_tfcell veriusertfs[] = {
//  {userfunction|usertask, data, checktf(), sizetf(), calltf(),        misctf(), "$tfname",        forwref},
    {usertask,              0,    0,         0,        benchmark_pli,   0,        "$benchmark_pli",       1},
    {0}  // last entry must be 0
};

p_tfcell bootstrap() {
    return veriusertfs;
}

