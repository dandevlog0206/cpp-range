/*************************************************************************/
/* range.cpp                                                             */
/*************************************************************************/
/* https://www.dandevlog.com/all/programming/1289/                       */
/* https://github.com/dandevlog0206/cpp-range                            */
/*************************************************************************/
/* Copyright (c) 2024 www.dandevlog.com                                  */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#pragma once

#include <assert.h>

template <class T>
class range_iter {
	template <class U>
	friend class range_t;

	range_iter(const T& step, const T& curr) :
		step(step), curr(curr) {}

public:
	T operator*() const {
		return curr;
	}

	range_iter& operator++() {
		curr += step;
		return *this;
	}

	bool operator!=(const range_iter<T>& rhs) const {
		if (0 <= step) return curr < rhs.curr;
		else return rhs.curr < curr;
	}

private:
	T step;
	T curr;
};

template <class T>
class range_t {
	template <class U>
	friend range_t<U> range(const U&, const U&, const U&);
	template <class U>
	friend range_t<U> range(const U&);

	range_t(const T& first, const T& last, const T& step) :
		first(first), last(last), step(step) {}

public:
	range_iter<T> begin() const {
		return { step, first };
	}

	range_iter<T> end() const {
		return { step, last };
	}

private:
	T first;
	T last;
	T step;
};

template <class T>
range_t<T> range(const T& first, const T& last, const T& step = static_cast<T>(1)) {
	assert((0 <= step && first <= last) || (step < 0 && last <= first));
	return { first, last, step };
}

template <class T>
range_t<T> range(const T& last) {
	return { static_cast<T>(0), last, static_cast<T>(1) };
}