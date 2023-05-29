#include "omaha10.h"

int calc_OT2(const int* hands, const int* scenes, const int deck[52], const int ftrsz[5], char* json) {
  const int* h0 = hands;
  const int* h1 = hands + 5;

  int totl = 0;
  int wins[2] = { 0 };
  int ties[1] = { 0 };
  for(int d0 = 0; d0 < ftrsz[0]; ++d0) {
    for(int d1 = d0 + 1; d1 < ftrsz[1]; ++d1) {
      for(int d2 = d1 + 1; d2 < ftrsz[2]; ++d2) {
        for(int d3 = d2 + 1; d3 < ftrsz[3]; ++d3) {
          for(int d4 = d3 + 1; d4 < ftrsz[4]; ++d4) {
            ++totl;
            int h0r = eval_OT(deck[d0], deck[d1], deck[d2], deck[d3], deck[d4], h0[0], h0[1], h0[2], h0[3], h0[4]);
            int h1r = eval_OT(deck[d0], deck[d1], deck[d2], deck[d3], deck[d4], h1[0], h1[1], h1[2], h1[3], h1[4]);
                                           // 2 choose 1 = 2
                 if(h0r <  h1r) ++wins[0]; // 0
            else if(h1r <  h0r) ++wins[1]; // 1
                                           // 2 choose 2 = 1
            else if(h0r == h1r) ++ties[0]; // 0 1
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
        "{ 'scn': %d, 'cnt': %d },"
        "{ 'scn': %d, 'cnt': %d }"
      "],"
      "'ties':"
      "["
        "{ 'scn': [ %d, %d ], 'cnt': %d }"
      "]"
    "}",
    totl,
    scenes[0], wins[0],
    scenes[1], wins[1],
    scenes[0], scenes[1], ties[0]
  );
  repl(json);
  return 0;
}
