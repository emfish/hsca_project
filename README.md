# Analysis of Sequential Logic Synthesis Tools for the Generation of Arithmetic Circuits

## Goal
- The adders and multipliers in class require much ingenuity.
- Automated circuit syntehsis tools are growing more powerful
- Questions:
 - How do the automatically optimized circuits produced by current syntehsis tools compare to the manually generated ones we have discussed in class?
 - Can the underlying algorithm used to optimize the circuit be improved (in terms of circuit delay, complexity, or algorithmic runtime)?

## Synthesis Tools
- Berkeley ABC
- Mockturtle

## Starting Arithmetic Circuits
- Adders
 - 8-bit RCA
 - 16-bit RCA
 - 32-bit RCA
 - 64-bit RCA
- Multipliers
 - 8-bit Array Multiplier
 - 8-bit Booth Multiplier
 - 8-bit Wallace Tree Multiplier
- Dividers
 - TBD

## Approach
- Run each starting arithmetic circuit through each synthesis tool
- Compare the output of each to the original in regards to:
 - Complexity (number of gates)
 - Delay (number of gates in the critical path)
- If the synthesized circuits do not have better results then the starting circuits, we will investigate underlying algorithms to try to close the gap.


