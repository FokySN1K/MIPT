#include "Number.h"

Number:: Number() {
    //Number(0);
    capacity = size = 1;
    data = new char[capacity];
    data[0] = 0;
}
Number:: Number(long long a){
        // Ќаходим размер необходимой пам€ти под это число
        long long temp = a;
        capacity = 0;
        while (temp != 0)
        {
            temp /= base;
            capacity += 1;
        }

        // ќтдельно обрабатываем случай, когда число равно 0
        if (capacity == 0)
            capacity = 1;

        // ¬ыдел€ем пам€ть и записывем число a в массив data
        // Ќапример, число 12345678 представитс€ в виде массива [78, 56, 34, 12]

        data = new char[capacity];

        for (long long i = 0; i < capacity; ++i)
        {
            data[i] = a % base;
            a /= base;
        }

        // ¬ данном случае размер будет равен вместимости
        size = capacity;
}
Number:: Number(const Number& left) {
        capacity = left.capacity;
        size = left.size;
        data = new char[capacity];
        for (int i = 0; i < size; i++) {
            data[i] = left.data[i];
        }

}
Number:: Number(const char* str) {
        int len = strlen(str);
        size = capacity = (len / 2 + len % 2);

        data = new char[capacity];
        int len_1 = 0;
        for (int i = len - 1; i >= 0 && len_1 < size; i = i - 2) {
            if (i - 1 < 0) {
                data[len_1++] = str[i] - '0';
            }
            else {
                data[len_1++] = (str[i - 1] - '0') * 10 + str[i] - '0';
            }

        }
}
Number:: ~Number()
    {
        delete[] data;
    }


Number& Number::operator =(const Number& left) {
        capacity = left.capacity;
        size = left.size;
        data = new char[capacity];
        for (int i = 0; i < size; i++) {
            data[i] = left.data[i];
        }
        return *this;
}
Number Number:: operator +(const Number& left) const {
        Number n;
        Number result;
        // максимально может изменитьс€ размер на 1 символ, 
        // что в конце мы и проверим
        n.size = max(size, left.size) + 1;
        n.capacity = n.size;
        n.data = (char*)calloc(sizeof(char), n.size);
        int ost = 0, cel = 0; // остаток и цела€ часть
        for (int i = 0; i <= n.size - 2; i++) {
            if (i >= left.size) {
                ost = (int)data[i];
            }
            else if (i >= size) {
                ost = (int)left.data[i];
            }
            else {
                ost = (int)data[i] + (int)left.data[i];
                cel = ost / 100;
            }
            ost += (int)n.data[i];
            cel = ost / 100;
            ost %= 100;
            n.data[i] = ost;
            n.data[i + 1] = cel;
}
        // провер€ем ли был задейстован полседний разр€д или нет(1-ый)
        if (n.data[n.size - 1] == 0) {
            result.size = n.size - 1;
            result.capacity = result.size;
            result.data = new char[result.size];
            for (int i = 0; i < result.size; i++) {
                result.data[i] = n.data[i];
            }
            return result; // почему this?
        }
        else {
            return n;
        }
}
void Number:: operator +=(const Number& left) {
        *this = *this + left;
}
Number Number:: operator *(const Number& left) const {
        Number result;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < left.size; j++) {
                int multiplier = (int)data[i] * (int)left.data[j];
                if (multiplier == 0) {
                    continue;
                }
                int size_number = 0;
                // тупо, но должно сработать
                if (multiplier / 10 == 0) {
                    size_number = 1;
                }
                else if (multiplier / 100 == 0) {
                    size_number = 2;
                }
                else if (multiplier / 1000 == 0) {
                    size_number = 3;
                }
                else {
                    size_number = 4;
                }
                int stepen = 2 * (i + j);

                int len = stepen + size_number;
                char* s = (char*)calloc(sizeof(char), len + 1);
                int step = size_number - 1;
                for (int k = 0; k < size_number; k++) {
                    s[k] = multiplier / (int)pow(10, step) + '0';
                    multiplier %= (int)pow(10, step--);
                }
                for (int k = size_number; k < len; k++) {
                    s[k] = '0';
                }
                if (true) {
                    Number a = s;
                    result += a;
                }
                free(s);
            }
        }
        return result;
}
void Number:: operator *=(const Number& left) {
        *this = *this * left;
}
bool Number:: operator >(const Number& left) const {
    if (size != left.size) {
        if (size > left.size) {
            return true;
        }
        return false;
    }
    else {
        for (int i = size - 1; i >= 0; i--) {
            if ((int)data[i] > (int)left.data[i]) {
                return true;
            }
            else if ((int)data[i] < (int)left.data[i]) {
                return false;
            }
            else {
                continue;
            }
        }
        return false;
    }

}
bool Number:: operator <(const Number& left) const {
    if (*this > left) {
        return false;
    }
    return true;

}
char Number:: operator [](int n) const {
    return data[n];
}

int Number:: get_size() {
    return size;
}

void Number::divide_by_2() {
    // 124 -> 241 надо делить по одному числу, прибавл€€ 5, если число нечетное  
    // 256 -> 562
    if ((int)data[0] % 2 != 0) {
        cout << "fall" << endl;
        assert(0);
    }
    int first, second; // второй и первый разр€ды 
    for (int i = 0; i < size; i++) {
        first = (int)data[i] % 10;
        second = (int)data[i] / 10;
        // делаю всЄ поразр€дно, а не быстро
        if (first % 2 == 0) {
            data[i] = ((int)data[i] / 10) * 10 + ((int)data[i] % 10) / 2;
        }
        else {
            data[i] = ((int)data[i] / 10) * 10 + ((int)data[i] % 10) / 2;
            data[i - 1] = (int)data[i - 1] + 50;
        }
        if (second % 2 == 0) {
            data[i] = ((int)data[i] / 10) * 10 / 2 + ((int)data[i] % 10);
        }
        else {
            data[i] = ((int)data[i] / 10) / 2 * 10 + ((int)data[i] % 10 + 5);
        }
    }
    if ((int)data[size - 1] == 0) {
        Number result;
        free(result.data);
        result.capacity = result.size = size - 1;
        result.data = new char[result.size];
        for (int i = 0; i < result.size; i++) {
            result.data[i] = data[i];
        }
        *this = result;
    }
}
bool isEven(const Number& right) {
    return (((int)right.data[0] % 2) == 0);
}
ostream& operator<<(ostream& stream, const Number& right)
{
    // ѕечатаем самый большой разр€д
    stream << (int)right.data[right.size - 1];

    // ѕечатаем остальные разр€ды с заполнением нул€ми до 2-х цифр
    // setfill и setw это то же самое, что и в €зыке C спецификатор %02d
    for (std::size_t i = 0; i < right.size - 1; ++i)
        stream << setfill('0') << setw(2) << (int)right.data[right.size - 2 - i];

    return stream;
}

