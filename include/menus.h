#ifndef MENUS_H
#define MENUS_H

#include <string>

namespace acg_menus{

/**
 * menus index
 */
enum Menus {
    MAIN_WIN,
    RENAME_WIN
};

/**
 * main win config
 */
struct WinConfig {
    int max_y_;
    int max_x_;
    int main_height_;
    int main_width_;
    int info_height_;
    int info_width_;
    std::string rename_path_;
    int c_;
    int highlight_;
    Menus menus_;
};


void CreateMainWindow();

void Run();

}

#endif //ACG_RENAMING_H