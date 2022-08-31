//
// Created by gmm41414 on 28.10.2020.
//

#ifndef OOP__AWESOME_POINT_H_
#define OOP__AWESOME_POINT_H_

class AwesomePoint {
 public:
  AwesomePoint() {}
  AwesomePoint(double x, double y) {
    //this->x = x;
    //this->y = y;
    y_ = y;
    x_ = x;

  }

  void SetX(double x) {
    if (std::abs(x) >= 1E6) {
      std::cerr << "imprecise calculation is possible";
    }
    this->x = x;

    //double getx void sety  !!!!!!!!!

    ConvertToPolar()
  }
 private:
  double x_, y_;
};

#endif //OOP__AWESOME_POINT_H_
