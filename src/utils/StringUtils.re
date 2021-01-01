// String repeat.
let repeat = (count, s) => {
  List.init(count, _ => s) |> String.concat("");
};
