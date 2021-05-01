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

/**
 * inverseSqrt(x)
 *
 * Computes 1/sqrt(x) precisely (as allowed by floating point reprsentations).
 * This approach is more precise, but slower than `fastInverseSqrt`.
 */
let inverseSqrt = x => {
  1. /. sqrt(x)
};

/**
 * fastInverseSqrt(x)
 *
 * Quickly computes an approximation for 1/sqrt(x). This approximation is no
 * more than 1% off from the correct value.
 *
 * Behavior is undefined for:
 *
 *   - Negative numbers
 *   - Infinite numbers
 *   - NaN
 *   - Denormal numbers (or subnormal)
 */
let fastInverseSqrt = x => {
  let i = Int32.bits_of_float(x);
  let j = Int32.sub(0x5F3759DFl, Int32.shift_right(i, 1));
  let y = Int32.float_of_bits(j);
  y *. (1.5 -. 0.5 *. x *. y *. y);
};

/**
 * percentError(actual, expected)
 *
 * Computes the percent error of actual from expected.
 *
 *   |actual - expected| / expected * 100%
 */
let percentError = (actual, expected) => {
  abs_float(actual -. expected) /. expected *. 100.;
};
