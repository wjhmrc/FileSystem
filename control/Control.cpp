//
// Created by 王敬衡 on 19-6-27.
//

#include <iostream>
#include <ios>
#include <limits>
#include <climits>
#include "Control.h"
#include "../user/User.h"
#include "../user/Login.h"
#include "../fileControl/FileControl.h"

#define RESET "\033[0m"
#define MAGENTA "\033[35m" /* Magenta */

extern std::string current_user; //当前用户
extern std::string current_path;

std::string Control::read_command()
{
    std::cout << "[" << current_user << "]" << MAGENTA << current_path << RESET << ">>";
    std::string command;
    getline(std::cin, command);
    return command;
}

void Control::init()
{
    readUserList();

    Login login;
    login.login();
}

void Control::progress()
{
    FileControl fileControl;
    fileControl.cdroot();
    std::cin.ignore(INT_MAX, '\n'); //清空cin缓存（不然后面的getline会先读缓存区中的\n)
    while (1)
    {
        std::string command = read_command();
        if (command == "logout")
        {
            break;
        }
        else if (command.substr(0, 10) == "canceluser")
        {
            std::string username = command.substr(command.find(" ") + 1, command.length() - 1);
            canceluser(username);
        }
        else if (command.substr(0, 9) == "modifypsw")
        {
            std::string username = command.substr(command.find(" ") + 1, command.length() - 1);
            modifypsw(username);
        }
        else if (command == "dir")
        {
            fileControl.dir();
        }
        else if (command == "cd")
        {
            fileControl.cd();
        }
        else if (command.substr(0, 6) == "cdfore")
        {
            std::string dir = command.substr(command.find(" ") + 1, command.length() - 1);
            fileControl.cdfore(dir);
        }
        else if (command == "cdroot")
        {
            fileControl.cdroot();
        }
        else if (command == "cdback")
        {
            fileControl.cdback();
        }
        else if (command.substr(0, 5) == "mkdir")
        {
            std::string dir = command.substr(command.find(" ") + 1, command.length() - 1);
            fileControl.mkdir(dir);
        }
        else if (command.substr(0, 12) == "my_deletedir")
        {
            std::string dir = command.substr(command.find(" ") + 1, command.length() - 1);
            fileControl.my_deletedir(dir);
        }
        else if (command.substr(0, 9) == "my_create")
        {
            std::string filename = command.substr(command.find(" ") + 1, command.length() - 1);
            fileControl.my_create(filename);
        }
        else if (command.substr(0, 13) == "my_deletefile")
        {
            std::string filename = command.substr(command.find(" ") + 1, command.length() - 1);
            fileControl.my_deletefile(filename);
        }
        else
        {
            std::cout << "No such command!" << std::endl;
        }
    }
    Login login;
    login.logout();
}