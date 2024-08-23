
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
void Handle_exit(int sig) {
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

    signal(SIGINT, Handle_exit);
    signal(SIGTERM, Handle_exit);
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
    info_start_y = (cmd_y * 0.2 - cmd_y) / 2;
    info_start_x = start_x;
    info_win = newwin(info_height, info_width, 0, info_start_x);
    box(info_win, 0, 0);
    mvwprintw(info_win, 1, 1, "info");


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

void run() {
    initscr();// 初始化屏幕并进入 ncurses 模式
    cbreak();// 将输入模式设置为逐字符模式，避免缓冲，直接传递输入
    noecho();
    curs_set(0);// 隐藏终端光标
    keypad(stdscr, TRUE);// 启用标准屏幕（stdscr）的键盘功能，支持捕获特殊键（如箭头键）

    // 设置信号处理
    signal(SIGINT, Handle_exit);   // 捕获 Ctrl+C
    signal(SIGTERM, Handle_exit);  // 捕获终止信号
    endwin();

}
}
