/* A program to play tic-tac-toe with the computer. */
#include <stdio.h>
#include <assert.h>

#define BOARD_SIZE (3)

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
            printf("%c ", board[row][col]);
        }
        printf("\n");
    }
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

/*
 * board should be an unfinished game.
 */
move_t best_move(board_t board, player_t player)
{
    move_t response;
    move_t candidate;
    int no_candidate = 1;

    // print_board(board); printf("With player %c\n", player);

    assert(!is_full(board));
    assert(!has_won(board, player));
    assert(!has_won(board, other_player(player)));

    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (board[row][col] == '.') {
                board[row][col] = player;
                if (has_won(board, player)) {
                    board[row][col] = '.';
                    return (move_t) {
                        row,
                        col,
                        1
                    };
                }
                board[row][col] = '.';
            }
        }
    }

    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (board[row][col] == '.') {
                board[row][col] = player;
                /*
                 * There is a Heisenbug here.
                 *
                 * We may be calling best_move() on a full board.
                 */
                if (is_full(board)) {
                    board[row][col] = '.';
                    return (move_t) {
                        .row = row,
                        .col = col,
                        .score = 0
                    };
                }
                response = best_move(board, other_player(player));
                board[row][col] = '.';
                if (response.score == -1) {
                    return (move_t) {
                        .row = row,
                        .col = col,
                        .score = 1
                    };
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
    return candidate;
}

void print_key()
{
    int i = 0;
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            printf("%4d ", i++);
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    int move, row, col;
    board_t board;
    move_t response;
    player_t current = 'X';

    init_board(board);
    while (1) {
        print_board(board); printf("\n\n");
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
