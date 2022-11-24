#pragma once

#include "tuple_helper.h"

#include <list>
#include <type_traits>
#include <vector>

/**
 * @brief общая шаблонная структура
 */
template<typename T, typename Enable = void>
struct IP {
  /**
   * @brief print статическая ф-я выводящая в консоль переданный в нее аргумент
   * @param value аргумент ф-и
   */
  static constexpr void print(T&& value) {
    std::cout << value << "\n";
  }
};

/**
 * @brief явная специализация шаблона структуры IP для интегральных типов
 */
template <typename T>
struct IP<T, typename std::enable_if<std::is_integral<T>::value>::type> {

  static constexpr void print(T&& value) {
    using unsigned_t = typename std::make_unsigned<T>::type;
    const std::size_t bytes = sizeof(T);
    for(std::size_t i=0; i<bytes; ++i) {
      unsigned offset = ((bytes - 1) - i) * 8;
      std::cout << (i != 0 ? "." : "") << ((value & (static_cast<unsigned_t>(0xFF) << offset)) >> offset);
    }
    std::cout << std::endl;
  }
};

/**
 * @brief явная специализация шаблона структуры IP для tuple
 */
template <typename T>
struct IP<T, typename std::enable_if<is_tuple<T>::value>::type> {

  static constexpr void print(T&& value) {
    print_tuple(value);
    std::cout << std::endl;
  }
};

/**
 * @brief явная специализация шаблона структуры IP для
 *  контейнеров std::vector или std::list
 */
template<typename T>
struct IP<T, typename std::enable_if<
    std::is_same<std::list<typename T::value_type>, T>::value
      || std::is_same<std::vector<typename T::value_type>, T>::value
    >::type> {
  static constexpr void print(T&& value) {
    for(auto it = value.cbegin(); it != value.cend(); ++it) {
      std::cout << ( it != value.cbegin() ? "." : "") << *it;
    }
    std::cout << std::endl;
  }
};

/**
 * @brief явная специализация шаблона структуры IP для std::string
 */
template <typename T>
struct IP<T, typename std::enable_if<
    std::is_same<std::string, T>::value>::type> {

  static constexpr void print(T&& value) {
    std::cout << value << std::endl;
  }
};
