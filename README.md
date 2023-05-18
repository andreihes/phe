# phe
This is a copy of [PokerHandEvaluator](https://github.com/HenryRLee/PokerHandEvaluator) by [Henry Lee](https://github.com/HenryRLee) without all the features except Omaha 9 cards evaluator.
It has been also extended with brute force Omaha 10 cards evaluator: no optimizations, just plain 5 calls of the original Omaha 9 cards evaluator.
Few more utilities added:
1. Exact odds calculation for 2-6 5-cards hands
2. Pre-flop, flop, turn and river exact odds

It is now possible to use in Python directly from DLL. The original python port is ~50-100 times slower than this plain C version. So, instead of dealing with port optmization tricks
this one just use plain C to deliver accptable speed. Below there is an example of how this can be used to calculate 10 cards odds from Python.

# prepare
Init ctypes, load DDL, card mappings:
<details>
<summary>Python calc.py</summary>

```python
import copy
import json
import ctypes

PHE = ctypes.windll.LoadLibrary('phe.dll')

CARDS_DICT = { '2c': 0,  '2d': 1,  '2h': 2,  '2s': 3,
               '3c': 4,  '3d': 5,  '3h': 6,  '3s': 7,
               '4c': 8,  '4d': 9,  '4h': 10, '4s': 11,
               '5c': 12, '5d': 13, '5h': 14, '5s': 15,
               '6c': 16, '6d': 17, '6h': 18, '6s': 19,
               '7c': 20, '7d': 21, '7h': 22, '7s': 23,
               '8c': 24, '8d': 25, '8h': 26, '8s': 27,
               '9c': 28, '9d': 29, '9h': 30, '9s': 31,
               'Tc': 32, 'Td': 33, 'Th': 34, 'Ts': 35,
               'Jc': 36, 'Jd': 37, 'Jh': 38, 'Js': 39,
               'Qc': 40, 'Qd': 41, 'Qh': 42, 'Qs': 43,
               'Kc': 44, 'Kd': 45, 'Kh': 46, 'Ks': 47,
               'Ac': 48, 'Ad': 49, 'Ah': 50, 'As': 51 }

# O(n^2) one-liner because I have no idea if dict returns items in any order...
CARDS_LIST = [ list(filter(lambda kv: kv[1] == id, CARDS_DICT.items()))[0][0] for id in range(52) ]

def str2ids(line: str = None) -> list[int]:
  ids: list[int] = [ ]
  if line is None:
    return ids
  for card in line.split():
    if(len(card) != 2):
      raise ValueError(f'invalid card "{card}" in line "{line}": length is not 2')
    key = card[0].upper() + card[1].lower()
    if key not in CARDS_DICT:
      raise ValueError(f'invalid card "{card}" in line "{line}": unknown card')
    ids.append(CARDS_DICT[card])
  return ids

def ids2str(ids: list[int]) -> str:
  ret = ''
  for id in ids:
    ret += CARDS_LIST[id] + ' '
  return ret.strip()

def odds(hands: list[list[int]], board: list[int], deads: list[int]) -> any:
  for hand in hands:
    if len(hand) != 5:
      raise ValueError('each hand must be 5 cards')

  c_hands = ((ctypes.c_int * 5) * len(hands))()
  for hi, hand in enumerate(hands):
    for ci, card in enumerate(hand):
      c_hands[hi][ci] = card

  c_board = (ctypes.c_int * len(board))()
  for ci, card in enumerate(board):
    c_board[ci] = card

  c_deads = (ctypes.c_int * len(deads))()
  for ci, card in enumerate(deads):
    c_deads[ci] = card

  c_json = ctypes.c_char_p(b'x' * 1024 * 4)
  PHE.calc_OT(c_hands, len(hands), c_board, len(board), c_deads, len(deads), c_json)

  result = { }
  result['hands'] = copy.copy(hands)
  result['board'] = copy.copy(board)
  result['deads'] = copy.copy(deads)
  result['calcs'] = json.loads(c_json.value.decode())
  return result

def pct01(data):
  ret = { }
  for win in data['calcs']['wins']:
    ret[win['arg']] = win['cnt'] / data['calcs']['totl']
  return ret

def pct02(data):
  ret = { }
  for win in data['calcs']['wins']:
    ties = 0
    for tie in data['calcs']['ties']:
      if win['idx'] in tie['idx']:
        ties += tie['cnt'] / len(tie['idx'])
    ret[win['arg']] = (win['cnt'] + ties) / data['calcs']['totl']
  return ret
```
</details>

# use
Prepare and calc odds for some cases:
<details>
<summary>Python main.py</summary>

```python
import calc

def case01():
  hand1 = calc.str2ids('2s 3s 4s 5s 6s')
  hand2 = calc.str2ids('2d 3d 4d 5d 6d')
  board = calc.str2ids()
  deads = calc.str2ids()
  datas = calc.odds([hand1, hand2], board, deads)
  return datas

def case02():
  hand1 = calc.str2ids('Kd Jd Tc 4s 3s')
  hand2 = calc.str2ids('Ad 9d 7h 6d 3c')
  hand3 = calc.str2ids('As Jh 9s 7d 5d')
  board = calc.str2ids('Td 7s Qd')
  deads = calc.str2ids()
  datas = calc.odds([hand1, hand2, hand3], board, deads)
  return datas

def case03():
  hand1 = calc.str2ids('Kd Jd Tc 4s 3s')
  hand2 = calc.str2ids('Ad 9d 7h 6d 3c')
  hand3 = calc.str2ids('As Jh 9s 7d 5d')
  board = calc.str2ids('Td 7s Qd')
  deads = calc.str2ids('2s')
  datas = calc.odds([hand1, hand2, hand3], board, deads)
  return datas

def case04():
  hand1 = calc.str2ids('Kd Jd Tc 4s 3s')
  hand2 = calc.str2ids('Ad 9d 7h 6d 3c')
  hand3 = calc.str2ids('As Jh 9s 7d 5d')
  board = calc.str2ids()
  deads = calc.str2ids('2s 2d 2c 2h')
  datas = calc.odds([hand1, hand2, hand3], board, deads)
  return datas

def case05():
  hand1 = calc.str2ids('Kd Jd Tc 4s 3s')
  hand2 = calc.str2ids('Ad 9d 7h 6d 3c')
  hand3 = calc.str2ids('As Jh 9s 7d 5d')
  board = calc.str2ids()
  deads = calc.str2ids('2s Jd 2c 2h')
  datas = calc.odds([hand1, hand2, hand3], board, deads)
  return datas

def pretty(data):
  print(f'DEADS: {calc.ids2str(data["deads"])}')
  print(f'BOARD: {calc.ids2str(data["board"])}')
  if data['calcs']['eror']:
    for hand in data['hands']:
      print(f'-> {calc.ids2str(hand)}')
    print(f'ERROR: {data["calcs"]["info"]}')
    return
  print(f'TOTAL: {data["calcs"]["totl"]}')
  pct1 = calc.pct01(data)
  pct2 = calc.pct02(data)
  for win in data['calcs']['wins']:
    print(f'{win["arg"]} -> {calc.ids2str(win["ids"])}: ', end = '')
    print(f'{pct1[win["arg"]] * 100:4.2f}% | {pct2[win["arg"]] * 100:4.2f}%')

if __name__ == '__main__':
  pretty(case01())
  print('-' * 20)

  pretty(case02())
  print('-' * 20)

  pretty(case03())
  print('-' * 20)

  pretty(case04())
  print('-' * 20)

  pretty(case05())
  print('-' * 20)
```
</details>

# results
See results:
<details>
<summary>Outputs</summary>

```
DEADS: 
BOARD:
TOTAL: 850668
h1 -> 2s 3s 4s 5s 6s: 3.98% | 50.00%
h2 -> 2d 3d 4d 5d 6d: 3.98% | 50.00%
--------------------
DEADS:
BOARD: Td 7s Qd
TOTAL: 561
h1 -> Kd Jd Tc 4s 3s: 41.35% | 41.89%
h2 -> Ad 9d 7h 6d 3c: 24.96% | 26.20%
h3 -> As Jh 9s 7d 5d: 30.12% | 31.91%
--------------------
DEADS: 2s
BOARD: Td 7s Qd
TOTAL: 528
h1 -> Kd Jd Tc 4s 3s: 41.48% | 42.05%
h2 -> Ad 9d 7h 6d 3c: 25.38% | 26.61%
h3 -> As Jh 9s 7d 5d: 29.55% | 31.34%
--------------------
DEADS: 2s 2d 2c 2h
BOARD:
TOTAL: 237336
h1 -> Kd Jd Tc 4s 3s: 38.39% | 39.07%
h2 -> Ad 9d 7h 6d 3c: 15.81% | 22.01%
h3 -> As Jh 9s 7d 5d: 32.41% | 38.92%
--------------------
DEADS: 2s Jd 2c 2h
BOARD:
-> Kd Jd Tc 4s 3s
-> Ad 9d 7h 6d 3c
-> As Jh 9s 7d 5d
ERROR: invalid deads card: duplicates existing cards
--------------------
```
</details>
