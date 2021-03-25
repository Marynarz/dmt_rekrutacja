#include <iostream>
#include <fstream>
#include <vector>
#include <string>

const std::string range_file_path {"../data/rang.txt"};  //default rang file path
const std::string test_file_path {"../data/track.txt"}; // default test file path
const std::string log_file_path {"../log_zad2.txt"};            //default log file

class Range
{
    std::string range_min;
    std::string range_max;
    std::string card_name;
    std::ofstream * log_file;

    public:
    Range (const std::string & line, std::ofstream * lg_file);
    Range(std::string rng_min, std::string rng_max, std::string crd_name, std::ofstream * lg_file) : range_min {rng_min}, range_max {rng_max}, card_name {crd_name}, log_file {lg_file} {};

    bool is_in_range(const std::string & test_str);
    std::string get_card_name();
};

void load_card_numbers(std::vector<std::string> & buff, std::ofstream & log_file, const std::string path = test_file_path); // load file to vector
void load_ranges(std::vector<Range> & buff, std::ofstream & log_file, const std::string path = range_file_path);

int main()
{
    // Creating log file object
    std::ofstream log_file(log_file_path);
    log_file <<"Try to validate track2\n";

    // vector with cardnumbers and ranges
    std::vector<std::string> cards_nums;
    std::vector<Range> ranges;
    
    // Magic
    load_card_numbers(cards_nums, log_file);
    load_ranges(ranges, log_file);

    for(auto & crd: cards_nums)
    {
        for(auto & rng: ranges)
        {
            if(rng.is_in_range(crd))
            {
                std::cout <<"Card name:\t" <<rng.get_card_name() <<std::endl;
                log_file <<"Card name:\t" <<rng.get_card_name() <<std::endl;
                break;
            }
        }
    }

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

void load_ranges(std::vector<Range> & buff, std::ofstream & log_file, const std::string path)
{
    log_file <<"\tLOAD_RANGES\nTrying to load file from path:\t" <<path <<std::endl;
    std::cout <<"\tLOAD_RANGES\nTrying to load file from path:\t" <<path <<std::endl;
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
            log_file <<"adding line to vector: " <<line <<std::endl;
            std::cout <<"adding line to vector: " <<line <<std::endl;
            buff.push_back(Range(line, &log_file));
        }        
    }
    else
        std::cout <<"Unable to open file!\n";
}

Range::Range(const std::string & line, std::ofstream * lg_file)
{
    log_file = lg_file;
    *log_file <<"Creating object from line: " <<line <<std::endl;
    size_t first_sep = line.find('|');
    size_t sec_sep = line.find('|', first_sep + 1);
    range_min = line.substr(0, first_sep - 1);
    range_max = line.substr(first_sep + 1, sec_sep -1);
    card_name = line.substr(sec_sep + 1);
    *log_file <<"range max:\t" <<range_max <<"\nrange min:\t" <<range_min <<"\ncard name:\t" <<card_name <<std::endl;
}

bool Range::is_in_range(const std::string & test_str)
{
    *log_file <<"\n\tIS_IN_RANGE\nchecking: " <<test_str <<std::endl;
    for(int letter = 0; letter < range_min.size(); letter++)
    {
        if(range_min[letter] >= test_str[letter] && range_max[letter] <= test_str[letter] )
        {
            *log_file <<"Digit: '" <<test_str[letter] <<"' is NOT in range" <<std::endl;
            return false;
        }
        *log_file <<"Digit: '" <<test_str[letter] <<"' is in range " <<range_min[letter] <<" max: " <<range_max[letter] <<std::endl;
    }
    *log_file <<"All line is in range\n";
    return true;
}

std::string Range::get_card_name()
{
    return card_name;
}
