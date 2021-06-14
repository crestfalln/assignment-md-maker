#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

std::string& findAndReplace(std::string& file , std::string& replace  , std::string& keyword)
{
    std::string subs = "";
    file.reserve(replace.length());
    for(long it = 0; it < file.length(); it++)
    {
        if(file[it] == ' ')
        {
            if(subs == keyword)
            {
                file.erase(it - subs.length() - 1, subs.length()+1);
                it = it - subs.length() - 1;
                file.insert(it , replace);
                it+=replace.length();
            }
            subs.clear();
        }
        else
            subs+=file[it];
    }
    return file;
}

int main(int argc, char *argv[])
{
    auto replace = new std::string;
    auto newfile = new std::string;
    replace->clear();
    newfile->clear();
    {
        std::ifstream replace_file(argv[2]);
        char tmp;
        while (replace_file.get(tmp))
        {
            *replace+=tmp;
        }
    }

    {
        std::ifstream file(argv[3]);
        char tmp;
        while (file.get(tmp))
            *newfile+=tmp;
    }
    std::ofstream file(argv[3], std::ios::out | std::ios::trunc);
    std::string keyword = argv[1];
    findAndReplace(*newfile , *replace ,keyword );
    file << *newfile;
    delete newfile;
    delete replace;
}