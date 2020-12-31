open Butter;
open TestFramework;

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
});
