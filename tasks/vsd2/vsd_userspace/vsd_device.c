#include <sys/mman.h>

#include <stdio.h>
#include <fcntl.h>

#include "vsd_device.h"
#include "../vsd_driver/vsd_ioctl.h"

int desc = -1;

int vsd_init()
{
    if ((desc = open("/dev/vsd", O_RDWR)) < 0) return -1;
    return 0;
}

int vsd_deinit()
{
    if (desc < 0) return -1;
    close(desc);
    return 0;
}

int vsd_get_size(size_t *out_size)
{
    if (desc < 0) return -1;
    vsd_ioctl_get_size_arg_t iotcl_size;
    if (ioctl(desc, VSD_IOCTL_GET_SIZE, &iotcl_size)) return -1;
    *out_size = iotcl_size.size;
    return 0;
}

int vsd_set_size(size_t size)
{
    if (desc < 0) return -1;
    vsd_ioctl_set_size_arg_t iotcl_size;
    iotcl_size.size = size;
    if (ioctl(desc, VSD_IOCTL_SET_SIZE, &iotcl_size)) return -1;
    return 0;
}

ssize_t vsd_read(char* dst, off_t offset, size_t size)
{
    if (desc < 0) return -1;
    if (lseek(desc, offset, SEEK_SET) < 0) {
        close(desc);
        return -1;
    }
    if (read(desc, dst, size) < 0) {
        close(desc);
        return -1;
    }
    return 0;
}

ssize_t vsd_write(const char* src, off_t offset, size_t size)
{
    if (desc < 0) return -1;
    if (lseek(desc, offset, SEEK_SET) < 0) {
        close(desc);
        return -1;
    }
    if (write(desc, src, size) < 0) {
        close(desc);
        return -1;
    }
    return 0;
}

void* vsd_mmap(size_t offset)
{
    size_t size;
    if (desc < 0) return MAP_FAILED;
    if (offset % getpagesize() != 0) return MAP_FAILED;
    if (vsd_get_size(&size) < 0) return MAP_FAILED;
    return mmap(NULL, size - offset, PROT_READ | PROT_WRITE, MAP_SHARED, desc, offset);
}

int vsd_munmap(void* addr, size_t offset)
{
    size_t size;
    if (desc < 0) return -1;
    if ((size_t) addr % getpagesize() != 0 || offset % getpagesize() != 0)
        return -1;
    if (vsd_get_size(&size) < 0) return -1;
    return munmap(addr, size - offset);
}
