#include <stdio.h>
#include <stdlib.h> /* malloc */
#include <string.h> /* string funcs */
#include <math.h>   /* power */
#include <stddef.h> /* size_t */
#include <ctype.h>  /* isdigits*/
#include <assert.h> /* assert */
#include <errno.h>  /*errno*/

#include "calculator.h"

#define MAX(A, B) ((A) > (B) ? (A) : (B))

typedef struct general_structure general_structure_t;
typedef struct function_record function_record_t;
typedef struct operant_package operant_package_t;

typedef void (*operation_func_t)(stack_t *values_stack, stack_t *operand_stack, operant_package_t *package);
typedef double(opernad_calculate_f)(double num1, double num2, status_t *error_marker);

typedef enum
{
	GET_NUM,
	GET_OPERAND,
	FIN,
	FAIL,
	STATES_COUNT
} states_t;

typedef enum
{
	OPENING_BRACKETS,
	ADD_SUB,
	MULTI_DIV,
	POWER_ROOT,
	CLOSING_BRACKETS
} priority_t;

typedef enum
{
	LEFT_ASSOSIACTIVE,
	RIGHT_ASSOSIACTIVE
} assosiativity_t;

typedef enum
{
	FAILURE,
	ZERO,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	PLUS,
	MINUS,
	MULTIPLICATION,
	DIVISION,
	POWER,
	LEFT_BRACKETS,
	RIGHT_BRACKETS,
	WHITE_SPACE,
	NULL_TERMINATOR,
	OPERATORS_COUNT
} numbers_operations_t;

struct general_structure
{
	stack_t *values_stack;
	stack_t *operand_stack;
	operation_func_t func;
	states_t next_state;
	char input;
};

struct function_record
{
	operation_func_t actual_function;
	priority_t priority_rating;
	assosiativity_t assosiative_direction;
	numbers_operations_t symbol_enum;
	char symbol;
	/* 	numbers_operations_t symbol:5;
	priority_t priority_rating: 3;
	assosiativity_t assosiative_direction: 1; 
	can't do bit fields, so fuck it*/
};

struct operant_package
{
	numbers_operations_t operand;
	status_t *error_marker;
	double data;
};

static general_structure_t OPERAND_ACTIONS[OPERATORS_COUNT];
static general_structure_t NUMBERS_ACTIONS[OPERATORS_COUNT];
static numbers_operations_t *states_LUT[STATES_COUNT] = {0};
static general_structure_t *actions_LUT[STATES_COUNT] = {0};
static numbers_operations_t get_operand_lut[256] = {FAILURE};
static numbers_operations_t get_numbers_lut[256] = {FAILURE};

static operant_package_t GetNextCommand(states_t current_state, const char *input, status_t *error_marker, size_t *steps);

static void UpdateOperandNumbersLut(numbers_operations_t operand_lut[256], numbers_operations_t numbers_lut[256]);

static void UpdateNumbersACTIONS(void);
static void AssignGeneralStruct(general_structure_t *OPERAND_ACTIONS, char c, operation_func_t func, states_t next_state);

static void FailOperate(stack_t *values_stack, stack_t *operand_stack, operant_package_t *package);
static void PushNumber(stack_t *values_stack, stack_t *operand_stack, operant_package_t *package);
static void PushOperand(stack_t *values_stack, stack_t *operand_stack, operant_package_t *package);
static void PushBrackets(stack_t *values_stack, stack_t *operand_stack, operant_package_t *package);

static void DoNothing(stack_t *values_stack, stack_t *operand_stack, operant_package_t *package);
static void ResolveAll(stack_t *values_stack, stack_t *operand_stack, operant_package_t *package);
static void ResolveONE(stack_t *values_stack, stack_t *operand_stack, operant_package_t *package);
static void ResolveBrackets(stack_t *values_stack, stack_t *operand_stack, operant_package_t *package);

static void CalculateOperate(stack_t *values_stack, stack_t *operand_stack, status_t *error_marker);
static double CalculatePower(double base, double exponent, status_t *error_marker);
static double CalculatePlus(double addend_a, double addend_b, status_t *error_marker);
static double CalculateMinus(double num_a, double num_b, status_t *error_marker);
static double CalculateMultiplication(double factor_a, double factor_b, status_t *error_marker);
static double CalculateDivision(double dividend, double divisor, status_t *error_marker);

static priority_t GetPriority(numbers_operations_t incoming_operand);
static assosiativity_t GetAssosiativity(numbers_operations_t incoming_operand);
static int IsPossibleNumStart(numbers_operations_t active_operand);

static void UpdateOperandNumbersLut(numbers_operations_t operand_lut[256], numbers_operations_t numbers_lut[256])
{
	operand_lut['+'] = PLUS;
	operand_lut['-'] = MINUS;
	operand_lut['*'] = MULTIPLICATION;
	operand_lut['/'] = DIVISION;
	operand_lut['^'] = POWER;
	operand_lut['('] = LEFT_BRACKETS;
	operand_lut[')'] = RIGHT_BRACKETS;
	operand_lut[' '] = WHITE_SPACE;
	operand_lut['\t'] = WHITE_SPACE;
	operand_lut['\0'] = NULL_TERMINATOR;

	/*numbers lut table!*/
	numbers_lut['+'] = PLUS;
	numbers_lut['-'] = MINUS;
	numbers_lut['0'] = ZERO;
	numbers_lut['1'] = ONE;
	numbers_lut['2'] = TWO;
	numbers_lut['3'] = THREE;
	numbers_lut['4'] = FOUR;
	numbers_lut['5'] = FIVE;
	numbers_lut['6'] = SIX;
	numbers_lut['7'] = SEVEN;
	numbers_lut['8'] = EIGHT;
	numbers_lut['9'] = NINE;
	numbers_lut['('] = LEFT_BRACKETS;
	numbers_lut[')'] = RIGHT_BRACKETS;
	numbers_lut[' '] = WHITE_SPACE;
	numbers_lut['\t'] = WHITE_SPACE;
	numbers_lut['\0'] = NULL_TERMINATOR;
}

static void AssignGeneralStruct(general_structure_t *ACTION_LUT, char c, operation_func_t func, states_t next_state)
{
	ACTION_LUT->input = c;
	ACTION_LUT->func = func;
	ACTION_LUT->next_state = next_state;
}

static void UpdateNumbersACTIONS(void)
{
	size_t idx = 0;
	for (idx = 0; idx < 10; ++idx)
	{
		AssignGeneralStruct(&NUMBERS_ACTIONS[ZERO + idx], (char)'0' + idx, PushNumber, GET_OPERAND);
	}

	AssignGeneralStruct(&OPERAND_ACTIONS[FAILURE], (char)0, FailOperate, FAIL);
	AssignGeneralStruct(&NUMBERS_ACTIONS[PLUS], (char)'+', PushNumber, GET_OPERAND);
	AssignGeneralStruct(&NUMBERS_ACTIONS[MINUS], (char)'-', PushNumber, GET_OPERAND);
	AssignGeneralStruct(&NUMBERS_ACTIONS[WHITE_SPACE], (char)' ', DoNothing, GET_NUM);
	AssignGeneralStruct(&NUMBERS_ACTIONS[WHITE_SPACE], (char)'\t', DoNothing, GET_NUM);
	AssignGeneralStruct(&NUMBERS_ACTIONS[NULL_TERMINATOR], (char)'\0', FailOperate, FAIL);
	AssignGeneralStruct(&NUMBERS_ACTIONS[LEFT_BRACKETS], (char)'(', PushBrackets, GET_NUM);
	AssignGeneralStruct(&NUMBERS_ACTIONS[RIGHT_BRACKETS], (char)')', FailOperate, GET_NUM);
	AssignGeneralStruct(&NUMBERS_ACTIONS[FAILURE], (char)'F', FailOperate, FAIL);

	AssignGeneralStruct(&OPERAND_ACTIONS[WHITE_SPACE], (char)' ', DoNothing, GET_OPERAND);
	AssignGeneralStruct(&OPERAND_ACTIONS[WHITE_SPACE], (char)'\t', DoNothing, GET_OPERAND);
	AssignGeneralStruct(&OPERAND_ACTIONS[NULL_TERMINATOR], (char)'\0', ResolveAll, FIN);
	AssignGeneralStruct(&OPERAND_ACTIONS[FAILURE], (char)'F', FailOperate, FAIL);
	AssignGeneralStruct(&OPERAND_ACTIONS[PLUS], (char)'+', PushOperand, GET_NUM);
	AssignGeneralStruct(&OPERAND_ACTIONS[MINUS], (char)'-', PushOperand, GET_NUM);
	AssignGeneralStruct(&OPERAND_ACTIONS[MULTIPLICATION], (char)'*', PushOperand, GET_NUM);
	AssignGeneralStruct(&OPERAND_ACTIONS[DIVISION], (char)'/', PushOperand, GET_NUM);
	AssignGeneralStruct(&OPERAND_ACTIONS[POWER], (char)'^', PushOperand, GET_NUM);
	AssignGeneralStruct(&OPERAND_ACTIONS[RIGHT_BRACKETS], (char)')', ResolveBrackets, GET_OPERAND);
	AssignGeneralStruct(&OPERAND_ACTIONS[LEFT_BRACKETS], (char)'(', FailOperate, FAIL);
}

double Calculator(const char *s, status_t *error_marker)
{

	char *s_travel = (char *)s;
	double running_result = 0.0;
	stack_t values_stack;
	stack_t operand_stack;

	*error_marker = PROPER_INPUT;

	
	/* this should happen only once */
	if (get_operand_lut['+'] == 0)
	{
		UpdateOperandNumbersLut(get_operand_lut, get_numbers_lut);
		UpdateNumbersACTIONS();
		states_LUT[GET_NUM] = get_numbers_lut;
		states_LUT[GET_OPERAND] = get_operand_lut;
		actions_LUT[GET_NUM] = NUMBERS_ACTIONS;
		actions_LUT[GET_OPERAND] = OPERAND_ACTIONS;
	}
	/* if we managed to build out stacks */
	if (*error_marker == PROPER_INPUT)
	{
		states_t current_state = GET_NUM;
		numbers_operations_t active_operant = PLUS;
		operant_package_t next_cmd_package;
		size_t steps_to_walk = 0;
		running_result = 0.0;

		values_stack.push(running_result);
		operand_stack.push(active_operant);

		/* the state machine */
		while (current_state <= GET_OPERAND)
		{
			steps_to_walk = 1;
			next_cmd_package = GetNextCommand(current_state, s_travel, error_marker, &steps_to_walk);

			active_operant = next_cmd_package.operand;
			actions_LUT[current_state][active_operant].func(&values_stack, &operand_stack, &next_cmd_package);

			if (*error_marker == PROPER_INPUT)
			{
				assert(steps_to_walk > 0);
				current_state = actions_LUT[current_state][active_operant].next_state;
				s_travel = s_travel + steps_to_walk;
			}
			else
			{
				current_state = FAIL;
			}
		}

		if (current_state == FIN)
		{
			assert(values_stack.size() == 1);
			assert(operand_stack.size() == 0);
			running_result = values_stack.top();
		}

		/* do some clean up */
		//StackDestroy(values_stack);
		//values_stack = NULL;
		//StackDestroy(operand_stack);
		//operand_stack = NULL;
	}

	/* return the result */
	return (running_result);
}
/* finished with the calculation! */
/********************************************************************************************************/

/* The actions!! */
/********************************************************************************************************/
/* this gets the next number and the operant! it */

static operant_package_t GetNextCommand(states_t current_state, const char *input, status_t *error_marker, size_t *steps)
{

	char *input_stream = (char *)input;
	char *end_marker = input_stream;
	char input_char = *input_stream;
	int err = 0;
	operant_package_t new_package;
	numbers_operations_t active_operand;

	errno = 0;
	active_operand = states_LUT[current_state][(unsigned char)input_char];
	new_package.operand = active_operand;
	new_package.data = 0.0;
	new_package.error_marker = error_marker;
	*steps = 1;

/* get the number from the stream */
	if (current_state == GET_NUM)
	{
		if (IsPossibleNumStart(active_operand))
		{
			double temp = 0.0;
			temp = strtod(input_stream, &end_marker);
			err = errno;
			if ((err != 0) || (end_marker == input_stream))
			{
				*error_marker = ILLEGAL_INPUT;
				new_package.operand = FAILURE;
				*steps = 1;
			}
			else
			{
				*steps = (end_marker - input_stream);
				new_package.data = temp;
				*error_marker = PROPER_INPUT;
			}
		}
		else if (active_operand == FAILURE)
		{
			*error_marker = ILLEGAL_INPUT;
			*steps = 1;
		}
	}

	return (new_package);
}

static int IsPossibleNumStart(numbers_operations_t active_operand)
{
	return (active_operand <= MINUS);
}

/* this is the big function! */
static void PushOperand(stack_t *values_stack, stack_t *operand_stack, operant_package_t *package)
{
	numbers_operations_t incoming_operand = package->operand;

	numbers_operations_t top_operand = (numbers_operations_t )operand_stack->top();
	priority_t input_priority = GetPriority(incoming_operand);
	priority_t top_priority = GetPriority(top_operand);
	assosiativity_t top_assosiativity = GetAssosiativity(top_operand);

	/* decide wether to push the operator to the stack or to resolve it */
	assert((operand_stack->size() > 0));
	while (((operand_stack->size()) > 1) &&
		   (*package->error_marker == PROPER_INPUT) &&
		   ((top_priority > input_priority) || (((top_priority == input_priority) && (top_assosiativity == LEFT_ASSOSIACTIVE)))))
	{
		ResolveONE(values_stack, operand_stack, package);
		top_operand = (numbers_operations_t)operand_stack->top();
		top_priority = GetPriority(top_operand);
		top_assosiativity = GetAssosiativity(top_operand);
	}

	operand_stack->push(incoming_operand);
	assert(operand_stack->size() > 0);
}

static void PushNumber(stack_t *values_stack, stack_t *operand_stack, operant_package_t *package)
{
	double number = package->data;
	(void)operand_stack;

	*package->error_marker = PROPER_INPUT;
	values_stack->push(number);
}

static void PushBrackets(stack_t *values_stack, stack_t *operand_stack, operant_package_t *package)
{
	numbers_operations_t incoming_operand = package->operand;
	*package->error_marker = PROPER_INPUT;

	(void)values_stack;
	operand_stack->push(incoming_operand);
}

static void FailOperate(stack_t *values_stack, stack_t *operand_stack, operant_package_t *package)
{
	(void)values_stack;
	(void)operand_stack;
	*package->error_marker = ILLEGAL_INPUT;
}

static void DoNothing(stack_t *values_stack, stack_t *operand_stack, operant_package_t *package)
{
	(void)values_stack;
	(void)operand_stack;
	*package->error_marker = PROPER_INPUT;
}

/* functions that resolve expressions */
/* ********************************************************************************************************** */

static void ResolveONE(stack_t *values_stack, stack_t *operand_stack, operant_package_t *package)
{

	assert((operand_stack->size() > 0) && "no opeands in operands stack?");
	assert((values_stack->size() > 1) && "not enough values in values stack?");
	CalculateOperate(values_stack, operand_stack, package->error_marker);
	operand_stack->pop();
}

static void ResolveAll(stack_t *values_stack, stack_t *operand_stack, operant_package_t *package)
{
	while ((values_stack->size() > 1) &&
		   (*package->error_marker == PROPER_INPUT))
	{
		ResolveONE(values_stack, operand_stack, package);
	}
	assert(((operand_stack->size() == 0) || (*package->error_marker != PROPER_INPUT)) && "opernat stack isn't empty?");
	assert(((values_stack->size() == 1) || (*package->error_marker != PROPER_INPUT)) && "values stack doesn't have one element?");
}

static void ResolveBrackets(stack_t *values_stack, stack_t *operand_stack, operant_package_t *package)
{

	/* resolve until you see the left brackets */
	while ((values_stack->size() > 1) &&
		   (operand_stack->size() > 0) &&
		   (*package->error_marker == PROPER_INPUT) &&
		   (((numbers_operations_t)operand_stack->top()) != LEFT_BRACKETS))
	{
		ResolveONE(values_stack, operand_stack, package);
	}

/* check why we've stopped */
	if (*package->error_marker == PROPER_INPUT)
	{
		if (operand_stack->size() == 0)
		{
			*package->error_marker = ILLEGAL_INPUT;
		}
		else if (values_stack->size() == 0)
		{
			*package->error_marker = ILLEGAL_INPUT;
		}
		else if (((numbers_operations_t)operand_stack->top()) == LEFT_BRACKETS)
		{
			operand_stack->pop();
		}
		else if (((numbers_operations_t)operand_stack->top()) != LEFT_BRACKETS)
		{
			*package->error_marker = ILLEGAL_INPUT;
		}
	}
}

/* functions that do calculations */
/* ********************************************************************************************************** */

static void CalculateOperate(stack_t *values_stack, stack_t *operand_stack, status_t *error_marker)
{

	static opernad_calculate_f *functions_LUT[OPERATORS_COUNT] = {0};
	numbers_operations_t which_operant = (numbers_operations_t)operand_stack->top();

	/* this should happen only once! */
	if (functions_LUT[PLUS] != CalculatePlus)
	{
		functions_LUT[PLUS] = CalculatePlus;
		functions_LUT[MINUS] = CalculateMinus;
		functions_LUT[MULTIPLICATION] = CalculateMultiplication;
		functions_LUT[DIVISION] = CalculateDivision;
		functions_LUT[POWER] = CalculatePower;
	}

	assert(values_stack->size() > 1);
	if ((functions_LUT[which_operant] != 0))
	{
		double num1 = 0.0;
		double num2 = 0.0;
		double answer = 0.0;
		num2 = values_stack->top();
		values_stack->pop();
		num1 =values_stack->top();
		values_stack->pop();

		/* call the spesific function!*/
		answer = functions_LUT[which_operant](num1, num2, error_marker);
		if (*error_marker == PROPER_INPUT)
		{
			values_stack->push(answer);
		}
	}
	else
	{
		*error_marker = ILLEGAL_INPUT;
	}
}

static double CalculatePower(double base, double exponent, status_t *error_marker)
{
	double powered = 0.0;
	errno = 0;
	powered = pow(base, exponent);
	if (errno != 0)
	{
		*error_marker = ILLEGAL_ALGEBRIC_ACTION;
		errno = 0;
	}
	return (powered);
}

static double CalculatePlus(double addend_a, double addend_b, status_t *error_marker)
{
	double sum = 0.0;
	(void)error_marker;
	sum = addend_a + addend_b;
	return (sum);
}
static double CalculateMinus(double num_a, double num_b, status_t *error_marker)
{
	double difference = 0.0;
	(void)error_marker;
	difference = num_a - num_b;
	return (difference);
}
static double CalculateMultiplication(double factor_a, double factor_b, status_t *error_marker)
{
	double product = 0.0;
	(void)error_marker;
	product = factor_a * factor_b;
	return (product);
}
static double CalculateDivision(double dividend, double divisor, status_t *error_marker)
{
	double ratio = 0.0;
	if (divisor == 0)
	{
		*error_marker = ILLEGAL_ALGEBRIC_ACTION;
	}
	else
	{
		ratio = dividend / divisor;
	}

	return (ratio);
}

/* functions that give priorities */
/* ********************************************************************************************************** */
static priority_t GetPriority(numbers_operations_t incoming_operand)
{
	static priority_t priority_table[OPERATORS_COUNT];
	/* happends once */
	if (priority_table[PLUS] != ADD_SUB)
	{
		priority_table[PLUS] = ADD_SUB;
		priority_table[MINUS] = ADD_SUB;
		priority_table[MULTIPLICATION] = MULTI_DIV;
		priority_table[DIVISION] = MULTI_DIV;
		priority_table[POWER] = POWER_ROOT;
		priority_table[LEFT_BRACKETS] = OPENING_BRACKETS;
		priority_table[RIGHT_BRACKETS] = CLOSING_BRACKETS;
	}

	return (priority_table[incoming_operand]);
}

static assosiativity_t GetAssosiativity(numbers_operations_t incoming_operand)
{
	static assosiativity_t assosiativity_table[OPERATORS_COUNT];
	/* happends once */
	if (assosiativity_table[POWER] == LEFT_ASSOSIACTIVE)
	{
		assosiativity_table[PLUS] = LEFT_ASSOSIACTIVE;
		assosiativity_table[MINUS] = LEFT_ASSOSIACTIVE;
		assosiativity_table[MULTIPLICATION] = LEFT_ASSOSIACTIVE;
		assosiativity_table[DIVISION] = LEFT_ASSOSIACTIVE;
		assosiativity_table[POWER] = RIGHT_ASSOSIACTIVE;
		assosiativity_table[LEFT_BRACKETS] = LEFT_ASSOSIACTIVE;
		assosiativity_table[RIGHT_BRACKETS] = LEFT_ASSOSIACTIVE;
	}

	return (assosiativity_table[incoming_operand]);
}
