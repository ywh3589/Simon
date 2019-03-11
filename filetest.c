#include "types.h"
#include "user.h"
#include "fcntl.h"

#define N 100

struct test {
    char name[512];
    int number;
};

void
save(void)
{
    int fd;
    struct test t;
    strcpy(t.name, "CS_467");
    t.number = 467;

    fd = open("backup", O_CREATE | O_RDWR);
    if(fd >= 0) {
        printf(1, "ok: create backup file succeed\n");
    } else {
        printf(1, "error: create backup file failed\n");
        exit();
    }

    int size = sizeof(t);
    if(write(fd, &t, size) != size){
        printf(1, "error: write to backup file failed\n");
        exit();
    }
    printf(1, "file contents name %s and number %d\n", t.name, t.number);
    printf(1, "write ok\n");
    close(fd);
}

void
load(void)
{
    int fd;
    struct test t;

    fd = open("backup", O_RDONLY);
    if(fd >= 0) {
        printf(1, "ok: read backup file succeed\n");
    } else {
        printf(1, "error: read backup file failed\n");
        exit();
    }

    int size = sizeof(t);
    if(read(fd, &t, size) != size){
        printf(1, "error: read from backup file failed\n");
        exit();
    }
    printf(1, "file contents name %s and number %d\n", t.name, t.number);
    printf(1, "read ok\n");
    close(fd);
}

void
createTestFile(void)
{
    int fd;
    char data[1024];
    strcpy(data, "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n");

    fd = open("tail_test", O_CREATE | O_RDWR);
    if(fd >= 0) {
        printf(1, "ok: create file succeed\n");
    } else {
        printf(1, "error: create file failed\n");
        exit();
    }

    int size = sizeof(data);
    if(write(fd, &data, size) != size){
        printf(1, "error: write to file failed\n");
        exit();
    }
    printf(1, "write ok\n");
    close(fd);
}

int
main(void)
{
    // save();
    // load();
    createTestFile();

    exit();
}

//https://stackoverflow.com/questions/32872767/how-to-create-files-in-the-xv6