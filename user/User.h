//
// Created by 王敬衡 on 19-6-27.
//

#ifndef FILESYSTEM_USER_H
#define FILESYSTEM_USER_H

#include <string>
#include <vector>

typedef struct User
{
    std::string username; //用户名
    std::string password; //密码
} User;

void readUserList();                   //从文件读用户
void canceluser(std::string username); //取消一个用户
void modifypsw(std::string username);  //修改用户的密码

#endif //FILESYSTEM_USER_H
