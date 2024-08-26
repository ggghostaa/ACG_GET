
#include "menus.h"
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <ncurses.h>
#include <dirent.h>
#include <csignal>
#include <algorithm>
#include <sys/ioctl.h>

std::vector<std::string> GetFilesInDirectory(const std::string& directory_path) {
    std::vector<std::string> files;
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir(directory_path.c_str())) != nullptr) {

        while ((ent = readdir(dir)) != nullptr) {
            if (strcmp(ent->d_name, ".") == 0) continue;
            files.push_back(ent->d_name);
        }
        closedir(dir);
    } else {
        perror("opendir");
    }
    std::sort(files.begin(), files.end());
    return files;
}

namespace acg_menus{

WINDOW *main_win;
WINDOW *info_win;
WinConfig win_config;


/**
 * remove win content
 */
void ClearWinContent(WINDOW *win) {
    wmove(win, 1, 1);
    wclrtoeol(win);
}

/**
 * clear
 */
void HandleExit(int sig) {
    if (main_win != nullptr) {
        delwin(main_win);
        main_win = nullptr;
    }
    if (info_win != nullptr) {
        delwin(info_win);
        info_win = nullptr;
    }
    endwin();  // 退出 ncurses 模式，恢复终端状态
    exit(0);
}

/**
 * rename menus
 */
void XRenameMenus(const std::string& path) {
    int c;
    int highligt = 0;
    std::vector<std::string> files = GetFilesInDirectory(path);
    ClearWinContent(info_win);
    mvwprintw(info_win, 1, 1, path.c_str());
    wrefresh(info_win);
    refresh();

    while (1) {
        wmove(main_win, 1, 1);
        wclrtoeol(main_win);

        for (int i = 0; i < files.size(); ++i) {
            if (i == highligt) {
                attron(A_REVERSE);
            }
            mvwprintw(main_win, i + 1, 1, files[i].c_str());
        }
        wrefresh(main_win);

        c = getch();
    }
}
void CreateMainWindow() {
    initscr();// 初始化屏幕并进入 ncurses 模式
    cbreak();// 将输入模式设置为逐字符模式，避免缓冲，直接传递输入
    noecho();// 启用标准屏幕（stdscr）的键盘功能，支持捕获特殊键（如箭头键）
    curs_set(0);// 隐藏终端光标
    keypad(stdscr, TRUE);

    signal(SIGINT, HandleExit);
    signal(SIGTERM, HandleExit);
    int cmd_x, cmd_y;
    getmaxyx(stdscr, cmd_y, cmd_x);

    int main_height, main_width, start_x, start_y;
    main_height = cmd_y * 0.8;
    main_width = cmd_x * 0.9;
    start_y = (cmd_y - main_height) / 2;
    start_x = (cmd_x - main_width) / 2;


    //create main window
    main_win = newwin(main_height, main_width, start_y, start_x);
    box(main_win, 0, 0);//draw window border
    //create info window
    int info_height, info_width, info_start_y, info_start_x;
    info_height = cmd_y * 0.12;
    info_width = main_width;
    info_start_y = (cmd_y * 0.2 - info_height) / 2;
    info_start_x = start_x;
    info_win = newwin(info_height, info_width, 0, info_start_x);



    // mvwprintw(main_win, 1, 1, "hihihi");
    // mvwprintw(main_win, 2, 1, "this is a window");
    refresh();
    wrefresh(main_win);
    wrefresh(info_win);

    int c;

    c = getch();

    XRenameMenus("/yun_data/video");

    delwin(main_win);
    delwin(info_win);
    endwin();//exit
}


void DrawMainWin(int t) {
    //get scr size
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    win_config.max_y_ = w.ws_row;
    win_config.max_x_ = w.ws_col;
    win_config.main_height_ = win_config.max_y_ * 0.8;
    win_config.main_width_ = win_config.max_x_;
    win_config.info_height_ = win_config.max_y_ * 0.12;
    win_config.info_width_ = win_config.main_width_;

    int start_y = (win_config.max_y_ - win_config.main_height_) / 2;
    int start_x = (win_config.max_x_ - win_config.main_width_) / 2;
    int info_start_y = (win_config.max_x_ * 0.2 ) / 2;
    //create win or reset win size
    if (t == 0 ) {//create
        main_win = newwin(win_config.main_height_, win_config.main_width_, start_y, start_x);
        info_win = newwin(win_config.info_height_, win_config.info_width_, 0, start_x);
    } else {//reset
        clear();
        resize_term(0, 0);
        wresize(main_win, win_config.main_height_, win_config.main_width_);
        wclear(main_win);
        wresize(info_win, win_config.info_height_, win_config.info_width_);
        wclear(info_win);  
    }

    box(main_win, 0, 0);
    mvwprintw(main_win, 1, 1, "main_win");
    box(info_win, 0, 0);
    mvwprintw(info_win, 1, 1, "info");
    refresh();
    wrefresh(main_win);
    wrefresh(info_win);
}
void HandleWinCh(int sig) {
    DrawMainWin(1);
}

void Run() {
    initscr();// 初始化屏幕并进入 ncurses 模式
    cbreak();// 将输入模式设置为逐字符模式，避免缓冲，直接传递输入
    noecho();
    curs_set(0);// 隐藏终端光标
    keypad(stdscr, TRUE);// 启用标准屏幕（stdscr）的键盘功能，支持捕获特殊键（如箭头键）

    // 设置信号处理
    signal(SIGINT, HandleExit);   // 捕获 Ctrl+C
    signal(SIGTERM, HandleExit);  // 捕获终止信号
    signal(SIGWINCH, HandleWinCh);

    DrawMainWin(0);
    while (1) {
        int c;
        c = getch();
    }
    
    HandleExit(1);
    endwin();

}
}
