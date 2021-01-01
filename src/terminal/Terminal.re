module Block = UnicodeSymbols.Block;

module Controls = {
  let escapeCode = "\027";

  module Move = {
    let toColumn = c => {
      let code = escapeCode ++ "[" ++ string_of_int(c) ++ "G";
      print_string(code);
      flush(stdout);
    };

    let up = x => {
      let code = escapeCode ++ "[" ++ string_of_int(x) ++ "A";
      print_string(code);
      flush(stdout);
    };

    let down = x => {
      let code = escapeCode ++ "[" ++ string_of_int(x) ++ "B";
      print_string(code);
      flush(stdout);
    };

    let right = x => {
      let code = escapeCode ++ "[" ++ string_of_int(x) ++ "C";
      print_string(code);
      flush(stdout);
    };

    let left = x => {
      let code = escapeCode ++ "[" ++ string_of_int(x) ++ "D";
      print_string(code);
      flush(stdout);
    };
  };

  module Erase = {
    let toEndOfLine = () => {
      let code = escapeCode ++ "[0K";
      print_string(code);
      flush(stdout);
    };

    let toStartOfLine = () => {
      let code = escapeCode ++ "[1K";
      print_string(code);
      flush(stdout);
    };

    let line = () => {
      let code = escapeCode ++ "[2K";
      print_string(code);
      flush(stdout);
    };
  };
};

let progressBar = (~numbers=true, ~width=80, ~total=100, progress) => {
  // Some input validation. TODO, throw exceptions, etc.
  let width =
    if (width < 10) {
      10;
    } else {
      width;
    };

  let progress =
    if (progress < 0) {
      0;
    } else {
      progress;
    };

  let progress =
    if (progress > total) {
      total;
    } else {
      progress;
    };

  let left = "[";
  let right = numbers ? "] " : "]";

  let totalS = string_of_int(total);
  let maxNumbers = numbers ? totalS ++ "/" ++ totalS : "";

  let numbers =
    numbers ? string_of_int(progress) ++ "/" ++ string_of_int(total) : "";

  let remaining =
    width
    - String.length(left)
    - String.length(right)
    - String.length(maxNumbers);

  let filled = progress * remaining / total;

  let f = float_of_int;
  let filledF = f(progress) *. f(remaining) /. f(total);
  let fraction = filledF -. f(filled);

  let unfilled = (total - progress) * remaining / total;

  // Increments of 1/8, centered around the fraction the UnicodeSymbol
  // represents. 1/8 = 0.125, so the oneEightBlock is used for the range
  // [0.75, 0.2], which is a range with 0.125 in the center.
  let partial =
    if (remaining - filled - unfilled === 0) {
      "";
    } else if (fraction < 0.075) {
      " ";
    } else if (fraction < 0.2) {
      Block.leftOneEighthBlock;
    } else if (fraction < 0.325) {
      Block.leftOneQuarterBlock;
    } else if (fraction < 0.45) {
      Block.leftThreeEighthsBlock;
    } else if (fraction < 0.575) {
      Block.leftHalfBlock;
    } else if (fraction < 0.7) {
      Block.leftFiveEighthsBlock;
    } else if (fraction < 0.825) {
      Block.leftThreeQuartersBlock;
    } else if (fraction < 1.00) {
      Block.leftSevenEighthsBlock;
    } else {
      Block.fullBlock;
    };

  let filled = StringUtils.repeat(filled, Block.fullBlock);
  let unfilled = StringUtils.repeat(unfilled, " ");
  let result = left ++ filled ++ partial ++ unfilled ++ right ++ numbers;
  result;
};

let controllableProgressBar =
    (~numbers=true, ~width=80, ~total=100, initialProgress) => {
  let progress = ref(0);
  let update = value => {
    progress := value;
    Controls.Move.toColumn(0);
    Controls.Erase.toEndOfLine();
    let bar = progressBar(~numbers, ~width, ~total, progress^);
    print_string(bar);
    flush(stdout);
  };
  update(initialProgress);
  update;
};
