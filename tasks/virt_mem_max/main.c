#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>

int main()
{
    size_t size = 0;
    for (size_t i = 1UL << (8 * sizeof(size_t) - 1); i > 0; ) {
        if (mmap(0, i, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, 0, 0) != MAP_FAILED) {
            size += i;
        } else {
            i = i >> 1;
        }
    }
    printf("%lu\n", size);
    return 0;
}
