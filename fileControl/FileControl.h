//
// Created by 王敬衡 on 19-6-27.
//

#ifndef FILESYSTEM_FILECONTROL_H
#define FILESYSTEM_FILECONTROL_H

#include <vector>
#include <string>

class FileControl
{
private:
    void initDir(std::string path); //初始化一个目录
public:
    void dir();                               //列出当前目录下的所有文件及子目录
    void cd();                                //显示当前的目录名
    void cdback();                            //退到上一级目录
    void cdfore(std::string dir);             //进入下一级子目录
    void cdroot();                            //回到根目录
    void mkdir(std::string dir);              //新建一个子目录
    void my_deletedir(std::string dir);       //删除一个子目录
    void my_create(std::string filename);     //新建一个文件
    void my_deletefile(std::string filename); //删除一个文件
};

#endif //FILESYSTEM_FILECONTROL_H
