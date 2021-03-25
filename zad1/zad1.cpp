#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <regex>

const std::string test_file_path {"../data/track.txt"}; // default test file path
const std::string log_file_path {"../log_zad1.txt"}; //default log file

struct card_data
{
    std::string card_number;
    std::string card_data_line;
    int yy;                        // year
    int mm;                        // month
    bool date_valid;
    bool number_valid;             // is number valid
};

void load_file(std::vector<card_data> & buff, std::ofstream & log_file, const std::string path = test_file_path); // load file to vector
void check_dates(std::vector<card_data> & buff, std::ofstream & log_file);
void card_number_validation(std::vector<card_data> & buff, std::ofstream & log_file);
void show_card_data(const std::vector<card_data> & buff, std::ofstream & log_file);

int main()
{
    // Creating log file object
    std::ofstream log_file(log_file_path);
    log_file <<"Try to validate track2\n";

    // vector with struct of card
    std::vector<card_data> buffer_vec;
    
    // Magic
    load_file(buffer_vec, log_file);    
    check_dates(buffer_vec, log_file);
    card_number_validation(buffer_vec, log_file);
    show_card_data(buffer_vec, log_file);

    std::cout <<"\nBye!\n";
    log_file <<"\nBye!\n";
    return 0;
}

void load_file(std::vector<card_data> & buff, std::ofstream & log_file, const std::string path)
{
    log_file <<"\tLOAD_FILE\nTrying to load file from path:\t" <<path <<std::endl;
    std::cout <<"\tLOAD_FILE\nTrying to load file from path:\t" <<path <<std::endl;
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
    std::cout <<"\tVeryfin date\n";
    log_file <<"\tVeryfin date\n";
    time_t now = time(NULL);
    tm *local_time = std::localtime(&now);
    
    // veryfing date for every card
    for(auto & b: buff)
    {
        b.yy = std::stoi(b.card_data_line.substr(0,2));
        b.mm = std::stoi(b.card_data_line.substr(2,2));
        if(b.yy > (local_time->tm_year % 100) ||
        (b.yy == (local_time->tm_year % 100) && b.mm >= 1 + local_time->tm_mon))
            b.date_valid = true;
        else
            b.date_valid = false;

        log_file <<b.card_number <<"\tYEAR: " <<b.yy <<"\t MONTH: " <<b.mm <<"\tDATE VALID: " <<b.date_valid <<std::endl;
        std::cout <<b.card_number <<"\tYEAR: " <<b.yy <<"\t MONTH: " <<b.mm <<"\tDATE VALID: " <<b.date_valid <<std::endl;
    }
}

void card_number_validation(std::vector<card_data> & buff, std::ofstream & log_file)
{
    log_file <<"\tCard number validation\n";
    std::cout <<"\tCard number validation\n";
    // This regex matches Visa, MasterCard, American Express, Diners Club, Discover, and JCB cards:
    std::regex re("^(?:4[0-9]{12}(?:[0-9]{3})?|[25][1-7][0-9]{14}|6(?:011|5[0-9][0-9])[0-9]{12}|3[47][0-9]{13}|3(?:0[0-5]|[68][0-9])[0-9]{11}|(?:2131|1800|35\\d{3})\\d{11})$");
    
    // check for match for every card number
    for(auto & b: buff)
    {
        b.number_valid = std::regex_match(b.card_number, re);
        log_file <<"Card: " <<b.card_number <<" is: " <<b.number_valid <<std::endl;
        std::cout <<"Card: " <<b.card_number <<" is: " <<b.number_valid <<std::endl;
    }
}

// showing collected data
void show_card_data(const std::vector<card_data> & buff, std::ofstream & log_file)
{
    std::cout <<"\n\tFINAL:\n";
    log_file <<"\n\tFINAL:\n";
    for(auto & b: buff)
    {
        std::cout <<"Card: \t\t" <<b.card_number <<std::endl;
        std::cout <<"Number isvalid:\t" <<b.number_valid <<std::endl;
        std::cout <<"Track2 data:\t" <<b.card_data_line <<std::endl;
        std::cout <<"Date mm/yy: \t" <<b.mm <<"/" <<b.yy <<std::endl;
        std::cout <<"Date is valid:\t" <<b.date_valid <<std::endl; 
        std::cout <<"\n---\n";

        log_file <<"Card: \t\t" <<b.card_number <<std::endl;
        log_file <<"Number isvalid:\t" <<b.number_valid <<std::endl;
        log_file <<"Track2 data:\t" <<b.card_data_line <<std::endl;
        log_file <<"Date mm/yy: \t" <<b.mm <<"/" <<b.yy <<std::endl;
        log_file <<"Date is valid:\t" <<b.date_valid <<std::endl; 
        log_file <<"\n---\n\n";
    }
}