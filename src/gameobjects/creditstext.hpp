#ifndef CREDITSTEXT_H
#define CREDITSTEXT_H
#include "text.hpp"

class CreditsText : public GameObject {
 public:
  CreditsText();
  virtual ~CreditsText();

  void Draw();
  void Update();

 private:
  vector<Text*> lines;
};

#endif /* CREDITSTEXT_H */
