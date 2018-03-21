#include <iostream>
#include <fstream>
#include <string>
#include <curses.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <vector>
#include <sstream>
#include "parser_driver.h"
#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>

using namespace std;

string interpret(string s) {
  string ret;
  ofstream myfile;

  myfile.open (".tmp_to_read_187.txt");
  myfile << s;
  myfile.close();

  stringstream sstrm;
  parser_driver driver (".tmp_to_read_187.txt");
  shared_ptr<Exp> expr = driver.parse(0);
  sstrm << expr->eval();

  remove(".tmp_to_read_187.txt");
  return sstrm.str();
}

void curses_init() {
  initscr();
  keypad(stdscr, TRUE);
  cbreak();
  scrollok(stdscr, TRUE);
  noecho();
}

void curses_cleanup() {
  endwin();
}

void quit() {
  curses_cleanup();
  exit(0);
}
int main(void) {
  curses_init();
  addstr("Welcome to this shitty language's repl!\n");
  addstr("Keep in mind that state does not persist across calls!\n");
  addstr("Try not to have too much fun with this bad boy...\n");
  addstr("Press <esc> to exit.\n");
  //wrefresh(stdscr);
  string curline;
  std::vector<string> all_lines;

  int line_num = 0;
  int last_line = 0;
  int line_length = 0;
  int x = 0;
  int y = 4;
  int c;
  //int addstr(const char *str)
  while(1) {
    stringstream strm;
    printw("> ");
    move(y, (x += 2));
    line_length = 0;
    line_num = last_line;
    while(1) {
      c = mvgetch(y,x);
      //go up to last read line
      if(c == KEY_UP) {
        line_num = (line_num - 1 >= 0) ? line_num - 1 : 0;
        move(y, (x = 2));
        clrtoeol();
        if(all_lines.empty()) {
          continue;
        }
        curline = all_lines.at(line_num);
        strm.flush();
        strm << curline;
        printw("%s", curline.c_str());
        move(y, (x += curline.length()));
        line_length = curline.length();
      } else if(c == KEY_DOWN) {
        line_num = (line_num + 1 < last_line) ? line_num + 1 : last_line - 1;
        move(y, (x = 2));
        clrtoeol();
        if(all_lines.empty()) {
          continue;
        }
        curline = all_lines.at(line_num);
        printw("%s", curline.c_str());
        move(y, (x += curline.length()));
        line_length = curline.length();
      } else if(c == KEY_LEFT) {
        x = x - 1 >= 2 ? x-1 : 2;
        move(y, x);
      } else if(c == KEY_RIGHT) {
        x = (x + 1 <= line_length + 3 ? x + 1 : x);
        move(y, x);
      } else if(c == 27) { //esc key
        quit();
      } else if(c == '\n' || c == 13) {
        curline = strm.str();

        all_lines.push_back(curline);
        last_line++;
        line_num++;

        string result = interpret(curline);
        move(++y, (x = 0));
        printw(result.c_str());
        move(++y, (x = 0));
        break; //exit to outer loop and interpret
      } else if(c == KEY_BACKSPACE || c == KEY_DC || c == 127) {
        x = x - 1 >= 2 ? x-1 : 2;
        move(y, x);
        delch();
        auto old_pos = strm.tellg();
        strm.seekp(x - 2);
        strm.get();
        strm.seekg(old_pos); //could do strm.end if this doesn't work
        line_length = line_length - 1 > 0 ? line_length - 1 : 0;
      } else if(c <= 126 && c >= 32){
        addch(c);
        move(y, ++x);
        line_length++;
        strm.put(c);
      } else {
        move(y, --x);
      }
    }
  }
  return 0;
}
