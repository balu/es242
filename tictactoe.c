/* A program to play tic-tac-toe with the computer. */
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#define BOARD_SIZE (4)

typedef char player_t; // 'X' or 'O'
typedef char board_t[BOARD_SIZE][BOARD_SIZE]; // 'X' or 'O' or '.'

void init_board(board_t board)
{
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            board[row][col] = '.';
        }
    }
}

void print_board(board_t board)
{
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            printf("%3c ", board[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}

int is_full(board_t board)
{
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (board[row][col] == '.') { return 0; }
        }
    }
    return 1;
}

int has_won(board_t board, player_t player)
{
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (board[row][col] != player) {
                goto next_row;
            }
        }
        return 1;
    next_row:
    }

    for (int col = 0; col < BOARD_SIZE; ++col) {
        for (int row = 0; row < BOARD_SIZE; ++row) {
            if (board[row][col] != player) {
                goto next_col;
            }
        }
        return 1;
    next_col:
    }

    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (board[i][i] != player) goto next_diagonal;
    }
    return 1;

next_diagonal:
    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (board[i][BOARD_SIZE-1-i] != player) return 0;
    }
    return 1;
}

player_t other_player(player_t player)
{
    switch (player) {
    case 'X': return 'O';
    case 'O': return 'X';
    default: assert(0);
    }
}

typedef struct {
    int row;
    int col;
    /* -1 for a loss, 0 for a draw, 1 for a win. */
    int score;
} move_t;

#define MAX_ORD (43046720)

uint8_t computed_moves[MAX_ORD+1];

uint8_t encode_move(move_t m)
{
    uint8_t b = 0;

    assert(0 <= m.row && m.row <= 3);
    b |= m.row;

    assert(0 <= m.col && m.col <= 3);
    b |= m.col << 2;

    switch (m.score) {
    case -1: b |= 1 << 6; break;
    case 0: b |= 1 << 5; break;
    case 1: b |= 1 << 4; break;
    }

    return b;
}

move_t decode_move(uint8_t b)
{
    move_t m;

    m.row = b & 0x3;
    m.col = (b & 0xC) >> 2;
    if (b & 0x10) m.score = 1;
    if (b & 0x20) m.score = 0;
    if (b & 0x40) m.score = -1;
    return m;
}

int ord(board_t board)
{
    int p = 1;
    int i = 0;
    int d;

    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            switch (board[row][col]) {
            case 'X': d = 1; break;
            case 'O': d = 2; break;
            case '.': d = 0; break;
            }
            i += d * p;
            p *= 3;
        }
    }

    return i;
}

/*
 * board should be an unfinished game.
 */
move_t best_move(board_t board, player_t player)
{
    move_t response;
    move_t candidate;
    int no_candidate = 1;

    assert(!is_full(board));
    assert(!has_won(board, player));
    assert(!has_won(board, other_player(player)));

    int o = ord(board);

    if (computed_moves[o]) {
        return decode_move(computed_moves[o]);
    }

    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (board[row][col] == '.') {
                board[row][col] = player;
                if (has_won(board, player)) {
                    board[row][col] = '.';
                    computed_moves[o] = encode_move(candidate = (move_t) {
                        .row = row,
                        .col = col,
                        .score = 1
                        });
                    return candidate;
                }
                board[row][col] = '.';
            }
        }
    }

    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (board[row][col] == '.') {
                board[row][col] = player;
                if (is_full(board)) {
                    board[row][col] = '.';
                    computed_moves[o] = encode_move(candidate = (move_t) {
                        .row = row,
                        .col = col,
                        .score = 0
                        });
                    return candidate;
                }
                response = best_move(board, other_player(player));
                board[row][col] = '.';
                if (response.score == -1) {
                    computed_moves[o] = encode_move(candidate = (move_t) {
                        .row = row,
                        .col = col,
                        .score = 1
                        });
                    return candidate;
                } else if (response.score == 0) {
                    candidate = (move_t) {
                        .row = row,
                        .col = col,
                        .score = 0
                    };
                    no_candidate = 0;
                } else { /* response.score == +1 */
                    if (no_candidate) {
                        candidate = (move_t) {
                            .row = row,
                            .col = col,
                            .score = -1
                        };
                        no_candidate = 0;
                    }
                }
            }
        }
    }
    computed_moves[o] = encode_move(candidate);
    return candidate;
}

void print_key()
{
    int i = 0;
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            printf("%3d ", i++);
        }
        printf("\n");
    }
    printf("\n");
}

#if TEST
int main()
{
#if 0
    uint8_t b = encode_move((move_t){ .row = 2, .col = 1, .score = 0 });
    printf("%X %d\n", b, b);
    printf("%X\n", encode_move((move_t){ .row = 3, .col = 3, .score = -1 }));

    move_t m = decode_move(b);
    printf("row = %d, col = %d, score = %d\n", m.row, m.col, m.score);

    board_t board = {
        { 'X', 'O', '.', '.' },
        { 'X', 'O', '.', '.' },
        { 'X', 'O', '.', '.' },
        { 'O', 'X', '.', '.' }
    };

    printf("%d\n", ord(board));
#endif
    board_t board;
    init_board(board);
    best_move(board, 'X');

    int count = 0;
    for (int o = 0; o <= 66; ++o) {
        if (computed_moves[o]) {
            ++count;
        }
    }
    printf("%d positions analyzed.\n", count);

    return 0;
}
#else
int main()
{
    int move, row, col;
    board_t board;
    move_t response;
    player_t current = 'X';

    init_board(board);
    while (1) {
        print_board(board);
        if (current == 'X') {
            print_key();
            printf("Enter your move: ");
            scanf("%d", &move);
            row = move / BOARD_SIZE;
            col = move % BOARD_SIZE;
            assert(board[row][col] == '.');
            board[row][col] = current;
        } else {
            response = best_move(board, current);
            board[response.row][response.col] = current;
        }
        if (has_won(board, current)) {
            print_board(board);
            printf("Player %c has won!\n", current);
            break;
        } else if (is_full(board)) {
            print_board(board);
            printf("Draw.\n");
            break;
        }
        current = other_player(current);
    }

    return 0;
}
#endif
