#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include "input.h"
#include "func.h"

/**
 *
 * @param in input stream
 * \throw runtime_error Bad stream or EOF
 */
void input::process_error(std::istream& in) {
    if (in.eof()) {
        throw std::runtime_error("EOF");
    }
    if (in.bad()) {
        throw std::runtime_error("Bad stream");
    }
    if (in.fail()) {
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
}

/**
 *
 * @param detail struct to fill by user input
 */
Detail input::input_struct() {
    Detail detail = {};
    std::cout << "Input id:" << std::endl;
    std::cin >> std::setw(8) >> detail.id;
    while(!std::cin.good()) {
        input::process_error(std::cin);
        std::cin >> std::setw(8) >> detail.id;
    }
    std::cout << "Input name:" << std::endl;
    std::cin >> detail.name;
    while(!std::cin.good()) {
        input::process_error(std::cin);
        std::cin >> detail.name;
    }
    std::cout << "Input count:" << std::endl;
    std::cin >> detail.count;
    while(!std::cin.good()) {
        input::process_error(std::cin);
        std::cin >> detail.count;
    }
    return detail;
}

/**
 *
 * @param json string to fill by user input
 */
std::string input::input_json() {
    std::string json;
    std::cout << "Input json:" << std::endl;
    std::getline(std::cin, json);
    while(!std::cin.good()) {
        input::process_error(std::cin);
        std::getline(std::cin, json);
    }
    return json;
}