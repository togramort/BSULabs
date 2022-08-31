#ifndef DAD_MUM__SAY_H_
#define DAD_MUM__SAY_H_
#include <string>

class Say {
 public:
  Say(int ms, int n, std::string word);
  void say();
  static int cur_amount;
  static int max_amount;

 private:
  int ms_, n_;
  std::string word_;
};

#endif //DAD_MUM__SAY_H_
