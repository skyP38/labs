/**
 * \file
 * \brief h file with input functions
 */
#ifndef L1_INPUT_H
#define L1_INPUT_H

#include "func.h"

namespace input {
    void process_error(std::istream& in);
    Detail input_struct();
    std::string input_json();
}
#endif //L1_INPUT_H
