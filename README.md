# phe
This is a copy of [PokerHandEvaluator](https://github.com/HenryRLee/PokerHandEvaluator) by [Henry Lee](https://github.com/HenryRLee) without all the features except Omaha 9 cards evaluator.
It has been also extended with brute force Omaha 10 cards evaluator: no optimizations, just plain 5 calls of the original Omaha 9 cards evaluator.
Few more utilities added:
1. Exact odds calculation for 2-6 5-cards hands
2. Pre-flop, flop, turn and river exact odds

PS: copied an improved latest 5-card omaha hand evaluator: see `eval_OT_slow` vs `eval_OT`. 

# example
```C#
using System.Text;
using System.Runtime.InteropServices;

namespace Barmaglot.Calcs
{
  public class Demo
  {
    [DllImport("phe.dll", EntryPoint = "calc_OT", CharSet = CharSet.Ansi)]
    private static extern int CalcOdds([In] int[] hands, [In] int[] scene, [In] int hsz, [In] int[] board, int bsz, [In] int[] deads, [In] int dsz, [Out] StringBuilder json);

    public static void Main()
    {
      int[] hands =
      {
        0, 4, 8, 12, 16, // 2c 3c 4c 5c 6c VS
        1, 5, 9, 13, 17, // 2d 3d 4d 5d 6d VS
        2, 6, 10, 14, 18 // 2h 3h 4h 5h 6h
      };
      int[] scene = { 0, 1, 2 };
      int[] board = { };
      int[] deads = { };

      StringBuilder json = new StringBuilder(4 * 1024); // 4K ought to be enough for anybody
      int code = Demo.CalcOdds(hands, scene, scene.Length, board, board.Length, deads, deads.Length, json);
      Console.WriteLine(code);
      Console.WriteLine(json.ToString());
    }
  }
}
```

# result
```json
{
  "eror": false,   # no error detected
  "totl": 435897,  # total combos iterated: n choose k = (52 total - 15 hands) choose (5 board) = 37 choose 5
  "wins": [
    {
      "scn": 0,
      "cnt": 24822 # scene 0 (hands[0,1,2,3,4]) clear wins
    },
    {
      "scn": 1,
      "cnt": 24822 # scene 1 (hands[5,6,7,8,9]) clear wins
    },
    {
      "scn": 2,
      "cnt": 24822 # scene 2 (hands[10,11,12,13,14]) clear wins
    }
  ],
  "ties": [
    {
      "scn": [
        0,
        1
      ],
      "cnt": 0    # no ties between scene 0 and 1 (scene 2 loses)
    },
    {
      "scn": [
        0,
        2
      ],
      "cnt": 0    # no ties between scene 0 and 2 (scene 1 loses)
    },
    {
      "scn": [
        1,
        2
      ],
      "cnt": 0   # no ties between scene 1 and 2 (scene 0 loses)
    },
    {
      "scn": [
        0,
        1,
        2
      ],
      "cnt": 361431  # ties for scenes 0, 1, 2
    }
  ]
}
```
