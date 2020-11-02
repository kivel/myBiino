#ifndef MENU_H
#define MENU_H

#include "config.h"
#include "LCD.h"

class Menu {
  public:
    Menu(LCDisplay *lcd);
    void init();
    void enter();
    void next();
    void prev();
    enum Menus {volume, inputs, power} mainMenu;
    enum PwrMen {exit, off} pwrMenu;
    bool onOff;
    bool action;
  private:
    LCDisplay *disp;
    void printPwrMenu();
    void printMenu();
};

#endif /* MENU_H */
