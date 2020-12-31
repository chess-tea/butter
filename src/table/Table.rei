// Based on: https://github.com/substack/text-table

/**
Simple API to create text-based tables.

Example 1:

    Table.table([
      ["one", "two", "three", "four"],
      ["1", "", "3", "4"],
      ["a", "bb", "", "dddd"],
    ]);

    one two three four
    1       3     4
    a   bb        dddd


Example 2 (with border):

    Table.table(
      ~border=true,
      [
        ["one", "two", "three", "four"],
        ["1", "", "3", "4"],
        ["a", "bb", "", "dddd"],
      ],
    );

    ┌─────┬─────┬───────┬──────┐
    │ one │ two │ three │ four │
    ├─────┼─────┼───────┼──────┤
    │ 1   │     │ 3     │ 4    │
    ├─────┼─────┼───────┼──────┤
    │ a   │ bb  │       │ dddd │
    └─────┴─────┴───────┴──────┘

Example 3 (with border and header):

    Table.table(
      ~border=true,
      ~header=true,
      [
        ["one", "two", "three", "four"],
        ["1", "", "3", "4"],
        ["a", "bb", "", "dddd"],
      ],
    );

    ┌─────┬─────┬───────┬──────┐
    │ one │ two │ three │ four │
    ╞═════╪═════╪═══════╪══════╡
    │ 1   │     │ 3     │ 4    │
    ├─────┼─────┼───────┼──────┤
    │ a   │ bb  │       │ dddd │
    └─────┴─────┴───────┴──────┘
 */
let table:
  (
    ~border: bool=?,
    ~header: bool=?,
    ~strict: bool=?,
    ~stringLength: string => int=?,
    list(list(string))
  ) =>
  string;
