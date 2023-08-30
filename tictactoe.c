/* A program to play tic-tac-toe with the computer. */
#include <stdio.h>
#include <assert.h>

typedef char player_t; // 'X' or 'O'
typedef char board_t[3][3]; // 'X' or 'O' or '.'

void init_board(board_t board)
{
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            board[row][col] = '.';
        }
    }
}

void print_board(board_t board)
{
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            printf("%c ", board[row][col]);
        }
        printf("\n");
    }
}

int is_full(board_t board)
{
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (board[row][col] == '.') { return 0; }
        }
    }
    return 1;
}

int has_won(board_t board, player_t player)
{
    for (int row = 0; row < 3; ++row) {
        if ((board[row][0] == player) &&
            (board[row][1] == player) &&
            (board[row][2] == player)) {
            return 1;
        }
    }

    for (int col = 0; col < 3; ++col) {
        if ((board[0][col] == player) &&
            (board[1][col] == player) &&
            (board[2][col] == player)) {
            return 1;
        }
    }

    if ((board[0][0] == player) &&
        (board[1][1] == player) &&
        (board[2][2] == player)) {
        return 1;
    }

    if ((board[0][2] == player) &&
        (board[1][1] == player) &&
        (board[2][0] == player)) {
        return 1;
    }

    return 0;
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

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
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

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
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
            printf("0 1 2\n3 4 5\n6 7 8\n");
            printf("Enter your move: ");
            scanf("%d", &move);
            row = move / 3;
            col = move % 3;
            assert(board[row][col] == '.');
            board[row][col] = current;
        } else {
            response = best_move(board, current);
            // printf("Response is (%d, %d)\n", response.row, response.col);
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
