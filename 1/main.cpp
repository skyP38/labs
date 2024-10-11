#include <iostream>
#include <format>
#include "func.h"
#include "input.h"

int main() {
  std::cout << "Input mode(0-struct2json, 1-json2struct):" << std::endl;
  int mode;
  try {
      std::cin >> mode;
      while(!std::cin.good()) {
          input::process_error(std::cin);
          std::cin >> mode;
      }
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      if (mode == 0) {
          Detail detail = input::input_struct();
          std::cout << handler::str2json(detail) << std::endl;
      } else if (mode == 1) {
          std::string json = input::input_json();
          Detail detail = handler::json2str(json);
          std::cout << std::format("id: {}, name: {}, count: {}", detail.id, detail.name, detail.count) << std::endl;
      } else
          throw std::runtime_error("Wrong mode");
  }

  catch(const std::exception& e) {
      std::cerr << e.what() << std::endl;
  }
}