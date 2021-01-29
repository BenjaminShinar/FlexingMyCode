#include <stdio.h>
#include <stdlib.h> /* fmalloc, random */
#include <string.h> /* string compares  */
#include <time.h>   /* clock */
#include <math.h>   /* clock */
#include <assert.h> /* asserts */

#include "bit_array.h"

#define ROWS 8

enum directions
{
    LEFT_UP,
    LEFT_DOWN,
    DOWN_LEFT,
    DOWN_RIGHT,
    RIGHT_DOWN,
    RIGHT_UP,
    UP_RIGHT,
    UP_LEFT,
    DIRECTIONS_COUNT
};

struct movement_count
{
    enum directions move_list;
    int posssible_moves;
};

static int options[ROWS * ROWS][8];

int Game(size_t row_length, int *visits);
void InitOptions();
void PrintBoard(int *visits, size_t row_length);
int CheckBoardForVisits(int *board, size_t row_length);
int FirstCheckLegalMove(int row_length, int current_position, int requested_postion);
int CheckLegalMove(bit_arr_t bit_board, int current_position, enum directions movement);
int MoveKnight(int position, enum directions movement, size_t row_length);
int CMPStruct(const void *internal_data, const void *external_data);
void SortMoves(struct movement_count *moves, bit_arr_t bit_board, int current_position, size_t row_length);

int PlayTurn(bit_arr_t game_board, int next_position, size_t row_length, int *visits);

int main()
{

    int visits[ROWS * ROWS] = {0};
    int result = 0;
    srand(time(0));
    InitOptions();

    result = Game(ROWS, visits);
    (void)result;
    return (0);
}

int Game(size_t row_length, int *visits)
{
    size_t board_size = row_length * row_length;
    bit_arr_t bit_board = (bit_arr_t)0;
    int current_position = rand() % board_size;
    int result = 1;
    memset(visits, 0, sizeof(int) * row_length * row_length);
    result = PlayTurn(bit_board, current_position, row_length, visits);

    return (result);
}

int PlayTurn(bit_arr_t game_board, int next_position, size_t row_length, int *visits)
{
    bit_arr_t modified_board = BitArraySetOn(game_board, next_position);
    size_t turns = BitArrayLutCountOn(modified_board);
    visits[next_position] = turns;
    if (turns == (row_length * row_length))
    {
        puts("success!");
        PrintBoard(visits, ROWS);
        return (0);
    }
    else
    {
        int status = 1;
        int current_position = next_position;
        enum directions next_move;
        struct movement_count minimal_moves[DIRECTIONS_COUNT] = {{LEFT_UP, 0}, {LEFT_DOWN, 0}, {DOWN_LEFT, 0}, {DOWN_RIGHT, 0}, {RIGHT_DOWN, 0}, {RIGHT_UP, 0}, {UP_RIGHT, 0}, {UP_LEFT, 0}};
        size_t num_of_moves = DIRECTIONS_COUNT;
        size_t tries = 0;

        SortMoves(minimal_moves, modified_board, current_position, row_length);
        next_move = minimal_moves[tries].move_list;
        while ((tries < (num_of_moves)) && (status == 1))
        {
            /* */
            if (CheckLegalMove(modified_board, current_position, next_move))
            {
                int next_position = MoveKnight(current_position, next_move, row_length);
                assert(BitArrayIsBitOff(modified_board, next_position));
                status = PlayTurn(modified_board, next_position, row_length, visits);
            }

            ++tries;
            next_move = minimal_moves[tries].move_list;
        }

        return (status);
    }
}

void InitOptions()
{
    int idx = 0;
    enum directions idx_b = 0;
    int next = 0;
    for (idx = 0; idx < ROWS * ROWS; ++idx)
    {
        for (idx_b = 0; idx_b < DIRECTIONS_COUNT; ++idx_b)
        {
            options[idx][idx_b] = -1;
            next = MoveKnight(idx, idx_b, ROWS);
            if (FirstCheckLegalMove(ROWS, idx, next))
            {
                options[idx][idx_b] = next;
            }
        }
    }
}

int MoveKnight(int position, enum directions movement, size_t row_length)
{
    static const int YOffsets[DIRECTIONS_COUNT] = {1, -1, -2, -2, -1, 1, 2, 2};
    static const int XOffsets[DIRECTIONS_COUNT] = {-2, -2, -1, 1, 2, 2, 1, -1};
    int offset = YOffsets[movement] * row_length + XOffsets[movement];
    int new_position = position + offset;
    /* assert((new_position >= 0) && (new_position <= (row_length * number_of_rows)) && "illegal movement request"); */

    return (new_position);
}

int CheckLegalMove(bit_arr_t bit_board, int current_position, enum directions movement)
{
    int next = options[current_position][movement];
    if (next == -1)
    {
        return (0);
    }

    return (BitArrayIsBitOff(bit_board, next));
}

int FirstCheckLegalMove(int row_length, int current_position, int requested_postion)
{
    int current_row = current_position / row_length;
    int next_row = requested_postion / row_length;
    int current_col = (current_position - (current_row * row_length));
    int next_col = (requested_postion - (next_row * row_length));

    if (((current_col == (row_length - 1)) && (next_col == 0)) || ((current_col == 0) && (next_col == (row_length - 1))))
    {
        return (0);
    }
    if (((current_col == 0) && (next_col == (row_length - 1))) || ((current_col == (row_length - 1) && (next_col == 0))))
    {
        return (0);
    }
    if (((current_row - next_row) > 2) || (((current_col - next_col) > 2)))
    {
        return (0);
    }
    if ((((next_row - current_row)) > 2) || ((next_col - current_col) > 2))
    {
        return (0);
    }
    if ((current_row == next_row) || ((current_col == next_col)))
    {
        return (0);
    }
    if ((requested_postion < 0) || (requested_postion >= (int)(row_length * row_length)))
    {
        return (0);
    }

    assert((current_row < row_length) && (current_row >= 0));
    assert((next_row < row_length) && (next_row >= 0));
    assert((current_col < row_length) && (current_col >= 0));
    assert((next_col < row_length) && (next_col >= 0));
    return (1);
}

void PrintBoard(int *visits, size_t row_length)
{
    size_t idx = 0;
    size_t ctr = 0;
    size_t board_size = row_length * row_length;
    while (ctr < board_size)
    {
        printf("|");
        for (idx = 0; idx < row_length; ++idx)
        {
            printf("%2.0d ", visits[ctr + idx]);
        }
        printf("|\n");
        ctr += row_length;
    }
}

void SortMoves(struct movement_count *moves, bit_arr_t bit_board, int current_position, size_t row_length)
{
    size_t idx = 0;
    size_t idx_b = 0;
    for (idx = 0; idx < DIRECTIONS_COUNT; ++idx)
    {
        if (CheckLegalMove(bit_board, current_position, idx))
        {
            int next_position = MoveKnight(current_position, idx, row_length);
            for (idx_b = 0; idx_b < DIRECTIONS_COUNT; ++idx_b)
            {
                moves[idx].posssible_moves += CheckLegalMove(bit_board, next_position, idx_b);
            }
        }
    }
    qsort(moves, DIRECTIONS_COUNT, sizeof(struct movement_count), CMPStruct);
}

int CMPStruct(const void *internal_data, const void *external_data)
{
    struct movement_count *item_a = (struct movement_count *)internal_data;
    struct movement_count *item_b = (struct movement_count *)external_data;
    return (item_a->posssible_moves - item_b->posssible_moves);
}
