#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <curses.h>

#include <algorithm>
#include <random>

#define MAPSIZE 200

char map[MAPSIZE * MAPSIZE];
int char_x = MAPSIZE / 2;
int char_y = MAPSIZE / 2;

void finish(int sig) {
	endwin();

	exit(0);
}

void init_map() {
	std::default_random_engine generator;
	std::normal_distribution<float> distribution(4., 1.);

	for (int i = 0; i < MAPSIZE; i++) {
		for (int j = 0; j < MAPSIZE; j++) {
			float n = distribution(generator);
			char c;
			if (n <= 0.) c = 'o';
			else if (n <= 1.) c = '^';
			else if (n <= 2.) c = '\'';
			else if (n <= 3.) c = '`';
			else if (n <= 4.) c = ',';
			else if (n <= 5.) c = '.';
			else if (n <= 6.) c = ';';
			else if (n <= 7.) c = '\"';
			else c = '*';

			map[j * MAPSIZE + i] = c;
		}
	}
}

int main() {

	init_map();

	signal(SIGINT, finish);

	initscr();
	keypad(stdscr, TRUE);
	nonl();
	cbreak();
	curs_set(0);

	if (has_colors()) {
		start_color();

		init_pair(1, COLOR_RED, COLOR_BLACK);
	}


	while(1) {
		int sx = char_x - COLS / 2;
		int sy = char_y - LINES / 2;

		for (int j = 0; j < LINES; j++) {
			for (int i = 0; i < COLS; i++) {
				char g = ' ';
				int x = sx + i, y = sy + j;
				if (x >= 0 && x < MAPSIZE && y >= 0 && y < MAPSIZE) {
					g = map[y * MAPSIZE + x];
				}
				move(j, i);

				if (char_x == x && char_y == y) {
					attron(COLOR_PAIR(1));
					addch('@');
					attroff(COLOR_PAIR(1));
				} else {
					addch(g);
				}
			}
		}

		refresh();
		
		int c = getch();
		
		if (c == '.') {
			continue;
 		} else if (c == KEY_UP) {
			char_y = std::max(0, char_y - 1);
 		} else if (c == KEY_DOWN) {
			char_y = std::min(MAPSIZE-1, char_y + 1);
 		} else if (c == KEY_LEFT) {
			char_x = std::max(0, char_x - 1);
 		} else if (c == KEY_RIGHT) {
			char_x = std::min(MAPSIZE-1, char_x + 1);
		} else if (c == 27) {  //escape
			break;
		}
	}

	finish(0);
	return 0;
}
