/* SPDX-License-Identifier: Apache-2.0 */

#include "substrait/expression/Expression.h"
#include "substrait/expression/ExpressionVisitor.h"

namespace io::substrait {

void NullLiteral::accept(ExpressionVisitor& visitor) {
  visitor.visit(*this);
}

void BoolLiteral::accept(ExpressionVisitor& visitor) {
  visitor.visit(*this);
}

void TinyIntLiteral::accept(ExpressionVisitor& visitor) {
  visitor.visit(*this);
}

void SmallIntLiteral::accept(ExpressionVisitor& visitor) {
  visitor.visit(*this);
}

void IntLiteral::accept(ExpressionVisitor& visitor) {
  visitor.visit(*this);
}

void BigIntLiteral::accept(ExpressionVisitor& visitor) {
  visitor.visit(*this);
}

void FloatLiteral::accept(ExpressionVisitor& visitor) {
  visitor.visit(*this);
}

void DoubleLiteral::accept(ExpressionVisitor& visitor) {
  visitor.visit(*this);
}

void StrLiteral::accept(ExpressionVisitor& visitor) {
  visitor.visit(*this);
}

void BinaryLiteral::accept(ExpressionVisitor& visitor) {
  visitor.visit(*this);
}

void TimeLiteral::accept(ExpressionVisitor& visitor) {
  visitor.visit(*this);
}

void DateLiteral::accept(ExpressionVisitor& visitor) {
  visitor.visit(*this);
}

void TimestampLiteral::accept(ExpressionVisitor& visitor) {
  visitor.visit(*this);
}

void TimestampTzLiteral::accept(ExpressionVisitor& visitor) {
  visitor.visit(*this);
}

void IntervalYearLiteral::accept(ExpressionVisitor& visitor) {
  visitor.visit(*this);
}

void IntervalDayLiteral::accept(ExpressionVisitor& visitor) {
  visitor.visit(*this);
}

void FixedCharLiteral::accept(ExpressionVisitor& visitor) {
  visitor.visit(*this);
}

void VarCharLiteral::accept(ExpressionVisitor& visitor) {
  visitor.visit(*this);
}

void FixedBinaryLiteral::accept(ExpressionVisitor& visitor) {
  visitor.visit(*this);
}

void DecimalLiteral::accept(ExpressionVisitor& visitor) {
  visitor.visit(*this);
}

void MapLiteral::accept(ExpressionVisitor& visitor) {
  visitor.visit(*this);
}

void ListLiteral::accept(ExpressionVisitor& visitor) {
  visitor.visit(*this);
}

void StructLiteral::accept(ExpressionVisitor& visitor) {
  visitor.visit(*this);
}

void Switch::accept(ExpressionVisitor& visitor) {
  visitor.visit(*this);
}

void IfThen::accept(ExpressionVisitor& visitor) {
  visitor.visit(*this);
}

void ScalarFunction::accept(ExpressionVisitor& visitor) {
  visitor.visit(*this);
}

void Cast::accept(ExpressionVisitor& visitor) {
  visitor.visit(*this);
}

void SingularOrList::accept(ExpressionVisitor& visitor) {
  visitor.visit(*this);
}

void MultiOrList::accept(ExpressionVisitor& visitor) {
  visitor.visit(*this);
}

} // namespace io::substrait
