#include "Beer.h"

Beer::Beer(const std::string &name, double volume, double degree, Raw raw) : Booze(name, volume, degree) {
  raw_ = raw;
}

std::string Beer::getRaw() const {
  switch (raw_) {
    case Raw::barley:return "barley";
    case Raw::wheat:return "wheat";
    case Raw::ginger:return "ginger";

  }
}