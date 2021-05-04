#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

//std::stringstream& findAndReplace(std::stringstream& file , std::stringstream& replace , std::string keyword)
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
                //it = file.str().erase(it - subs.length() , it);
                file.insert(it , replace);
                file.erase(it - subs.length() , subs.length());
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
/*
    std::stringstream replace;
    std::stringstream newfile;
*/
    auto replace = new std::string;
    auto newfile = new std::string;
    replace->clear();
    newfile->clear();
    {
        std::ifstream replace_file(argv[2]);
        char tmp;
        while (replace_file.get(tmp))
            *replace+=tmp;
            //replace << tmp;
    }

    {
        std::ifstream file(argv[3]);
        char tmp;
        while (file.get(tmp))
            *newfile+=tmp;
            //newfile << tmp;
    }
    //std::cout << *newfile << std::endl;
    std::ofstream file(argv[3], std::ios::out | std::ios::trunc);
    std::string keyword = argv[1];
    findAndReplace(*newfile , *replace ,keyword );
    file << *newfile;
}