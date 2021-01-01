let gcd = (a, b) => {
  // Make sure to always pass in the minimum element first.
  let (a, b) = a < b ? (a, b) : (b, a);
  let rec impl = (a, b) =>
    if (a === 0) {
      b;
    } else {
      impl(b mod a, a);
    };
  impl(a, b);
};
