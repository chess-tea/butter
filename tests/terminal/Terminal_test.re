open Butter;
open TestFramework;

let debugPrint = actual => {
  print_endline("");
  print_endline(actual);
  print_endline("");
};
let concat = strings =>
  strings |> List.map((++)("\n")) |> String.concat("");

describe("Terminal", ({test}) => {
  test("Basic 1", ({expect}) => {
    let actual = [
      Terminal.progressBar(0),
      Terminal.progressBar(1),
      Terminal.progressBar(2),
      Terminal.progressBar(10),
      Terminal.progressBar(20),
      Terminal.progressBar(30),
      Terminal.progressBar(40),
      Terminal.progressBar(50),
      Terminal.progressBar(60),
      Terminal.progressBar(70),
      Terminal.progressBar(80),
      Terminal.progressBar(90),
      Terminal.progressBar(98),
      Terminal.progressBar(99),
      Terminal.progressBar(100),
    ];
    let actual = concat(actual);

    let expected = [
      "[                                                                      ] 0/100",
      "[▊                                                                     ] 1/100",
      "[█▍                                                                    ] 2/100",
      "[███████                                                               ] 10/100",
      "[██████████████                                                        ] 20/100",
      "[█████████████████████                                                 ] 30/100",
      "[████████████████████████████                                          ] 40/100",
      "[███████████████████████████████████                                   ] 50/100",
      "[██████████████████████████████████████████                            ] 60/100",
      "[█████████████████████████████████████████████████                     ] 70/100",
      "[████████████████████████████████████████████████████████              ] 80/100",
      "[███████████████████████████████████████████████████████████████       ] 90/100",
      "[████████████████████████████████████████████████████████████████████▋ ] 98/100",
      "[█████████████████████████████████████████████████████████████████████▎] 99/100",
      "[██████████████████████████████████████████████████████████████████████] 100/100",
    ];
    let expected = concat(expected);

    expect.string(actual).toEqual(expected);
  });

  test("Basic 2", ({expect}) => {
    let actual = [
      Terminal.progressBar(~total=200, 140),
      Terminal.progressBar(~total=200, 141),
      Terminal.progressBar(~total=200, 142),
      Terminal.progressBar(~total=200, 143),
      Terminal.progressBar(~total=200, 144),
      Terminal.progressBar(~total=200, 145),
      Terminal.progressBar(~total=200, 146),
      Terminal.progressBar(~total=200, 147),
      Terminal.progressBar(~total=200, 148),
      Terminal.progressBar(~total=200, 149),
    ];
    let actual = concat(actual);

    let expected = [
      "[█████████████████████████████████████████████████                     ] 140/200",
      "[█████████████████████████████████████████████████▍                    ] 141/200",
      "[█████████████████████████████████████████████████▊                    ] 142/200",
      "[██████████████████████████████████████████████████                    ] 143/200",
      "[██████████████████████████████████████████████████▍                   ] 144/200",
      "[██████████████████████████████████████████████████▊                   ] 145/200",
      "[███████████████████████████████████████████████████▏                  ] 146/200",
      "[███████████████████████████████████████████████████▌                  ] 147/200",
      "[███████████████████████████████████████████████████▊                  ] 148/200",
      "[████████████████████████████████████████████████████▏                 ] 149/200",
    ];
    let expected = concat(expected);

    expect.string(actual).toEqual(expected);
  });

  test("Manual", ({expect}) => {
    // TODO: Set up capture input testing utility.
    let manual = false;
    if (manual) {
      print_endline("");
      print_endline("");

      let setProgress = Terminal.controllableProgressBar(0);
      for (i in 0 to 75) {
        setProgress(i);
        Unix.sleepf(0.05);
      };

      print_endline("");
      print_endline("");
    };

    expect.int(1).toBe(1);
  });
});
