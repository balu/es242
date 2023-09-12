/* Implement connect 4 on a 5 (columns) x 4 (rows) board. */
enum {
    EMPTY = 0,
    RED,
    BLUE,
};

typedef char board_t[4][5];
typedef char player_t;

int has_won(board_t board, player_t player)
{}

int is_full(board_t board)
{}

typedef struct {
    int col;
    int score;
} move_t;

move_t best_move(board_t board, player_t player)
{}

void print_board(board_t board)
{}

int main()
{
    /* Your game play logic. */
    /* The user should have the option to select red or blue player. */
    return 0;
}
