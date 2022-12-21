/* SPDX-License-Identifier: Apache-2.0 */

#include "substrait/expression/Expression.h"
#include "substrait/expression/ExpressionVisitor.h"

namespace substrait {

template <typename Visitable>
void ExpressionBase<Visitable>::accept(ExpressionVisitor& v) {
  v.visit(static_cast<const Visitable&>(*this));
}

template <typename Visitable>
void LiteralBase<Visitable>::accept(ExpressionVisitor& v) {
  v.visit(static_cast<const Visitable&>(*this));
}

} // namespace substrait
