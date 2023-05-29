#include "omaha10.h"

// eval omaha 5 cards using omaha 4 cards
// brute force, no optimizations and etc.
int eval_OT(const int b0, const int b1, const int b2, const int b3, const int b4, const int h0, const int h1, const int h2, const int h3, const int h4)
{
  // run eval for all possible hand cards combos
  int no0 = evaluate_omaha_cards(b0, b1, b2, b3, b4, h1, h2, h3, h4);
  int no1 = evaluate_omaha_cards(b0, b1, b2, b3, b4, h0, h2, h3, h4);
  int no2 = evaluate_omaha_cards(b0, b1, b2, b3, b4, h0, h1, h3, h4);
  int no3 = evaluate_omaha_cards(b0, b1, b2, b3, b4, h0, h1, h2, h4);
  int no4 = evaluate_omaha_cards(b0, b1, b2, b3, b4, h0, h1, h2, h3);

  // and pick a minimum
  if(no0 > no1) no0 = no1;
  if(no0 > no2) no0 = no2;
  if(no0 > no3) no0 = no3;
  if(no0 > no4) no0 = no4;

  // this is a final rank
  return no0;
}
