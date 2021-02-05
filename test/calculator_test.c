#include <stdio.h>
#include <stdlib.h> /* fmalloc, random */
#include <string.h> /* string compares  */
#include <time.h>   /* clock */
#include <math.h>   /* clock */
#include <assert.h> /* asserts */
#include <errno.h> /*errno*/

#include "calculator.h"
#define ABS(X)  ((X) < 0 ? (-1*(X)) : (X))

void FullTests();
int UnitTestFull(const char* s,double expected);
void StageOneTests();


int main()
{   
    StageOneTests();
    FullTests();

    return(0);
}




void StageOneTests()
{

    const char *string = "7^2^2" ;
    const double expected = 2401;
    double result = 0.0;
    status_t error_marker = PROPER_INPUT;
    double epsilon = 0.0000001;
    result = Calculator(string, &error_marker);

    if (ABS(result - expected) > epsilon)
    {
        printf("something went wrong! \nresult for {%s} was %2.2f instead of %2.2f\n",string, result, expected);
    }
    else if(errno == 0)
    {
        printf("result for {%s} was %2.2f\n",string,result);
    }
    assert(errno == 0);

}

int UnitTestFull(const char* s,double expected)
{
    
    
    status_t error_marker = PROPER_INPUT;
    double result = 0.0;
    double epsilon = 0.0000001;
    result = Calculator(s, &error_marker);

        if ((error_marker != 0) || (ABS(result - expected) > epsilon))
        {
            printf("for string: \"%s\" (error code %d) was %4.2f and we wanted %4.2f\n",
                   s,error_marker, result, expected);
            error_marker = ILLEGAL_INPUT;
        }
        assert(errno == 0);
        return (error_marker);
}

void FullTests()
{
    const char *strings[1024]= {"3*3*10","9*10","-75 +150","0.55 + 1.45",
                        "-10 - -3", "10+ 5 * 8 +4 *6 -1",
                        "10+5-20*8+4-1", "10+5-20*8 + 4","10+ 5- 20*8","10+ 5- 20","10 + 5 - 20 *8+4-1",
                        "5-20*8+4", "5 - 5 + 4",
                        "10 *   10 *10", "10*10", "100*100 ","100* 100", "100 *100" ,"+100 * +100",
                        "50*5","50* 5","50 *5","50+1","5*5",
                        "(2 * 5)", "(2+7)","3 * (10-10)", "(10 + 7) *10" , "(5) + (5) + (5)", "(7 + 14)", "5 + ( 1 + 2 + (5 - 10))",
                        "2^4", "0^0", "0^5", "0^-2","-5^2","-5^3", "2^4 + 2^4", "2^2 * 2^3", "-2 ^ ((2^2)+1)",
                        "4/4", "50/12.5", "36 / 18", "10 * (27/(-1*(-3^3)))","\t 1005.58 \t","4^3^2","2^1^3","3^1^2","0^0.5",
                        "5 ++2", "0+0+12","f+0.5" ,"++7",
                        "55 + ( 7 +9", "55 ++ 8","55 + )", "1 +(1+(1+))(5+2)", "2 + (2 +( 2)))", "2 +()", "6*3 +3/0", "6*3 +3/0  ", "(6+7)(7+1)"};
    double answers[] = {90,90,75,2.0, -7.0,73.0,
                        -142, -141,-145,-5, -142,-151,4,
                        1000,100,10000,10000,10000,10000,
                        250,250,250,51,25,
                        10,9,0,170,15,21,3,
                        16, 1,0,0,25,-125, 32,32,-32,
                        1,4,2,10,1005.58,262144,2,3,0.0,
                        7,12,-111,-111,
                        -111,-111,-111,-111,-111,-111,-111,-111,-111};
    size_t num_of_strings = sizeof(answers) / sizeof(*answers);
    size_t i = 0;
    size_t errors = 0;

    for (i = 0; i < num_of_strings; ++i)
    {
        errors += UnitTestFull(strings[i],answers[i]);
    }

    printf("run %ld Complete tests, got %ld errors!\n", num_of_strings, errors);
}

