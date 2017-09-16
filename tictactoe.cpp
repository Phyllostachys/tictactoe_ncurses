#include <cstdio>
#include <curses.h>

class Tictactoe {
public:
    Tictactoe() : player(1), winner(0), quit(false), key_pressed(0) {}

    void init() {
        mainwin = initscr();
        timeout(250);
        clear();
        noecho();
        cbreak();

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = EMPTY;
            }
        }
    }

    void deinit() {
        delwin(mainwin);
        endwin();
        refresh();
    }

    void replay() {
        player = 1;
        winner = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = EMPTY;
            }
        }
        update = true;
    }

    void process_input() {
        if (kbhit()) {
            int ch = getch();
            switch (ch) {
                default: key_pressed = 0; break;
                case 'q': quit = true; break;
                case 'r': replay(); break;
                case '1': key_pressed = 1; break;
                case '2': key_pressed = 2; break;
                case '3': key_pressed = 3; break;
                case '4': key_pressed = 4; break;
                case '5': key_pressed = 5; break;
                case '6': key_pressed = 6; break;
                case '7': key_pressed = 7; break;
                case '8': key_pressed = 8; break;
                case '9': key_pressed = 9; break;
            }
        }
    }

    void tick_logic() {
        if (key_pressed == 0) return;

        int x,y;
        switch (key_pressed) {
            case 1: x = 0; y = 0; break;
            case 2: x = 1; y = 0; break;
            case 3: x = 2; y = 0; break;
            case 4: x = 0; y = 1; break;
            case 5: x = 1; y = 1; break;
            case 6: x = 2; y = 1; break;
            case 7: x = 0; y = 2; break;
            case 8: x = 1; y = 2; break;
            case 9: x = 2; y = 2; break;
        }
        key_pressed = 0;

        if (board[y][x] == EMPTY) {
            board[y][x] = player == 1 ? FIRST_P : SECOND_P;
            player = player == 1 ? 2 : 1;
            update = true;
        }

        // check win horz
        if (board[0][0] != EMPTY && board[0][1] != EMPTY && board[0][2] != EMPTY &&
            board[0][0] == board[0][1] && board[0][1] == board[0][2]) {
            winner = board[0][0];
        }

        else if (board[1][0] != EMPTY && board[1][1] != EMPTY && board[1][2] != EMPTY &&
            board[1][0] == board[1][1] && board[1][1] == board[1][2]) {
            winner = board[1][0];
        }

        else if (board[2][0] != EMPTY && board[2][1] != EMPTY && board[2][2] != EMPTY &&
            board[2][0] == board[2][1] && board[2][1] == board[2][2]) {
            winner = board[2][0];
        }

        // check win vert
        else if (board[0][0] != EMPTY && board[1][0] != EMPTY && board[2][0] != EMPTY &&
            board[0][0] == board[1][0] && board[1][0] == board[2][0]) {
            winner = board[0][0];
        }

        else if (board[0][1] != EMPTY && board[1][1] != EMPTY && board[2][1] != EMPTY &&
            board[0][1] == board[1][1] && board[1][1] == board[2][1]) {
            winner = board[0][1];
        }

        else if (board[0][2] != EMPTY && board[1][2] != EMPTY && board[2][2] != EMPTY &&
            board[0][2] == board[1][2] && board[1][2] == board[2][2]) {
            winner = board[0][2];
        }

        // check win diag
        else if (board[0][0] != EMPTY && board[1][1] != EMPTY && board[2][2] != EMPTY &&
            board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            winner = board[0][0];
        }

        else if (board[2][0] != EMPTY && board[1][1] != EMPTY && board[0][2] != EMPTY &&
            board[2][0] == board[1][1] && board[1][1] == board[0][2]) {
            winner = board[2][0];
        }

    }

    void render() {
        move(0,0);
        if (update) {
            printw("Player %d", player);
            move(0,1);
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    switch (board[i][j]) {
                        default:
                        case EMPTY: mvaddch(i+1, j, '-'); break;
                        case FIRST_P: mvaddch(i+1, j, 'X'); break;
                        case SECOND_P: mvaddch(i+1, j, 'O'); break;
                    }
                    //addch(' ');
                }
            }
            refresh();
            update = false;
        }

        if (winner > 0) {
            move(0,0);
            printw("Player %d wins!", winner);
            refresh();
        }
    }

    bool quit_game() {
        return quit;
    }

private:
    WINDOW *mainwin;
    int player, winner;
    bool quit, update;
    int key_pressed;

    enum {
        EMPTY,
        FIRST_P,
        SECOND_P
    };
    int board[3][3];

    int kbhit() {
        int ch = getch();
        if (ch != ERR) {
            ungetch(ch);
            return 1;
        } else {
            return 0;
        }
    }
};

int main () {
    Tictactoe game;
    game.init();
    while (!game.quit_game()) {
        game.process_input();
        game.tick_logic();
        game.render();
    }
    game.deinit();
    return 0;
}
