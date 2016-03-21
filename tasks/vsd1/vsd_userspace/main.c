/*
 * TODO parse command line arguments and call proper
 * VSD_IOCTL_* using C function ioctl (see man ioctl).
 */

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include "../vsd_driver/vsd_ioctl.h"

#define CLOSEXIT(f) fclose(f); return EXIT_FAILURE;

int main(int argc, char **argv) {

    if (argc == 2 && strcmp(argv[1], "size_get") == 0) {
        FILE * f = fopen("/dev/vsd", "rw");
        if (f == 0) {
            printf("No device found.\n");
            return EXIT_FAILURE;
        }
        vsd_ioctl_get_size_arg_t vsd_ioctl_get_size_arg;
        int res = ioctl(fileno(f), VSD_IOCTL_GET_SIZE, &vsd_ioctl_get_size_arg);
        if (res != 0) {
            printf("Can't use ioctl. Error code = %d.\n", res);
            CLOSEXIT(f);
        }
        fclose(f);
        printf("Current size = %d\n", vsd_ioctl_get_size_arg.size);
    } else if (argc == 3 && strcmp(argv[1], "size_set") == 0) {
        FILE * f = fopen("/dev/vsd", "rw");
        if (f == 0) {
            printf("No device found.\n");
            return EXIT_FAILURE;
        }
        errno = 0;
        char *end = argv[2] + strlen(argv[2]);
        int nsize = strtol(argv[2], &end, 10);
        if (errno || nsize == 0) {
            printf("Can't parse number.\n");
            printf("%s\n",strerror(errno));
            CLOSEXIT(f);
        }
        vsd_ioctl_set_size_arg_t vsd_ioctl_set_size_arg;
        vsd_ioctl_set_size_arg.size = nsize;
        int res = ioctl(fileno(f), VSD_IOCTL_SET_SIZE, &vsd_ioctl_set_size_arg);
        if (res != 0) {
            printf("Can't use ioctl. Error code = %d.\n", res);
            CLOSEXIT(f);
        }
        fclose(f);
        printf("Size changed to %d\n", vsd_ioctl_set_size_arg.size);
    } else {
        printf("Wrong use. You should type:\n");
        printf("'vsd_userspace size_get' to print current buffer size\n");
        printf("'vsd_userspace size_set NUM' to set buffer size\n");
    }
    return EXIT_SUCCESS;
}
