#include <format>
#include <algorithm>
#include <string>
#include <ranges>
#include <sstream>
#include "func.h"
#include <cstring>
#include <string_view>
#include <vector>

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

std::vector<std::string> split(const std::string& str, char del) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while(getline(tokenStream, token, del))
        tokens.push_back(token);
    return tokens;
}

Detail handler::json2str(const std::string& input) {
    std::vector <std::string> arr1 = split(input.substr(0, input.rfind('}')), ',');
    std::vector<std::pair<std::string, std::string>> result(arr1.size());

    std::transform(arr1.begin(), arr1.end(), result.begin(), [](auto pair){
        std::vector<std::string> kv = split(pair, ':');
        if (kv.size() == 2) {
            kv[0] = kv[0].substr(kv[0].find('\"') + 1, kv[0].rfind('\"') - kv[0].find('\"') - 1);
            return std::make_pair(kv[0], kv[1]);
        } else
            throw std::logic_error("invalid key-value");
    });

    auto detail = Detail ();
    auto idIt = std::find_if(result.begin(), result.end(), [](const auto & item){return item.first == "id";});
    auto nameIt = std::find_if(result.begin(), result.end(), [](const auto & item){return item.first == "name";});
    auto countIt = std::find_if(result.begin(), result.end(), [](const auto & item){return item.first == "count";});

    detail.id = idIt->second.substr(idIt->second.find('\"') + 1,
                                        idIt->second.rfind('\"') - idIt->second.find('\"') - 1).substr(0, 8);;
    detail.name = nameIt->second.substr(nameIt->second.find('\"') + 1,
                                       nameIt->second.rfind('\"') - nameIt->second.find('\"') - 1);
    detail.count = stoi(countIt->second);
    return detail;
}

/**
 *
 * @param json user json string
 * @return detail struct
 * \throw logic_error if input json is nullptr
 */
Detail handler::json2str(const char* json) {
    return json2str(json, strlen(json));
}

/**
 *
 * @param json user json string
 * @param size size of json string
 * @return detail struct
 */
Detail handler::json2str(const char* json, size_t size) {
    if (json == nullptr) {
        throw std::logic_error("str is nullptr");
    }
    if (size > strlen(json))
        size = strlen(json);
    return json2str(std::string {json, size});
}