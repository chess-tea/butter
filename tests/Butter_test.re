open Butter;
open TestFramework;

describe("Butter", ({test}) => {
  test("Strings", ({expect}) => {
    let actual = Example.hello;
    let expected = "Hello World!";
    expect.string(actual).toEqual(expected);
  });

  test("Snapshots", ({expect}) => {
    let actual = Example.hello;
    expect.string(actual).toMatchSnapshot();
  });
});
