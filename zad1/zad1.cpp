#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>

const std::string test_file_path {"../data/track.txt"}; // default test file path
const std::string log_file_path {"log.txt"}; //default log file

enum ver_method {pin, signature, none};

struct card_data
{
    std::string card_number;
    std::string card_data_line;
    int yy;                        // year
    int mm;                        // month
    bool date_valid;
    ver_method verification;
};

void load_file(std::vector<card_data> & buff, std::ofstream & log_file, const std::string path = test_file_path); // load file to vector
void check_dates(std::vector<card_data> & buff, std::ofstream & log_file);

int main()
{
    std::ofstream log_file(log_file_path);
    log_file <<"Try to validate track2\n";

    std::vector<card_data> buffer_vec;
    load_file(buffer_vec, log_file);

    for(auto & b: buffer_vec)
        std::cout <<b.card_number <<"\t" <<b.card_data_line <<std::endl;
    
    check_dates(buffer_vec, log_file);
    return 0;
}

void load_file(std::vector<card_data> & buff, std::ofstream & log_file, const std::string path)
{
    log_file <<"\tLOAD_FILE\nTrying to load file from path:\t" <<path <<std::endl;
    std::ifstream test_file(path);
    if(test_file.is_open())
    {
        log_file <<"test file is opened\n";
        std::cout <<"test file is opened\n";
        std::string line;
        while(std::getline(test_file, line))
        {
            log_file <<"adding line to vector: " <<line <<std::endl;
            std::cout <<"adding line to vector: " <<line <<std::endl;
            std::size_t pos_middle_char = line.find('=');
            std::size_t pos_last_char = line.find('\?');
            card_data tmp_data = {line.substr(1, pos_middle_char - 1), line.substr(pos_middle_char + 1)};
            buff.push_back(tmp_data);
        }        
    }
    else
        std::cout <<"Unable to open file!\n";
}

void check_dates(std::vector<card_data> & buff, std::ofstream & log_file)
{
    time_t now = time(NULL);
    tm *local_time = std::localtime(&now);
    std::cout <<local_time->tm_year <<std::endl;
    for(auto & b: buff)
    {
        b.yy = std::stoi(b.card_data_line.substr(0,2));
        b.mm = std::stoi(b.card_data_line.substr(2,2));
        if(b.yy > (local_time->tm_year % 100))
            b.date_valid = true;
        else if(b.yy == (local_time->tm_year % 100) && b.mm >= 1 + local_time->tm_mon)
            b.date_valid = true;
        else
            b.date_valid = false;

        log_file <<b.card_number <<"\tYEAR: " <<b.yy <<"\t MONTH: " <<b.mm <<"\tDATE VALID: " <<b.date_valid <<std::endl;
        std::cout <<b.card_number <<"\tYEAR: " <<b.yy <<"\t MONTH: " <<b.mm <<"\tDATE VALID: " <<b.date_valid <<std::endl;
    }
}