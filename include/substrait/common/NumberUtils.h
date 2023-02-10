/* SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include <iostream>

namespace io::substrait::common {

class NumberUtils {
 public:
  static bool is_number(const std::string& value) {
    std::string::const_iterator it = value.begin();
    while (it != value.end() && std::isdigit(*it)) {
      ++it;
    }
    return !value.empty() && it == value.end();
  }
};

} // namespace io::substrait::common