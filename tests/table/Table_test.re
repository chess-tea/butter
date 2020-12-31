open Butter;
open TestFramework;

let debugPrint = actual => {
  print_endline("");
  print_endline("");
  print_endline(actual);
  print_endline("");
};

describe("Table", ({test}) => {
  test("Basic 1", ({expect}) => {
    let actual =
      Table.table([
        ["one", "two", "three", "four"],
        ["1", "2", "3", "4"],
        ["a", "bb", "ccc", "dddd"],
      ]);
    expect.string(actual).toMatchSnapshot();
  });

  test("Basic 2", ({expect}) => {
    let actual =
      Table.table([
        ["one", "two", "three", "four"],
        ["1", "", "3", "4"],
        ["a", "bb", "", "dddd"],
      ]);
    expect.string(actual).toMatchSnapshot();
  });

  test("Borders 1", ({expect}) => {
    let actual =
      Table.table(
        ~border=true,
        [
          ["one", "two", "three", "four"],
          ["1", "", "3", "4"],
          ["a", "bb", "", "dddd"],
        ],
      );
    expect.string(actual).toMatchSnapshot();
  });

  test("Borders with header", ({expect}) => {
    let actual =
      Table.table(
        ~border=true,
        ~header=true,
        [
          ["one", "two", "three", "four"],
          ["1", "", "3", "4"],
          ["a", "bb", "", "dddd"],
        ],
      );
    expect.string(actual).toMatchSnapshot();
  });
});
