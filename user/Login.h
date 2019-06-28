/*
 * 登录模块
 */
#ifndef FILESYSTEM_LOGIN_H
#define FILESYSTEM_LOGIN_H

#include <string>
#include "User.h"

class Login
{
public:
    void login();  //登入
    void logout(); //登出
private:
    std::string searchPwd(std::string username); //查找密码
};

#endif //FILESYSTEM_LOGIN_H
