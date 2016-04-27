#ifndef _VSD_UAPI_H
#define _VSD_UAPI_H

#ifdef __KERNEL__
#include <asm/ioctl.h>
#include "shared_spinlock.h"
#else
#include <sys/ioctl.h>
#include <stddef.h>
#include <shared_spinlock.h>
#endif //__KERNEL__

#define MUTEX_IOCTL_MAGIC 'M'

typedef unsigned long mutex_id_t;

typedef struct mutex_ioctl_lock_create_arg {
    mutex_id_t id; // out param
} mutex_ioctl_lock_create_arg_t;

typedef struct mutex_ioctl_lock_destroy_arg {
    mutex_id_t id;
} mutex_ioctl_lock_destroy_arg_t;

typedef struct mutex_ioctl_lock_wait_arg {
    shared_spinlock_t *spinlock;
    mutex_id_t id;
} mutex_ioctl_lock_wait_arg_t;

typedef struct mutex_ioctl_lock_wake_arg {
    shared_spinlock_t *spinlock;
    mutex_id_t id;
} mutex_ioctl_lock_wake_arg_t;

#define MUTEX_IOCTL_LOCK_CREATE \
    _IOR(MUTEX_IOCTL_MAGIC, 1, mutex_ioctl_lock_create_arg_t)
#define MUTEX_IOCTL_LOCK_DESTROY \
    _IOR(MUTEX_IOCTL_MAGIC, 2, mutex_ioctl_lock_destroy_arg_t)
#define MUTEX_IOCTL_LOCK_WAIT \
    _IOR(MUTEX_IOCTL_MAGIC, 3, mutex_ioctl_lock_wait_arg_t)
#define MUTEX_IOCTL_LOCK_WAKE \
    _IOW(MUTEX_IOCTL_MAGIC, 4, mutex_ioctl_lock_wake_arg_t)

#endif //_VSD_UAPI_H
