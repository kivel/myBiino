#include "menu.h"

Menu::Menu(LCDisplay *lcd){
  disp=lcd;
  init();
}

void Menu::init(){
  action=false;
  pwrMenu=exit;
  mainMenu=volume;
}

void Menu::enter(){
  switch (mainMenu) {
    case volume: mainMenu=inputs; break;
    case inputs: mainMenu=power; printPwrMenu(); break;
    case power: action=true;
    default: mainMenu=volume;
  }
}

void Menu::next(){
  if(mainMenu==power){
    pwrMenu = off;
    printPwrMenu();
  }
}

void Menu::prev(){
  if(mainMenu==power){
    pwrMenu = exit;
    printPwrMenu();
  }
}

void Menu::printPwrMenu(){
  disp->clear();
  disp->LCD.setCursor(0,0);
  disp->LCD.print("Power Menu: ");
  disp->LCD.setCursor(0,1);
  if(pwrMenu){
    disp->LCD.print("Enter to power off  ");
  } else {
    disp->LCD.print("Enter to exit       ");
  }
}

void Menu::printMenu(){
  disp->LCD.setCursor(0,1);
  disp->LCD.print("P: ");
  disp->LCD.print(pwrMenu);
}
