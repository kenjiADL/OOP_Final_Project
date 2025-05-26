#include "SalesReport.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Initializes revenue and counts to zero.
SalesReport::SalesReport()
    : pTotalSalesCents(0) {}

float SalesReport::getTotalSales() const
{
    return pTotalSalesCents / 100.0f;
}

const map<int, int>& SalesReport::getItemsSold() const
{
    return pItemsSold;
}

void SalesReport::recordSale(int code, int priceCents)
{
    pTotalSalesCents += priceCents;
    pItemsSold[code] += 1;
}
// Load all past purchases so totalSales and counts are cumulative.
void SalesReport::loadFromLog(const string& logFile) {
    ifstream in(logFile);
    if (!in) return;
    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        istringstream ss(line);
        int code;
        ss >> code;
        ss >> ws;
        if (ss.peek() == '"') {
            ss.get();
            string name;
            getline(ss, name, '"');
        }
        float price;
        ss >> price;
        int priceCents = static_cast<int>(round(price * 100));
        recordSale(code, priceCents);
    }
}