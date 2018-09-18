#include "lib.h"

#include "version.h"

#include <algorithm>
#include <iostream>
#include <string>

int lib::version_major() {
    return PROJECT_VERSION_MAJOR;
}

int lib::version_minor() {
    return PROJECT_VERSION_MINOR;
}

int lib::version_patch() {
    return PROJECT_VERSION_PATCH;
}