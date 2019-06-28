//
// Created by 王敬衡 on 19-6-27.
//

#include "FileControl.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <algorithm>

#define RESET "\033[0m"
#define BLACK "\033[30m"   /* Black */
#define RED "\033[31m"     /* Red */
#define GREEN "\033[32m"   /* Green */
#define YELLOW "\033[33m"  /* Yellow */
#define BLUE "\033[34m"    /* Blue */
#define MAGENTA "\033[35m" /* Magenta */
#define CYAN "\033[36m"    /* Cyan */
#define WHITE "\033[37m"   /* White */

#define ROOT_PATH "/home/wjh/Code/FileSystem/file"

std::string current_path;               //当前路径
std::string parent_path;                //当前路径的父目录
std::vector<std::string> childrenDirs;  //前路径的子目录
std::vector<std::string> childrenFiles; //前路径的子文件

//列出当前目录下的所有文件及子目录
void FileControl::dir()
{

    for (auto dir : childrenDirs)
    {
        std::cout << BLUE << dir << " ";
    }

    for (auto file : childrenFiles)
    {
        std::cout << GREEN << file << " ";
    }
    std::cout << RESET << std::endl;
}

//显示当前的目录名
void FileControl::cd()
{
    std::cout << current_path << std::endl;
}

//退到上一级目录
void FileControl::cdback()
{
    if (current_path == "/")
    {
        std::cout << "Already in the root directory!" << std::endl;
        return;
    }
    current_path = parent_path;

    if (parent_path == "/")
    {
        parent_path = "#";
    }
    else
    {
        //截掉最后一段路径
        std::string grandparent_path = parent_path.substr(parent_path.rfind('/', parent_path.length() - 2), parent_path.length() - 1);
        parent_path = grandparent_path;
    }

    initDir(current_path);
}

//进入下一级子目录
void FileControl::cdfore(std::string dir)
{
    if (std::count(childrenDirs.begin(), childrenDirs.end(), dir) == 0)
    {
        std::cout << "No such directory!" << std::endl;
        return;
    }
    parent_path = current_path;
    current_path = current_path + dir + "/";
    initDir(current_path);
}

//回到根目录
void FileControl::cdroot()
{
    current_path = "/";
    parent_path = "#";
    initDir("/");
}

void FileControl::mkdir(std::string dir)
{
    //检测是否存在此文件夹
    if (std::count(childrenDirs.begin(), childrenDirs.end(), dir) > 0)
    {
        std::cout << "This folder already exists！" << std::endl;
        return;
    }

    childrenDirs.push_back(dir);
    std::sort(childrenDirs.begin(), childrenDirs.end());

    //修改目录文件
    std::ofstream fout(ROOT_PATH + current_path + ".dir", std::ios::trunc);
    fout << "DIR:";
    for (auto dir : childrenDirs)
    {
        fout << dir << ";";
    }
    fout << std::endl;

    fout << "FILE:";
    for (auto file : childrenFiles)
    {
        fout << file << ";";
    }
    fout << std::endl;

    fout.close();

    //新建文件夹
    std::string command = "mkdir -p " + std::string(ROOT_PATH) + current_path + dir + "/";
    system(command.c_str());
}

void FileControl::my_deletedir(std::string dir)
{
    //检测是否存在此文件夹
    if (std::count(childrenDirs.begin(), childrenDirs.end(), dir) == 0)
    {
        std::cout << "No such directory!" << std::endl;
        return;
    }

    childrenDirs.erase(std::find(childrenDirs.begin(), childrenDirs.end(), dir));

    //修改目录文件
    std::ofstream fout(ROOT_PATH + current_path + ".dir", std::ios::trunc);
    fout << "DIR:";
    for (auto dir : childrenDirs)
    {
        fout << dir << ";";
    }
    fout << std::endl;

    fout << "FILE:";
    for (auto file : childrenFiles)
    {
        fout << file << ";";
    }
    fout << std::endl;

    fout.close();

    std::string command = "rm -rf " + std::string(ROOT_PATH) + current_path + dir + "/";
    system(command.c_str());
}

void FileControl::my_create(std::string filename)
{
    //检测是否存在此文件
    if (std::count(childrenFiles.begin(), childrenFiles.end(), filename) > 0)
    {
        std::cout << "This file already exists！" << std::endl;
        return;
    }

    childrenFiles.push_back(filename);
    std::sort(childrenFiles.begin(), childrenFiles.end());

    //修改目录文件
    std::ofstream fout(ROOT_PATH + current_path + ".dir", std::ios::trunc);
    fout << "DIR:";
    for (auto dir : childrenDirs)
    {
        fout << dir << ";";
    }
    fout << std::endl;

    fout << "FILE:";
    for (auto file : childrenFiles)
    {
        fout << file << ";";
    }
    fout << std::endl;

    fout.close();

    //新建文件
    std::string command = "touch " + std::string(ROOT_PATH) + current_path + filename;
    system(command.c_str());
}

void FileControl::my_deletefile(std::string filename)
{
    //检测是否存在此文件
    if (std::count(childrenFiles.begin(), childrenFiles.end(), filename) == 0)
    {
        std::cout << "No such file!" << std::endl;
        return;
    }

    childrenFiles.erase(std::find(childrenFiles.begin(), childrenFiles.end(), filename));

    //修改目录文件
    std::ofstream fout(ROOT_PATH + current_path + ".dir", std::ios::trunc);
    fout << "DIR:";
    for (auto dir : childrenDirs)
    {
        fout << dir << ";";
    }
    fout << std::endl;

    fout << "FILE:";
    for (auto file : childrenFiles)
    {
        fout << file << ";";
    }
    fout << std::endl;

    fout.close();

    std::string command = "rm -rf " + std::string(ROOT_PATH) + current_path + filename;
    system(command.c_str());
}

//初始化一个目录
void FileControl::initDir(std::string path)
{
    std::ifstream fin(ROOT_PATH + current_path + ".dir", std::ios::in);
    std::string line;

    //初始化子文件、目录向量
    childrenDirs.clear();
    childrenFiles.clear();

    while (getline(fin, line))
    {
        int sign = 0;
        //如果是文件夹
        if (line[0] == 'D')
        {
            sign = 1;
        }
        line = line.substr(line.find(":") + 1, line.length() - 1); //截取冒号之后的部分字符串

        //获取目录内的文件夹和文件
        std::stringstream ss(line);
        std::string children;

        while (getline(ss, children, ';'))
        {
            if (sign == 1)
            {
                childrenDirs.push_back(children);
            }
            else
            {
                childrenFiles.push_back(children);
            }
        }
    }
}
