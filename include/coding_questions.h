#pragma once
#include <string>
#include <vector>
#include <chrono>
#include <iostream>
class TimerWithExportedValue
{
private:
    unsigned int *m_ref;
    std::chrono::time_point<std::chrono::system_clock> m_created_at;
    std::string m_operation_name;

public:
    explicit TimerWithExportedValue(unsigned int *exportedValue, std::string &&str = "") : m_ref(exportedValue), m_created_at(std::chrono::system_clock::now()), m_operation_name(str)
    {
    }
    TimerWithExportedValue(const TimerWithExportedValue &other) = delete;
    TimerWithExportedValue &operator=(const TimerWithExportedValue &other) = delete;

    ~TimerWithExportedValue()
    {
        auto ml{std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now() - m_created_at).count()};
        *m_ref = ml;
        std::cout << m_operation_name << " requried " << ml << '\n';
    }
};

/**
 * @brief 
 * Question 35 in the large file
 * find a char in an array of size 1^7
 * simple way
 * @param arr 
 * @param arr_size 
 * @param x 
 * @return true 
 * @return false 
 */
[[nodiscard]] bool FindInArray(const unsigned int *arr, std::size_t arr_size, unsigned int x);
/**
 * @brief 
 * Question 35 in the large file
 * find a char in an array of size 1^7
 * better way
 * @param arr 
 * @param arr_size 
 * @param x 
 * @return true 
 * @return false 
 */
[[nodiscard]] bool BetterFindInArray(const unsigned int *arr, std::size_t arr_size, unsigned int x);
/**
 * @brief 
 * Question 35 in the large file
 * find a char in an array of size 1^7
 * slower way 
 * @param arr 
 * @param arr_size 
 * @param x 
 * @return true 
 * @return false 
 */
[[nodiscard]] bool SlowFindInArray(const unsigned int *arr, std::size_t arr_size, unsigned int x);