/* SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include <memory>
#include "substrait/expression/Expression.h"

namespace io::substrait {

class ExpressionVisitor {
 public:
  virtual void visitFallback(const Expression& literal) {}

  virtual void visit(const NullLiteral& expr) {
    visitFallback(expr);
  }

  virtual void visit(const BoolLiteral& expr) {
    visitFallback(expr);
  }

  virtual void visit(const TinyIntLiteral& expr) {
    visitFallback(expr);
  }

  virtual void visit(const SmallIntLiteral& expr) {
    visitFallback(expr);
  }

  virtual void visit(const IntLiteral& expr) {
    visitFallback(expr);
  }

  virtual void visit(const BigIntLiteral& expr) {
    visitFallback(expr);
  }

  virtual void visit(const FloatLiteral& expr) {
    visitFallback(expr);
  }

  virtual void visit(const DoubleLiteral& expr) {
    visitFallback(expr);
  }

  virtual void visit(const StrLiteral& expr) {
    visitFallback(expr);
  }

  virtual void visit(const BinaryLiteral& expr) {
    visitFallback(expr);
  }

  virtual void visit(const TimeLiteral& expr) {
    visitFallback(expr);
  }

  virtual void visit(const DateLiteral& expr) {
    visitFallback(expr);
  }

  virtual void visit(const TimestampLiteral& expr) {
    visitFallback(expr);
  }

  virtual void visit(const TimestampTzLiteral& expr) {
    visitFallback(expr);
  }

  virtual void visit(const IntervalYearLiteral& expr) {
    visitFallback(expr);
  }

  virtual void visit(const IntervalDayLiteral& expr) {
    visitFallback(expr);
  }

  virtual void visit(const FixedCharLiteral& expr) {
    visitFallback(expr);
  }

  virtual void visit(const VarCharLiteral& expr) {
    visitFallback(expr);
  }

  virtual void visit(const FixedBinaryLiteral& expr) {
    visitFallback(expr);
  }

  virtual void visit(const DecimalLiteral& expr) {
    visitFallback(expr);
  }

  virtual void visit(const MapLiteral& expr) {
    visitFallback(expr);
  }

  virtual void visit(const ListLiteral& expr) {
    visitFallback(expr);
  }

  virtual void visit(const StructLiteral& expr) {
    visitFallback(expr);
  }

  virtual void visit(const Switch& expr) {
    visitFallback(expr);
  }

  virtual void visit(const IfThen& expr) {
    visitFallback(expr);
  }

  virtual void visit(const ScalarFunction& expr) {
    visitFallback(expr);
  }

  virtual void visit(const Cast& expr) {
    visitFallback(expr);
  }

  virtual void visit(const SingularOrList& expr) {
    visitFallback(expr);
  }

  virtual void visit(const MultiOrList& expr) {
    visitFallback(expr);
  }
};

} // namespace io::substrait
