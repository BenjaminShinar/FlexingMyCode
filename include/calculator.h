#include <stack>

#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__


typedef enum status
{
    PROPER_INPUT,
    ILLEGAL_INPUT,
    ILLEGAL_ALGEBRIC_ACTION,
    MEMORY_ERROR,
    STATUS_COUNT
}status_t;

typedef std::stack<double> stack_t;
double Calculator(const char *str, status_t *status);

#endif /* __CALCULATOR_H__ */
