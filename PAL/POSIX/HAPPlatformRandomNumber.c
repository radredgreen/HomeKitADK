// Copyright (c) 2015-2019 The HomeKit ADK Contributors
//
// Licensed under the Apache License, Version 2.0 (the “License”);
// you may not use this file except in compliance with the License.
// See [CONTRIBUTORS.md] for the list of HomeKit ADK project authors.

#include <errno.h>
#include <linux/random.h>
#include <syscall.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "HAPPlatform.h"

/**
 * Linux Random Number generator.
 *
 * This Random Number generator makes use of the Linux getrandom(2) interface.
 * Please note that this interface is only supported from Linux 3.17 onwards.
 *
 * For more information see:
 *  - LWN - The long road to getrandom() in glibc: https://lwn.net/Articles/711013/
 *  - Getrandom Manpage: http://man7.org/linux/man-pages/man2/getrandom.2.html
 */

static const HAPLogObject logObject = { .subsystem = kHAPPlatform_LogSubsystem, .category = "RandomNumber" };

#define GRND_RANDOM 0x1
#define GRND_NONBLOCK 0x2

void HAPPlatformRandomNumberFill(void* bytes, size_t numBytes) {
    HAPPrecondition(bytes);

    // Flags to call getrandom.
    const int getrandomFlags = GRND_NONBLOCK; // Use the urandom source and do not block.
    
    // With glibc >= 2.25 it is possible to call getrandom() directly.
    // Source: man page of getrandom(2).
    // n = syscall(SYS_getrandom, &((uint8_t*) bytes)[o], c, getrandomFlags);

    // wyrecam: Kernel 3.10.14 doesn't support getrandom

    int fd;
    ssize_t result = 0;
    /* select right source */
    //char* source = getrandomFlags & GRND_RANDOM ? "/dev/random" : "/dev/urandom";
    char* source = "/dev/urandom";

    fd = open(source, O_RDONLY | O_CLOEXEC);
    if (fd < 0){
        int _errno = errno;
        HAPLogError(&logObject, "Could not open /dev/urandom: %d.",_errno);
        HAPFatalError();
    }

    while (result < numBytes) {
        result += read(fd, &((uint8_t*) bytes)[result], numBytes - result);
        HAPLogDebug(&logObject, "Read %d bytes from /dev/urandom.", result);
    }
    
    close(fd);


    // Verify random data.
    if (numBytes < 128 / 8 || !HAPRawBufferIsZero(bytes, numBytes)) {
        return;
    }
    HAPLogError(&logObject, "getrandom produced only zeros.");
    HAPFatalError();
}
