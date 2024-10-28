/**
 * Author: chilli, Ramchandra Apte, Noam527, Simon Lindholm
 * Date: 2019-04-24
 * License: CC0
 * Source: https://github.com/RamchandraApte/OmniTemplate/blob/master/src/number_theory/modulo.hpp
 * Description: Calculate $a\cdot b\bmod c$ (or $a^b \bmod c$) for $0 \le a, b \le c \le 7.2\cdot 10^{18}$.
 * Time: O(1) for \texttt{modmul}, O(\log b) for \texttt{modpow}
 * Status: stress-tested, proven correct
 * Details:
 * This runs ~2x faster than the naive (__int128_t)a * b % M.
 * A proof of correctness is in doc/modmul-proof.tex. An earlier version of the proof,
 * from when the code used a * b / (long double)M, is in doc/modmul-proof.md.
 * The proof assumes that long doubles are implemented as x87 80-bit floats; if they
 * are 64-bit, as on e.g. MSVC, the implementation is only valid for
 * $0 \le a, b \le c < 2^{52} \approx 4.5 \cdot 10^{15}$.
 */
#pragma once

typedef unsigned int uint;
typedef unsigned long long ull;
uint modmul(uint a, uint b, uint M) {
#ifdef _WIN32
	ull x = ull(a) * ull(b);
	uint xh = uint(x >> 32), xl = uint(x), d, m;
	asm("divl %4; \n\t" : "=a"(d), "=d"(m)
		: "d"(xh), "a"(xl), "r"(M()));
	return m;
#else
	uint ret;
	asm("mul %%ebx\ndiv %%ecx\nmov %%edx, %0\n"
	: "=ret"(ret): "a"(a), "b"(b), "c"(M): "edx");
	return ret;
#endif
}
ull modmul(ull a, ull b, ull M) {
#ifdef _WIN32
	ll ret = a * b - M * ull(1.L / M * a * b);
	return ret + M * (ret < 0) - M * (ret >= (ll)M);
#else
	ull ret;
	asm("mul %%rbx\ndiv %%rcx\n" : "=d"(ret)
		: "a"(a), "b"(b), "c"(M));
	return ret;
#endif
}
ull modpow(ull b, ull e, ull mod) {
	ull ans = 1;
	for (; e; b = modmul(b, b, mod), e /= 2)
		if (e & 1) ans = modmul(ans, b, mod);
	return ans;
}
