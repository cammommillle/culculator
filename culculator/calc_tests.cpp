#include "calc.h"
#include "gtest/gtest.h"

TEST (Calculator, Semple_binary) {
  ASSERT_EQ(Calculator::Calculate("2 + 2"), 4);
  ASSERT_EQ(Calculator::Calculate("2 - 2"), 0);
  ASSERT_EQ(Calculator::Calculate("3 * 3"), 9);
  ASSERT_EQ(Calculator::Calculate("8 / 2"), 4);
  ASSERT_EQ(Calculator::Calculate("10 % 3"), 1);
}

TEST (Calculator, Semple_unary) {
  ASSERT_EQ(Calculator::Calculate("-7"), -7);
  ASSERT_EQ(Calculator::Calculate("abs(7)"), 7);
  ASSERT_EQ(Calculator::Calculate("abs(-7)"), 7);
}

TEST (Calculator, Semple_grobs) {
  ASSERT_EQ(Calculator::Calculate("7%2 +abs(3 * -4) +(3 * -4)"), 1);
  ASSERT_EQ(Calculator::Calculate("-abs(3)"), -3);
  ASSERT_EQ(Calculator::Calculate("-abs(-(3 * -4))"), -12);
  ASSERT_EQ(Calculator::Calculate("-abs(abs(-4))"), -4);
  ASSERT_EQ(Calculator::Calculate("-abs(abs(4))"), -4);
  ASSERT_EQ(Calculator::Calculate("-(-(-(-7)))"), 7);
  ASSERT_EQ(Calculator::Calculate("abs(abs(-2*abs(-4))-abs(5))"), 3);
  ASSERT_EQ(Calculator::Calculate("157549 % abs( -abs( - 10))"), 9);
}
