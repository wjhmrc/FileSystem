//
// Created by 王敬衡 on 19-6-27.
//

#ifndef FILESYSTEM_CONTROL_H
#define FILESYSTEM_CONTROL_H

#include <string>

class Control
{
private:
    std::string read_command(); //读取命令
public:
    void init();     //系统初始化
    void progress(); //主进程
};

#endif //FILESYSTEM_CONTROL_H
