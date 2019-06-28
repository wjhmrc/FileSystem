//
// Created by 王敬衡 on 19-6-27.
//
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <climits>
#include "User.h"

std::vector<User> userlist; //用户列表
std::string current_user;   //当前用户

//从文件中读取用户列表
void readUserList()
{
    //打开文件
    std::ifstream fin("../data/user", std::ios::in);
    std::string line;

    //逐行读取，插入用户列表
    while (getline(fin, line))
    {
        std::string name, password;
        std::stringstream word(line);
        word >> name;
        word >> password;

        User user = {name, password};
        userlist.push_back(user);
    }
}

//取消一个用户
void canceluser(std::string username)
{
    std::ifstream in;
    in.open("../data/user");

    std::string strFileData = "";
    char lineData[1024] = {0};
    int count = 0;
    while (in.getline(lineData, sizeof(lineData)))
    {
        if (std::string(lineData).substr(0, username.length()) == username)
        {
            count++;
            continue;
        }
        else
        {
            strFileData += std::string(lineData);
        }
    }
    in.close();

    if (count == 0)
    {
        std::cout << "No such user!" << std::endl;
        return;
    }

    std::ofstream out;
    out.open("../data/user");
    out << strFileData;

    out.close();
}

//重载比较函数（自己提供模板参数避免模板自己推断参数类型）
struct compare : std::binary_function<User, std::string, bool>
{
    bool operator()(User &user, std::string username) const
    {
        return user.username == username;
    }
};

//修改用户的密码
void modifypsw(std::string username)
{
    if (std::count_if(userlist.begin(), userlist.end(), std::bind2nd(compare(), username)) == 0)
    {
        std::cout << "No such user!" << std::endl;
        return;
    }
    std::string newpwd;
    std::cout << "NEW PASSWORD:";
    std::cin >> newpwd;

    std::ifstream in;
    in.open("../data/user");

    std::string strFileData = "";
    char lineData[1024] = {0};
    while (in.getline(lineData, sizeof(lineData)))
    {
        if (std::string(lineData).substr(0, username.length()) == username)
        {
            strFileData += username + " " + newpwd;
            strFileData += "\n";
        }
        else
        {
            strFileData += std::string(lineData);
            strFileData += "\n";
        }
    }
    in.close();

    std::ofstream out;
    out.open("../data/user");
    out << strFileData;

    out.close();
    std::cin.ignore(INT_MAX, '\n');
}