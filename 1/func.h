/**
 * \file
 * \brief h file with functions for conversation from json to struct and back
 */

#ifndef L1_FUNC_H
#define L1_FUNC_H

struct Detail{
    std::string id;
    std::string name;
    size_t count;

    bool operator == (const Detail &detail) const {
        return this->id == detail.id && this->name == detail.name && this->count == detail.count;
    }
};

namespace handler {
    std::string str2json(const Detail &);

    Detail json2str(const std::string &);

    Detail json2str(const char *);

    Detail json2str(const char *, size_t);
}

#endif //L1_FUNC_H
