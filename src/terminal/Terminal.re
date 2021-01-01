module Block = UnicodeSymbols.Block;

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
