/* SPDX-License-Identifier: Apache-2.0 */

#pragma once

namespace substrait {

template<typename VisitorImpl, typename VisitablePtr, typename ResultType>
class ValueGetter
{
 public:
  static ResultType GetValue(VisitablePtr n)
  {
    VisitorImpl vis;
    n->Accept(vis); // this call fills the return value
    return vis.value;
  }

  void Return(ResultType value_)
  {
    value = value_;
  }
 private:
  ResultType value;
};


} // namespace substrait
