/* SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include <cassert>
#include <utility>

#include "substrait/function/Function.h"
#include "substrait/type/Type.h"

namespace io::substrait {

class ExpressionVisitor;

class Expression {
 public:
  virtual TypePtr getType() const = 0;

  virtual void accept(ExpressionVisitor& vis) = 0;
};

using ExpressionPtr = std::shared_ptr<Expression>;

template <typename Visitable>
class ExpressionBase : public Expression {
 public:
  using Expression::Expression;
  void accept(ExpressionVisitor& v) override;
};

class Literal : public Expression {
 public:
  explicit Literal(const bool nullable = false) : nullable_(nullable){};

  bool isNullable() const {
    return nullable_;
  }

 protected:
  bool nullable_;
};

using LiteralPtr = std::shared_ptr<Literal>;

template <typename Visitable>
class LiteralBase : public Literal {
 public:
  using Literal::Literal;
  void accept(ExpressionVisitor& v) override;
};

class NullLiteral : public LiteralBase<NullLiteral> {
 public:
  explicit NullLiteral(TypePtr type, const bool nullable = false)
      : LiteralBase(nullable), type_(std::move(type)){};

  TypePtr getType() const override {
    return type_;
  }

 private:
  TypePtr type_;
};

class BoolLiteral : public LiteralBase<BoolLiteral> {
  explicit BoolLiteral(const bool value, const bool nullable = false)
      : LiteralBase(nullable), value_(value){};

  TypePtr getType() const override {
    return BOOL(isNullable());
  }

  bool getValue() const {
    return value_;
  }

 private:
  bool value_;
};

class TinyIntLiteral : public LiteralBase<TinyIntLiteral> {
 public:
  explicit TinyIntLiteral(const int8_t value, const bool nullable = false)
      : LiteralBase(nullable), value_(value){};
  TypePtr getType() const override {
    return TINYINT(isNullable());
  }
  int8_t getValue() const {
    return value_;
  }

 private:
  int8_t value_;
};

class SmallIntLiteral : public LiteralBase<SmallIntLiteral> {
 public:
  explicit SmallIntLiteral(const int16_t value, const bool nullable = false)
      : LiteralBase(nullable), value(value){};

  TypePtr getType() const override {
    return SMALLINT(isNullable());
  }

  int16_t getValue() const {
    return value;
  }

 private:
  int16_t value;
};

class IntLiteral : public LiteralBase<IntLiteral> {
 public:
  explicit IntLiteral(const int32_t value, const bool nullable = false)
      : LiteralBase(nullable), value_(value){};
  TypePtr getType() const override {
    return INTEGER(isNullable());
  }
  int32_t getValue() const {
    return value_;
  }

 private:
  int32_t value_;
};

class BigIntLiteral : public LiteralBase<BigIntLiteral> {
 public:
  explicit BigIntLiteral(const int64_t value, const bool nullable = false)
      : LiteralBase(nullable), value_(value){};
  TypePtr getType() const override {
    return BIGINT(isNullable());
  }
  int64_t getValue() const {
    return value_;
  }

 private:
  int64_t value_;
};

class FloatLiteral : public LiteralBase<FloatLiteral> {
 public:
  explicit FloatLiteral(const float value, const bool nullable = false)
      : LiteralBase(nullable), value_(value){};
  TypePtr getType() const override {
    return FLOAT(isNullable());
  }
  float getValue() const {
    return value_;
  }

 private:
  float value_;
};

class DoubleLiteral : public LiteralBase<DoubleLiteral> {
 public:
  explicit DoubleLiteral(const double value, const bool nullable = false)
      : LiteralBase(nullable), value_(value){};
  TypePtr getType() const override {
    return DOUBLE(isNullable());
  }

  double getValue() const {
    return value_;
  }

 private:
  double value_;
};

class StrLiteral : public LiteralBase<StrLiteral> {
 public:
  explicit StrLiteral(std::string value, const bool nullable = false)
      : LiteralBase(nullable), value_(std::move(value)){};
  TypePtr getType() const override {
    return STRING(isNullable());
  }
  const std::string& getValue() const {
    return value_;
  }

 private:
  std::string value_;
};

class BinaryLiteral : public LiteralBase<BinaryLiteral> {
 public:
  explicit BinaryLiteral(std::string value, const bool nullable = false)
      : LiteralBase(nullable), value_(std::move(value)){};
  TypePtr getType() const override {
    return STRING(isNullable());
  }
  const std::string& getValue() const {
    return value_;
  }

 private:
  std::string value_;
};

class TimestampLiteral : public LiteralBase<TimestampLiteral> {
 public:
  explicit TimestampLiteral(const int64_t value, const bool nullable = false)
      : LiteralBase(nullable), value_(value){};
  TypePtr getType() const override {
    return TIMESTAMP(isNullable());
  }
  int64_t getValue() const {
    return value_;
  }

 private:
  int64_t value_;
};

class TimeLiteral : public LiteralBase<TimeLiteral> {
 public:
  explicit TimeLiteral(const int64_t value, const bool nullable = false)
      : LiteralBase(nullable), value_(value){};
  TypePtr getType() const override {
    return TIME(isNullable());
  }

  int64_t getValue() const {
    return value_;
  }

 private:
  int64_t value_;
};

class DateLiteral : public LiteralBase<DateLiteral> {
 public:
  explicit DateLiteral(const int32_t value, const bool nullable = false)
      : LiteralBase(nullable), value_(value){};
  TypePtr getType() const override {
    return DATE(isNullable());
  }
  int32_t getValue() const {
    return value_;
  }

 private:
  int32_t value_;
};

struct TimestampTzLiteral : public LiteralBase<TimestampTzLiteral> {
  explicit TimestampTzLiteral(const int64_t value, const bool nullable = false)
      : LiteralBase(nullable), value_(value){};
  TypePtr getType() const override {
    return TIMESTAMP_TZ(isNullable());
  }
  int64_t getValue() const {
    return value_;
  }

 private:
  int64_t value_;
};

class IntervalYearLiteral : public LiteralBase<IntervalYearLiteral> {
 public:
  explicit IntervalYearLiteral(
      const int32_t years,
      const int32_t months,
      const bool nullable = false)
      : LiteralBase(nullable), years_(years), months_(months){};

  TypePtr getType() const override {
    return INTERVAL_YEAR(isNullable());
  }
  int64_t getYears() const {
    return years_;
  }
  int64_t getMonth() const {
    return months_;
  }

 private:
  int32_t years_;
  int32_t months_;
};

class IntervalDayLiteral : public LiteralBase<IntervalDayLiteral> {
 public:
  explicit IntervalDayLiteral(
      const int32_t days,
      const int32_t seconds,
      const bool nullable = false)
      : LiteralBase(nullable), days_(days), seconds_(seconds){};

  TypePtr getType() const override {
    return INTERVAL_DAY(isNullable());
  }
  int32_t getDays() const {
    return days_;
  }
  int32_t getSeconds() const {
    return seconds_;
  }

 private:
  int32_t days_;
  int32_t seconds_;
};

class FixedCharLiteral : public LiteralBase<FixedCharLiteral> {
 public:
  explicit FixedCharLiteral(std::string value, const bool nullable = false)
      : LiteralBase(nullable), value_(std::move(value)){};

  TypePtr getType() const override {
    return FIXED_CHAR(value_.length(), isNullable());
  }
  const std::string& getValue() const {
    return value_;
  }

 private:
  std::string value_;
};

class VarCharLiteral : public LiteralBase<VarCharLiteral> {
 public:
  explicit VarCharLiteral(const std::string& value, const bool nullable = false)
      : LiteralBase(nullable), value_(value), len_(value.length()){};

  TypePtr getType() const override {
    return VARCHAR(len_, isNullable());
  }

  const std::string& getValue() const {
    return value_;
  }
  int getLen() const {
    return len_;
  }

 private:
  std::string value_;
  int len_;
};
class FixedBinaryLiteral : public LiteralBase<FixedBinaryLiteral> {
 public:
  explicit FixedBinaryLiteral(
      const std::string& value,
      const bool nullable = false)
      : LiteralBase(nullable), value_(value), len_(value.length()){};

  TypePtr getType() const override {
    return FIXED_BINARY(len_, isNullable());
  }
  const std::string& getValue() const {
    return value_;
  }
  int getLen() const {
    return len_;
  }

 private:
  std::string value_;
  int len_;
};

class DecimalLiteral : public LiteralBase<DecimalLiteral> {
 public:
  explicit DecimalLiteral(
      std::string value,
      const int32_t precision,
      const int32_t scale,
      const bool nullable = false)
      : LiteralBase(nullable),
        value_(std::move(value)),
        precision_(precision),
        scale_(scale){};

  TypePtr getType() const override {
    return DECIMAL(precision_, scale_, isNullable());
  }

  int32_t getPrecision() const {
    return precision_;
  }

  int32_t getScale() const {
    return scale_;
  }
  const std::string& getValue() const {
    return value_;
  }

 private:
  int32_t precision_;
  int32_t scale_;
  std::string value_;
};

class MapLiteral : public LiteralBase<MapLiteral> {
 public:
  explicit MapLiteral(
      std::unordered_map<LiteralPtr, LiteralPtr> value,
      const bool nullable = false)
      : LiteralBase(nullable), value_(std::move(value)){};

  TypePtr getType() const override {
    auto keyValue = value_.begin();
    return MAP(
        keyValue->first->getType(), keyValue->second->getType(), isNullable());
  }

  const std::unordered_map<LiteralPtr, LiteralPtr>& getValue() const {
    return value_;
  }

 private:
  std::unordered_map<LiteralPtr, LiteralPtr> value_;
};

class ListLiteral : public LiteralBase<ListLiteral> {
 public:
  explicit ListLiteral(
      std::vector<LiteralPtr> value,
      const bool nullable = false)
      : LiteralBase(nullable), value_(std::move(value)){};

  TypePtr getType() const override {
    return LIST(value_.begin()[0]->getType(), isNullable());
  }
  const std::vector<LiteralPtr>& getValue() const {
    return value_;
  }

 private:
  std::vector<LiteralPtr> value_;
};

class StructLiteral : public LiteralBase<StructLiteral> {
 public:
  explicit StructLiteral(
      std::vector<LiteralPtr> fields,
      const bool nullable = false)
      : LiteralBase(nullable), fields_(std::move(fields)){};

  TypePtr getType() const override {
    std::vector<TypePtr> types;
    types.reserve(fields_.size());
    for (const auto& field : fields_) {
      types.emplace_back(field->getType());
    }
    return STRUCT(types, isNullable());
  }
  const std::vector<LiteralPtr>& getFields() const {
    return fields_;
  }

 private:
  std::vector<LiteralPtr> fields_;
};

struct SwitchClause {
  LiteralPtr condition;
  ExpressionPtr then;

  SwitchClause(LiteralPtr condition, ExpressionPtr then)
      : condition(std::move(condition)), then(std::move(then)) {}
};

class Switch : public ExpressionBase<Switch> {
 public:
  Switch(
      std::vector<std::shared_ptr<SwitchClause>> switchClauses,
      ExpressionPtr defaultClause)
      : switchClauses_(std::move(switchClauses)),
        defaultClause_(std::move(defaultClause)) {}

  TypePtr getType() const override {
    return defaultClause_->getType();
  }

  const std::vector<std::shared_ptr<SwitchClause>>& getSwitchClauses() const {
    return switchClauses_;
  }

  const ExpressionPtr& getDefaultClause() const {
    return defaultClause_;
  }

 private:
  std::vector<std::shared_ptr<SwitchClause>> switchClauses_;
  ExpressionPtr defaultClause_;
};

struct IfClause {
  ExpressionPtr condition;
  ExpressionPtr then;

  IfClause(ExpressionPtr condition, ExpressionPtr then)
      : condition(std::move(condition)), then(std::move(then)) {}
};

class IfThen : public ExpressionBase<IfThen> {
 public:
  IfThen(
      std::vector<std::shared_ptr<IfClause>> ifClauses,
      ExpressionPtr elseClause)
      : ifClauses_(std::move(ifClauses)), elseClause_(std::move(elseClause)) {}

  TypePtr getType() const override {
    return elseClause_->getType();
  }

  const std::vector<std::shared_ptr<IfClause>>& getIfClauses() const {
    return ifClauses_;
  }

  const ExpressionPtr& getElseClause() const {
    return elseClause_;
  }

 private:
  std::vector<std::shared_ptr<IfClause>> ifClauses_;
  ExpressionPtr elseClause_;
};

class Cast : public ExpressionBase<Cast> {
 public:
  Cast(ExpressionPtr input, TypePtr type)
      : input_(std::move(input)), type_(std::move(type)){};
  TypePtr getType() const override {
    return type_;
  }

  const ExpressionPtr& getInput() const {
    return input_;
  }

 private:
  ExpressionPtr input_;
  TypePtr type_;
};

class ScalarFunction : public ExpressionBase<ScalarFunction> {
 public:
  ScalarFunction(
      std::shared_ptr<ScalarFunctionImplementation> implementation,
      std::vector<FunctionArgumentPtr> arguments,
      TypePtr outputType)
      : implementation_(std::move(implementation)),
        arguments_(std::move(arguments)),
        outputType_(std::move(outputType)){};

  TypePtr getType() const override {
    return outputType_;
  }

  const std::shared_ptr<ScalarFunctionImplementation>& getImplementation()
      const {
    return implementation_;
  }
  const std::vector<FunctionArgumentPtr>& getArguments() const {
    return arguments_;
  }

 private:
  std::shared_ptr<ScalarFunctionImplementation> implementation_;
  std::vector<FunctionArgumentPtr> arguments_;
  TypePtr outputType_;
};

class SingularOrList : public ExpressionBase<SingularOrList> {
 public:
  SingularOrList(ExpressionPtr condition, std::vector<ExpressionPtr> options)
      : condition_(std::move(condition)), options_(std::move(options)){};

  const ExpressionPtr& getCondition() const {
    return condition_;
  }

  const std::vector<ExpressionPtr>& getOptions() const {
    return options_;
  }

 private:
  ExpressionPtr condition_;
  std::vector<ExpressionPtr> options_;
};

struct MultiOrListRecord {
  std::vector<ExpressionPtr> values;
  explicit MultiOrListRecord(std::vector<ExpressionPtr> values)
      : values(std::move(values)){};
};

class MultiOrList : public ExpressionBase<MultiOrList> {
 public:
  MultiOrList(
      std::vector<ExpressionPtr> conditions,
      std::vector<std::shared_ptr<MultiOrListRecord>> options)
      : conditions_(std::move(conditions)), options_(std::move(options)){};

  const std::vector<ExpressionPtr>& getConditions() const {
    return conditions_;
  }

  const std::vector<std::shared_ptr<MultiOrListRecord>>& getOptions() const {
    return options_;
  }

  TypePtr getType() const override {
    return BOOL(true);
  }

 private:
  std::vector<ExpressionPtr> conditions_;
  std::vector<std::shared_ptr<MultiOrListRecord>> options_;
};

} // namespace io::substrait
