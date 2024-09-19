/**
 * \file
 * \brief h file with input functions
 */
#ifndef L1_INPUT_H
#define L1_INPUT_H

struct Detail;

namespace input {
    void process_error(std::istream& in);
    void input_struct(Detail &);
    void input_json(std::string&);
}
#endif //L1_INPUT_H
