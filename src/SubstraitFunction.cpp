/*
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "SubstraitFunction.h"
#include <sstream>

namespace io::substrait {

std::string SubstraitFunctionVariant::signature(
    const std::string& name,
    const std::vector<SubstraitFunctionArgumentPtr>& arguments) {
  std::stringstream ss;
  ss << name;
  if (!arguments.empty()) {
    ss << ":";
    for (auto it = arguments.begin(); it != arguments.end(); ++it) {
      const auto& typeSign = (*it)->toTypeString();
      if (it == arguments.end() - 1) {
        ss << typeSign;
      } else {
        ss << typeSign << "_";
      }
    }
  }

  return ss.str();
}

bool SubstraitFunctionVariant::tryMatch(
    const std::vector<SubstraitTypePtr>& actualTypes) {
  if (variadic.has_value()) {
    // return false if actual types length less than min of variadic
    const auto max = variadic->max;
    if ((actualTypes.size() < variadic->min) ||
        (max.has_value() && actualTypes.size() > max.value())) {
      return false;
    }

    const auto& variadicArgument = arguments[0];
    // actual type must same as the variadicArgument
    if (const auto& variadicValueArgument =
            std::dynamic_pointer_cast<const SubstraitValueArgument>(
                variadicArgument)) {
      for (auto& actualType : actualTypes) {
        if (!variadicValueArgument->type->isSameAs(actualType)) {
          return false;
        }
      }
    }
    return true;
  } else {
    std::vector<std::shared_ptr<const SubstraitValueArgument>> valueArguments;
    for (const auto& argument : arguments) {
      if (const auto& variadicValueArgument =
              std::dynamic_pointer_cast<const SubstraitValueArgument>(
                  argument)) {
        valueArguments.emplace_back(variadicValueArgument);
      }
    }
    // return false if size of actual types not equal to size of value
    // arguments.
    if (valueArguments.size() != actualTypes.size()) {
      return false;
    }

    for (auto i = 0; i < actualTypes.size(); i++) {
      const auto& valueArgument = valueArguments[i];
      if (!valueArgument->type->isSameAs(actualTypes[i])) {
        return false;
      }
    }
    return true;
  }
}

bool SubstraitAggregateFunctionVariant::tryMatch(
    const std::vector<SubstraitTypePtr>& actualTypes) {
  bool matched = SubstraitFunctionVariant::tryMatch(actualTypes);
  if (!matched && intermediate) {
    if (actualTypes.size() == 1) {
      return intermediate->isSameAs(actualTypes[0]);
    }
  }
  return matched;
}

} // namespace io::substrait
