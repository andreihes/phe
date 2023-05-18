#include "omaha10.h"

int calc_OT2(const int h1[5], const int h2[5], const int deck[52], const int ftrsz[5], char* json) {
  int totl = 0;
  int wins[2] = { 0, 0 };
  int ties[1] = { 0 };
  for(int d1 = 0; d1 < ftrsz[0]; ++d1) {
    for(int d2 = d1 + 1; d2 < ftrsz[1]; ++d2) {
      for(int d3 = d2 + 1; d3 < ftrsz[2]; ++d3) {
        for(int d4 = d3 + 1; d4 < ftrsz[3]; ++d4) {
          for(int d5 = d4 + 1; d5 < ftrsz[4]; ++d5) {
            ++totl;
            int h1r = eval_OT(deck[d1], deck[d2], deck[d3], deck[d4], deck[d5], h1[0], h1[1], h1[2], h1[3], h1[4]);
            int h2r = eval_OT(deck[d1], deck[d2], deck[d3], deck[d4], deck[d5], h2[0], h2[1], h2[2], h2[3], h2[4]);
                                           // 2 choose 1 = 2
                 if(h1r <  h2r) ++wins[0]; // h1
            else if(h2r <  h1r) ++wins[1]; // h2
                                           // 2 choose 2 = 1
            else if(h1r == h2r) ++ties[0]; // h1 h2
            else return eror(json, "calc_OT2 missed to process a ranking case");
          }
        }
      }
    }
  }

  int vrfy = 0;
  for(int idx = 0; idx < sizeof(wins) / sizeof(int); idx++) {
    vrfy += wins[idx];
  }
  for(int idx = 0; idx < sizeof(ties) / sizeof(int); idx++) {
    vrfy += ties[idx];
  }
  if(totl != vrfy) {
    return eror(json, "calc_OT2 wins + ties != totl");
  }

  sprintf
  (
    json,
    "{"
      "'eror': false,"
      "'totl': %d,"
      "'wins':"
      "["
        "{ 'arg': 'h1', 'idx': 0, 'ids': [ %d, %d, %d, %d, %d ], 'cnt': %d },"
        "{ 'arg': 'h2', 'idx': 1, 'ids': [ %d, %d, %d, %d, %d ], 'cnt': %d }"
      "],"
      "'ties':"
      "["
        "{ 'arg': [ 'h1', 'h2' ], 'idx': [ 0, 1 ], 'cnt': %d }"
      "]"
    "}",
    totl,
    h1[0], h1[1], h1[2], h1[3], h1[4], wins[0],
    h2[0], h2[1], h2[2], h2[3], h2[4], wins[1],
    ties[0]
  );
  repl(json);
  return 0;
}
