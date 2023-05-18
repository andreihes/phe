#include "omaha10.h"

/**
 * 0. return value
 *    returns 0 if calculation is successful, non-zero means some kind of error
 * 1. hands
 * 2. hsz
 * 3. board
 * 4. bsz
 * 5. deads
 * 6. dsz
 * 7. json
 *    In case of error (return != 0) contains error as JSON object:
 *    "eror": boolean
 *            Will be always true in case of error
 *    "info": string
 *            a brief informational message about the error
 * 
 *    In case of successful calculation contains results as JSON object:
 *    "eror": boolean
 *            it is always false in case of 0 exit code
 *    "totl": int
 *            a total number of combinations (all possible) checked (n choose k)
 *    "wins": list of objects (size == number of hands)
 *            it is winners information with below object structure for items
 *            "arg": string
 *                   h1|h2|h3|h4|h5|h6 - just a hand name mapped from hand index in hands param
 *            "idx": int
 *                   0|1|2|3|4|5 - matches hand index in hands param
 *            "ids": list of ints (size 5)
 *                   contains 5 hand card ids as in the hands param
 *            "cnt": int
 *                   an exact number of evaluations where this hand won
 *    "ties": list of objects (size = 1 for 2 hands, 4 for 3 hands, 11 for 4 hands, 26 for 5 hands, TODO for 6 hands)
 *            since there are different permutations when it is a tie all varians are preserved
 *            "arg": list of str
 *                   contains all hands arg (see wins) that made a tie
 *            "idx": list of int
 *                   contains all hands idx (see wins) that made a tie
 *            "cnt": int
 *                   an exact number of evaluations where the hands from "arg" ("idx") made a tie (all other hands lost)
 */
int calc_OT(const int hands[][5], const int hsz, const int* board, const int bsz, const int* deads, const int dsz, char* json) {
  // create and init a full deck
  int deck[52];
  int expect = 52;
  int decksz = init(deck);
  if(expect != decksz || ccnt(deck, 52) != 52) {
    return eror(json, "invalid deck: who you gonna call?");
  }

  // ensure hands count is 2-6
  if(hsz < 1 || hsz > 6) {
    return eror(json, "invalid hands count: must be 2-6");
  }

  // kick every card of every hand from the deck
  for(int idx = 0; idx < hsz; idx++) {
    if(ccnt(hands[idx], 5) != 5) {
      return eror(json, "invalid hand: all cards must be 0-51");
    }
    expect -= 5;
    decksz = kick(deck, decksz, hands[idx], 5);
    if(expect != decksz) {
      return eror(json, "invalid hand card: duplicates existing cards");
    }
  }

  // ensure board size is 0, 3, 4 or 5
  if(bsz != 0 && bsz != 3 && bsz != 4 && bsz != 5) {
    return eror(json, "invalid board size: must be 0, 3, 4, 5");
  }

  // kick every board card from the deck
  if(ccnt(board, bsz) != bsz) {
    return eror(json, "invalid board: all cards must be 0-51");
  }
  expect -= bsz;
  decksz = kick(deck, decksz, board, bsz);
  if(expect != decksz) {
    return eror(json, "invalid board card: duplicates existing cards");
  }

  // kick every deads card from the deck
  if(ccnt(deads, dsz) != dsz) {
    return eror(json, "invalid deads: all cards must be 0-51");
  }
  expect -= dsz;
  if(expect < 0 || dsz + decksz > 52) {
    return eror(json, "invalid deads: too many deads");
  }
  decksz = kick(deck, decksz, deads, dsz);
  if(expect != decksz) {
    return eror(json, "invalid deads card: duplicates existing cards");
  }

  // prepend board into the deck
  for(int idx = bsz; idx > 0; idx--) {
    decksz = push(deck, decksz, board[idx - 1]);
  }

  // flop-turn-river sizes
  int ftrsz[5];
  ftrsz[0] = bsz >= 3 ? 1 : decksz; // once there is flop then fix flop card end indexed at 1, 2, 3
  ftrsz[1] = bsz >= 3 ? 2 : decksz; // we already have flop-turn-river cards at the start of the deck
  ftrsz[2] = bsz >= 3 ? 3 : decksz; // otherwise let it iterate up to deck size
  ftrsz[3] = bsz >= 4 ? 4 : decksz; // same logic for turn
  ftrsz[4] = bsz == 5 ? 5 : decksz; // and same for river

  // brute force everything
  switch(hsz) {
    case 2:
      return calc_OT2(hands[0], hands[1], deck, ftrsz, json);
    case 3:
      return calc_OT3(hands[0], hands[1], hands[2], deck, ftrsz, json);
    case 4:
      return calc_OT4(hands[0], hands[1], hands[2], hands[3], deck, ftrsz, json);
    case 5:
      return calc_OT5(hands[0], hands[1], hands[2], hands[3], hands[4], deck, ftrsz, json);
    case 6:
      return calc_OT6(hands[0], hands[1], hands[2], hands[3], hands[4], hands[5], deck, ftrsz, json);
  }

  return eror(json, "invalid code: who you gonna call?");
}
