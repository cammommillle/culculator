#include "date.h"
#include "gtest/gtest.h"

TEST(Date, Sample_1) {
  const Date date(1, 2, 3333);
  ASSERT_EQ(date.day, 1);
  ASSERT_EQ(date.month, 2);
  ASSERT_EQ(date.year, 3333);
  ASSERT_EQ(DateToString(date), "01.02.3333");
  ASSERT_EQ(NextDate(date), "02.02.3333");
  ASSERT_EQ(PrevDate(date), "31.01.3333");
}

TEST(Date, Sample_2) {
  const Date date(1, 1, 43);
  ASSERT_EQ(DateToString(date), "01.01.0043");
  ASSERT_EQ(NextDate(date), "02.01.0043");
  ASSERT_EQ(PrevDate(date), "31.12.0042");
}

TEST(Date, Sample_3) {
  const Date date(28, 2, 40);
  ASSERT_EQ(DateToString(date), "28.02.0040");
  ASSERT_EQ(NextDate(date), "29.02.0040");
  ASSERT_EQ(PrevDate(date), "27.02.0040");
}

TEST(Date, Sample_4) {
  const Date date(28, 2, 41);
  ASSERT_EQ(DateToString(date), "28.02.0041");
  ASSERT_EQ(NextDate(date), "01.03.0041");
  ASSERT_EQ(PrevDate(date), "27.02.0041");
}

TEST(Date, Sample_5) {
  const Date date(31, 12, 41);
  ASSERT_EQ(DateToString(date), "31.12.0041");
  ASSERT_EQ(NextDate(date), "01.01.0042");
  ASSERT_EQ(PrevDate(date), "30.12.0041");
}

TEST(Date, DateToDays) {
  const Date date_1(1, 1, 3);
  ASSERT_EQ(DateToDays(date_1), 1096);
  const Date date_2(1, 1, 0);
  ASSERT_EQ(DateToDays(date_2), 1);
  const Date date(3, 1, 4);
  ASSERT_EQ(DateToDays(date), 1464);
}



