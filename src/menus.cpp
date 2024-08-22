
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

void handle_exit(int sig) {
    endwin();  // 退出 ncurses 模式，恢复终端状态
    exit(0);
}

void run() {
    initscr();// 初始化屏幕并进入 ncurses 模式
    cbreak();// 将输入模式设置为逐字符模式，避免缓冲，直接传递输入
    noecho();
    curs_set(0);// 隐藏终端光标
    keypad(stdscr, TRUE);// 启用标准屏幕（stdscr）的键盘功能，支持捕获特殊键（如箭头键）

    // 设置信号处理
    signal(SIGINT, handle_exit);   // 捕获 Ctrl+C
    signal(SIGTERM, handle_exit);  // 捕获终止信号

    std::string path = ".";
    std::vector<std::string> files = GetFilesInDirectory(path);

    int highlight = 0;  // 变量，用于记录当前高亮显示的文件索引
    int choice = 0;     // 变量，用于记录用户选择的文件索引
    int c;              // 变量，用于捕获用户输入的字符

    while (1) {
        clear();

        for (int i = 0; i < files.size(); ++i) {
            if (i == highlight) {
                attron(A_REVERSE);
            }

            mvprintw(i, 0, files[i].c_str());
            mvprintw(i, COLS / 2, files[i].c_str());
            attroff(A_REVERSE);
        }

        c = getch();

        switch (c) {
        case KEY_UP:
            highlight = (highlight - 1 + files.size()) % files.size();
            break;
        case KEY_DOWN:
            highlight = (highlight + 1) % files.size();
            break;
        case 10:
            choice = highlight;
            break;
        default:
            break;
        }

        if (c == 10) {
            break;
        }
    }
    endwin();

    std::cout << "Selected file:" << files[choice] << std::endl;
}
}
