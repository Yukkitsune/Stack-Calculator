#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
void print(std::string str){
    for (size_t i = 0; i < str.size();++i) {
        std::cout << str[i];
    }
    std::cout << std::endl;
}
void printvec(std::vector<char> str) {
    for (size_t i = 0; i < str.size();++i) {
        std::cout << str[i];
    }
    std::cout << std::endl;
}
void printdouble(std::vector<double> str) {
    for (size_t i = 0; i < str.size();++i) {
        std::cout << str[i]<<' ';
    }
    std::cout << std::endl;
}
void answer(double str) {
    std::cout << str << std::endl;
    std::cout << std::endl;
}

double result_case(std::vector<char> parsed_signs, std::vector<double> parsed_nums) {
    double result = 0.0;
    for (size_t i = 0; i < parsed_signs.size();++i) {
        if (parsed_signs[i] == '*') {
            result = parsed_nums[i];
            break;
        }
        else if (parsed_nums[i] == '/') {
            result = parsed_nums[i];
            break;
        }
        else if (parsed_nums[i] == '+') {
            result = parsed_nums[i];
            break;
        }
        else if (parsed_nums[i] == '-') {
            result = parsed_nums[i];
            break;
        }
    }
    return result;
}
std::vector<double> recursive_res(std::vector<char> parsed_signs, std::vector<double> parsed_nums) {
    size_t i = 0;
    while (i < parsed_signs.size()) {
        double temp = 0.0;
        bool flag = false;
        if (flag) {
            recursive_res( parsed_signs, parsed_nums);
            return parsed_nums;
        }
        switch (parsed_signs[i]) {
        case '*':
            temp = parsed_nums[i] * parsed_nums[i + 1];
            parsed_nums[i] = temp;
            parsed_nums.erase(parsed_nums.begin() + i + 1);
            flag = true;
            ++i;
            printdouble(parsed_nums);
            break;
        case '/':
            if (parsed_nums[i + 1] != 0) {
                temp = parsed_nums[i] / parsed_nums[i + 1];
                parsed_nums[i] = temp;
                parsed_nums.erase(parsed_nums.begin() + i + 1);
                flag = true;
                ++i;
                printdouble(parsed_nums);
                break;
            }
            else {
                std::cerr << "Incorrect equasion - division by zero :(\n";
                system("pause");
            }
        }
    }
}
int main()
{

    std::cout << "Enter equasion: ";
    std::string equasion;
    std::getline(std::cin, equasion);
    equasion += '+';
    size_t i = 0;
    std::vector<double> parsed_nums;
    std::vector<char> parsed_signs;
    std::string temp = "";
    while (i < equasion.size()) {
        if (i == 0 && equasion[i] == '-') {
            temp += equasion[i];
            i += 1;
        }
        if (equasion[i] != '+' && equasion[i] != '-' && equasion[i] != '*' && equasion[i] != '/') {
            if (isdigit(equasion[i])) {
                temp += equasion[i];
                i += 1;
            }
            else {
                std::cerr << "Incorrect equasion :(\n";
                system("pause");
                return -1;
            }
        }
        else {
            if (temp.size() > 0) {
                parsed_nums.push_back(stod(temp));
            }
            temp = "";
            parsed_signs.push_back(equasion[i]);
            i += 1;
        }
    }
    parsed_signs.pop_back();
    print(equasion);
    printvec(parsed_signs);
    printdouble(parsed_nums);
    if (parsed_signs.size() >= parsed_nums.size()) {
        std::cerr << "Incorrect equasion :(\n";
        system("pause");
        return -1;
    }
    double result = 0.0;//result_case(parsed_signs, parsed_nums);
    answer(result);
    /*for (size_t i = 0; i < parsed_signs.size(); ++i) {
        double temp = 0.0;
        switch (parsed_signs[i]) {
        case '*':
            temp = parsed_nums[i] * parsed_nums[i + 1];
            parsed_nums[i] = temp;
            parsed_nums.erase(parsed_nums.begin() + i+1);
            printdouble(parsed_nums);
            break;
        case '/':
            if (parsed_nums[i + 1] != 0) {
                temp = parsed_nums[i] / parsed_nums[i + 1];
                parsed_nums[i] = temp;
                parsed_nums.erase(parsed_nums.begin() + i + 1);
                printdouble(parsed_nums);
                break;
            }
            else {
                std::cerr << "Incorrect equasion - division by zero :(\n";
                system("pause");
                return -1;
            }
        }
    }*/
    std::vector<double> peparsed_nums = recursive_res(parsed_signs, parsed_nums);
    std::cout << "OH";
    printdouble(peparsed_nums);
    printdouble(parsed_nums);
    printvec(parsed_signs);
        for (size_t i = 0; i < parsed_signs.size(); ++i) {
            double temp = 0.0;
            switch (parsed_signs[i]) {
                case '+':
                    temp = parsed_nums[i] + parsed_nums[i + 1];
                    parsed_nums[i] = temp;
                    parsed_nums.erase(parsed_nums.begin() + i + 1);
                    printdouble(parsed_nums);
                    break;
                case '-':
                    temp = parsed_nums[i] - parsed_nums[i + 1];
                    parsed_nums[i] = temp;
                    parsed_nums.erase(parsed_nums.begin() + i + 1);
                    printdouble(parsed_nums);
                    break;
            }
        }
        std::cout << "Parsed nums: ";
        printdouble(parsed_nums);
        /*for (size_t i = 0; i < parsed_signs.size(); ++i) {
            result += parsed_nums[i];
        }*/
        answer(result);
        return 0;
    }
