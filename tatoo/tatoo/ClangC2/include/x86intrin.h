/*===---- x86intrin.h - X86 intrinsics -------------------------------------===
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 *===-----------------------------------------------------------------------===
 */

#ifndef __X86INTRIN_H
#define __X86INTRIN_H
#ifndef RC_INVOKED

#include <ia32intrin.h>

#include <immintrin.h>

#include <mm3dnow.h>

#include <bmiintrin.h>

#include <bmi2intrin.h>

#include <lzcntintrin.h>

#include <popcntintrin.h>

#include <rdseedintrin.h>

#include <prfchwintrin.h>

#include <ammintrin.h>

#include <fma4intrin.h>

#include <xopintrin.h>

#include <tbmintrin.h>

#include <f16cintrin.h>

/* FIXME: LWP */

#endif /* RC_INVOKED */
#endif /* __X86INTRIN_H */
