#include "omaha10.h"

int calc_OT(const int* hands, const int* scenes, const int hsz, const int* board, const int bsz, const int* deads, const int dsz, char* json) {
  // create and init a full deck
  int deck[52];
  int expect = 52;
  int decksz = init(deck);
  if(expect != decksz || ccnt(deck, 52) != 52) {
    return eror(json, "invalid deck: who you gonna call?");
  }

  // ensure hands size is 2-6, all cards are 0-51, kick all from the deck
  if(hsz < 2 || hsz > 6) {
    return eror(json, "invalid hands count: must be 2-6");
  }
  if(ccnt(hands, hsz * 5) != hsz * 5) {
    return eror(json, "invalid hands: all cards must be 0-51");
  }
  expect -= hsz * 5;
  decksz = kick(deck, decksz, hands, hsz * 5);
  if(expect != decksz) {
    return eror(json, "invalid hand card: duplicates existing cards");
  }

  // ensure board size is 0-5, all cards are 0-51, kick all from the deck
  if(bsz < 0 || bsz > 5) {
    return eror(json, "invalid board size: must be 0-5");
  }
  if(ccnt(board, bsz) != bsz) {
    return eror(json, "invalid board: all cards must be 0-51");
  }
  expect -= bsz;
  decksz = kick(deck, decksz, board, bsz);
  if(expect != decksz) {
    return eror(json, "invalid board card: duplicates existing cards");
  }

  // ensure deads size is 0-52, all cards are 0-51, kick all from the deck
  if(dsz < 0 || bsz > 52) {
    return eror(json, "invalid deads size: must be 0-52");
  }
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
      return calc_OT2(hands, scenes, deck, ftrsz, json);
    case 3:
      return calc_OT3(hands, scenes, deck, ftrsz, json);
    case 4:
      return calc_OT4(hands, scenes, deck, ftrsz, json);
    case 5:
      return calc_OT5(hands, scenes, deck, ftrsz, json);
    case 6:
      return calc_OT6(hands, scenes, deck, ftrsz, json);
  }

  return eror(json, "invalid code: who you gonna call?");
}
