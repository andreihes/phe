#include "omaha10.h"

int calc_OT5(const int h1[5], const int h2[5], const int h3[5], const int h4[5], const int h5[5], const int deck[52], const int ftrsz[5], char* json) {
  int totl = 0;
  int wins[5] = { 0, 0, 0, 0, 0 };
  int ties[26] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  for(int d1 = 0; d1 < ftrsz[0]; ++d1) {
    for(int d2 = d1 + 1; d2 < ftrsz[1]; ++d2) {
      for(int d3 = d2 + 1; d3 < ftrsz[2]; ++d3) {
        for(int d4 = d3 + 1; d4 < ftrsz[3]; ++d4) {
          for(int d5 = d4 + 1; d5 < ftrsz[4]; ++d5) {
            ++totl;
            int h1r = eval_OT(deck[d1], deck[d2], deck[d3], deck[d4], deck[d5], h1[0], h1[1], h1[2], h1[3], h1[4]);
            int h2r = eval_OT(deck[d1], deck[d2], deck[d3], deck[d4], deck[d5], h2[0], h2[1], h2[2], h2[3], h2[4]);
            int h3r = eval_OT(deck[d1], deck[d2], deck[d3], deck[d4], deck[d5], h3[0], h3[1], h3[2], h3[3], h3[4]);
            int h4r = eval_OT(deck[d1], deck[d2], deck[d3], deck[d4], deck[d5], h4[0], h4[1], h4[2], h4[3], h4[4]);
            int h5r = eval_OT(deck[d1], deck[d2], deck[d3], deck[d4], deck[d5], h5[0], h5[1], h5[2], h5[3], h5[4]);
                                                                                      // 5 choose 1 = 5
                 if(h1r <  h2r && h1r <  h3r && h1r <  h4r && h1r <  h5r) ++wins[0];  // h1
            else if(h2r <  h1r && h2r <  h3r && h2r <  h4r && h2r <  h5r) ++wins[1];  // h2
            else if(h3r <  h1r && h3r <  h2r && h3r <  h4r && h3r <  h5r) ++wins[2];  // h3
            else if(h4r <  h1r && h4r <  h2r && h4r <  h3r && h4r <  h5r) ++wins[3];  // h4
            else if(h5r <  h1r && h5r <  h2r && h5r <  h3r && h5r <  h4r) ++wins[4];  // h5
                                                                                      // 5 choose 2 = 10
            else if(h1r == h2r && h1r <  h3r && h1r  < h4r && h1r <  h5r) ++ties[0];  // h1 h2
            else if(h1r == h3r && h1r <  h2r && h1r  < h4r && h1r <  h5r) ++ties[1];  // h1 h3
            else if(h1r == h4r && h1r <  h2r && h1r  < h3r && h1r <  h5r) ++ties[2];  // h1 h4
            else if(h1r == h5r && h1r <  h2r && h1r  < h3r && h1r <  h4r) ++ties[3];  // h1 h5
            else if(h2r == h3r && h2r <  h1r && h2r  < h4r && h2r <  h5r) ++ties[4];  // h2 h3
            else if(h2r == h4r && h2r <  h1r && h2r  < h3r && h2r <  h5r) ++ties[5];  // h2 h4
            else if(h2r == h5r && h2r <  h1r && h2r  < h3r && h2r <  h4r) ++ties[6];  // h2 h5
            else if(h3r == h4r && h3r <  h1r && h3r  < h2r && h3r <  h5r) ++ties[7];  // h3 h4
            else if(h3r == h5r && h3r <  h1r && h3r  < h2r && h3r <  h4r) ++ties[8];  // h3 h5
            else if(h4r == h5r && h4r <  h1r && h4r  < h2r && h4r <  h3r) ++ties[9];  // h4 h5
                                                                                      // 5 choose 3 = 10
            else if(h1r == h2r && h1r == h3r && h1r  < h4r && h1r <  h5r) ++ties[10]; // h1 h2 h3
            else if(h1r == h2r && h1r == h4r && h1r  < h3r && h1r <  h5r) ++ties[11]; // h1 h2 h4
            else if(h1r == h2r && h1r == h5r && h1r  < h3r && h1r <  h4r) ++ties[12]; // h1 h2 h5
            else if(h1r == h3r && h1r == h4r && h1r  < h2r && h1r <  h5r) ++ties[13]; // h1 h3 h4
            else if(h1r == h3r && h1r == h5r && h1r  < h2r && h1r <  h4r) ++ties[14]; // h1 h3 h5
            else if(h1r == h4r && h1r == h5r && h1r  < h2r && h1r <  h3r) ++ties[15]; // h1 h4 h5
            else if(h2r == h3r && h2r == h4r && h2r  < h1r && h2r <  h5r) ++ties[16]; // h2 h3 h4
            else if(h2r == h3r && h2r == h5r && h2r  < h1r && h2r <  h4r) ++ties[17]; // h2 h3 h5
            else if(h2r == h4r && h2r == h5r && h2r  < h1r && h2r <  h3r) ++ties[18]; // h2 h4 h5
            else if(h3r == h4r && h3r == h5r && h3r  < h1r && h3r <  h2r) ++ties[19]; // h3 h4 h5
                                                                                      // 5 choose 4 = 5
            else if(h1r == h2r && h1r == h3r && h1r == h4r && h1r <  h5r) ++ties[20]; // h1 h2 h3 h4
            else if(h1r == h2r && h1r == h3r && h1r == h5r && h1r <  h4r) ++ties[21]; // h1 h2 h3 h5
            else if(h1r == h2r && h1r == h4r && h1r == h5r && h1r <  h3r) ++ties[22]; // h1 h2 h4 h5
            else if(h1r == h3r && h1r == h4r && h1r == h5r && h1r <  h2r) ++ties[23]; // h1 h3 h4 h5
            else if(h2r == h3r && h2r == h4r && h2r == h5r && h2r <  h1r) ++ties[24]; // h2 h3 h4 h5
                                                                                      // 5 choose 5 = 1
            else if(h1r == h2r && h1r == h3r && h1r == h4r && h1r == h5r) ++ties[25]; // h1 h2 h3 h4 h5
            else return eror(json, "calc_OT5 missed to process a ranking case");
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
    return eror(json, "calc_OT5 wins + ties != totl");
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
        "{ 'arg': 'h2', 'idx': 1, 'ids': [ %d, %d, %d, %d, %d ], 'cnt': %d },"
        "{ 'arg': 'h3', 'idx': 2, 'ids': [ %d, %d, %d, %d, %d ], 'cnt': %d },"
        "{ 'arg': 'h4', 'idx': 3, 'ids': [ %d, %d, %d, %d, %d ], 'cnt': %d },"
        "{ 'arg': 'h5', 'idx': 4, 'ids': [ %d, %d, %d, %d, %d ], 'cnt': %d }"
      "],"
      "'ties':"
      "["
        "{ 'arg': [ 'h1', 'h2' ], 'idx': [ 0, 1 ], 'cnt': %d },"
        "{ 'arg': [ 'h1', 'h3' ], 'idx': [ 0, 2 ], 'cnt': %d },"
        "{ 'arg': [ 'h1', 'h4' ], 'idx': [ 0, 3 ], 'cnt': %d },"
        "{ 'arg': [ 'h1', 'h5' ], 'idx': [ 0, 4 ], 'cnt': %d },"
        "{ 'arg': [ 'h2', 'h3' ], 'idx': [ 1, 2 ], 'cnt': %d },"
        "{ 'arg': [ 'h2', 'h4' ], 'idx': [ 1, 3 ], 'cnt': %d },"
        "{ 'arg': [ 'h2', 'h5' ], 'idx': [ 1, 4 ], 'cnt': %d },"
        "{ 'arg': [ 'h3', 'h4' ], 'idx': [ 2, 3 ], 'cnt': %d },"
        "{ 'arg': [ 'h3', 'h5' ], 'idx': [ 2, 4 ], 'cnt': %d },"
        "{ 'arg': [ 'h4', 'h5' ], 'idx': [ 3, 4 ], 'cnt': %d },"
        "{ 'arg': [ 'h1', 'h2', 'h3' ], 'idx': [ 0, 1, 2 ], 'cnt': %d },"
        "{ 'arg': [ 'h1', 'h2', 'h4' ], 'idx': [ 0, 1, 3 ], 'cnt': %d },"
        "{ 'arg': [ 'h1', 'h2', 'h5' ], 'idx': [ 0, 1, 4 ], 'cnt': %d },"
        "{ 'arg': [ 'h1', 'h3', 'h4' ], 'idx': [ 0, 2, 3 ], 'cnt': %d },"
        "{ 'arg': [ 'h1', 'h3', 'h5' ], 'idx': [ 0, 2, 4 ], 'cnt': %d },"
        "{ 'arg': [ 'h1', 'h4', 'h5' ], 'idx': [ 0, 3, 4 ], 'cnt': %d },"
        "{ 'arg': [ 'h2', 'h3', 'h4' ], 'idx': [ 1, 2, 3 ], 'cnt': %d },"
        "{ 'arg': [ 'h2', 'h3', 'h5' ], 'idx': [ 1, 2, 4 ], 'cnt': %d },"
        "{ 'arg': [ 'h2', 'h4', 'h5' ], 'idx': [ 1, 3, 4 ], 'cnt': %d },"
        "{ 'arg': [ 'h3', 'h4', 'h5' ], 'idx': [ 2, 3, 4 ], 'cnt': %d },"
        "{ 'arg': [ 'h1', 'h2', 'h3', 'h4' ], 'idx': [ 0, 1, 2, 3 ], 'cnt': %d },"
        "{ 'arg': [ 'h1', 'h2', 'h3', 'h5' ], 'idx': [ 0, 1, 2, 4 ], 'cnt': %d },"
        "{ 'arg': [ 'h1', 'h2', 'h4', 'h5' ], 'idx': [ 0, 1, 3, 4 ], 'cnt': %d },"
        "{ 'arg': [ 'h1', 'h3', 'h4', 'h5' ], 'idx': [ 0, 2, 3, 4 ], 'cnt': %d },"
        "{ 'arg': [ 'h2', 'h3', 'h4', 'h5' ], 'idx': [ 1, 2, 3, 4 ], 'cnt': %d },"
        "{ 'arg': [ 'h1', 'h2', 'h3', 'h4', 'h5' ], 'idx': [ 0, 1, 2, 3, 4 ], 'cnt': %d }"
      "]"
    "}",
    totl,
    h1[0], h1[1], h1[2], h1[3], h1[4], wins[0],
    h2[0], h2[1], h2[2], h2[3], h2[4], wins[1],
    h3[0], h3[1], h3[2], h3[3], h3[4], wins[2],
    h4[0], h4[1], h4[2], h4[3], h4[4], wins[3],
    h5[0], h5[1], h5[2], h5[3], h5[4], wins[4],
    ties[0], ties[1], ties[2], ties[3], ties[4], ties[5],
    ties[6], ties[7], ties[8], ties[9], ties[10], 
    ties[11], ties[12], ties[13], ties[14], ties[15],
    ties[16], ties[17], ties[18], ties[19], ties[20],
    ties[21], ties[22], ties[23], ties[24], ties[25]
  );
  repl(json);
  return 0;
}
