#pragma once

#include <debug.h>
#include <limits>


// Yes, this is a dirty way of implementing these limits but they are currently
// not provided by the CE Toolchain.
namespace std {
	template<> class numeric_limits<int24_t> {
	public:
		static int24_t max() {return 0x7fffff;};
		static int24_t min() {return -0x800000;};
	};
}

template<typename BaseType, int FracDigits>
struct fp {
	constexpr static BaseType factor = 1 << FracDigits;

	BaseType data;

	fp() {}
	fp(double d) : data(static_cast<BaseType>(d*factor)) {}

	fp& operator=(double d) {
		data = static_cast<BaseType>(d*factor);
		return *this;
	}

	operator double() const {
		return static_cast<double>(data)/factor;
	}
};

template<typename T, int FracDigits>
constexpr fp<T,FracDigits> fpFromData(T data) {
	return *(fp<T,FracDigits>*)(&data);
}

template<typename T, int FracDigits>
constexpr fp<T,FracDigits> operator+(const fp<T,FracDigits>& a, const fp<T,FracDigits>& b) {

#ifdef DEBUG
	if ((a.data > 0 && b.data > 0 && std::numeric_limits<T>::max() - a.data < b.data)
	    || (a.data < 0 && b.data < 0 && std::numeric_limits<T>::min() - a.data > b.data)) {
		dbg_sprintf(dbgerr, "Fixed point overflow: %f + %f\n", (double) a, (double) b);
	}
#endif

	return fpFromData<T,FracDigits>(a.data + b.data);
}

template<typename T, int FracDigits>
constexpr fp<T,FracDigits> operator-(const fp<T,FracDigits>& a, const fp<T,FracDigits>& b) {

#ifdef DEBUG
	if ((a.data > 0 && b.data < 0 && std::numeric_limits<T>::max() - a.data < -b.data)
	    || (a.data < 0 && b.data > 0 && std::numeric_limits<T>::min() - a.data > b.data)) {
		dbg_sprintf(dbgerr, "Fixed point overflow: %f - %f\n", (double) a, (double) b);
	}
#endif

	return fpFromData<T,FracDigits>(a.data - b.data);
}

template<typename T, int FracDigits>
constexpr fp<T,FracDigits> operator*(const fp<T,FracDigits>& a, const fp<T,FracDigits>& b) {

#ifdef DEBUG
	volatile T result = a.data * b.data;
	if (b.data != 0 && a.data != result / b.data) {
		dbg_sprintf(dbgerr, "Fixed point overflow: %f * %f\n", (double) a, (double) b);
		dbg_sprintf(dbgerr, "-- %i * %i\n",  a.data, b.data);
	}
#endif

	// Note bit shifting negative numbers is undefined and, on the TI-84,
	// doesn't behave nicely, hence we have to prevent this.
	if ((a.data < 0) != (b.data < 0)) {
		return fpFromData<T,FracDigits>(-((-(a.data * b.data)) >> FracDigits));
	}
	return fpFromData<T,FracDigits>((a.data * b.data) >> FracDigits);
}

template<typename T, int FracDigits>
constexpr fp<T,FracDigits> operator/(const fp<T,FracDigits>& a, const fp<T,FracDigits>& b) {
	// Note bit shifting negative numbers is undefined and, on the TI-84,
	// doesn't behave nicely, hence we have to prevent this.
	if ((a.data < 0) != (b.data < 0)) {
		return fpFromData<T,FracDigits>(-((-(a.data / b.data)) << FracDigits));
	}
	return fpFromData<T,FracDigits>((a.data / b.data) << FracDigits);
}

template<typename T, int FracDigits>
constexpr bool operator>(const fp<T,FracDigits>& a, const fp<T,FracDigits>& b) {
	return a.data > b.data;
}

template<typename T, int FracDigits>
constexpr bool operator>=(const fp<T,FracDigits>& a, const fp<T,FracDigits>& b) {
	return  a.data >= b.data;
}

template<typename T, int FracDigits>
constexpr bool operator<(const fp<T,FracDigits>& a, const fp<T,FracDigits>& b) {
	return a.data < b.data;
}

template<typename T, int FracDigits>
constexpr bool operator<=(const fp<T,FracDigits>& a, const fp<T,FracDigits>& b) {
	return a.data <= b.data;
}

template<typename T, int FracDigits>
constexpr bool operator==(const fp<T,FracDigits>& a, const fp<T,FracDigits>& b) {
	return a.data == b.data;
}
