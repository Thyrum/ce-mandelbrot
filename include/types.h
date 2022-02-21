#pragma once

template<typename T>
struct cplx {
	cplx() {};
	cplx(T a, T b) : real(a), imag(b) {};
	union {
		struct {
			T real, imag;
		};
		struct {
			T a,b;
		};
	};
};

template<typename T>
constexpr cplx<T> operator+(const cplx<T>& a, const cplx<T>& b) {
	return { a.real + b.real, a.imag + b.imag };
}

template<typename T>
constexpr cplx<T> operator-(const cplx<T>& a, const cplx<T>& b) {
	return { a.real - b.real, a.imag - b.imag };
}

template<typename T>
constexpr cplx<T> operator*(const cplx<T>& a, const cplx<T>& b) {
	return { a.real * b.real - a.imag * b.imag, a.real * b.imag + a.imag * b.real };
}
