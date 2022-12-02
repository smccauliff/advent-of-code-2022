#pragma once

#include <boost/outcome.hpp>
namespace outcome {

template <typename T, typename ErrorType = std::error_code>
using result = BOOST_OUTCOME_V2_NAMESPACE::unchecked<T, ErrorType>;

template <typename T, typename ErrorType = std::error_code>
result<T, ErrorType> make_result(T&& value) {
  return result<T, ErrorType>(std::forward<T>(value));
}

}