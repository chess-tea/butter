// Based on: https://github.com/substack/text-table
();

// Private type to hold config information.
type config = {
  border: bool,
  header: bool,
  strict: bool,
  length: string => int,
};

module Impl = {
  // String repeat.
  let repeat = (count, s) => {
    List.init(count, _ => s) |> String.concat("");
  };

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
        s ++ repeat(need, " ");
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

  // Builds a border based on the given columnWidths and joints.
  let getBorder =
      (~leftJoint, ~innerJoint, ~rightJoint, ~horizontal, columnWidths) => {
    let border =
      columnWidths
      |> Array.to_list
      |> List.map(width => {repeat(width + 2, horizontal)})
      |> String.concat(innerJoint);
    let border = leftJoint ++ border ++ rightJoint ++ "\n";
    border;
  };

  let getInnerBorder =
    getBorder(
      ~leftJoint=Unicode.lightVerticalAndRight,
      ~innerJoint=Unicode.lightVerticalAndHorizontal,
      ~rightJoint=Unicode.lightVerticalAndLeft,
      ~horizontal=Unicode.lightHorizontal,
    );

  let getHeaderBorder =
    getBorder(
      ~leftJoint=Unicode.verticalSingleAndRightDouble,
      ~innerJoint=Unicode.verticalSingleAndHorizontalDouble,
      ~rightJoint=Unicode.verticalSingleAndLeftDouble,
      ~horizontal=Unicode.doubleHorizontal,
    );

  let getTopBorder =
    getBorder(
      ~leftJoint=Unicode.lightDownAndRight,
      ~innerJoint=Unicode.lightDownAndHorizontal,
      ~rightJoint=Unicode.lightDownAndLeft,
      ~horizontal=Unicode.lightHorizontal,
    );

  let getBottomBorder =
    getBorder(
      ~leftJoint=Unicode.lightUpAndRight,
      ~innerJoint=Unicode.lightUpAndHorizontal,
      ~rightJoint=Unicode.lightUpAndLeft,
      ~horizontal=Unicode.lightHorizontal,
    );
};

let table =
    (
      ~border=false,
      ~header=false,
      ~strict=false,
      ~stringLength=String.length,
      rows: list(list(string)),
    ) => {
  let config = {border, header, strict, length: stringLength};
  let rowCount = List.length(rows);
  let columnCount = Impl.getColumnCount(~config, rows);
  let columnWidths = Impl.getColumnWidths(~config, ~columnCount, rows);

  // Figure out the separators and borders.
  let sep = config.border ? " " ++ Unicode.lightVertical ++ " " : " ";
  let left = config.border ? Unicode.lightVertical ++ " " : "";
  let right = config.border ? " " ++ Unicode.lightVertical : "";
  let innerBorder = Impl.getInnerBorder(columnWidths);
  let headerBorder = Impl.getHeaderBorder(columnWidths);
  let topBorder = Impl.getTopBorder(columnWidths);
  let bottomBorder = Impl.getBottomBorder(columnWidths);

  let padRight = Impl.getPadRight(~config);

  let paddedRows =
    List.map(
      row => {List.mapi((i, el) => padRight(el, columnWidths[i]), row)},
      rows,
    );

  let combinedRows =
    List.map(
      row => left ++ String.concat(sep, row) ++ right ++ "\n",
      paddedRows,
    );

  let result =
    List.mapi(
      (i, row) => {
        ();
        if (config.border) {
          // Add the top border if this is the first row.
          let row = i === 0 ? topBorder ++ row : row;

          // Now add either the header, inner, or bottom border as appropriate.
          let row =
            if (i === rowCount - 1) {
              row ++ bottomBorder;
            } else if (i === 0 && config.header) {
              row ++ headerBorder;
            } else {
              row ++ innerBorder;
            };

          row;
        } else {
          row;
        };
      },
      combinedRows,
    );

  let result = String.concat("", result);

  result;
};
