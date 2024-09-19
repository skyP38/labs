#include <format>
#include <algorithm>
#include <string>
#include <ranges>
#include <sstream>
#include "func.h"

/**
 *
 * @param detail - struct from user
 * @return std::string in json format
 */
std::string handler::str2json(const Detail& detail) {
    return "{" + std::format(R"("id": "{}", "name": "{}", "count": {})", detail.id, detail.name, detail.count) + "}";
}

/**
 *
 * @param input json string from user
 * @return detail struct
 * \throw logic_error if string format is invalid
 */
Detail handler::json2str(const std::string& input) {
    auto detail = Detail ();
    std::stringstream json(input.substr(0, input.rfind('}')));

    while (json.good()) {
        std::string word;
        getline(json, word, ',');
        std::string key = word.substr(0, word.find(':'));
        key = key.substr(key.find('\"') + 1, key.rfind('\"') - key.find('\"') - 1);
        if (key == "id") {
            if (detail.id.empty()) {
                detail.id = word.substr(word.find(':'));
                detail.id = detail.id.substr(detail.id.find('\"') + 1,
                                             detail.id.rfind('\"') - detail.id.find('\"') - 1).substr(0, 8);
            } else
                throw std::logic_error("Value is already exist");
        } else if (key == "name") {
            if (detail.name.empty()) {
                detail.name = word.substr(word.find(':'));
                detail.name = detail.name.substr(detail.name.find('\"') + 1,
                                                 detail.name.rfind('\"') - detail.name.find('\"') - 1);
            } else
                throw std::logic_error("Value is already exist");
        } else if(key == "count") {
            if (!detail.count) {
                std::string tmp = word.substr(word.find(':') + 1);
                if (!(std::any_of(tmp.begin(), tmp.end(), [](char c) { return std::isalpha(c);})))
                    detail.count = stoi(tmp);
                else
                    throw std::logic_error("Invalid argument in count field");
            } else
                    throw std::logic_error("Value is already exist");
        } else
            throw std::logic_error("String is invalid");
    }
    return detail;
}

//{"count":3245, "name":"fgh", "id": "ioejjjj"}

/**
 *
 * @param json user json string
 * @return detail struct
 * \throw logic_error if input json is nullptr
 */
Detail handler::json2str(const char* json) {
    if (json == nullptr) {
        throw std::logic_error("str is nullptr");
    }
    return json2str((std::string)json);
}

/**
 *
 * @param json user json string
 * @param size size of json string
 * @return detail struct
 */
Detail handler::json2str(const char* json, size_t size) {
    return json2str(json);
}