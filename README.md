# phe
This is a copy of [PokerHandEvaluator](https://github.com/HenryRLee/PokerHandEvaluator) by [Henry Lee](https://github.com/HenryRLee) without all the features except Omaha 9 cards evaluator.
It has been also extended with brute force Omaha 10 cards evaluator: no optimizations, just plain 5 calls of the original Omaha 9 cards evaluator.
Few more utilities added:
1. Exact odds calculation for 2-6 5-cards hands
2. Pre-flop, flop, turn and river exact odds

It is now possible to use in Python directly from DLL. The original python port is ~50-100 times slower than this plain C version. So, instead of dealing with port optmization tricks
this one just use plain C to deliver accptable speed. Below there is an example of how this can be used to calculate 10 cards odds from Python.

# prepare
Init ctypes, load DDL, cards mappings:
```python
import json
import ctypes

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

PHE = ctypes.windll.LoadLibrary('phe.dll')

def parse(line: str) -> list[int]:
  ids: list[int] = [ ]
  for card in line.split():
    if(len(card) != 2):
      raise ValueError(f'invalid card "{card}" in line "{line}": length is not 2')
    key = card[0].upper() + card[1].lower()
    if key not in CARDS_DICT:
      raise ValueError(f'invalid card "{card}" in line "{line}": unknown card')
    ids.append(CARDS_DICT[card])
  return ids

def calc(hands: list[list[int]], board: list[int], dead: list[int]) -> any:
  if len(hands) < 2 or len(hands) > 6:
    raise ValueError('min 2 hands and max 6 hands')
  for hand in hands:
    if len(hand) != 5:
      raise ValueError('hand must be 5 cards')
  if len(board) != 5:
    raise ValueError('board must be 5 cards')
  if(len(dead) != 52):
    raise ValueError('dead must be 5 cards')

  c_hands = ((ctypes.c_int * 5) * len(hands))()
  for hi, hand in enumerate(hands):
    for ci in range(5):
      c_hands[hi][ci] = hand[ci]

  c_board = (ctypes.c_int * 5)()
  for ci in range(5):
    c_board[ci] = board[ci]

  c_dead = (ctypes.c_int * 52)()
  for ci in range(52):
    c_dead[ci] = dead[ci]

  c_json = ctypes.c_char_p(b'x' * 1000)

  PHE.calc_OT(c_hands, len(hands), c_board, c_dead, c_json)
  return json.loads(c_json.value.decode())
```

# use
Just prepare hands, boards, dead cards and call eval from DLL:
```python
def main():
  hand1 = parse('2s 3s 4s 5s 6s')
  hand2 = parse('2d 3d 4d 5d 6d')
  board = [ -1, -1, -1, -1, -1 ]
  deads = [ -1 for _ in range(52) ]
  result = calc([hand1, hand2], board, deads)
  print(result)

if __name__ == '__main__':
  main()
```
Output: `{'eror': False, 'wins': [33852, 33852], 'ties': [782964]}`
