/* SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include <memory>
#include <utility>

#include "substrait/function/Function.h"
#include "substrait/type/Type.h"

namespace io::substrait {

class ExpressionVisitor;

class Expression {
 public:
  [[nodiscard]] virtual TypePtr type() const = 0;

  virtual void accept(ExpressionVisitor& vis) = 0;
};

using ExpressionPtr = std::shared_ptr<Expression>;

class Literal : public Expression {
 public:
  explicit Literal(const bool nullable = false) : nullable_(nullable){};

  [[nodiscard]] bool isNullable() const {
    return nullable_;
  }

 protected:
  bool nullable_;
};

using LiteralPtr = std::shared_ptr<Literal>;

class NullLiteral final : public Literal {
 public:
  explicit NullLiteral(TypePtr type, const bool nullable = false)
      : Literal(nullable), type_(std::move(type)){};

  [[nodiscard]] TypePtr type() const override {
    return type_;
  }

  void accept(ExpressionVisitor& vis) override;

 private:
  TypePtr type_;
};

class BoolLiteral final : public Literal {
 public:
  explicit BoolLiteral(const bool value, const bool nullable = false)
      : Literal(nullable), value_(value){};

  [[nodiscard]] TypePtr type() const override {
    return BOOL(isNullable());
  }

  [[nodiscard]] bool value() const {
    return value_;
  }

  void accept(ExpressionVisitor& vis) override;

 private:
  bool value_;
};

class TinyIntLiteral final : public Literal {
 public:
  explicit TinyIntLiteral(const int8_t value, const bool nullable = false)
      : Literal(nullable), value_(value){};

  [[nodiscard]] TypePtr type() const override {
    return TINYINT(nullable_);
  }
  [[nodiscard]] int8_t value() const {
    return value_;
  }

  void accept(ExpressionVisitor& vis) override;

 private:
  int8_t value_;
};

class SmallIntLiteral final : public Literal {
 public:
  explicit SmallIntLiteral(const int16_t value, const bool nullable = false)
      : Literal(nullable), value_(value){};

  [[nodiscard]] TypePtr type() const override {
    return SMALLINT(nullable_);
  }

  [[nodiscard]] int16_t value() const {
    return value_;
  }

  void accept(ExpressionVisitor& vis) override;

 private:
  int16_t value_;
};

class IntLiteral final : public Literal {
 public:
  explicit IntLiteral(const uint32_t value, const bool nullable = false)
      : Literal(nullable), value_(value){};
  [[nodiscard]] TypePtr type() const override {
    return INTEGER(nullable_);
  }
  [[nodiscard]] uint32_t value() const {
    return value_;
  }

  void accept(ExpressionVisitor& vis) override;

 private:
  uint32_t value_;
};

class BigIntLiteral final : public Literal {
 public:
  explicit BigIntLiteral(const int64_t value, const bool nullable = false)
      : Literal(nullable), value_(value){};

  [[nodiscard]] TypePtr type() const override {
    return BIGINT(nullable_);
  }
  [[nodiscard]] int64_t value() const {
    return value_;
  }

  void accept(ExpressionVisitor& vis) override;

 private:
  int64_t value_;
};

class FloatLiteral final : public Literal {
 public:
  explicit FloatLiteral(const float value, const bool nullable = false)
      : Literal(nullable), value_(value){};

  [[nodiscard]] TypePtr type() const override {
    return FLOAT(nullable_);
  }
  [[nodiscard]] float value() const {
    return value_;
  }

  void accept(ExpressionVisitor& vis) override;

 private:
  float value_;
};

class DoubleLiteral final : public Literal {
 public:
  explicit DoubleLiteral(const double value, const bool nullable = false)
      : Literal(nullable), value_(value){};

  [[nodiscard]] TypePtr type() const override {
    return DOUBLE(nullable_);
  }

  [[nodiscard]] double value() const {
    return value_;
  }

  void accept(ExpressionVisitor& vis) override;

 private:
  double value_;
};

class StrLiteral final : public Literal {
 public:
  explicit StrLiteral(std::string value, const bool nullable = false)
      : Literal(nullable), value_(std::move(value)){};
  [[nodiscard]] TypePtr type() const override {
    return STRING(nullable_);
  }
  [[nodiscard]] const std::string& value() const {
    return value_;
  }

  void accept(ExpressionVisitor& vis) override;

 private:
  std::string value_;
};

class BinaryLiteral final : public Literal {
 public:
  explicit BinaryLiteral(std::string value, const bool nullable = false)
      : Literal(nullable), value_(std::move(value)){};

  [[nodiscard]] TypePtr type() const override {
    return STRING(nullable_);
  }
  [[nodiscard]] const std::string& value() const {
    return value_;
  }

  void accept(ExpressionVisitor& vis) override;

 private:
  std::string value_;
};

class TimestampLiteral final : public Literal {
 public:
  explicit TimestampLiteral(const int64_t value, const bool nullable = false)
      : Literal(nullable), value_(value){};

  [[nodiscard]] TypePtr type() const override {
    return TIMESTAMP(nullable_);
  }
  [[nodiscard]] int64_t value() const {
    return value_;
  }

  void accept(ExpressionVisitor& vis) override;

 private:
  int64_t value_;
};

class TimeLiteral final : public Literal {
 public:
  explicit TimeLiteral(const int64_t value, const bool nullable = false)
      : Literal(nullable), value_(value){};

  [[nodiscard]] TypePtr type() const override {
    return TIME(nullable_);
  }

  [[nodiscard]] int64_t value() const {
    return value_;
  }

  void accept(ExpressionVisitor& vis) override;

 private:
  int64_t value_;
};

class DateLiteral final : public Literal {
 public:
  explicit DateLiteral(const uint32_t value, const bool nullable = false)
      : Literal(nullable), value_(value){};

  [[nodiscard]] TypePtr type() const override {
    return DATE(nullable_);
  }
  [[nodiscard]] uint32_t value() const {
    return value_;
  }

  void accept(ExpressionVisitor& vis) override;

 private:
  uint32_t value_;
};

class TimestampTzLiteral final : public Literal {
 public:
  explicit TimestampTzLiteral(const int64_t value, const bool nullable = false)
      : Literal(nullable), value_(value){};

  [[nodiscard]] TypePtr type() const override {
    return TIMESTAMP_TZ(nullable_);
  }
  [[nodiscard]] int64_t value() const {
    return value_;
  }

  void accept(ExpressionVisitor& vis) override;

 private:
  int64_t value_;
};

class IntervalYearLiteral final : public Literal {
 public:
  IntervalYearLiteral(
      const uint32_t years,
      const uint32_t months,
      const bool nullable = false)
      : Literal(nullable), years_(years), months_(months){};

  [[nodiscard]] TypePtr type() const override {
    return INTERVAL_YEAR(nullable_);
  }
  [[nodiscard]] int64_t years() const {
    return years_;
  }
  [[nodiscard]] int64_t months() const {
    return months_;
  }

  void accept(ExpressionVisitor& vis) override;

 private:
  uint32_t years_;
  uint32_t months_;
};

class IntervalDayLiteral final : public Literal {
 public:
  IntervalDayLiteral(
      const uint32_t days,
      const uint32_t seconds,
      const bool nullable = false)
      : Literal(nullable), days_(days), seconds_(seconds){};

  [[nodiscard]] TypePtr type() const override {
    return INTERVAL_DAY(nullable_);
  }
  [[nodiscard]] uint32_t days() const {
    return days_;
  }
  [[nodiscard]] uint32_t seconds() const {
    return seconds_;
  }

  void accept(ExpressionVisitor& vis) override;

 private:
  uint32_t days_;
  uint32_t seconds_;
};

class FixedCharLiteral final : public Literal {
 public:
  explicit FixedCharLiteral(std::string value, const bool nullable = false)
      : Literal(nullable), value_(std::move(value)){};

  [[nodiscard]] TypePtr type() const override {
    return FIXED_CHAR(value_.length(), nullable_);
  }
  [[nodiscard]] const std::string& value() const {
    return value_;
  }

  void accept(ExpressionVisitor& vis) override;

 private:
  std::string value_;
};

class VarCharLiteral final : public Literal {
 public:
  explicit VarCharLiteral(std::string value, const bool nullable = false)
      : Literal(nullable), value_(std::move(value)), len_(value.length()){};

  [[nodiscard]] TypePtr type() const override {
    return VARCHAR(len_, nullable_);
  }

  [[nodiscard]] const std::string& value() const {
    return value_;
  }
  [[nodiscard]] int len() const {
    return len_;
  }

  void accept(ExpressionVisitor& vis) override;

 private:
  std::string value_;
  int len_;
};
class FixedBinaryLiteral final : public Literal {
 public:
  explicit FixedBinaryLiteral(std::string value, const bool nullable = false)
      : Literal(nullable), value_(std::move(value)), len_(value.length()){};

  [[nodiscard]] TypePtr type() const override {
    return FIXED_BINARY(len_, nullable_);
  }
  [[nodiscard]] const std::string& value() const {
    return value_;
  }
  [[nodiscard]] uint32_t len() const {
    return len_;
  }

  void accept(ExpressionVisitor& vis) override;

 private:
  std::string value_;
  uint32_t len_;
};

class DecimalLiteral final : public Literal {
 public:
  DecimalLiteral(
      std::string value,
      const uint32_t precision,
      const uint32_t scale,
      const bool nullable = false)
      : Literal(nullable),
        value_(std::move(value)),
        precision_(precision),
        scale_(scale){};

  [[nodiscard]] TypePtr type() const override {
    return DECIMAL(precision_, scale_, nullable_);
  }

  [[nodiscard]] uint32_t precision() const {
    return precision_;
  }

  [[nodiscard]] uint32_t scale() const {
    return scale_;
  }
  [[nodiscard]] const std::string& value() const {
    return value_;
  }

  void accept(ExpressionVisitor& vis) override;

 private:
  uint32_t precision_;
  uint32_t scale_;
  std::string value_;
};

class MapLiteral final : public Literal {
 public:
  explicit MapLiteral(
      std::unordered_map<LiteralPtr, LiteralPtr> value,
      const bool nullable = false)
      : Literal(nullable), value_(std::move(value)){};

  [[nodiscard]] TypePtr type() const override {
    auto keyValue = value_.begin();
    return MAP(keyValue->first->type(), keyValue->second->type(), nullable_);
  }

  [[nodiscard]] const std::unordered_map<LiteralPtr, LiteralPtr>& value()
      const {
    return value_;
  }

  void accept(ExpressionVisitor& vis) override;

 private:
  std::unordered_map<LiteralPtr, LiteralPtr> value_;
};

class ListLiteral final : public Literal {
 public:
  explicit ListLiteral(
      std::vector<LiteralPtr> value,
      const bool nullable = false)
      : Literal(nullable), value_(std::move(value)){};

  [[nodiscard]] TypePtr type() const override {
    return LIST(value_.begin()[0]->type(), nullable_);
  }
  [[nodiscard]] const std::vector<LiteralPtr>& value() const {
    return value_;
  }

  void accept(ExpressionVisitor& vis) override;

 private:
  std::vector<LiteralPtr> value_;
};

class StructLiteral final : public Literal {
 public:
  explicit StructLiteral(
      std::vector<LiteralPtr> fields,
      const bool nullable = false)
      : Literal(nullable), fields_(std::move(fields)){};

  [[nodiscard]] TypePtr type() const override {
    std::vector<TypePtr> types;
    types.reserve(fields_.size());
    for (const auto& field : fields_) {
      types.emplace_back(field->type());
    }
    return STRUCT(types, nullable_);
  }
  [[nodiscard]] const std::vector<LiteralPtr>& fields() const {
    return fields_;
  }

  void accept(ExpressionVisitor& vis) override;

 private:
  std::vector<LiteralPtr> fields_;
};

struct SwitchClause {
  LiteralPtr condition;
  ExpressionPtr then;

  SwitchClause(LiteralPtr condition, ExpressionPtr then)
      : condition(std::move(condition)), then(std::move(then)) {}
};

class Switch final : public Expression {
 public:
  Switch(
      std::vector<std::shared_ptr<SwitchClause>> switchClauses,
      ExpressionPtr defaultClause)
      : switchClauses_(std::move(switchClauses)),
        defaultClause_(std::move(defaultClause)) {}

  [[nodiscard]] TypePtr type() const override {
    return defaultClause_->type();
  }

  [[nodiscard]] const std::vector<std::shared_ptr<SwitchClause>>&
  switchClauses() const {
    return switchClauses_;
  }

  [[nodiscard]] const ExpressionPtr& defaultClause() const {
    return defaultClause_;
  }
  void accept(ExpressionVisitor& vis) override;

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

class IfThen final : public Expression {
 public:
  IfThen(
      std::vector<std::shared_ptr<IfClause>> ifClauses,
      ExpressionPtr elseClause)
      : ifClauses_(std::move(ifClauses)), elseClause_(std::move(elseClause)) {}

  [[nodiscard]] TypePtr type() const override {
    return elseClause_->type();
  }

  [[nodiscard]] const std::vector<std::shared_ptr<IfClause>>& ifClauses()
      const {
    return ifClauses_;
  }

  [[nodiscard]] const ExpressionPtr& elseClause() const {
    return elseClause_;
  }

  void accept(ExpressionVisitor& vis) override;

 private:
  std::vector<std::shared_ptr<IfClause>> ifClauses_;
  ExpressionPtr elseClause_;
};

class Cast final : public Expression {
 public:
  Cast(ExpressionPtr input, TypePtr type)
      : input_(std::move(input)), type_(std::move(type)){};

  [[nodiscard]] TypePtr type() const override {
    return type_;
  }

  [[nodiscard]] const ExpressionPtr& input() const {
    return input_;
  }

  void accept(ExpressionVisitor& vis) override;

 private:
  ExpressionPtr input_;
  TypePtr type_;
};

class ScalarFunction final : public Expression {
 public:
  ScalarFunction(
      std::shared_ptr<ScalarFunctionImplementation> implementation,
      std::vector<FunctionArgumentPtr> arguments,
      TypePtr outputType)
      : implementation_(std::move(implementation)),
        arguments_(std::move(arguments)),
        outputType_(std::move(outputType)){};

  [[nodiscard]] TypePtr type() const override {
    return outputType_;
  }

  [[nodiscard]] const std::shared_ptr<ScalarFunctionImplementation>&
  implementation() const {
    return implementation_;
  }
  [[nodiscard]] const std::vector<FunctionArgumentPtr>& arguments() const {
    return arguments_;
  }

  void accept(ExpressionVisitor& vis) override;

 private:
  std::shared_ptr<ScalarFunctionImplementation> implementation_;
  std::vector<FunctionArgumentPtr> arguments_;
  TypePtr outputType_;
};

class SingularOrList final : public Expression {
 public:
  SingularOrList(ExpressionPtr condition, std::vector<ExpressionPtr> options)
      : condition_(std::move(condition)), options_(std::move(options)){};

  [[nodiscard]] const ExpressionPtr& condition() const {
    return condition_;
  }

  [[nodiscard]] const std::vector<ExpressionPtr>& options() const {
    return options_;
  }

  [[nodiscard]] TypePtr type() const override {
    return BOOL(true);
  }

  void accept(ExpressionVisitor& vis) override;

 private:
  ExpressionPtr condition_;
  std::vector<ExpressionPtr> options_;
};

struct MultiOrListRecord {
  std::vector<ExpressionPtr> values;
  explicit MultiOrListRecord(std::vector<ExpressionPtr> values)
      : values(std::move(values)){};
};

class MultiOrList final : public Expression {
 public:
  MultiOrList(
      std::vector<ExpressionPtr> conditions,
      std::vector<std::shared_ptr<MultiOrListRecord>> options)
      : conditions_(std::move(conditions)), options_(std::move(options)){};

  [[nodiscard]] const std::vector<ExpressionPtr>& conditions() const {
    return conditions_;
  }

  [[nodiscard]] const std::vector<std::shared_ptr<MultiOrListRecord>>& options()
      const {
    return options_;
  }

  [[nodiscard]] TypePtr type() const override {
    return BOOL(true);
  }

  void accept(ExpressionVisitor& vis) override;

 private:
  std::vector<ExpressionPtr> conditions_;
  std::vector<std::shared_ptr<MultiOrListRecord>> options_;
};

} // namespace io::substrait
