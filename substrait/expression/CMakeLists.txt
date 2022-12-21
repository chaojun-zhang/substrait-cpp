# SPDX-License-Identifier: Apache-2.0

set(EXPRESSION_SRCS
        Expression.cpp)

add_library(substrait_expression ${EXPRESSION_SRCS})

target_link_libraries(
        substrait_expression
        substrait_function)
