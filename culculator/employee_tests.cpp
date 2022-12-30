#include "employee.h"
#include "gtest/gtest.h"

TEST(Employee, Sample_1) {
  const Employee employee(
      "Ivan", "Ivanov",
      Date(1, 9, 2019),
      Date(9, 10, 2019));
  ASSERT_EQ(employee.GetFullName(), "Ivan Ivanov");
  ASSERT_EQ(employee.ToString(),
            "Ivan Ivanov 01.09.2019 -> hired 09.10.2019");
  ASSERT_EQ(employee.GetAgeInYears(Date(10, 10, 2019)), 0);
  ASSERT_EQ(employee.GetAgeInYears(Date(10, 10, 2020)), 1);
  ASSERT_EQ(employee.GetTenureInDays(Date(11, 10, 2019)), 2);
}

TEST(Employee, Sample_2) {
  const Employee employee(
      "Vova", "Runets",
      Date(23, 12, 2003),
      Date(23, 10, 2021));
  ASSERT_EQ(employee.GetFullName(), "Vova Runets");
  ASSERT_EQ(employee.ToString(),
            "Vova Runets 23.12.2003 -> hired 23.10.2021");
  ASSERT_EQ(employee.GetAgeInYears(Date(10, 10, 2003)), 0);
  ASSERT_EQ(employee.GetAgeInYears(Date(23, 12, 2021)), 18);
  ASSERT_EQ(employee.GetAgeInYears(Date(1, 1, 2021)), 17);
  ASSERT_EQ(employee.GetTenureInDays(Date(11, 10, 2021)), 0);
  ASSERT_EQ(employee.GetTenureInDays(Date(27, 10, 2022)), 365 + 4);
  ASSERT_EQ(employee.GetTenureInDays(Date(22, 10, 2023)), 729);
}