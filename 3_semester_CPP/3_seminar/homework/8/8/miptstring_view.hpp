#pragma once

#include <iostream>
#include <cstring>
#include "miptstring.hpp"


namespace mipt1 {

	class StringView {

	private:
		const char* mpData;
		std::size_t mSize;

	private:

        StringView() {
            ;
            mSize = 0;
            mpData = nullptr;
        }
        StringView(StringView& str) {
            mSize = str.mSize;
            mpData = str.mpData;
        }
        StringView(const mipt::String& s) {
            mSize = s.getSize();
            mpData = s.cStr();
        }
        StringView(const char* s) {
            mpData = s;
            mSize = strlen(s);
        }
        const char& at(size_t i)
        {
            if (i >= mSize)
            {
                throw std::out_of_range("Error! Index is out of bounds.");
                std::exit(1);
            }
            return mpData[i];
        }
        const char& operator[](size_t i) const
        {
            return mpData[i];
        }
        bool operator<( StringView& right) const
        {
            size_t i = 0;
            while (i < mSize && i < right.mSize && mpData[i] == right.mpData[i])
                i++;

            return mpData[i] < right.mpData[i];
        }
        size_t size() const {
            return mSize;
        }
        StringView substr(size_t pos, size_t count) {
            if (pos > mSize)
                throw std::out_of_range("Error! Index is out of bounds.");
            if (pos + count > mSize)
                count = mSize - pos;
            StringView result;
            result.mpData = mpData + pos;
            result.mSize = count;
            return result;
        }
        void remove_prefix(size_t n) {
            mSize -= n;
        }
        void remove_suffix(size_t n) {
            mSize -= n;
            mpData += n;
        }
	};

	std::ostream& operator<<(std::ostream& out, StringView& sv);





}