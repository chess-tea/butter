// Based on: https://github.com/substack/text-table
();

type config = {
  strict: bool,
  length: string => int,
};

let defaultConfig = {strict: false, length: String.length};

module Impl = {
  // Gets the number of columns in the table.
  let getColumnCount = (~config, rows) => {
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
    columnCount;
  };

  // Gets an array of widths. Keep in mind that arrays are mutable. Only use
  // the results of this function internally.
  let getColumnWidths = (~config, ~columnCount, rows) => {
    let widths = Array.make(columnCount, 0);
    List.iter(
      row => {
        List.iteri(
          (i, el) => {
            let n = config.length(el);
            if (n > widths[i]) {
              widths[i] = n;
            };
          },
          row,
        )
      },
      rows,
    );
    widths;
  };

  // Builds an appropriate pad-right function based on the config.
  let getPadRight = (~config) => {
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
    padRight;
  };
};

let table = (~config=defaultConfig, rows: list(list(string))) => {
  let columnCount = Impl.getColumnCount(~config, rows);

  let columnWidths = Impl.getColumnWidths(~config, ~columnCount, rows);

  let padRight = Impl.getPadRight(~config);

  let paddedRows =
    List.map(
      row => {List.mapi((i, el) => padRight(el, columnWidths[i]), row)},
      rows,
    );

  let sep = " ";

  let combinedContents = List.map(String.concat(sep), paddedRows);

  let result = String.concat("\n", combinedContents) ++ "\n";

  result;
};
