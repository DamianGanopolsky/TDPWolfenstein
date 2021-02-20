#ifndef __LOGINCONTROLLER_H__
#define __LOGINCONTROLLER_H__
#include "LoginView.h"



class LogInController {
public:
    LogInController(LoginView& LoginView);
    void run();
private: 
    LoginView& loginview;
    bool handle_events();
    
};

#endif