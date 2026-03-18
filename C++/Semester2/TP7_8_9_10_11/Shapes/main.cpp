// main.cpp
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

#include "ez-draw++.hpp"
#include "MyWindow.hpp"

int main()
{
 EZDraw ezDraw;

 vector<unique_ptr<MyWindow>> windows;
 windows.push_back(make_unique<MyWindow>(800,600,"Some shapes"));
 //windows.push_back(make_unique<MyWindow>(800,800,"Some other shapes"));

 ezDraw.mainLoop();

 return 0;
}
