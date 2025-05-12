#include "SalesReport.h"
#include <fstream>
#include <sstream>
#include <string>
// Initializes revenue and counts to zero.
SalesReport::SalesReport()
    : pTotalSales(0.0f) {}

float SalesReport::getTotalSales() const
{
    return pTotalSales;
}

const std::map<int, int>& SalesReport::getItemsSold() const
{
    return pItemsSold;
}

void SalesReport::recordSale(int code, float price)
{
    pTotalSales += price;
    pItemsSold[code] += 1;
}
// Load all past purchases so totalSales and counts are cumulative.
void SalesReport::loadFromLog(const std::string& logFile) {
    std::ifstream in(logFile);
    if (!in) return;
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::istringstream ss(line);
        int code;
        ss >> code;
        ss >> std::ws;
        if (ss.peek() == '"') {
            ss.get();
            std::string name;
            std::getline(ss, name, '"');
        }
        float price;
        ss >> price;
        recordSale(code, price);
    }
}