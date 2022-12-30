cmake_minimum_required(VERSION 3.20)
project(Laba_5)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(Laba_5_date_and_employee
        date.cpp date.h date_tests.cpp
        employee.cpp employee.h employee_tests.cpp)
add_executable(Laba_5_calc
        calc.cpp calc.h calc_tests.cpp)
target_link_libraries(Laba_5_date_and_employee gtest_main)
target_link_libraries(Laba_5_calc gtest_main)



