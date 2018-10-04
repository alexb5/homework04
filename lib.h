#pragma once

#include <list>
#include <ostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

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
 * @tparam Args 
 */
template <typename... Args> 
struct is_container<std::vector<Args...>>:std::true_type{};

/**
 * @brief Specification of type trait is_container for std::list.
 * 
 * @tparam Args 
 */
template <typename... Args> 
struct is_container<std::list<Args...>>:std::true_type{};

/**
 * @brief Generic template of type trait is_tuple.
 * 
 * @tparam T 
 */
template<class T>
struct is_tuple :  std::false_type {};

/**
 * @brief Specification of type trait is_tuple for std::tuple.
 * 
 * @tparam Args 
 */
template <typename... Args> 
struct is_tuple<std::tuple<Args...>>:std::true_type{};

template< class T >
constexpr bool is_container_v = is_container<T>::value;

template< class T >
constexpr bool is_tuple_v = is_tuple<T>::value;

template< class T >
constexpr bool is_integral_v = std::is_integral<T>::value;

template< class T, class U >
constexpr bool is_same_v = std::is_same<T, U>::value;

/**
 * @brief Helper class for printing tuples 
 * 
 * @tparam T Tuple type
 * @tparam N Tuple size
 */
template<class T, std::size_t N>
struct PrintTuple {
    static void print_tuple(const T& t, std::ostream& out) 
    {
        PrintTuple<T, N-1>::print_tuple(t, out);
        out << "." << std::get<N-1>(t);
    }
};

/**
 * @brief Partial specification of helper class for printing tuples
 * 
 * @tparam T Tuple type
 */
template<class T>
struct PrintTuple<T, 1> 
{
    static void print_tuple(const T& t, std::ostream& out) 
    {
        out << std::get<0>(t);
    }
};

/**
 * @brief Helper functions for printing tuples
 * 
 * @tparam Args Types of tuple
 * @param out Output streap for print
 * @param t Tuple for print
 */
template<class... Args>
static void print_tuple(std::ostream& out, const std::tuple<Args...>& t) 
{
    PrintTuple<decltype(t), sizeof ...(Args)>::print_tuple(t, out);
}

/**
 * @brief Template function for printing IP address
 * 
 * @tparam T Type of argument
 * @param ip IP address
 * @param out Output stream for print
 */
template<class T>
void print_ip(T ip, std::ostream& out)
{
    std::string ip_string{};
    if constexpr(is_integral_v<T>) {
        auto size = sizeof(T);
        std::string ip_string{};
        const auto begin = reinterpret_cast<uint8_t*>(&ip);
        for (auto i = begin + size - 1; i >= begin; --i) {
            ip_string.append(std::to_string(*i));
            ip_string.append(".");
        }
        ip_string.pop_back();
        out << ip_string << std::endl;    
    }
    else if constexpr(is_container_v<T>) {
        for (auto& byte : ip) {
            ip_string.append(std::to_string(byte));
            ip_string.append(".");
        }
        ip_string.pop_back();
        out << ip_string << std::endl;    
    }
    else if constexpr(is_tuple_v<T>) {
        print_tuple(out, ip);
        out << std::endl;    
    }
    else if constexpr (is_same_v<T, std::string>) {
         out << ip << std::endl;
    }
    else {
        out << "Not supported type" << std::endl;
    }
}

} // namespace lib