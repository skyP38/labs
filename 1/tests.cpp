#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "func.h"

TEST_CASE ("func") {
    SECTION("no throw") {
        std::string tmp[] = {(std::string) R"({"count":3245, "name":"fgh", "id": "ioejjjj"}")",
                (std::string) R"({"name":"fgh", "count":3245, "id": "ioejjjj"}")",
                (std::string) R"({ "id": "ioejjjj", "count":3245, "name":"fgh"}")"};
        Detail res = {"ioejjjj", "fgh", 3245};
        REQUIRE_NOTHROW(handler::json2str(tmp[0]) == res);
        REQUIRE_NOTHROW(handler::json2str(tmp[1]) == res);
        REQUIRE_NOTHROW(handler::json2str(tmp[2]) == res);
    }
    SECTION("ovf id") {
        std::string tmp[] = {(std::string) R"({"count":3245, "id": "1234567890", "name":"fgh"}")",
                             (std::string) R"({"name":"fgh", "count":3245, "id": "1234567890"}")",
                             (std::string) R"({ "id": "1234567890", "count":3245, "name":"fgh"}")"};
        Detail res = {"12345678", "fgh", 3245};
        REQUIRE_NOTHROW(handler::json2str(tmp[0]) == res);
        REQUIRE_NOTHROW(handler::json2str(tmp[1]) == res);
        REQUIRE_NOTHROW(handler::json2str(tmp[2]) == res);
    }
    SECTION("throw error") {
        std::string tmp[] = {(std::string) R"({"id":3245, "id": "1234567890", "name":"fgh"}")",
                             (std::string) R"({"name":"fgh", "name":3245, "id": "1234567890"}")",
                             (std::string) R"({ "id": "1234567890", "count":"3245", "name":"fgh"}")",
                             (std::string) R"({ "id": , "count":"3245", "name":"fgh"}")",
                             (std::string) R"({ djhdghfdfjsh }")",
                             (std::string) R"({"count":32fgsdg45, "id": "1234567890", "name":"fgh"}")",
                             (std::string) R"({"count":3245, "count": 1234567890, "name":"fgh"}")"};
        REQUIRE_THROWS_AS(handler::json2str(tmp[0]), std::logic_error);
        REQUIRE_THROWS_AS(handler::json2str(tmp[1]), std::logic_error);
        REQUIRE_THROWS_AS(handler::json2str(tmp[2]), std::logic_error);
        REQUIRE_THROWS_AS(handler::json2str(tmp[3]), std::logic_error);
        REQUIRE_THROWS_AS(handler::json2str(tmp[4]), std::logic_error);
        REQUIRE_THROWS_AS(handler::json2str(tmp[5]), std::logic_error);
        REQUIRE_THROWS_AS(handler::json2str(tmp[6]), std::logic_error);
    }
    SECTION("char*") {
        char* tmp = (char *) R"({"name":"fgh", "count":3245, "id": "ioejjjj"}")";
        Detail res = {"ioejjjj", "fgh", 3245};
        REQUIRE_NOTHROW(handler::json2str(tmp) == res);
        REQUIRE_NOTHROW(handler::json2str(tmp, strlen(tmp)) == res);
        tmp = (char *) R"({ "id": "ioejjjj", "count":3245, "name":"fgh"}")";
        REQUIRE_NOTHROW(handler::json2str(tmp, strlen(tmp)) == res);
        tmp = nullptr;
        REQUIRE_THROWS_AS(handler::json2str(tmp, 0), std::logic_error);
    }
    SECTION("json to struct") {
        std::string tmp = (std::string) R"({ "id": "ioejjjj", "count":3245, "name":"fgh"}")";
        Detail res = {"ioejjjj", "fgh", 3245};
        REQUIRE_NOTHROW(handler::str2json(res) == tmp);
    }
}