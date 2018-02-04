# Precision
Revamped Precision number library

Modules to implement:
---------------------------------------------------------------------------------
| Module Name       | Dependencies      | Description               | Status    |
---------------------------------------------------------------------------------
| exception         |                   | Common exception type     | Done      |
|                   |                   | number types throw        |           |
---------------------------------------------------------------------------------
| Digit container   |                   | Basic interface to manage | Done      |
|                   |                   | a string of digits        |           |
---------------------------------------------------------------------------------
| Signed Class      |                   | Basic POD representing    | Done      |
|                   |                   | a number sign             |           |
---------------------------------------------------------------------------------
| Signed Interface  | Signed Class      | Basic interface to manage | Done      |
|                   |                   | number signs              |           |
---------------------------------------------------------------------------------
| Integer           | exception         | A set of functions and/or | Done      |
| Operations        |                   | operations for dealing    |           |
|                   |                   | with integer-based data   |           |
---------------------------------------------------------------------------------
| Abstract Static   | Integer           | A class representing an   | Done      |
| General Base      | Operations        | "abstract", or without    |           |
| Integer           |                   | visual representation,    |           |
|                   | Signed Interface  | integer with a number     |           |
|                   |                   | radix fixed at            |           |
|                   | Digit Container   | compile-time              |           |
---------------------------------------------------------------------------------
| Image Set         |                   | Basic interface to manage | Done      |
| Interface         |                   | digit and symbol glyphs   |           |
---------------------------------------------------------------------------------
| Integer Image     | Image Set         | A set of functions and/or | Done      |
| Operations        | Interface         | operations for dealing    |           |
|                   |                   | with image-based data     |           |
---------------------------------------------------------------------------------
| Static            | Abstract Static   | A class representing an   | Done      |
| General Base      | General Base      | integer with visual       |           |
| Integer           | Integer           | representation and a      |           |
|                   |                   | number radix fixed at     |           |
|                   | Image Set         | compile-time              |           |
|                   | Operations        |                           |           |
---------------------------------------------------------------------------------
| Base Converter    |                   | A utility for converting  | Done      |
|                   |                   | among number bases        |           |
---------------------------------------------------------------------------------
| Abstract Dynamic  | Integer           | A class representing an   | Done      |
| General Base      | Operations        | "abstract", or without    |           |
| Integer           |                   | visual representation,    |           |
|                   | Signed Interface  | integer with a number     |           |
|                   |                   | radix mutable at          |           |
|                   | Digit Container   | compile-time              |           |
|                   |                   |                           |           |
|                   | Base converter    |                           |           |
---------------------------------------------------------------------------------
| Dynamic           | Abstract Dynamic  | A class representing an   | Not       |
| General Base      | General Base      | integer with visual       | Started   |
| Integer           | Integer           | representation and a      |           |
|                   |                   | number radix mutable at   |           |
|                   | Image Set         | compile-time              |           |
|                   | Operations        |                           |           |
---------------------------------------------------------------------------------
| Floating          | exception         | A set of functions and/or | Not       |
| Operations        |                   | operations for dealing    | Started   |
|                   |                   | with floating-based data  |           |
---------------------------------------------------------------------------------
| Floating          | Integer           | Classes representing      | Not       |
| - Abstract Static | - Abstract Static | arbitrary precision       | Started   |
| - Static          | - Static          | numbers that have decimal |           |
| - Abstract Dynamic| - Abstract Dynamic| portions.                 |           |
| - Dynamic         | - Dynamic         |                           |           |
|                   |                   |                           |           |
|                   | Floating          |                           |           |
|                   | Operations        |                           |           |
---------------------------------------------------------------------------------
| Fraction          | exception         | A set of functions and/or | Not       |
| Operations        |                   | operations for dealing    | Started   |
|                   |                   | with fraction-based data  |           |
---------------------------------------------------------------------------------
| Fraction          | Floating          | Classes representing      | Not       |
| - Abstract Static | - Abstract Static | numerator/denominator     | Started   |
| - Static          | - Static          | fractions                 |           |
| - Abstract Dynamic| - Abstract Dynamic|                           |           |
| - Dynamic         | - Dynamic         |                           |           |
|                   |                   |                           |           |
|                   | Fraction          |                           |           |
|                   | Operations        |                           |           |
---------------------------------------------------------------------------------
| Complex           | exception         | A set of functions and/or | Not       |
| Operations        |                   | operations for dealing    | Started   |
|                   |                   | with complex-based data   |           |
---------------------------------------------------------------------------------
| Complex           | Complex           | Classes representing      | Not       |
| Polar             | Operations        | complex numbers. The      | Started   |
|                   |                   | scalar numbers may be     |           |
|                   |                   | represented by any other  |           |
|                   |                   | number type.              |           |
---------------------------------------------------------------------------------
| PRNG              |                   | Basic proof-of-concept    | Not       |
|                   |                   | PRNG that supports        | Started   |
|                   |                   | any of the number types   |           |
---------------------------------------------------------------------------------
| Mathematical      | Integer           | Basic mathematics system  | Not       |
| System            | Operations        | with support for common   | Started   |
| - Trigonometry    |                   | operations                |           |
| - Logarithmic/Exp | Floating          |                           |           |
| - Factorials      | Operations        |                           |           |
| - Fraction-based  |                   |                           |           |
|                   | Fraction          |                           |           |
|                   | Operations        |                           |           |
---------------------------------------------------------------------------------
| Iterator          |                   | An interface in all       | In        |
| Interface         |                   | types to make them STL-   | Consider- |
|                   |                   | container-like            | ation     |
---------------------------------------------------------------------------------
| Conservative      |                   | A digit string manager    | In        |
| Digit Container   |                   | that stuffs data into     | Consider- |
|                   |                   | the most compact form     | ation     |
|                   |                   | possible                  |           |
---------------------------------------------------------------------------------
| Documentation     |                   | Web-based documentation   | In        |
|                   |                   | of library using doxygen  | Progress  |
---------------------------------------------------------------------------------
