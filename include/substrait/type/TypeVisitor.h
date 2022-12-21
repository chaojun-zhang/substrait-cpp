/* SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include "substrait/type/Type.h"

namespace substrait {

class TypeVisitor {
 public:
  virtual void visitFallback(const ParameterizedType& type) {}

  virtual void visit(const Bool& type) {
    visitFallback(type);
  }
  virtual void visit(const TinyInt& type) {
    visitFallback(type);
  }
  virtual void visit(const SmallInt& type) {
    visitFallback(type);
  }
  virtual void visit(const Integer& type) {
    visitFallback(type);
  }
  virtual void visit(const BigInt& type) {
    visitFallback(type);
  }
  virtual void visit(const Float& type) {
    visitFallback(type);
  }
  virtual void visit(const Double& type) {
    visitFallback(type);
  }
  virtual void visit(const String& type) {
    visitFallback(type);
  }
  virtual void visit(const Binary& type) {
    visitFallback(type);
  }
  virtual void visit(const Date& type) {
    visitFallback(type);
  }
  virtual void visit(const Time& type) {
    visitFallback(type);
  }
  virtual void visit(const Timestamp& type) {
    visitFallback(type);
  }
  virtual void visit(const TimestampTz& type) {
    visitFallback(type);
  }
  virtual void visit(const IntervalYear& type) {
    visitFallback(type);
  }
  virtual void visit(const IntervalDay& type) {
    visitFallback(type);
  }
  virtual void visit(const Uuid& type) {
    visitFallback(type);
  }
  virtual void visit(const FixedChar& type) {
    visitFallback(type);
  }
  virtual void visit(const Varchar& type) {
    visitFallback(type);
  }
  virtual void visit(const FixedBinary& type) {
    visitFallback(type);
  }
  virtual void visit(const Decimal& type) {
    visitFallback(type);
  }
  virtual void visit(const Struct& type) {
    visitFallback(type);
  }

  virtual void visit(const List& type) {
    visitFallback(type);
  }
  virtual void visit(const Map& type) {
    visitFallback(type);
  }

  virtual void visit(const ParameterizedFixedChar& expr) {
    visitFallback(expr);
  }

  virtual void visit(const ParameterizedVarchar& expr) {
    visitFallback(expr);
  }

  virtual void visit(const ParameterizedFixedBinary& expr) {
    visitFallback(expr);
  }

  virtual void visit(const ParameterizedDecimal& expr) {
    visitFallback(expr);
  }

  virtual void visit(const ParameterizedStruct& expr) {
    visitFallback(expr);
  }

  virtual void visit(const ParameterizedList& expr) {
    visitFallback(expr);
  }

  virtual void visit(const ParameterizedMap& expr) {
    visitFallback(expr);
  }

  virtual void visit(const StringLiteral& expr) {
    visitFallback(expr);
  }
};

} // namespace substrait
