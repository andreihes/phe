#include "omaha10.h"

// eval omaha 5 cards using omaha 4 cards
// brute force, no optimizations and etc.
int eval_OT(const int b1, const int b2, const int b3, const int b4, const int b5, const int h1, const int h2, const int h3, const int h4, const int h5)
{
  // run eval for all possible hand cards combos
  int no1 = evaluate_omaha_cards(b1, b2, b3, b4, b5, h1, h2, h3, h4);
  int no2 = evaluate_omaha_cards(b1, b2, b3, b4, b5, h1, h2, h3, h5);
  int no3 = evaluate_omaha_cards(b1, b2, b3, b4, b5, h1, h2, h4, h5);
  int no4 = evaluate_omaha_cards(b1, b2, b3, b4, b5, h1, h3, h4, h5);
  int no5 = evaluate_omaha_cards(b1, b2, b3, b4, b5, h2, h3, h4, h5);

  // and pick a minimum
  if(no1 > no2) no1 = no2;
  if(no1 > no3) no1 = no3;
  if(no1 > no4) no1 = no4;
  if(no1 > no5) no1 = no5;

  // this is a final rank
  return no1;
}
