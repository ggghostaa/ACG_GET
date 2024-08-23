#ifndef MENUS_H
#define MENUS_H

namespace acg_menus{

/**
 * menus index
 */
enum MenusPoint {
    MAIN_WIN,
    RENAME_WIN
};

/**
 * main win config
 */
struct WinConfig {
    int max_y_;
    int max_x_;
    std::string rename_path_;
    int c_;
    int highlight_;
};


void CreateMainWindow();

void run();

}

#endif //ACG_RENAMING_H