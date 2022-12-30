#include "employee.h"

Employee::Employee(const std::string& first_name,
                   const std::string& last_name,
                   const Date& birth_date,
                   const Date& hiring_date)
    : first_name_(first_name), last_name_(last_name),
      birth_date_(birth_date), hiring_date_(hiring_date) {}
std::string Employee::GetFullName() const {
  return first_name_ + ' ' + last_name_;
}

std::string Employee::ToString() const {
  return GetFullName() + ' ' +
      DateToString(birth_date_) + " -> hired " +
      DateToString(hiring_date_);
}

int Employee::GetAgeInYears(const Date& curr_date) const {
  if (IsLess(curr_date, birth_date_)) return 0;
  int year_variance = curr_date.year - birth_date_.year;
  if (IsLess(curr_date, Date(birth_date_.day,
                             birth_date_.month,
                             birth_date_.year + year_variance))) {
    year_variance--;
  }
  return year_variance;
}

int Employee::GetTenureInDays(const Date& curr_date) const {
  if (IsLess(curr_date, hiring_date_)) return 0;
  return DateToDays(curr_date) - DateToDays(hiring_date_);
}
