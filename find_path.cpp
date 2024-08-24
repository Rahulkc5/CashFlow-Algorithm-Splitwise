#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

// Function declarations
void findPath(std::map<std::string, double>& details);
std::string getKeyFromValue(const std::map<std::string, double>& hm, double value);
double round(double value, int places);

int main() {
    std::map<std::string, double> parm;
    parm["A"] = -5.0;
    parm["B"] = 25.0;
    parm["C"] = -20.0;
    parm["D"] = 25.0;
    parm["E"] = -20.0;
    parm["F"] = -5.0;

    // Passing values to findPath Method.
    findPath(parm);

    return 0;
}

void findPath(std::map<std::string, double>& details) {
    std::vector<std::string> printBill;
    double Max_Value = std::max_element(details.begin(), details.end(),
                                        [](const std::pair<std::string, double>& a, const std::pair<std::string, double>& b) {
                                            return a.second < b.second;
                                        })->second;
    double Min_Value = std::min_element(details.begin(), details.end(),
                                        [](const std::pair<std::string, double>& a, const std::pair<std::string, double>& b) {
                                            return a.second < b.second;
                                        })->second;
    
    if (Max_Value != Min_Value) {
        std::string Max_Key = getKeyFromValue(details, Max_Value);
        std::string Min_Key = getKeyFromValue(details, Min_Value);
        double result = Max_Value + Min_Value;
        result = round(result, 1);

        if (result >= 0.0) {
            std::cout << Min_Key << " needs to pay " << Max_Key << ": " << round(std::abs(Min_Value), 2) << std::endl;
            details.erase(Max_Key);
            details.erase(Min_Key);
            details[Max_Key] = result;
            details[Min_Key] = 0.0;
        } else {
            std::cout << Min_Key << " needs to pay " << Max_Key << ": " << round(std::abs(Max_Value), 2) << std::endl;
            details.erase(Max_Key);
            details.erase(Min_Key);
            details[Max_Key] = 0.0;
            details[Min_Key] = result;
        }
        findPath(details);
    }
}

std::string getKeyFromValue(const std::map<std::string, double>& hm, double value) {
    for (const auto& pair : hm) {
        if (pair.second == value) {
            return pair.first;
        }
    }
    return "";
}

double round(double value, int places) {
    if (places < 0) throw std::invalid_argument("places must be non-negative");

    double scale = std::pow(10.0, places);
    return std::round(value * scale) / scale;
}

