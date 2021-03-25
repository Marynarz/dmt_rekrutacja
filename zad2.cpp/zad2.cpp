#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <regex>

const std::string range_file_path {"../data/rang.txt"};  //default rang file path
const std::string test_file_path {"../data/track.txt"}; // default test file path
const std::string log_file_path {"log.txt"};            //default log file

class Range
{
    std::string range_min;
    std::string range_max;
    std::string card_name;

    public:
    Range(std::string rng_min, std::string rng_max, std::string crd_name) : range_min {rng_min}, range_max {rng_max}, card_name {crd_name} {};

    bool is_in_range();
    std::string get_card_name();
}

void load_card_numbers(std::vector<std::string> & buff, std::ofstream & log_file, const std::string path = test_file_path); // load file to vector
void load_card_ranges(std::vector<ranges> & buff, stf::ofstream & log_file, const std::string path = range_file_path)       // load ranges

int main()
{
    // Creating log file object
    std::ofstream log_file(log_file_path);
    log_file <<"Try to validate track2\n";

    // vector with struct of card
    std::vector<std::string> cards_nums;
    
    // Magic
    load_card_numbers(cards_nums, log_file);
    for(const card: cards_nums)
        log_file <<"Loaded card: " <<card <<std::endl;

        

    std::cout <<"\nBye!\n";
    log_file <<"\nBye!\n";
    return 0;
}

void load_card_numbers(std::vector<std::string> & buff, std::ofstream & log_file, const std::string path)
{
    log_file <<"\tLOAD_CARD_NUMBERS\nTrying to load file from path:\t" <<path <<std::endl;
    std::cout <<"\tLOAD_CARD_NUMBERS\nTrying to load file from path:\t" <<path <<std::endl;
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
            buff.push_back(line.substr(1, pos_middle_char - 1));
        }        
    }
    else
        std::cout <<"Unable to open file!\n";
}

bool Range::is_in_range();
std::string Range::get_card_name()
{
    return card_name;
}
