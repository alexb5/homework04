#pragma once

#include <algorithm>
#include <ostream>
#include <type_traits>
#include <vector>
#include <string>
#include <list>

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

/**
 * @brief Generic template of type trait is_container.
 * 
 * @tparam T 
 */
template<class T>
struct is_container :  std::false_type {};

/**
 * @brief Specification of type trait is_container for std::vector.
 * 
 * @tparam T 
 */
template <typename... Args> 
struct is_container<std::vector<Args...>>:std::true_type{};

/**
 * @brief Specification of type trait is_container for std::list.
 * 
 * @tparam T 
 */
template <typename... Args> 
struct is_container<std::list<Args...>>:std::true_type{};

template< class T >
constexpr bool is_container_v = is_container<T>::value;

template<class T>
void print_ip(T ip, std::ostream& out)
{
    std::string ip_string{};
    if constexpr(std::is_integral<T>::value) {
        auto size = sizeof(T);
        std::string ip_string{};
        const auto begin = reinterpret_cast<uint8_t*>(&ip);
        for (auto i = begin; i < begin + size; ++i) {
            ip_string.append(std::to_string(*i));
            ip_string.append(".");
        }
        ip_string.pop_back();
    }
    else constexpr(is_container_v<T>) {
        for (auto& byte : ip) {
            ip_string.append(std::to_string(byte));
            ip_string.append(".");
        }
        ip_string.pop_back();    
    }
    else {
        ip_string = ip;
    }
    out << ip_string << std::endl;
}

/**
 * @brief  Specification of function for integral types.
 * 
 * @param ip Ip address in numeric format.
 * @param out Stream for output.
 */
// template<class T, typename std::enable_if<std::is_integral<T>::value>::type* = nullptr>
// void print_ip(T ip, std::ostream& out)
// {
//     auto size = sizeof(T);
//     std::string ip_string{};
//     const auto begin = reinterpret_cast<uint8_t*>(&ip);
//     for (auto i = begin; i < begin + size; ++i) {
//         ip_string.append(std::to_string(*i));
//         ip_string.append(".");
//     }
//     ip_string.pop_back();
//     out << ip_string << std::endl;
// }

/**
 * @brief  Specification of function for container types.
 * 
 * @param ip Ip address in numeric format.
 * @param out Stream for output.
 */
// template<class T, typename std::enable_if<is_container<T>::value>::type* = nullptr>
// void print_ip(T ip, std::ostream& out)
// {
//     std::string ip_string{};
//     for (auto& byte : ip) {
//         ip_string.append(std::to_string(byte));
//         ip_string.append(".");
//     }
//     ip_string.pop_back();
//     out << ip_string << std::endl;
// }

} // namespace lib