// Gambling odds.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>

class BetDate {
    private:
    
        int seconds=0;
        int minutes=0;
        int hours=0;
        int day=0;
        int month=0;
        int year=0;
    public:
        BetDate() {
            seconds = 0;
            minutes = 0;
            hours = 0;
            day = 0;
            month = 0;
            year = 0;
        }
        BetDate(std::string line) {
            std::string::iterator it = line.begin();
            int dashcount=0;
            for (; *it != ']'; it++) {
                if (*it - 48 >= 0 and *it - 48 <= 9) {
                    switch (dashcount) {
                        case 0:
                            year = year * 10 + *it - 48;
                            break;
                        case 1:
                            month = month * 10 + *it - 48;
                            break;
                        case 2:
                            day = day * 10 + *it - 48;
                            break;
                        case 3:
                            hours = hours * 10 + *it - 48;
                            break;
                        case 4:
                            minutes = minutes * 10 + *it - 48;
                            break;
                        case 5:
                            seconds = seconds * 10 + *it - 48;
                            break;
                        
                    }
                }
                if (*it == ':' or *it == '-' or *it==' ') {
                    dashcount++;
                }
                
            }
                
        }
        int GetSeconds() {
            return seconds;
        }
        int GetMinutes() {
            return minutes;
        }
        int GetHours() {
            return hours;
        }
        int GetDay() {
            return day; 
        }
        int GetMonth() {
            return month;
        }
        int GetYear() {
            return year;
        }
        std::string getDateString() {
        
            return (std::to_string(year) + std::string("-") + std::to_string(month) + std::string("-") + std::to_string(day) + std::string(" ") + std::to_string(hours) + std::string(":") + std::to_string(minutes) + std::string(":") + std::to_string(seconds));
        
        }

};

struct SlotBet {
    std::string result;
    BetDate date;
    int ammount;
    SlotBet(std::string initialresult, BetDate initialdate, int initialammount) {
        result=initialresult;
        date=initialdate;
        ammount=initialammount;  
    }
};


void DataFill(std::vector<SlotBet>& bets,std::string line,std::string username){
    int pos=0;
    int value=0;
    if (line.find(username)!=std::string::npos) {
        if (line.find("you got") != std::string::npos) {
            pos = line.find("and lost your");
            if (pos != std::string::npos) {
                for (int i = pos+14; (line[i]-48>=0 and line[i]-48 <=9) and i <=500; i++) {
                    value = value * 10 + line[i] - 48;
                
                }
                bets.push_back(SlotBet(std::string("loss"), BetDate(line), value));
            
            }
            else {
                pos = pos = line.find("and won");
                if (pos != std::string::npos) {
                    for (int i = pos + 8; (line[i] - 48 >= 0 and line[i] - 48 <= 9) and i <= 500; i++) {
                        value = value * 10 + line[i] - 48;

                    }
                    bets.push_back(SlotBet(std::string("win"), BetDate(line), value));

                }
            }
            

        }
    }
}


int main()
{

    std::string line;
    std::string username;
    std::cout << "\n";
    std::vector<SlotBet> bets;
    bool condition = true;
    int count=0;
    int profit = 0;
    //data entry

    std::cout << "Introduce the name of the gambler: ";
    while (condition) {


        std::getline(std::cin, username);
        if (username != "") {
            for (int i = 0; username[i] != '\0'; i++) {
                if (username[i] == ' ') {
                    std::cout << std::endl << "Introduce the name of the gambler without spaces: ";
                    break;
                
                }
                else if (username[i + 1] == '\0')
                    condition = false;
                
            }
            
        }
        else {
            std::cout << std::endl << "Introduce the name of the gambler: ";
        }
        


    }
        
    std::ifstream botlogs; 
    botlogs.open("logs.txt");
    if (botlogs.is_open()) {
       
        while (std::getline(botlogs, line)) {

            DataFill(bets, line, username);
            
        }

        for (SlotBet bet : bets) {

            std::cout << bet.date.getDateString() << " " << bet.result << " " << std::to_string(bet.ammount)<<std::endl;
            if (bet.result == "win") {
                count++;

                profit = profit + bet.ammount;
            }
            else
                profit = profit - bet.ammount;
        }
        if (bets.size() > 0) {

            std::cout << std::endl << username << " had " << std::to_string(count) << " wins within the last " << std::to_string(bets.size()) << " bets with a final winrate of: " << std::to_string((double) count / bets.size() * 100) << "%" << " and a total profit of: " << std::to_string(profit) << " points." << std::endl;

        }
            
    }
    else
        std::cout << "buh it failed" << std::endl;
    botlogs.close();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
