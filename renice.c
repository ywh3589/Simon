#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main(int argc, char *argv[])
{
    if(argc < 3){
        printf(2, "Usage: nice pid priority\n");
        exit();
    }

    int pid = atoi(argv[1]);
    int pri = atoi(argv[2]);

    if (pri < -20 || pri > 19) {
        printf(2, "Usage: nice pid priority. Priority must be between -20 and 19\n");
        exit();
    }
    
    renice(pid, pri);

    exit();
}