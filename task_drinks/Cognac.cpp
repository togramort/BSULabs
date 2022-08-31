#include "Cognac.h"

Cognac::Cognac(const std::string &name, double volume, double degree, Grade grades) : Booze(name, volume, degree) {
  grades_ = grades;
}

std::string Cognac::getGrades() const {
  switch (grades_) {
    case Grade::VS:return "VS";
    case Grade::Superior:return "Superior";
    case Grade::VSOP:return "VSOP";
    case Grade::VVSOP:return "VVSOP";
    case Grade::XO:return "XO";
  }
}