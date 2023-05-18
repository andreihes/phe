#include "omaha10.h"

// replace ['] with ["]
int repl(char* json) {
  int ttl = 0;
  for(char* ch = json; *ch != 0; ch++) {
    if(*ch == '\'') {
      ++ttl;
      *ch = '"';
    }
  }
  return ttl;
}

// count valid card ids
int ccnt(const int* cards, const int cnt) {
  int ttl = 0;
  for(int idx = 0; idx < cnt; idx++) {
    if(cards[idx] >= 0 && cards[idx] < 52) {
      ++ttl;
    }
  }
  return ttl;
}

// init 52 cards deck
int init(int deck[52]) {
  for(int card = 0; card < 52; card++) {
    deck[card] = card;
  }
  return 52;
}

// move dead cards away from the deck returning a new deck size
int kick(int deck[52], int decksz, const int*  dead, const int deadsz) {
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
int push(int deck[52], int decksz, const int card) {
  for(int idx = decksz; idx > 0; idx--) {
    deck[idx] = deck[idx - 1];
  }
  deck[0] = card;
  return decksz + 1;
}

// populate eror JSON object
int eror(char* json, char* info)
{
  int wrong = 0;
  for(char* ch = info; *ch != 0; ch++) {
    if(*ch == '"' || *ch == '\'') {
      wrong = 1;
      break;
    }
  }
  if(wrong) {
    sprintf(json, "{ 'eror': true, 'info': 'msg contains wrong chars and has been truncated' }");
  }
  else {
    sprintf(json, "{ 'eror': true, 'info': '%s' }", info);
  }
  repl(json);
  return 1;
}
