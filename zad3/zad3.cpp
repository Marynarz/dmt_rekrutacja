#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

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
    std::map<std::string, bool> res_map;

    for(auto & str: test_vec)
        res_map[str] = is_valid(str, log_file);

    std::cout <<"\n\n\tFINAL RESPONSE:\n";
    log_file <<"\n\n\tFINAL RESPONSE:\n";
    for(const auto & rm: res_map)
    {
        std::cout <<"Account: " <<rm.first <<" is valid: " <<std::boolalpha <<rm.second <<std::endl;
        log_file <<"Account: " <<rm.first <<" is valid: " <<std::boolalpha <<rm.second <<std::endl;
    }
    std::cout <<"\n\tBYE!\n";
    log_file <<"\n\tBYE!\n";

    return 0;
}

bool is_valid(const std::string & acc_number, std::ofstream & log_file)
{
    std::cout <<"\n\n\tNumber validation: " <<std::endl;
    log_file <<"\n\n\tNumber validation: " <<std::endl;
    // check str size, should be 26
    if(acc_number.size() != 26)
    {
        std::cout <<"Number: " <<acc_number <<" is not valid, size: " <<acc_number.size() <<" (should be 26 digits)\n";
        log_file <<"Number: " <<acc_number <<" is not valid, size: " <<acc_number.size() <<" (should be 26 digits)\n";
    }
    else
    {
        // extract first two digits (control number)
        std::string first_two_numbers = acc_number.substr(0, 2);
        std::cout <<"control numbers: " <<first_two_numbers <<std::endl;
        log_file <<"control numbers: " <<first_two_numbers <<std::endl;

        // prepare substr with number to concatenate
        std::string mod_string = acc_number.substr(2);

        // add countrycode
        mod_string += "2521" + first_two_numbers;
        std::cout <<"Number to validate: " <<mod_string <<std::endl;
        log_file <<"Number to validate: " <<mod_string <<std::endl;
        unsigned res {0};
        for (int i = 0; i < mod_string.size(); i++)
            res = (res*10 + (int)mod_string[i] - '0') % 97;

        // if res is 1 than validation return true
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
        log_file <<"file version: " <<line <<std::endl;
        std::cout <<"file version: " <<line <<std::endl;

        getline(test_file, line);
        log_file <<"file date: " <<line <<std::endl;
        std::cout <<"file date: " <<line <<std::endl;

        while(std::getline(test_file, line))
        {
            // clean up manipultions to remove spaces from string if exist
            auto it = std::remove(line.begin(), line.end(), ' ');
            line.erase(it, line.end());
            line = line.substr(0, line.size()-1);

            // add string to vector
            log_file <<"adding line to vector: " <<line <<std::endl;
            std::cout <<"adding line to vector: " <<line <<std::endl;
            buff.push_back(line);
        }        
    }
    else
        std::cout <<"Unable to open file!\n";
}