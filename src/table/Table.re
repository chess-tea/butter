// Based on: https://github.com/substack/text-table
();

type config = {
  strict: bool,
  length: string => int,
};

let defaultConfig = {strict: false, length: String.length};

let table = (~config=defaultConfig, rows: list(list(string))) => {
  let columnCount =
    List.fold_left(
      (max, row) => {
        let n = List.length(row);
        if (max === (-1)) {
          n;
        } else {
          if (config.strict && n !== max) {
            failwith("Not all rows have the same number of columns.");
          };
          n > max ? n : max;
        };
      },
      -1,
      rows,
    );

  let columnWidth = Array.make(columnCount, 0);
  List.iter(
    row => {
      List.iteri(
        (i, el) => {
          let n = config.length(el);
          if (n > columnWidth[i]) {
            columnWidth[i] = n;
          };
        },
        row,
      )
    },
    rows,
  );

  let padRight = (s, n) => {
    let need = n - config.length(s);
    if (need > 0) {
      s ++ String.make(need, ' ');
    } else if (need === 0) {
      s;
    } else {
      failwith(
        "Invalid length function. String reported with negative length.",
      );
    };
  };

  let contents =
    List.map(
      row => {List.mapi((i, el) => padRight(el, columnWidth[i]), row)},
      rows,
    );

  let sep = " ";
  let combinedContents = List.map(String.concat(sep), contents);
  let result = String.concat("\n", combinedContents) ++ "\n";
  result;
};
