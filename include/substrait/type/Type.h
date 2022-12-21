/* SPDX-License-Identifier: Apache-2.0 */

#pragma once

#include <iostream>
#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

#include "substrait/common/NumberUtils.h"

namespace io::substrait {

enum class TypeKind : int8_t {
  kBool = 1,
  kI8 = 2,
  kI16 = 3,
  kI32 = 4,
  kI64 = 5,
  kFp32 = 6,
  kFp64 = 7,
  kString = 8,
  kBinary = 9,
  kTimestamp = 10,
  kDate = 11,
  kTime = 12,
  kIntervalYear = 13,
  kIntervalDay = 14,
  kTimestampTz = 15,
  kUuid = 16,
  kFixedChar = 17,
  kVarchar = 18,
  kFixedBinary = 19,
  kDecimal = 20,
  kStruct = 21,
  kList = 22,
  kMap = 23,
  KIND_NOT_SET = 0,
};

template <TypeKind KIND>
struct TypeTraits {};

template <>
struct TypeTraits<TypeKind::kBool> {
  static constexpr const char* signature = "bool";
  static constexpr const char* typeString = "boolean";
};

template <>
struct TypeTraits<TypeKind::kI8> {
  static constexpr const char* signature = "i8";
  static constexpr const char* typeString = "i8";
};

template <>
struct TypeTraits<TypeKind::kI16> {
  static constexpr const char* signature = "i16";
  static constexpr const char* typeString = "i16";
};

template <>
struct TypeTraits<TypeKind::kI32> {
  static constexpr const char* signature = "i32";
  static constexpr const char* typeString = "i32";
};

template <>
struct TypeTraits<TypeKind::kI64> {
  static constexpr const char* signature = "i64";
  static constexpr const char* typeString = "i64";
};

template <>
struct TypeTraits<TypeKind::kFp32> {
  static constexpr const char* signature = "fp32";
  static constexpr const char* typeString = "fp32";
};

template <>
struct TypeTraits<TypeKind::kFp64> {
  static constexpr const char* signature = "fp64";
  static constexpr const char* typeString = "fp64";
};

template <>
struct TypeTraits<TypeKind::kString> {
  static constexpr const char* signature = "str";
  static constexpr const char* typeString = "string";
};

template <>
struct TypeTraits<TypeKind::kBinary> {
  static constexpr const char* signature = "vbin";
  static constexpr const char* typeString = "binary";
};

template <>
struct TypeTraits<TypeKind::kTimestamp> {
  static constexpr const char* signature = "ts";
  static constexpr const char* typeString = "timestamp";
};

template <>
struct TypeTraits<TypeKind::kTimestampTz> {
  static constexpr const char* signature = "tstz";
  static constexpr const char* typeString = "timestamp_tz";
};

template <>
struct TypeTraits<TypeKind::kDate> {
  static constexpr const char* signature = "date";
  static constexpr const char* typeString = "date";
};

template <>
struct TypeTraits<TypeKind::kTime> {
  static constexpr const char* signature = "time";
  static constexpr const char* typeString = "time";
};

template <>
struct TypeTraits<TypeKind::kIntervalYear> {
  static constexpr const char* signature = "iyear";
  static constexpr const char* typeString = "interval_year";
};

template <>
struct TypeTraits<TypeKind::kIntervalDay> {
  static constexpr const char* signature = "iday";
  static constexpr const char* typeString = "interval_day";
};

template <>
struct TypeTraits<TypeKind::kUuid> {
  static constexpr const char* signature = "uuid";
  static constexpr const char* typeString = "uuid";
};

template <>
struct TypeTraits<TypeKind::kFixedChar> {
  static constexpr const char* signature = "fchar";
  static constexpr const char* typeString = "fixedchar";
};

template <>
struct TypeTraits<TypeKind::kVarchar> {
  static constexpr const char* signature = "vchar";
  static constexpr const char* typeString = "varchar";
};

template <>
struct TypeTraits<TypeKind::kFixedBinary> {
  static constexpr const char* signature = "fbin";
  static constexpr const char* typeString = "fixedbinary";
};

template <>
struct TypeTraits<TypeKind::kDecimal> {
  static constexpr const char* signature = "dec";
  static constexpr const char* typeString = "decimal";
};

template <>
struct TypeTraits<TypeKind::kStruct> {
  static constexpr const char* signature = "struct";
  static constexpr const char* typeString = "struct";
};

template <>
struct TypeTraits<TypeKind::kList> {
  static constexpr const char* signature = "list";
  static constexpr const char* typeString = "list";
};

template <>
struct TypeTraits<TypeKind::kMap> {
  static constexpr const char* signature = "map";
  static constexpr const char* typeString = "map";
};

class TypeVisitor;

class ParameterizedType {
 public:
  explicit ParameterizedType(bool nullable = false) : nullable_(nullable) {}

  [[nodiscard]] virtual std::string signature() const = 0;

  [[nodiscard]] virtual TypeKind kind() const = 0;

  /// Deserialize substrait raw type string into Substrait extension  type.
  /// @param rawType - substrait extension raw string type
  static std::shared_ptr<const ParameterizedType> decode(
      const std::string& rawType){
    return decode(rawType, true);
  }

  static std::shared_ptr<const ParameterizedType> decode(
      const std::string& rawType,bool isParameterized);

  [[nodiscard]] const bool& nullable() const {
    return nullable_;
  }

  [[nodiscard]] bool nullMatch(
      const std::shared_ptr<const ParameterizedType>& type) const {
    return nullable() || nullable() == type->nullable();
  }
  /// Test type is a Wildcard type or not.
  [[nodiscard]] virtual bool isWildcard() const {
    return false;
  }

  [[nodiscard]] virtual bool isMatch(
      const std::shared_ptr<const ParameterizedType>& type) const = 0;

  virtual void accept(TypeVisitor& visitor) = 0;

 private:
  const bool nullable_;
};

using ParameterizedTypePtr = std::shared_ptr<const ParameterizedType>;

class Type : public ParameterizedType {
 public:
  explicit Type(bool nullable = false) : ParameterizedType(nullable) {}
};

using TypePtr = std::shared_ptr<const Type>;

/// Types used in function argument declarations.
template <TypeKind Kind, typename Visitable>
class TypeBase : public Type {
 public:
  explicit TypeBase(bool nullable = false) : Type(nullable) {}

  [[nodiscard]] std::string signature() const override {
    return TypeTraits<Kind>::signature;
  }

  [[nodiscard]] TypeKind kind() const override {
    return Kind;
  }

  [[nodiscard]] bool isMatch(
      const std::shared_ptr<const ParameterizedType>& type) const override {
    return kind() == type->kind() && nullMatch(type);
  }

  void accept(TypeVisitor& v) override;
};

template <TypeKind Kind, typename Visitable>
class ScalarType : public TypeBase<Kind, Visitable> {
 public:
  explicit ScalarType(bool nullable) : TypeBase<Kind, Visitable>(nullable) {}
};

class Decimal : public TypeBase<TypeKind::kDecimal, Decimal> {
 public:
  Decimal(int precision, int scale, bool nullable = false)
      : TypeBase<TypeKind::kDecimal, Decimal>(nullable),
        precision_(precision),
        scale_(scale) {}

  [[nodiscard]] std::string signature() const override;

  [[nodiscard]] const int& precision() const {
    return precision_;
  }

  [[nodiscard]] const int& scale() const {
    return scale_;
  }

  [[nodiscard]] bool isMatch(
      const std::shared_ptr<const ParameterizedType>& type) const override;

 private:
  const int precision_;
  const int scale_;
};

class FixedBinary : public TypeBase<TypeKind::kFixedBinary, FixedBinary> {
 public:
  explicit FixedBinary(int length, bool nullable = false)
      : TypeBase<TypeKind::kFixedBinary, FixedBinary>(nullable),
        length_(length) {}

  [[nodiscard]] const int& length() const {
    return length_;
  }

  [[nodiscard]] std::string signature() const override;

  [[nodiscard]] bool isMatch(
      const std::shared_ptr<const ParameterizedType>& type) const override;

 private:
  const int length_;
};

class FixedChar : public TypeBase<TypeKind::kFixedChar, FixedChar> {
 public:
  explicit FixedChar(int length, bool nullable = false)
      : TypeBase<TypeKind::kFixedChar, FixedChar>(nullable), length_(length){};

  [[nodiscard]] const int& length() const {
    return length_;
  }

  [[nodiscard]] std::string signature() const override;

  [[nodiscard]] bool isMatch(
      const std::shared_ptr<const ParameterizedType>& type) const override;

 private:
  const int length_;
};

class Varchar : public TypeBase<TypeKind::kVarchar, Varchar> {
 public:
  explicit Varchar(int length, bool nullable = false)
      : TypeBase<TypeKind::kVarchar, Varchar>(nullable), length_(length){};

  [[nodiscard]] const int& length() const {
    return length_;
  }

  [[nodiscard]] std::string signature() const override;

  [[nodiscard]] bool isMatch(
      const std::shared_ptr<const ParameterizedType>& type) const override;

 private:
  const int length_;
};

class List : public TypeBase<TypeKind::kList, List> {
 public:
  explicit List(TypePtr elementType, bool nullable = false)
      : TypeBase<TypeKind::kList, List>(nullable),
        elementType_(std::move(elementType)){};

  [[nodiscard]] const TypePtr& elementType() const {
    return elementType_;
  }

  [[nodiscard]] std::string signature() const override;

  [[nodiscard]] bool isMatch(
      const std::shared_ptr<const ParameterizedType>& type) const override;

 private:
  const TypePtr elementType_;
};

class Struct : public TypeBase<TypeKind::kStruct, Struct> {
 public:
  explicit Struct(std::vector<TypePtr> types, bool nullable = false)
      : TypeBase<TypeKind::kStruct, Struct>(nullable),
        children_(std::move(types)) {}

  [[nodiscard]] std::string signature() const override;

  [[nodiscard]] const std::vector<TypePtr>& children() const {
    return children_;
  }

  [[nodiscard]] bool isMatch(
      const std::shared_ptr<const ParameterizedType>& type) const override;

 private:
  const std::vector<TypePtr> children_;
};

class Map : public TypeBase<TypeKind::kMap, Map> {
 public:
  Map(TypePtr keyType, TypePtr valueType, bool nullable = false)
      : TypeBase<TypeKind::kMap, Map>(nullable),
        keyType_(std::move(keyType)),
        valueType_(std::move(valueType)) {}

  [[nodiscard]] const TypePtr& keyType() const {
    return keyType_;
  }

  [[nodiscard]] const TypePtr& valueType() const {
    return valueType_;
  }

  [[nodiscard]] std::string signature() const override;

  [[nodiscard]] bool isMatch(
      const std::shared_ptr<const ParameterizedType>& type) const override;

 private:
  const TypePtr keyType_;
  const TypePtr valueType_;
};

template <typename Visitable>
class ParameterizedTypeBase : public ParameterizedType {
 public:
  explicit ParameterizedTypeBase(bool nullable = false)
      : ParameterizedType(nullable) {}

  void accept(TypeVisitor& visitor) override;
};

/// A string literal type can present the 'any1' or 'T','P1'.
class StringLiteral : public ParameterizedTypeBase<StringLiteral> {
 public:
  explicit StringLiteral(std::string value)
      : ParameterizedTypeBase(false), value_(std::move(value)) {}

  [[nodiscard]] std::string signature() const override {
    return value_;
  }

  [[nodiscard]] TypeKind kind() const override {
    return TypeKind::KIND_NOT_SET;
  }

  [[nodiscard]] const std::string& value() const {
    return value_;
  }

  [[nodiscard]] bool isWildcard() const override {
    return !common::NumberUtils::is_number(value_);
  }

  [[nodiscard]] bool isMatch(
      const std::shared_ptr<const ParameterizedType>& type) const override;

 private:
  const std::string value_;
};

using StringLiteralPtr = std::shared_ptr<const StringLiteral>;

class ParameterizedDecimal
    : public ParameterizedTypeBase<ParameterizedDecimal> {
 public:
  ParameterizedDecimal(
      StringLiteralPtr precision,
      StringLiteralPtr scale,
      bool nullable = false)
      : ParameterizedTypeBase(nullable),
        precision_(std::move(precision)),
        scale_(std::move(scale)) {}

  [[nodiscard]] std::string signature() const override;

  [[nodiscard]] const StringLiteralPtr& precision() const {
    return precision_;
  }

  [[nodiscard]] TypeKind kind() const override {
    return TypeKind::kDecimal;
  }

  [[nodiscard]] const StringLiteralPtr& scale() const {
    return scale_;
  }

  [[nodiscard]] bool isMatch(
      const std::shared_ptr<const ParameterizedType>& type) const override;

 private:
  StringLiteralPtr precision_;
  StringLiteralPtr scale_;
};

class ParameterizedFixedBinary
    : public ParameterizedTypeBase<ParameterizedFixedBinary> {
 public:
  explicit ParameterizedFixedBinary(
      StringLiteralPtr length,
      bool nullable = false)
      : ParameterizedTypeBase(nullable), length_(std::move(length)) {}

  [[nodiscard]] const StringLiteralPtr& length() const {
    return length_;
  }

  [[nodiscard]] TypeKind kind() const override {
    return TypeKind::kFixedBinary;
  }

  [[nodiscard]] std::string signature() const override;

  [[nodiscard]] bool isMatch(
      const std::shared_ptr<const ParameterizedType>& type) const override;

 private:
  const StringLiteralPtr length_;
};

class ParameterizedFixedChar
    : public ParameterizedTypeBase<ParameterizedFixedChar> {
 public:
  explicit ParameterizedFixedChar(
      StringLiteralPtr length,
      bool nullable = false)
      : ParameterizedTypeBase(nullable), length_(std::move(length)) {}

  [[nodiscard]] const StringLiteralPtr& length() const {
    return length_;
  }

  [[nodiscard]] TypeKind kind() const override {
    return TypeKind::kFixedChar;
  }

  [[nodiscard]] std::string signature() const override;

  [[nodiscard]] bool isMatch(
      const std::shared_ptr<const ParameterizedType>& type) const override;

 private:
  const StringLiteralPtr length_;
};

class ParameterizedVarchar
    : public ParameterizedTypeBase<ParameterizedVarchar> {
 public:
  explicit ParameterizedVarchar(StringLiteralPtr length, bool nullable = false)
      : ParameterizedTypeBase(nullable), length_(std::move(length)) {}

  [[nodiscard]] const StringLiteralPtr& length() const {
    return length_;
  }

  [[nodiscard]] TypeKind kind() const override {
    return TypeKind::kVarchar;
  }

  [[nodiscard]] std::string signature() const override;

  [[nodiscard]] bool isMatch(
      const std::shared_ptr<const ParameterizedType>& type) const override;

 private:
  const StringLiteralPtr length_;
};

class ParameterizedList : public ParameterizedTypeBase<ParameterizedList> {
 public:
  explicit ParameterizedList(
      ParameterizedTypePtr elementType,
      bool nullable = false)
      : ParameterizedTypeBase(nullable),
        elementType_(std::move(elementType)){};

  [[nodiscard]] const ParameterizedTypePtr& elementType() const {
    return elementType_;
  }

  [[nodiscard]] TypeKind kind() const override {
    return TypeKind::kList;
  }

  [[nodiscard]] std::string signature() const override;

  [[nodiscard]] bool isMatch(
      const std::shared_ptr<const ParameterizedType>& type) const override;

 private:
  const ParameterizedTypePtr elementType_;
};

class ParameterizedStruct
    : public ParameterizedTypeBase<ParameterizedStruct> {
 public:
  explicit ParameterizedStruct(
      std::vector<ParameterizedTypePtr> types,
      bool nullable = false)
      : ParameterizedTypeBase(nullable), children_(std::move(types)) {}

  [[nodiscard]] std::string signature() const override;

  [[nodiscard]] const std::vector<ParameterizedTypePtr>& children() const {
    return children_;
  }

  [[nodiscard]] TypeKind kind() const override {
    return TypeKind::kStruct;
  }

  [[nodiscard]] bool isMatch(
      const std::shared_ptr<const ParameterizedType>& type) const override;

 private:
  const std::vector<ParameterizedTypePtr> children_;
};

class ParameterizedMap : public ParameterizedTypeBase<ParameterizedMap> {
 public:
  ParameterizedMap(
      ParameterizedTypePtr keyType,
      ParameterizedTypePtr valueType,
      bool nullable = false)
      : ParameterizedTypeBase(nullable),
        keyType_(std::move(keyType)),
        valueType_(std::move(valueType)) {}

  [[nodiscard]] const ParameterizedTypePtr& keyType() const {
    return keyType_;
  }

  [[nodiscard]] TypeKind kind() const override {
    return TypeKind::kMap;
  }
  [[nodiscard]] const ParameterizedTypePtr& valueType() const {
    return valueType_;
  }

  [[nodiscard]] std::string signature() const override;

  [[nodiscard]] bool isMatch(
      const std::shared_ptr<const ParameterizedType>& type) const override;

 private:
  const ParameterizedTypePtr keyType_;
  const ParameterizedTypePtr valueType_;
};

class Bool : public ScalarType<TypeKind::kBool, Bool> {
 public:
  using ScalarType::ScalarType;
};

class TinyInt : public ScalarType<TypeKind::kI8, TinyInt> {
 public:
  using ScalarType::ScalarType;
};

class SmallInt : public ScalarType<TypeKind::kI16, SmallInt> {
 public:
  using ScalarType::ScalarType;
};

class Integer : public ScalarType<TypeKind::kI32, Integer> {
 public:
  using ScalarType::ScalarType;
};

class BigInt : public ScalarType<TypeKind::kI64, BigInt> {
 public:
  using ScalarType::ScalarType;
};
class Float : public ScalarType<TypeKind::kFp32, Float> {
 public:
  using ScalarType::ScalarType;
};
class Double : public ScalarType<TypeKind::kFp64, Double> {
 public:
  using ScalarType::ScalarType;
};
class String : public ScalarType<TypeKind::kString, String> {
 public:
  using ScalarType::ScalarType;
};
class Binary : public ScalarType<TypeKind::kBinary, Binary> {
 public:
  using ScalarType::ScalarType;
};

class Timestamp : public ScalarType<TypeKind::kTimestamp, Timestamp> {
 public:
  using ScalarType::ScalarType;
};
class TimestampTz : public ScalarType<TypeKind::kTimestampTz, TimestampTz> {
 public:
  using ScalarType::ScalarType;
};
class Date : public ScalarType<TypeKind::kDate, Date> {
 public:
  using ScalarType::ScalarType;
};
class Time : public ScalarType<TypeKind::kTime, Time> {
 public:
  using ScalarType::ScalarType;
};
class IntervalYear : public ScalarType<TypeKind::kIntervalYear, IntervalYear> {
 public:
  using ScalarType::ScalarType;
};
class IntervalDay : public ScalarType<TypeKind::kIntervalDay, IntervalDay> {
 public:
  using ScalarType::ScalarType;
};
class Uuid : public ScalarType<TypeKind::kUuid, Uuid> {
 public:
  using ScalarType::ScalarType;
};

std::shared_ptr<const Bool> BOOL(bool nullable = false);

std::shared_ptr<const TinyInt> TINYINT(bool nullable = false);

std::shared_ptr<const SmallInt> SMALLINT(bool nullable = false);

std::shared_ptr<const Integer> INTEGER(bool nullable = false);

std::shared_ptr<const BigInt> BIGINT(bool nullable = false);

std::shared_ptr<const Float> FLOAT(bool nullable = false);

std::shared_ptr<const Double> DOUBLE(bool nullable = false);

std::shared_ptr<const String> STRING(bool nullable = false);

std::shared_ptr<const Binary> BINARY(bool nullable = false);

std::shared_ptr<const Timestamp> TIMESTAMP(bool nullable = false);

std::shared_ptr<const TimestampTz> TIMESTAMP_TZ(bool nullable = false);

std::shared_ptr<const Date> DATE(bool nullable = false);

std::shared_ptr<const Time> TIME(bool nullable = false);

std::shared_ptr<const IntervalYear> INTERVAL_YEAR(bool nullable = false);

std::shared_ptr<const IntervalDay> INTERVAL_DAY(bool nullable = false);

std::shared_ptr<const Uuid> UUID(bool nullable = false);

std::shared_ptr<const Decimal>
DECIMAL(int precision, int scale, bool nullable = false);

std::shared_ptr<const Varchar> VARCHAR(int len, bool nullable = false);

std::shared_ptr<const FixedChar> FIXED_CHAR(int len, bool nullable = false);

std::shared_ptr<const FixedBinary> FIXED_BINARY(int len, bool nullable = false);

std::shared_ptr<const List> LIST(
    const TypePtr& elementType,
    bool nullable = false);

std::shared_ptr<const Map>
MAP(const TypePtr& keyType, const TypePtr& valueType, bool nullable = false);

std::shared_ptr<const Struct> STRUCT(
    const std::vector<TypePtr>& children,
    bool nullable = false);

} // namespace io::substrait
