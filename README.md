# Postfix-calculator
## Supported operators:
- Addition `+`
- Subtraction `-`
- Multiplication `*`
- Division `/`
- Modulo division `%`
- Exponentiation `^`
- Function call `()`

## Supported math functions:
| Function name              | Operation                       |
| -------------------------- | ------------------------------- |
| <b>Roots</b>               |                                 |
| `sqrt`                     | Square root                     |
| `cbrt`                     | Cube root                       |
| <b>Trigonometric functions</b> |                             |
| `cos`                      | Cosine                          |
| `sin`                      | Sine                            |
| `tg/tan`                   | Tangent                         |
| `arccos/acos`              | Arccosine                       |
| `arcsin/asin`              | Arcsine                         |
| `arctg/atan`               | Arctangent                      |
| <b>Logarithms</b>          |                                 |
| `ln`                       | Natural logarithm               |
| `log2`                     | Logarithm base 2                |
| `log10`                    | Logarithm base 10               |
| <b>Other</b>               |                                 |
| `abs`                      | Absolute value                  |
| `ceil`                     | Round to smallest integral value|
| `floor`                    | Round to largest integral value |
| `round`                    | Round to integral value         |

## Syntax rules:
- There is no unary minus, use subtraction from zero instead
- Floating-point numbers can be written both with a point and a comma
- New-line symbol interpreted as the end of expression
- Supports `pi` and `e` numbers
- There can be a different amount of whitespace characters between numbers and operators (`'\ '` or `'\t'`)
- You can enter variables, but they can't be used in operations.

Works with [infix2postfix](https://github.com/evgenyPro/Infix2postfix). Example: `echo "2 * (3 + 2)^2" | ./infix2postfix | ./postfixCalc`.
