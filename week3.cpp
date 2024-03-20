#include <iostream>
#include <vector>
#include <map>
#include <iomanip>

// Structure to hold the yield information for each milking session
struct YieldRecord {
    int day;
    double morningYield;
    double eveningYield;
};

// Use a map to associate each cow's ID with its yield records for the week
std::map<int, std::vector<YieldRecord>> cowYields;

void recordYield() {
    int herdSize;
    std::cout << "Enter the size of the herd: ";
    std::cin >> herdSize;

    for (int i = 0; i < herdSize; ++i) {
        int cowID;
        std::cout << "Enter cow " << i+1 << "'s ID: ";
        std::cin >> cowID;
        std::vector<YieldRecord> yields(7); // Assuming 7 days a week

        for (int day = 0; day < 7; ++day) {
            std::cout << "Day " << day+1 << " morning yield for cow " << cowID << ": ";
            std::cin >> yields[day].morningYield;
            std::cout << "Day " << day+1 << " evening yield for cow " << cowID << ": ";
            std::cin >> yields[day].eveningYield;
            yields[day].day = day+1;
        }
        cowYields[cowID] = yields;
    }
}
//TASK2
void calculateStatistics() {
    double totalYield = 0;
    for (const auto& cow : cowYields) {
        for (const auto& record : cow.second) {
            totalYield += record.morningYield + record.eveningYield;
        }
    }
    int totalCows = cowYields.size();
    std::cout << "Total weekly volume of milk for the herd: " << round(totalYield) << " litres\n";
    std::cout << "Average yield per cow in a week: " << round(totalYield / totalCows) << " litres\n";
}
//TAsk3
void identifyCows() {
    double highestYield = 0;
    int mostProductiveCow = 0;
    std::vector<int> lowYieldCows;

    for (const auto& cow : cowYields) {
        double cowTotalYield = 0;
        int lowYieldDays = 0;
        for (const auto& record : cow.second) {
            double dailyYield = record.morningYield + record.eveningYield;
            cowTotalYield += dailyYield;
            if (dailyYield < 12) ++lowYieldDays;
        }
        if (cowTotalYield > highestYield) {
            highestYield = cowTotalYield;
            mostProductiveCow = cow.first;
        }
        if (lowYieldDays >= 4) lowYieldCows.push_back(cow.first);
    }

    std::cout << "Most productive cow ID: " << mostProductiveCow << " with " << highestYield << " litres\n";
    std::cout << "Cows with low yield: ";
    for (int id : lowYieldCows) std::cout << id << " ";
    std::cout << "\n";
}

int main() {
    recordYield();
    calculateStatistics();
    identifyCows();
    return 0;
}
