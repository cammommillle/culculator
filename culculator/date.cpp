#include "date.h"

std::string DateToString(const Date& date) {
  std::string day_to_str = "00" + std::to_string(date.day);
  day_to_str.erase(0, day_to_str.length() - 2);
  std::string month_to_str = "00" + std::to_string(date.month);
  month_to_str.erase(0, month_to_str.length() - 2);
  std::string year_to_str = "0000" + std::to_string(date.year);
  year_to_str.erase(0, year_to_str.length() - 4);
  return day_to_str + '.' + month_to_str + '.' + year_to_str;
}

bool IsLipYear(const int year) {
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

std::string PrevDate(const Date& date) {
  if (date.day != 1) {
    return DateToString(Date(date.day - 1, date.month, date.year));
  }
  switch (date.month - 1) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10: {
      return DateToString(
          Date(31, date.month - 1, date.year));
    }
    case 4:
    case 6:
    case 9:
    case 11: {
      return DateToString(
          Date(30, date.month - 1, date.year));
    }
    case 2: {
      if (IsLipYear(date.year)) {
        return DateToString(
            Date(29, date.month - 1, date.year));
      } else {
        return DateToString(
            Date(28, date.month - 1, date.year));
      }
    }
    case 0: {
      return DateToString(
          Date(31, 12, date.year - 1));
    }
  }
  return "ERROR";
}

std::string NextDate(const Date& date) {
  switch (date.month) {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10: {
      if (date.day < 31) {
        return DateToString(
            Date(date.day + 1, date.month, date.year));
      } else {
        return DateToString(
            Date(1, date.month + 1, date.year));
      }
    }
    case 4:
    case 6:
    case 9:
    case 11: {
      if (date.day < 30) {
        return DateToString(
            Date(date.day + 1, date.month, date.year));
      } else {
        return DateToString(
            Date(1, date.month + 1, date.year));
      }
    }
    case 2: {
      if (date.day < 28) {
        return DateToString(
            Date(date.day + 1, date.month, date.year));
      } else {
        if (date.day == 29 || !IsLipYear(date.year)) {
          return DateToString(
              Date(1, date.month + 1, date.year));
        } else {
          return DateToString(
              Date(date.day + 1, date.month, date.year));
        }
      }
    }
    case 12: {
      if (date.day < 31) {
        return DateToString(
            Date(date.day + 1, date.month, date.year));
      } else {
        return DateToString(
            Date(1, 1, date.year + 1));
      }
    }
  }
  return "ERROR";
}

bool IsLess(const Date& date_1, const Date& date_2) {
  if (date_1.year == date_2.year) {
    if (date_1.month == date_2.month) {
      return date_1.day < date_2.day;
    } else {
      return date_1.month < date_2.month;
    }
  } else {
    return date_1.year < date_2.year;
  }
}

void ProcessDates(const std::string& input_file_name,
                  const std::string& output_file_name) {
  std::ifstream file_in(input_file_name);
  std::ofstream file_out(output_file_name);
  int count_of_data;
  file_in >> count_of_data;
  for (int i = 0; i < count_of_data; i++) {
    Date current_date;
    file_in >> current_date.day >> current_date.month >> current_date.year;
    file_out << PrevDate(current_date) << ' ';
    file_out << NextDate(current_date) << '\n';
  }
}

int DateToDays(const Date& date) {
  int days_count = date.day;

  // {31, 28/29, 31, 30,  31,  30,  31,  31,  30,  31,  30,  31};
  const std::vector<int> kDaysBeforeMonth
      = {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
  days_count += kDaysBeforeMonth.at(date.month);
  if (IsLipYear(date.year) && date.month > 2) {
    days_count++;
  }

  days_count += date.year * 365;
  days_count += date.year / 4 - date.year / 100 + date.year / 400;

  return days_count;
}
