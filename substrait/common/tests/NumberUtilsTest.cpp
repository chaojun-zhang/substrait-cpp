/* SPDX-License-Identifier: Apache-2.0 */

#include <gtest/gtest.h>
#include "substrait/common/NumberUtils.h"

using namespace io::substrait::common;

class NumberUtilsTest : public ::testing::Test {};

TEST_F(NumberUtilsTest, isNumber) {
  ASSERT_TRUE(NumberUtils::is_number("1"));
  ASSERT_TRUE(NumberUtils::is_number("0"));
  ASSERT_FALSE(NumberUtils::is_number("TEXT"));
  ASSERT_FALSE(NumberUtils::is_number(""));
}
