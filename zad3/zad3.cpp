#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

const std::string test_file_path {"../data/acc.txt"}; // default test file path
const std::string log_file_path {"log.txt"}; //default log file

bool is_valid(const std::string & acc_number, std::ofstream & log_file);
void load_file(std::vector<std::string> & buff, std::ofstream & log_file, const std::string path = test_file_path); 

int main()
{
    std::ofstream log_file(log_file_path);
    log_file <<"\tVALIDATION OF BANK ACCOUNT NUMBER\n";
    std::cout <<"\tVALIDATION OF BANK ACCOUNT NUMBER\n";

    std::vector<std::string> test_vec;
    load_file(test_vec, log_file);

    for(auto & str: test_vec)
        is_valid(str, log_file);

    return 0;
}

bool is_valid(const std::string & acc_number, std::ofstream & log_file)
{
    if(acc_number.size() != 26)
    {
        std::cout <<"Number: " <<acc_number <<" is not valid, size: " <<acc_number.size() <<" (should be 26 digits)\n";
        log_file <<"Number: " <<acc_number <<" is not valid, size: " <<acc_number.size() <<" (should be 26 digits)\n";
    }
    else
    {
        std::string first_two_numbers = acc_number.substr(0, 2);
        std::cout <<first_two_numbers <<std::endl;
        std::string mod_string = acc_number.substr(2);
        std::cout <<mod_string <<std::endl;
        unsigned res {0};
        for (int i = 0; i < acc_number.length(); i++)
            res = (res*10 + (int)acc_number[i] - '0') % 97;

        if(res == 1)
        {
            std::cout <<"Number: " <<acc_number <<" is valid, response: " <<res <<std::endl;
        log_file <<"Number: " <<acc_number <<" is valid, response: " <<res <<std::endl;
            return true;
        }
        std::cout <<"Number: " <<acc_number <<" is not valid, response: " <<res <<" (should be 1)\n";
        log_file <<"Number: " <<acc_number <<" is not valid, response: " <<res <<" (should be 1)\n";
    }
    return false;
}

void load_file(std::vector<std::string> & buff, std::ofstream & log_file, const std::string path)
{
    log_file <<"\tLOAD_FILE\nTrying to load file from path:\t" <<path <<std::endl;
    std::cout <<"\tLOAD_FILE\nTrying to load file from path:\t" <<path <<std::endl;
    std::ifstream test_file(path);
    if(test_file.is_open())
    {
        log_file <<"test file is opened\n";
        std::cout <<"test file is opened\n";
        
        std::string line;

        // skipping first two lines
        getline(test_file, line);
        getline(test_file, line);

        while(std::getline(test_file, line))
        {
            std::cout <<(int) line[line.size()-1] <<std::endl;
            std::remove(line.begin(), line.end(), ' ');
            line = line.substr(0, line.size()-1);
            log_file <<"adding line to vector: " <<line <<std::endl;
            std::cout <<"adding line to vector: " <<line <<std::endl;
            buff.push_back(line);
        }        
    }
    else
        std::cout <<"Unable to open file!\n";
}