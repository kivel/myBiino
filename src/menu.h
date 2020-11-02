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
    enum {volume, inputs, power} mainMenu;
    enum {exit, off} pwrMenu;
  private:
    LCDisplay *disp;
    void printPwrMenu();
};

#endif /* MENU_H */
