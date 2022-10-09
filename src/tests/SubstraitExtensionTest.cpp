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


#include <gtest/gtest.h>

#include "iostream"
#include "../SubstraitExtension.h"

using namespace io::substrait;

class SubstraitExtensionTest : public ::testing::Test {
protected:
    void testLookupFunction(
            const std::string &name,
            const std::vector<SubstraitTypePtr> &arguments,
            const std::string &matchedSignature) {
        const auto &functionOption = registry_->lookupFunction(name, arguments);

        ASSERT_TRUE(functionOption != nullptr);
        ASSERT_EQ(functionOption->signature(), matchedSignature);
    }

    /// Load registry from substrait core extension YAML files.
    SubstraitExtensionPtr registry_ = SubstraitExtension::load();
};

TEST_F(SubstraitExtensionTest, comparison_function) {
    testLookupFunction("lt", {kI8(), kI8()}, "lt:any1_any1");
    testLookupFunction("lt", {kI16(), kI16()}, "lt:any1_any1");
    testLookupFunction("lt", {kI32(), kI32()}, "lt:any1_any1");
    testLookupFunction("lt", {kI64(), kI64()}, "lt:any1_any1");
    testLookupFunction("lt", {kFp32(), kFp32()}, "lt:any1_any1");
    testLookupFunction("lt", {kFp64(), kFp64()}, "lt:any1_any1");

    testLookupFunction(
            "between", {kI8(), kI8(), kI8()}, "between:any1_any1_any1");
}

TEST_F(SubstraitExtensionTest, arithmetic_function) {
    testLookupFunction("add", {kI8(), kI8()}, "add:opt_i8_i8");
    testLookupFunction(
            "divide",
            {
                    kFp32(),
                    kFp32(),
            },
            "divide:opt_opt_opt_fp32_fp32");

    testLookupFunction(
            "avg", {SubstraitType::decode("struct<fp64,i64>")}, "avg:opt_fp32");
}

TEST_F(SubstraitExtensionTest, boolean_function) {
    testLookupFunction("and", {kBool(), kBool()}, "and:bool");
    testLookupFunction("or", {kBool(), kBool()}, "or:bool");
    testLookupFunction("not", {kBool()}, "not:bool");
    testLookupFunction(
            "xor", {kBool(), kBool()}, "xor:bool_bool");
}

TEST_F(SubstraitExtensionTest, string_function) {
    testLookupFunction(
            "like", {kString(), kString()}, "like:opt_str_str");
}

TEST_F(SubstraitExtensionTest, unknowLookup) {
    auto unknown = registry_->lookupType("unknown");
    ASSERT_TRUE(unknown);
    ASSERT_EQ(unknown->name, "unknown");
}
