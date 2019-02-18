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
    
    renice(atoi(argv[1]), atoi(argv[2]));

    exit();
}