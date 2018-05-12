#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <stddef.h>
#include <vector>
#include <string.h>

using namespace std;
typedef struct {
    std::string name;
    unsigned long max_time_gap;
    unsigned long timestamp;
    unsigned int volume;
    unsigned int price;
    unsigned int avg;
    unsigned int max_price;
} Stock_Detail_;

bool CompareName(const Stock_Detail_ &a, const Stock_Detail_ &b) {
    return a.name < b.name;
}

int main(){
    std::vector<Stock_Detail_> trades;
    ifstream infile("input.csv"); 
    string line = "";
    while(std::getline(std::cin, line)) {
        Stock_Detail_ new_stock;
        stringstream strline(line);
        if (strline.rdbuf()->in_avail() == 0)
            break;
        string temp = "";
        strline >> temp;
        new_stock.timestamp = std::stoul(temp);
        strline >> new_stock.name;
        temp = "";
        strline >> temp;
        new_stock.volume = std::stoi(temp);
        temp = "";
        std::getline(strline, temp, '\n');
        new_stock.price = std::stoi(temp);
        new_stock.avg = new_stock.price;
        new_stock.max_price = new_stock.price;
        new_stock.max_time_gap = 0;
        bool found = false;
        for(size_t i = 0; i < trades.size(); i++) {
            if (new_stock.name == trades[i].name) {
                found = true;   
                if (new_stock.timestamp - trades[i].timestamp > trades[i].max_time_gap) {
                    trades[i].max_time_gap = new_stock.timestamp - trades[i].timestamp;
                }
                trades[i].timestamp = new_stock.timestamp;
                trades[i].avg = ((trades[i].volume * trades[i].avg) +
                                 (new_stock.volume * new_stock.price)) /
                                 (trades[i].volume + new_stock.volume);
                trades[i].volume += new_stock.volume;
                if (trades[i].max_price < new_stock.price)
                    trades[i].max_price = new_stock.price;
                break;
            }
        }
        if (!found) {
            trades.push_back(new_stock);
        }
    }
    std::sort(trades.begin(), trades.end(), CompareName);
    //ofstream outfile("output.csv");
    for (size_t i; i < trades.size(); i++) {
        //if (outfile.is_open()) {
        //std::cout << trades[i].name << ",";
        //std::cout << trades[i].max_time_gap << ",";
        //std::cout << trades[i].volume << "," ;
        //std::cout << trades[i].avg << ",";
        //std::cout << trades[i].max_price << std::endl;
        outfile << trades[i].name << ",";
        outfile << trades[i].max_time_gap << ",";
        outfile << trades[i].volume << "," ;
        outfile << trades[i].avg << ",";
        outfile << trades[i].max_price << std::endl;
        } else {
            std::cout << "couldn't open file" << std::endl;
        }
    }
    outfile.close();
    cout << " Program complete" << std::endl;
    return 0;
}
