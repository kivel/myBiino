#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include "config.h"

class Menu{
  public:
    Menu();
    boolean button_Up = false;
    boolean button_Down = false;
    boolean button_Left = false;
    boolean button_Right = false;
    boolean button_Enter = false;
    boolean button_Menu = false;
    boolean button_Play = false;
    boolean button_Channel = false;
    boolean menu_action = false;
    boolean last_volume = false;
    boolean in_menu = false;
    boolean button_Power = false;
    void clearButtons();
    void rotEncoder(bool, bool);
};

Menu::Menu(){}

void Menu::clearButtons(){
  button_Up = false;
  button_Down = false;
  button_Left = false;
  button_Right = false;
  button_Enter = false;
  button_Menu = false;
  button_Play = false;
  button_Channel = false;
  menu_action = false;
  button_Power = false;
}

void Menu::rotEncoder(bool enc1, bool enc2){
  if(enc1 == enc2){
    if (in_menu == true){
      button_Left = true;
    }
    else{
      button_Down = true;
    }
  }
  else{
    if (in_menu == true){
      button_Right = true;
    }
    else{
      button_Up = true;
    }
  }
}

#endif /* MENU_H */
