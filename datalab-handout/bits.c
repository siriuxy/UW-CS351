/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
/*DeMorgan's Law */
  return ~(~x|~y);
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
/* using unsigned int that 
 * right shifts by logic 
 * plan changed since casting not allowed
 * now using & to remove heading FFs*/
int mv=0xFF<<((n)<<3);
x= x&mv;
x=(x)>>((n)<<3);
x=x&0xFF;
return  x;

}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
/* it looks like the following solution is not allowed
 * due to the use of big bin 
 * 
unsigned int filter=-1;
filter=filter>>n;
x=x>>n;
//filter=~filter;
//printf("filter is currently %x",filter);
x=x&filter; 
*/
int mask=0;
int filter=1;
filter=~(filter<<31);
mask=(filter);
//
mask=mask>>n;
mask=((mask)<<1)+1; //look... << has lower priority than +

x=(x>>n)&mask; //forgot to move x by n
 return x;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
/*idea: count 1s in a group of 2, then of 4, of 8, of 16, and eventually of 32 */


int twoGrouper=0x55;//used 55 instead of AA to avoid arithmetic shift problem
int fourGrouper=0x33;
int eightGrouper=0xF;
int sixteenGrouper=0xFF;
int thirtytwoGrouper=0xFF;
//printf("ater assignemtn\n 2, %x \n 4, %x\n 8, %x\n 16,%x \n 32,%x\n",twoGrouper,fourGrouper,eightGrouper,sixteenGrouper,thirtytwoGrouper);  
twoGrouper=((((((twoGrouper<<8)+twoGrouper)<<8)+twoGrouper)<<8)+twoGrouper);
x=(x&twoGrouper)+((x>>1)&twoGrouper);
fourGrouper=((((((fourGrouper<<8)+fourGrouper)<<8)+fourGrouper)<<8)+fourGrouper);
x=(x&fourGrouper)+((x>>2)&fourGrouper);
eightGrouper=((((((eightGrouper<<8)+eightGrouper)<<8)+eightGrouper)<<8)+eightGrouper);
x=(x&eightGrouper)+((x>>4)&eightGrouper);
sixteenGrouper=(sixteenGrouper<<16)+sixteenGrouper;
x=(x&sixteenGrouper)+((x>>8)&sixteenGrouper);
thirtytwoGrouper=(thirtytwoGrouper<<8)+thirtytwoGrouper;
x=(x&thirtytwoGrouper)+((x>>16)&thirtytwoGrouper);
//printf("2, %x \n 4, %x\n 8, %x\n 16,%x \n 32,%x\n",twoGrouper,fourGrouper,eightGrouper,sixteenGrouper,thirtytwoGrouper);  
return x;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
/*idea: use or operator to leave marks that whether certain position(s) has bits
 * */
x=(x>>16)|x;
x=(x>>8)|x;
x=(x>>4)|x;
x=(x>>2)|x;
x=(x>>1)|x;
x=(~x)&1; 
 return x;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
 
 return (0x1<<31);
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
int y=1;
int z=0;
y=(((y<<31)-1)<<1)+1;
//printf("y is %x\n ",y);
x=x>>(n-1);//reason for n-1: 2's complement's nth digit is the sign digit.
return (!(x^y))|(!(x^z));
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
/*used variable m to judge if the given x is divisible by 2^n */
int m=1;
m=(m<<n)-1;
m=!!(x&m);
    return (x>>n)+((x>>31)&(!!n)&(m));
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {

  return (~x)+1 ;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
int store=x;
x=(~(x>>31)); 
//printf("x = %x \n",x);
return x&(!!store);

}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
int isEqual;
int isSmall;
int isNegVsPos=(x>>31)&(~(y>>31))&1;
int isPosVsNeg=(~(x>>31))&((y>>31))&1;
y=(~y)+1;
isEqual=!(x+y);
isSmall=((x+y)>>31)&1;


 return isNegVsPos|(((~isPosVsNeg)&1)&(isEqual|isSmall));//feels like writing an if condition with bitwise operators....
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
/* a combination of bitTo1 and bitCount */
x=x|(x>>1);
x=x|(x>>2);
x=x|(x>>4);
x=x|(x>>8);
x=x|(x>>16);



int twoGrouper=0x55;//used 55 instead of AA to avoid arithmetic shift problem
int fourGrouper=0x33;
int eightGrouper=0xF;
int sixteenGrouper=0xFF;
int thirtytwoGrouper=0xFF;
//printf("ater assignemtn\n 2, %x \n 4, %x\n 8, %x\n 16,%x \n 32,%x\n",twoGrouper,fourGrouper,eightGrouper,sixteenGrouper,thirtytwoGrouper);  
twoGrouper=((((((twoGrouper<<8)+twoGrouper)<<8)+twoGrouper)<<8)+twoGrouper);
x=(x&twoGrouper)+((x>>1)&twoGrouper);
fourGrouper=((((((fourGrouper<<8)+fourGrouper)<<8)+fourGrouper)<<8)+fourGrouper);
x=(x&fourGrouper)+((x>>2)&fourGrouper);
eightGrouper=((((((eightGrouper<<8)+eightGrouper)<<8)+eightGrouper)<<8)+eightGrouper);
x=(x&eightGrouper)+((x>>4)&eightGrouper);
sixteenGrouper=(sixteenGrouper<<16)+sixteenGrouper;
x=(x&sixteenGrouper)+((x>>8)&sixteenGrouper);
thirtytwoGrouper=(thirtytwoGrouper<<8)+thirtytwoGrouper;
x=(x&thirtytwoGrouper)+((x>>16)&thirtytwoGrouper);
//printf("2, %x \n 4, %x\n 8, %x\n 16,%x \n 32,%x\n",twoGrouper,fourGrouper,eightGrouper,sixteenGrouper,thirtytwoGrouper);  
return x-1;


}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
 return 2;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  return 2;
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  return 2;
}
