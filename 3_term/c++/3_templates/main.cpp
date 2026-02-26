#include <iostream>
#include <queue>
#include <string>
#include <type_traits>

template <class T>
class Vec2D
{
    static_assert(std::is_arithmetic_v<T>, "T in vec2d<T> is not an arithmetic type");

public:
    Vec2D(T x = 0, T y = 0) : x(x), y(y) {}

    Vec2D<T> operator+(const Vec2D<T>& other) const
    {
        return { x + other.x, y + other.y };
    }

    template <class U>
    inline operator Vec2D<U>() const
    {
        return { static_cast<U>(x), static_cast<U>(y) };
    }

    T x, y;

    static T s_SomeStaticVariableWithTypeT;

};

template <class T>
T Vec2D<T>::s_SomeStaticVariableWithTypeT = 666;

namespace std
{
    /*string to_string(const Vec2D<double>& v)
    {
        return format("double: ({}, {})", v.x, v.y);
    }

    string to_string(const Vec2D<float>& v)
    {
        return format("long double: ({}, {})", v.x, v.y);
    }*/

    template <class T>
    string to_string(const Vec2D<T>& v)
    {
        return "(" + std::to_string(v.x) + ", " + std::to_string(v.y) + ")";
    }
}

template <class T1, class T2>
decltype(T1() + T2()) two_sum(T1 v1, T2 v2)
{
    return v1 + v2;
}

int main()
{
    using namespace std;

    Vec2D<int> v1(1, 2);
    cout << to_string(v1) << endl;

    cout << Vec2D<int>::s_SomeStaticVariableWithTypeT << endl;
    cout << two_sum(2, 42.3) << endl;
    cout << to_string(two_sum(v1, Vec2D<int>(2, 3))) << endl;
}
