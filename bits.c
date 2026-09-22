/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x|~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    int p1=~x&~y;//x0y0
    int res=~p1&~(x&y);//既非同0也非同1
    return res;
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    int signx=(x>>31)&1;
    int signy=(y>>31)&1;
    int x_0=!x;
    int y_0=!y;
    if(x_0&&y_0)return 1;
    if(x_0^y_0)return 0;
    return !(signx^signy);
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    
    int res = 0;
    res = res | (((v >> 16) > 0) << 4);        
    res = res | (((v >> (res | 8)) > 0) << 3);    
    res = res | (((v >> (res | 4)) > 0) << 2);    
    res = res | (((v >> (res | 2)) > 0) << 1);    
    res = res | ((v >> (res | 1)) > 0);           
    return res;


}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) 
{   int npos=n<<3;
    int mpos=m<<3;
    int mask1=0xFF<<npos;
    int mask2=0xFF<<mpos;
    int p1=((x>>npos)&0xFF)<<mpos;
    int p2=((x>>mpos)&0xFF)<<npos;
    int p3=x&~(mask1|mask2);
    int res=p1|p2|p3;
    return res;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    v = ((v >> 16) & 0xFFFF) | ((v & 0xFFFF) << 16);
    v = ((v >> 8) & 0x00FF00FF) | ((v & 0x00FF00FF) << 8);
    v = ((v >> 4) & 0x0F0F0F0F) | ((v & 0x0F0F0F0F) << 4);
    v = ((v >> 2) & 0x33333333) | ((v & 0x33333333) << 2);
    v = ((v >> 1) & 0x55555555) | ((v & 0x55555555) << 1);

    return v;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    return (x>>n)&~((1 << 31) >> n<<1) ;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int all1=!(~x);//全 1 时下面的折半最多只能数到 31，要单独补
    int count= 0;
    int count16 = x >> 16;
    count16 = !(~count16); 
    count += count16 << 4;
    x = x << (count16 << 4);
    int count8 = x >> 24;
    count8 = !(~count8);
    count += count8 << 3;
    x = x << (count8 << 3);
    int count4 = x >> 28;
    count4 = !(~count4);
    count += count4 << 2;
    x = x << (count4 << 2);
    int count2 = x >> 30;
    count2 = !(~count2);
    count += count2 << 1;
    x = x << (count2 << 1);
    int count1 = x >> 31;
    count1 = !(~count1);
    count += count1;
    return count + all1;

}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
   if (x == 0) return 0;
    if (x == 0x80000000) return 0xCF000000;
    unsigned sign = x & 0x80000000;
    unsigned exp = 0;
    unsigned cur;
    if (x < 0) {
        cur = ~x + 1;
    } else {
        cur = x;
    }
    unsigned temp = cur;
    while (temp > 1) {
        temp = temp >> 1;
        exp++;
    }
    unsigned raw = cur << (31 - exp);
    unsigned frac = (raw >> 8) & 0x007FFFFF;
    unsigned last_8 = raw & 0xFF;
    if ((last_8 > 0x80)|((last_8 == 0x80) & (frac & 1))) {
        frac += 1;
        if (frac >> 23) {
            frac = 0;
            exp++;
        }
    }
    unsigned E = (exp + 127) << 23;
    return sign | E | frac;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign = uf & 0x80000000;
    unsigned exp  = (uf >> 23) & 0xFF;
    unsigned frac = uf & 0x007FFFFF;

    if (exp == 0xFF) {
        return uf;
    }
    if (exp == 0) { 
        frac = frac << 1;
        return sign | frac;
    } else { 
        exp = exp + 1;
        return sign | (exp << 23) | frac;
    }
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
        unsigned sign = uf2 >> 31;
    unsigned E = (uf2 >> 20) & 0x7FF;
    // 指数小于 1023，即 |x| < 1，截断为 0
    if (E < 0x3FF) return 0;
    unsigned exp = E - 0x3FF;   // 无偏指数
   // exp >= 31 时，|x| >= 2^31，溢出（或恰好为 -2^31，也返回 0x80000000）
    if (exp >= 31) return 0x80000000;

    unsigned frac_high = uf2 & 0xFFFFF;  // 高 20 位小数
    unsigned magnitude;

    if (exp <= 20) {
        magnitude = (1 << exp) | (frac_high >> (20 - exp));
    } else {
        magnitude = (1 << exp) | (frac_high << (exp - 20)) | (uf1 >> (52 - exp));
    }

    if (sign) return -magnitude;
    return magnitude;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x > 127) {
        return 0x7F800000; 
    }
    if (x < -149) {
        return 0;
    }
    if (x >= -126) {
        unsigned exp = x + 127;
        return exp << 23;
    } else{
        int k = -126 - x;
        return 1 << (23 - k);
    }
}
