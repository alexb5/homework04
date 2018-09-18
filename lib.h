#pragma once

#include <array>
#include <cstdint>

namespace lib {
/**
 * @brief Return major version of project.
 * 
 * @return int 
 */
int version_major();

/**
 * @brief Return minor version of project.
 * 
 * @return int 
 */
int version_minor();

/**
 * @brief return patch version of project
 * 
 * @return int 
 */
int version_patch();

} // namespace lib