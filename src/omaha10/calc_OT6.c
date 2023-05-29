#include "omaha10.h"

int calc_OT6(const int* hands, const int* scenes, const int deck[52], const int ftrsz[5], char* json) {
  const int* h0 = hands;
  const int* h1 = hands + 5;
  const int* h2 = hands + 10;
  const int* h3 = hands + 15;
  const int* h4 = hands + 20;
  const int* h5 = hands + 25;

  int totl = 0;
  int wins[6] = { 0 };
  int ties[57] = { 0 };
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
            int h5r = eval_OT(deck[d0], deck[d1], deck[d2], deck[d3], deck[d4], h5[0], h5[1], h5[2], h5[3], h5[4]);
                                                                                                    // 6 choose 1 = 6
                 if(h0r <  h1r && h0r <  h2r && h0r <  h3r && h0r <  h4r && h0r <  h5r) ++wins[0];  // 0
            else if(h1r <  h0r && h1r <  h2r && h1r <  h3r && h1r <  h4r && h1r <  h5r) ++wins[1];  // 1
            else if(h2r <  h0r && h2r <  h1r && h2r <  h3r && h2r <  h4r && h2r <  h5r) ++wins[2];  // 2
            else if(h3r <  h0r && h3r <  h1r && h3r <  h2r && h3r <  h4r && h3r <  h5r) ++wins[3];  // 3
            else if(h4r <  h0r && h4r <  h1r && h4r <  h2r && h4r <  h3r && h4r <  h5r) ++wins[4];  // 4
            else if(h5r <  h0r && h5r <  h1r && h5r <  h2r && h5r <  h3r && h5r <  h4r) ++wins[5];  // 5
                                                                                                    // 6 choose 2 = 15
            else if(h0r == h1r && h0r <  h2r && h0r  < h3r && h0r <  h4r && h0r <  h5r) ++ties[0];  // 0 1
            else if(h0r == h2r && h0r <  h1r && h0r  < h3r && h0r <  h4r && h0r <  h5r) ++ties[1];  // 0 2
            else if(h0r == h3r && h0r <  h1r && h0r  < h2r && h0r <  h4r && h0r <  h5r) ++ties[2];  // 0 3
            else if(h0r == h4r && h0r <  h1r && h0r  < h2r && h0r <  h3r && h0r <  h5r) ++ties[3];  // 0 4
            else if(h0r == h5r && h0r <  h1r && h0r  < h2r && h0r <  h3r && h0r <  h4r) ++ties[4];  // 0 5
            else if(h1r == h2r && h1r <  h0r && h1r  < h3r && h1r <  h4r && h1r <  h5r) ++ties[5];  // 1 2
            else if(h1r == h3r && h1r <  h0r && h1r  < h2r && h1r <  h4r && h1r <  h5r) ++ties[6];  // 1 3
            else if(h1r == h4r && h1r <  h0r && h1r  < h2r && h1r <  h3r && h1r <  h5r) ++ties[7];  // 1 4
            else if(h1r == h5r && h1r <  h0r && h1r  < h2r && h1r <  h3r && h1r <  h4r) ++ties[8];  // 1 5
            else if(h2r == h3r && h2r <  h0r && h2r  < h1r && h2r <  h4r && h2r <  h5r) ++ties[9];  // 2 3
            else if(h2r == h4r && h2r <  h0r && h2r  < h1r && h2r <  h3r && h2r <  h5r) ++ties[10]; // 2 4
            else if(h2r == h5r && h2r <  h0r && h2r  < h1r && h2r <  h3r && h2r <  h4r) ++ties[11]; // 2 5
            else if(h3r == h4r && h3r <  h0r && h3r  < h1r && h3r <  h2r && h3r <  h5r) ++ties[12]; // 3 4
            else if(h3r == h5r && h3r <  h0r && h3r  < h1r && h3r <  h2r && h3r <  h4r) ++ties[13]; // 3 5
            else if(h4r == h5r && h4r <  h0r && h4r  < h1r && h4r <  h2r && h4r <  h3r) ++ties[14]; // 4 5
                                                                                                    // 6 choose 3 = 20
            else if(h0r == h1r && h0r == h2r && h0r  < h3r && h0r <  h4r && h0r <  h5r) ++ties[15]; // 0 1 2
            else if(h0r == h1r && h0r == h3r && h0r  < h2r && h0r <  h4r && h0r <  h5r) ++ties[16]; // 0 1 3
            else if(h0r == h1r && h0r == h4r && h0r  < h2r && h0r <  h3r && h0r <  h5r) ++ties[17]; // 0 1 4
            else if(h0r == h1r && h0r == h5r && h0r  < h2r && h0r <  h3r && h0r <  h4r) ++ties[18]; // 0 1 5
            else if(h0r == h2r && h0r == h3r && h0r  < h1r && h0r <  h4r && h0r <  h5r) ++ties[19]; // 0 2 3
            else if(h0r == h2r && h0r == h4r && h0r  < h1r && h0r <  h3r && h0r <  h5r) ++ties[20]; // 0 2 4
            else if(h0r == h2r && h0r == h5r && h0r  < h1r && h0r <  h3r && h0r <  h4r) ++ties[21]; // 0 2 5
            else if(h0r == h3r && h0r == h4r && h0r  < h1r && h0r <  h2r && h0r <  h5r) ++ties[22]; // 0 3 4
            else if(h0r == h3r && h0r == h5r && h0r  < h1r && h0r <  h2r && h0r <  h4r) ++ties[23]; // 0 3 5
            else if(h0r == h4r && h0r == h5r && h0r  < h1r && h0r <  h2r && h0r <  h3r) ++ties[24]; // 0 4 5
            else if(h1r == h2r && h1r == h3r && h1r  < h0r && h1r <  h4r && h1r <  h5r) ++ties[25]; // 1 2 3
            else if(h1r == h2r && h1r == h4r && h1r  < h0r && h1r <  h3r && h1r <  h5r) ++ties[26]; // 1 2 4
            else if(h1r == h2r && h1r == h5r && h1r  < h0r && h1r <  h3r && h1r <  h4r) ++ties[27]; // 1 2 5
            else if(h1r == h3r && h1r == h4r && h1r  < h0r && h1r <  h2r && h1r <  h5r) ++ties[28]; // 1 3 4
            else if(h1r == h3r && h1r == h5r && h1r  < h0r && h1r <  h2r && h1r <  h4r) ++ties[29]; // 1 3 5
            else if(h1r == h4r && h1r == h5r && h1r  < h0r && h1r <  h2r && h1r <  h3r) ++ties[30]; // 1 4 5
            else if(h2r == h3r && h2r == h4r && h2r  < h0r && h2r <  h1r && h2r <  h5r) ++ties[31]; // 2 3 4
            else if(h2r == h3r && h2r == h5r && h2r  < h0r && h2r <  h1r && h2r <  h4r) ++ties[32]; // 2 3 5
            else if(h2r == h4r && h2r == h5r && h2r  < h0r && h2r <  h1r && h2r <  h3r) ++ties[33]; // 2 4 5
            else if(h3r == h4r && h3r == h5r && h3r  < h0r && h3r <  h1r && h3r <  h2r) ++ties[34]; // 3 4 5
                                                                                                    // 6 choose 4 = 15
            else if(h0r == h1r && h0r == h2r && h0r == h3r && h0r <  h4r && h0r <  h5r) ++ties[35]; // 0 1 2 3
            else if(h0r == h1r && h0r == h2r && h0r == h4r && h0r <  h3r && h0r <  h5r) ++ties[36]; // 0 1 2 4
            else if(h0r == h1r && h0r == h2r && h0r == h5r && h0r <  h3r && h0r <  h4r) ++ties[37]; // 0 1 2 5
            else if(h0r == h1r && h0r == h3r && h0r == h4r && h0r <  h2r && h0r <  h5r) ++ties[38]; // 0 1 3 4
            else if(h0r == h1r && h0r == h3r && h0r == h5r && h0r <  h2r && h0r <  h4r) ++ties[39]; // 0 1 3 5
            else if(h0r == h1r && h0r == h4r && h0r == h5r && h0r <  h2r && h0r <  h3r) ++ties[40]; // 0 1 4 5
            else if(h0r == h2r && h0r == h3r && h0r == h4r && h0r <  h1r && h0r <  h5r) ++ties[41]; // 0 2 3 4
            else if(h0r == h2r && h0r == h3r && h0r == h5r && h0r <  h1r && h0r <  h4r) ++ties[42]; // 0 2 3 5
            else if(h0r == h2r && h0r == h4r && h0r == h5r && h0r <  h1r && h0r <  h3r) ++ties[43]; // 0 2 4 5
            else if(h0r == h3r && h0r == h4r && h0r == h5r && h0r <  h1r && h0r <  h2r) ++ties[44]; // 0 3 4 5
            else if(h1r == h2r && h1r == h3r && h1r == h4r && h1r <  h0r && h1r <  h5r) ++ties[45]; // 1 2 3 4
            else if(h1r == h2r && h1r == h3r && h1r == h5r && h1r <  h0r && h1r <  h4r) ++ties[46]; // 1 2 3 5
            else if(h1r == h2r && h1r == h4r && h1r == h5r && h1r <  h0r && h1r <  h3r) ++ties[47]; // 1 2 4 5
            else if(h1r == h3r && h1r == h4r && h1r == h5r && h1r <  h0r && h1r <  h2r) ++ties[48]; // 1 3 4 5
            else if(h2r == h3r && h2r == h4r && h2r == h5r && h2r <  h0r && h2r <  h1r) ++ties[49]; // 2 3 4 5
                                                                                                    // 6 choose 5 = 6
            else if(h0r == h1r && h0r == h2r && h0r == h3r && h0r == h4r && h0r <  h5r) ++ties[50]; // 0 1 2 3 4
            else if(h0r == h1r && h0r == h2r && h0r == h3r && h0r == h5r && h0r <  h4r) ++ties[51]; // 0 1 2 3 5
            else if(h0r == h1r && h0r == h2r && h0r == h4r && h0r == h5r && h0r <  h3r) ++ties[52]; // 0 1 2 4 5
            else if(h0r == h1r && h0r == h3r && h0r == h4r && h0r == h5r && h0r <  h2r) ++ties[53]; // 0 1 3 4 5
            else if(h0r == h2r && h0r == h3r && h0r == h4r && h0r == h5r && h0r <  h1r) ++ties[54]; // 0 2 3 4 5
            else if(h1r == h2r && h1r == h3r && h1r == h4r && h1r == h5r && h1r <  h0r) ++ties[55]; // 1 2 3 4 5
                                                                                                    // 6 choose 6 = 1
            else if(h0r == h1r && h0r == h2r && h0r == h3r && h0r == h4r && h0r == h5r) ++ties[56]; // 0 1 2 3 4 5
            else return eror(json, "calc_OT6 missed to process a ranking case");
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
        "{ 'scn': [ %d, %d, %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d, %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d, %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d, %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d, %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d, %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d, %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d, %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d, %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d, %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d, %d, %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d, %d, %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d, %d, %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d, %d, %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d, %d, %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d, %d, %d, %d ], 'cnt': %d },"
        "{ 'scn': [ %d, %d, %d, %d, %d, %d ], 'cnt': %d }"
      "]"
    "}",
    totl,
    scenes[0], wins[0],
    scenes[1], wins[1],
    scenes[2], wins[2],
    scenes[3], wins[3],
    scenes[4], wins[4],
    scenes[5], wins[5],
    scenes[0], scenes[1], ties[0],
    scenes[0], scenes[2], ties[1],
    scenes[0], scenes[3], ties[2],
    scenes[0], scenes[4], ties[3],
    scenes[0], scenes[5], ties[4],
    scenes[1], scenes[2], ties[5],
    scenes[1], scenes[3], ties[6],
    scenes[1], scenes[4], ties[7],
    scenes[1], scenes[5], ties[8],
    scenes[2], scenes[3], ties[9],
    scenes[2], scenes[4], ties[10],
    scenes[2], scenes[5], ties[11],
    scenes[3], scenes[4], ties[12],
    scenes[3], scenes[5], ties[13],
    scenes[4], scenes[5], ties[14],
    scenes[0], scenes[1], scenes[2], ties[15],
    scenes[0], scenes[1], scenes[3], ties[16],
    scenes[0], scenes[1], scenes[4], ties[17],
    scenes[0], scenes[1], scenes[5], ties[18],
    scenes[0], scenes[2], scenes[3], ties[19],
    scenes[0], scenes[2], scenes[4], ties[20],
    scenes[0], scenes[2], scenes[5], ties[21],
    scenes[0], scenes[3], scenes[4], ties[22],
    scenes[0], scenes[3], scenes[5], ties[23],
    scenes[0], scenes[4], scenes[5], ties[24],
    scenes[1], scenes[2], scenes[3], ties[25],
    scenes[1], scenes[2], scenes[4], ties[26],
    scenes[1], scenes[2], scenes[5], ties[27],
    scenes[1], scenes[3], scenes[4], ties[28],
    scenes[1], scenes[3], scenes[5], ties[29],
    scenes[1], scenes[4], scenes[5], ties[30],
    scenes[2], scenes[3], scenes[4], ties[31],
    scenes[2], scenes[3], scenes[5], ties[32],
    scenes[2], scenes[4], scenes[5], ties[33],
    scenes[3], scenes[4], scenes[5], ties[34],
    scenes[0], scenes[1], scenes[2], scenes[3], ties[35],
    scenes[0], scenes[1], scenes[2], scenes[4], ties[36],
    scenes[0], scenes[1], scenes[2], scenes[5], ties[37],
    scenes[0], scenes[1], scenes[3], scenes[4], ties[38],
    scenes[0], scenes[1], scenes[3], scenes[5], ties[39],
    scenes[0], scenes[1], scenes[4], scenes[5], ties[40],
    scenes[0], scenes[2], scenes[3], scenes[4], ties[41],
    scenes[0], scenes[2], scenes[3], scenes[5], ties[42],
    scenes[0], scenes[2], scenes[4], scenes[5], ties[43],
    scenes[0], scenes[3], scenes[4], scenes[5], ties[44],
    scenes[1], scenes[2], scenes[3], scenes[4], ties[45],
    scenes[1], scenes[2], scenes[3], scenes[5], ties[46],
    scenes[1], scenes[2], scenes[4], scenes[5], ties[47],
    scenes[1], scenes[3], scenes[4], scenes[5], ties[48],
    scenes[2], scenes[3], scenes[4], scenes[5], ties[49],
    scenes[0], scenes[1], scenes[2], scenes[3], scenes[4], ties[50],
    scenes[0], scenes[1], scenes[2], scenes[3], scenes[5], ties[51],
    scenes[0], scenes[1], scenes[2], scenes[4], scenes[5], ties[52],
    scenes[0], scenes[1], scenes[3], scenes[4], scenes[5], ties[53],
    scenes[0], scenes[2], scenes[3], scenes[4], scenes[5], ties[54],
    scenes[1], scenes[2], scenes[3], scenes[4], scenes[5], ties[55],
    scenes[0], scenes[1], scenes[2], scenes[3], scenes[4], scenes[5], ties[56]
  );
  repl(json);
  return 0;
}
