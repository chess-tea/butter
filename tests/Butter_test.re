open TestFramework;

describe("Butter", ({test}) => {
  test("Strings", ({expect}) => {
    let actual = Butter.hello;
    let expected = "Hello World!";
    expect.string(actual).toEqual(expected);
  });

  test("Snapshots", ({expect}) => {
    let actual = Butter.hello;
    expect.string(actual).toMatchSnapshot();
  });
});
