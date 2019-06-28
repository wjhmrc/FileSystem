//
// Created by 王敬衡 on 19-6-27.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include "Login.h"
#include "../control/Control.h"

extern std::vector<User> userlist; //用户列表
extern std::string current_user;   //当前用户

//登入
void Login::login()
{
    while (1)
    {
        std::cout << "USERNAME:";
        std::string username;
        std::cin >> username;

        std::cout << "PASSWORD:";
        std::string password;
        std::cin >> password;

        if (password == searchPwd(username))
        {
            current_user = username;
            std::cout << "Welcome!" << std::endl;
            break;
        }

        std::cout << "FALSE!" << std::endl;
    }

    Control control;
    control.progress();
}

//登出
void Login::logout()
{
    current_user = "";
    login();
}

//重载比较函数（自己提供模板参数避免模板自己推断参数类型）
struct compare : std::binary_function<User, std::string, bool>
{
    bool operator()(User &user, std::string username) const
    {
        return user.username == username;
    }
};

//查找密码
std::string Login::searchPwd(std::string username)
{
    std::vector<User>::iterator it = std::find_if(userlist.begin(), userlist.end(), std::bind2nd(compare(), username));
    return it->password;
}
