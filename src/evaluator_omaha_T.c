#include <stdio.h>
#include <stdarg.h>

int test(const int hands[][5], const int hc) {
  for(int hidx = 0; hidx < hc; hidx++) {
    printf("HAND #%02d:", hidx);
    for(int cidx = 0; cidx < 5; cidx++) {
      printf(" %02d", hands[hidx][cidx]);
    }
    printf("\n");
  }
  return 0;
}

// calculate omaha ten odds
// hands: array of hands 5 cards each
//    hc: hand count, must be 2-6
// board: 5 board cards: flop, turn, river (-1 means no card)
//  dead: up to 52 dead cards
//  json: string buffer to get the results as a serialized JSON string
int calc_OT(const int hands[][5], const int hc, const int board[5], const int dead[52], char* json) {
  // create and init a full deck
  int deck[52];
  int expect = 52;
  int decksz = init(deck);
  if(expect != decksz) return eror(json, "deck init failed");

  // kick all hands cards from deck
  for(int idx = 0; idx < hc; idx++) {
    expect -= 5;
    decksz = kick(deck, decksz, hands[idx], 5);
    if(expect != decksz) return eror(json, "some hand contains dups or bad cards");
  }

  // kick flop cards if any
  int hasf = 0;
  if(board[0] != -1 || board[1] != -1 || board[2] != -1) {
    hasf = 1;
    expect -= 3;
    decksz = kick(deck, decksz, board, 3);
    if(expect != decksz) return eror(json, "board flop contains dups or bad cards");
  }

  // kick turn card if any
  int hast = 0;
  if(board[3] != -1) {
    if(!hasf) {
      return eror(json, "there is no flop but turn exists");
    }
    hast = 1;
    expect -= 1;
    decksz = kick(deck, decksz, board + 3, 1);
    if(expect != decksz) return eror(json, "board turn contains dups or bad cards");
  }

  // kick river card if any
  int hasr = 0;
  if(board[4] != -1) {
    if(!hast) {
      return eror(json, "there is no turn but river exists");
    }
    hasr = 1;
    expect -= 1;
    decksz = kick(deck, decksz, board + 4, 1);
    if(expect != decksz) eror(json, "board river contains dups or bad cards");
  }

  // kick dead cards if any
  for(int idx = 0; idx < 52; idx++) {
    if(dead[idx] == -1) {
      continue;
    }
    expect -= 1;
    decksz = kick(deck, decksz, dead + idx, 1);
    if(expect != decksz) eror(json, "dead list contains dups or bad cards");
  }

  // prepend flop-turn-river in front of the deck
  if(hasr) {
    decksz = push(deck, decksz, board[4]);
  }

  if(hast) {
    decksz = push(deck, decksz, board[3]);
  }

  if(hasf) {
    decksz = push(deck, decksz, board[2]);
    decksz = push(deck, decksz, board[1]);
    decksz = push(deck, decksz, board[0]);
  }

  int f1sz = hasf ? 1 : decksz;
  int f2sz = hasf ? 2 : decksz;
  int f3sz = hasf ? 3 : decksz;
  int tsz = hast ? 4 : decksz;
  int rsz = hasr ? 5 : decksz;
  switch(hc) {
    case 2:
      return calc_OT2(hands[0], hands[1], deck, f1sz, f2sz, f3sz, tsz, rsz, json);
    case 3:
      return calc_OT3(hands[0], hands[1], hands[2], deck, f1sz, f2sz, f3sz, tsz, rsz, json);
    case 4:
      return eror(json, "4 hands not implemented");
    case 5:
      return eror(json, "5 hands not implemented");
    case 6:
      return eror(json, "6 hands not implemented");
    default:
      return eror(json, "hand count must be min 2 and max 6");
  }
}

// init 52 cards deck
int init(int deck[52]) {
  for(int card = 0; card < 52; card++) {
    deck[card] = card;
  }
  return 52;
}

// move dead cards away from the deck returning a new deck size
int kick(int deck[52], int decksz, const int* dead, const int deadsz) {
  for(int deadidx = 0; deadidx < deadsz; deadidx++) {
    for(int deckidx = 0; deckidx < decksz; deckidx++) {
      if(deck[deckidx] == dead[deadidx]) {
        --decksz;
        deck[deckidx] = deck[decksz];
        break;
      }
    }
  }
  return decksz;
}

// push card into position 0 into deck
int push(int deck[52], int decksz, int card) {
  for(int idx = decksz; idx > 0; idx--) {
    deck[idx] = deck[idx - 1];
  }
  deck[0] = card;
  return decksz + 1;
}

// populate a JSON object and an error exit code
int eror(char* json, const char* msg)
{
  sprintf(json, "{ \"eror\": true, \"msg\": \"%s\" }", msg);
  return 1;
}

// eval omaha 5 cards using omaha 4 cards
// brute force, no optimizations and etc.
int eval_OT(const int b1, const int b2, const int b3, const int b4, const int b5,
            const int h1, const int h2, const int h3, const int h4, const int h5)
{
  printf("[eval_OT]: board = %02d %02d %02d %02d %02d\n", b1, b2, b3, b4, b5);
  printf("[eval_OT]:  hand = %02d %02d %02d %02d %02d\n", h1, h2, h3, h4, h5);

  // run eval for all possible hand cards combos
  int no1 = evaluate_omaha_cards(b1, b2, b3, b4, b5, h1, h2, h3, h4);
  int no2 = evaluate_omaha_cards(b1, b2, b3, b4, b5, h1, h2, h3, h5);
  int no3 = evaluate_omaha_cards(b1, b2, b3, b4, b5, h1, h2, h4, h5);
  int no4 = evaluate_omaha_cards(b1, b2, b3, b4, b5, h1, h3, h4, h5);
  int no5 = evaluate_omaha_cards(b1, b2, b3, b4, b5, h2, h3, h4, h5);

  printf("[eval_OT]: no1 - no5 = %d %d %d %d %d\n", no1, no2, no3, no4, no5);

  // and pick a minimum
  if(no1 > no2) no1 = no2;
  if(no1 > no3) no1 = no3;
  if(no1 > no4) no1 = no4;
  if(no1 > no5) no1 = no5;

  printf("[eval_OT]: min of nos = %d\n", no1);

  // this is a final rank
  return no1;
}

int calc_OT2(const int h1[5], const int h2[5],
             const int deck[52], const int f1sz, const int f2sz, const int f3sz,
             const int tsz, const int rsz, char* json) {
  int wins[2] = { 0, 0 };
  int ties[1] = { 0 };
  for(int f1 = 0; f1 < f1sz; ++f1) {
    for(int f2 = f1 + 1; f2 < f2sz; ++f2) {
      for(int f3 = f2 + 1; f3 < f3sz; ++f3) {
        for(int t = f3 + 1; t < tsz; ++t) {
          for(int r = t + 1; r < rsz; ++r) {
            int p1rank = eval_OT(deck[f1], deck[f2], deck[f3], deck[t], deck[r], h1[0], h1[1], h1[2], h1[3], h1[4]);
            int p2rank = eval_OT(deck[f1], deck[f2], deck[f3], deck[t], deck[r], h2[0], h2[1], h2[2], h2[3], h2[4]);

                 if(p1rank <  p2rank) ++wins[0];
            else if(p2rank <  p1rank) ++wins[1];
            else if(p1rank == p2rank) ++ties[0];
            else return eror(json, "unexpected situation in calc_OT2");
          }
        }
      }
    }
  }
  sprintf(json, "{ \"eror\": false, \"wins\": [%d, %d], \"ties\": [%d]}", wins[0], wins[1], ties[0]);
  return 0;
}

int calc_OT3(const int h1[5], const int h2[5], const int h3[5],
             const int deck[52], const int f1sz, const int f2sz, const int f3sz,
             const int tsz, const int rsz, char* json) {
  int wins[3] = { 0, 0, 0 };
  int ties[4] = { 0, 0, 0, 0 };
  for(int f1 = 0; f1 < f1sz; ++f1) {
    for(int f2 = f1 + 1; f2 < f2sz; ++f2) {
      for(int f3 = f2 + 1; f3 < f3sz; ++f3) {
        for(int t = f3 + 1; t < tsz; ++t) {
          for(int r = t + 1; r < rsz; ++r) {
            int p1rank = eval_OT(deck[f1], deck[f2], deck[f3], deck[t], deck[r], h1[0], h1[1], h1[2], h1[3], h1[4]);
            int p2rank = eval_OT(deck[f1], deck[f2], deck[f3], deck[t], deck[r], h2[0], h2[1], h2[2], h2[3], h2[4]);
            int p3rank = eval_OT(deck[f1], deck[f2], deck[f3], deck[t], deck[r], h3[0], h3[1], h3[2], h3[3], h3[4]);

                 if(p1rank <  p2rank && p1rank <  p3rank) ++wins[0];    // p1 won
            else if(p2rank <  p1rank && p2rank <  p3rank) ++wins[1];    // p2 won
            else if(p3rank <  p1rank && p3rank <  p2rank) ++wins[2];    // p3 won
            else if(p1rank == p2rank && p1rank <  p3rank) ++ties[0];    // p1 tie to p2 (p3 lost)
            else if(p1rank == p3rank && p1rank <  p2rank) ++ties[1];    // p1 tie to p3 (p2 lost)
            else if(p2rank == p3rank && p2rank <  p1rank) ++ties[2];    // p2 tie to p3 (p1 lost)
            else if(p1rank == p2rank && p1rank == p3rank) ++ties[3];    // p1 tie to p2 and p3
            else return eror(json, "unexpected situation in calc_OT3");
          }
        }
      }
    }
  }
  sprintf(json, "{ \"eror\": false, \"wins\": [%d, %d, %d], \"ties\": [%d, %d, %d, %d]}", wins[0], wins[1], wins[2], ties[0], ties[1], ties[2], ties[3]);
  return 0;
}
