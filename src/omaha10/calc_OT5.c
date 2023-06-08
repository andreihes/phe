#include "omaha10.h"

int calc_OT5(const int* hands, const int* scenes, const int deck[52], const int ftrsz[5], char* json) {
  const int* h0 = hands;
  const int* h1 = hands + 5;
  const int* h2 = hands + 10;
  const int* h3 = hands + 15;
  const int* h4 = hands + 20;

  int totl = 0;
  int wins[5] = { 0 };
  int ties[26] = { 0 };
  for(int d0 = 0; d0 < ftrsz[0]; ++d0) {
    for(int d1 = d0 + 1; d1 < ftrsz[1]; ++d1) {
      for(int d2 = d1 + 1; d2 < ftrsz[2]; ++d2) {
        for(int d3 = d2 + 1; d3 < ftrsz[3]; ++d3) {
          for(int d4 = d3 + 1; d4 < ftrsz[4]; ++d4) {
            ++totl;
            int h0r = eval_OT(deck[d0], deck[d1], deck[d2], deck[d3], deck[d4], h0[0], h0[1], h0[2], h0[3], h0[4]);
            int h1r = eval_OT(deck[d0], deck[d1], deck[d2], deck[d3], deck[d4], h1[0], h1[1], h1[2], h1[3], h1[4]);
            int h2r = eval_OT(deck[d0], deck[d1], deck[d2], deck[d3], deck[d4], h2[0], h2[1], h2[2], h2[3], h2[4]);
            int h3r = eval_OT(deck[d0], deck[d1], deck[d2], deck[d3], deck[d4], h3[0], h3[1], h3[2], h3[3], h3[4]);
            int h4r = eval_OT(deck[d0], deck[d1], deck[d2], deck[d3], deck[d4], h4[0], h4[1], h4[2], h4[3], h4[4]);
                                                                                      // 5 choose 1 = 5
                 if(h0r <  h1r && h0r <  h2r && h0r <  h3r && h0r <  h4r) ++wins[0];  // 0
            else if(h1r <  h0r && h1r <  h2r && h1r <  h3r && h1r <  h4r) ++wins[1];  // 1
            else if(h2r <  h0r && h2r <  h1r && h2r <  h3r && h2r <  h4r) ++wins[2];  // 2
            else if(h3r <  h0r && h3r <  h1r && h3r <  h2r && h3r <  h4r) ++wins[3];  // 3
            else if(h4r <  h0r && h4r <  h1r && h4r <  h2r && h4r <  h3r) ++wins[4];  // 4
                                                                                      // 5 choose 2 = 10
            else if(h0r == h1r && h0r <  h2r && h0r  < h3r && h0r <  h4r) ++ties[0];  // 0 1
            else if(h0r == h2r && h0r <  h1r && h0r  < h3r && h0r <  h4r) ++ties[1];  // 0 2
            else if(h0r == h3r && h0r <  h1r && h0r  < h2r && h0r <  h4r) ++ties[2];  // 0 3
            else if(h0r == h4r && h0r <  h1r && h0r  < h2r && h0r <  h3r) ++ties[3];  // 0 4
            else if(h1r == h2r && h1r <  h0r && h1r  < h3r && h1r <  h4r) ++ties[4];  // 1 2
            else if(h1r == h3r && h1r <  h0r && h1r  < h2r && h1r <  h4r) ++ties[5];  // 1 3
            else if(h1r == h4r && h1r <  h0r && h1r  < h2r && h1r <  h3r) ++ties[6];  // 1 4
            else if(h2r == h3r && h2r <  h0r && h2r  < h1r && h2r <  h4r) ++ties[7];  // 2 3
            else if(h2r == h4r && h2r <  h0r && h2r  < h1r && h2r <  h3r) ++ties[8];  // 2 4
            else if(h3r == h4r && h3r <  h0r && h3r  < h1r && h3r <  h2r) ++ties[9];  // 3 4
                                                                                      // 5 choose 3 = 10
            else if(h0r == h1r && h0r == h2r && h0r  < h3r && h0r <  h4r) ++ties[10]; // 0 1 2
            else if(h0r == h1r && h0r == h3r && h0r  < h2r && h0r <  h4r) ++ties[11]; // 0 1 3
            else if(h0r == h1r && h0r == h4r && h0r  < h2r && h0r <  h3r) ++ties[12]; // 0 1 4
            else if(h0r == h2r && h0r == h3r && h0r  < h1r && h0r <  h4r) ++ties[13]; // 0 2 3
            else if(h0r == h2r && h0r == h4r && h0r  < h1r && h0r <  h3r) ++ties[14]; // 0 2 4
            else if(h0r == h3r && h0r == h4r && h0r  < h1r && h0r <  h2r) ++ties[15]; // 0 3 4
            else if(h1r == h2r && h1r == h3r && h1r  < h0r && h1r <  h4r) ++ties[16]; // 1 2 3
            else if(h1r == h2r && h1r == h4r && h1r  < h0r && h1r <  h3r) ++ties[17]; // 1 2 4
            else if(h1r == h3r && h1r == h4r && h1r  < h0r && h1r <  h2r) ++ties[18]; // 1 3 4
            else if(h2r == h3r && h2r == h4r && h2r  < h0r && h2r <  h1r) ++ties[19]; // 2 3 4
                                                                                      // 5 choose 4 = 5
            else if(h0r == h1r && h0r == h2r && h0r == h3r && h0r <  h4r) ++ties[20]; // 0 1 2 3
            else if(h0r == h1r && h0r == h2r && h0r == h4r && h0r <  h3r) ++ties[21]; // 0 1 2 4
            else if(h0r == h1r && h0r == h3r && h0r == h4r && h0r <  h2r) ++ties[22]; // 0 1 3 4
            else if(h0r == h2r && h0r == h3r && h0r == h4r && h0r <  h1r) ++ties[23]; // 0 2 3 4
            else if(h1r == h2r && h1r == h3r && h1r == h4r && h1r <  h0r) ++ties[24]; // 1 2 3 4
                                                                                      // 5 choose 5 = 1
            else if(h0r == h1r && h0r == h2r && h0r == h3r && h0r == h4r) ++ties[25]; // 0 1 2 3 4
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
        "{ 'scn': %d, 'cnt': %d },"
        "{ 'scn': %d, 'cnt': %d },"
        "{ 'scn': %d, 'cnt': %d },"
        "{ 'scn': %d, 'cnt': %d },"
        "{ 'scn': %d, 'cnt': %d }"
      "],"
      "'ties':"
      "["
        "{ 'scn': [ %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d, %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d, %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d, %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d, %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d, %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d, %d, %d, %d ], 'cnt': %d }"
      "]"
    "}",
    totl,
    scenes[0], wins[0],
    scenes[1], wins[1],
    scenes[2], wins[2],
    scenes[3], wins[3],
    scenes[4], wins[4],
    scenes[0], scenes[1], ties[0],
    scenes[0], scenes[2], ties[1],
    scenes[0], scenes[3], ties[2],
    scenes[0], scenes[4], ties[3],
    scenes[1], scenes[2], ties[4],
    scenes[1], scenes[3], ties[5],
    scenes[1], scenes[4], ties[6],
    scenes[2], scenes[3], ties[7],
    scenes[2], scenes[4], ties[8],
    scenes[3], scenes[4], ties[9],
    scenes[0], scenes[1], scenes[2], ties[10],
    scenes[0], scenes[1], scenes[3], ties[11],
    scenes[0], scenes[1], scenes[4], ties[12],
    scenes[0], scenes[2], scenes[3], ties[13],
    scenes[0], scenes[2], scenes[4], ties[14],
    scenes[0], scenes[3], scenes[4], ties[15],
    scenes[1], scenes[2], scenes[3], ties[16],
    scenes[1], scenes[2], scenes[4], ties[17],
    scenes[1], scenes[3], scenes[4], ties[18],
    scenes[2], scenes[3], scenes[4], ties[19],
    scenes[0], scenes[1], scenes[2], scenes[3], ties[20],
    scenes[0], scenes[1], scenes[2], scenes[4], ties[21],
    scenes[0], scenes[1], scenes[3], scenes[4], ties[22],
    scenes[0], scenes[2], scenes[3], scenes[4], ties[23],
    scenes[1], scenes[2], scenes[3], scenes[4], ties[24],
    scenes[0], scenes[1], scenes[2], scenes[3], scenes[4], ties[25]
  );
  repl(json);
  return 0;
}
