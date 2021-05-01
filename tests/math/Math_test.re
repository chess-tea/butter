open Butter;
open TestFramework;

let debugPrint = actual => {
  print_endline("");
  print_endline("");
  Console.log(actual);
  print_endline("");
};

describe("Math", ({test}) => {
  test("Basic 1", ({expect}) => {
    let value = 2.0;
    let actual = Math.fastInverseSqrt(value);
    let expected = Math.inverseSqrt(value);
    let error = Math.percentError(actual, expected);

    // Printf.printf("\n\n1/sqrt(%f) = %f\n", value, expected);
    // Printf.printf("1/sqrt(%f) ~= %f\n", value, actual);
    // Printf.printf("error: %f%%\n", error);
    // Printf.printf("\n");

    expect.bool(error < 1.).toBeTrue();
  });

  test("Basic 2", ({expect}) => {
    let value = 42.0;
    let actual = Math.fastInverseSqrt(value);
    let expected = Math.inverseSqrt(value);
    let error = Math.percentError(actual, expected);

    // Printf.printf("\n\n1/sqrt(%f) = %f\n", value, expected);
    // Printf.printf("1/sqrt(%f) ~= %f\n", value, actual);
    // Printf.printf("error: %f%%\n", error);
    // Printf.printf("\n");

    expect.bool(error < 1.).toBeTrue();
  });
});
