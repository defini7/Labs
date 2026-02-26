#include <iostream>
#include <algorithm>
/*#include <vector>
#include <queue>
#include <string>
#include <set>*/
#include <type_traits>
#include <iterator>
#include <numeric>
#include <sstream>
#include <deque>

template <class T>
struct Point2D
{
    T x, y;
};

template <class T>
using Container = std::deque<T>;

template <class T>
std::ostream& operator<<(std::ostream& os, const Point2D<T>& p)
{
    static_assert(std::is_same_v<decltype(os << T{}), std::ostream&>, "T must be printable");
    os << '(' << p.x << ',' << p.y << ')';
    return os;
}

template <class T>
void Print(const T& cont)
{
    for (const auto& v : cont)
        std::cout << v << ' ';
    std::cout << std::endl;
}

int main()
{
    srand(time(nullptr));

    Container<Point2D<int>> data;

    /*std::cout << "Queue:\n";

    std::queue<int> a;
    a.push(4);
    a.push(2);

    std::cout << a.front() << std::endl;
    a.pop();

    std::cout << a.front() << std::endl;
    a.pop();

    std::priority_queue<int> b;

    std::cout << "Priority queue:\n";

    b.push(2);
    b.push(3);
    b.push(-12);
    b.push(40);

    std::cout << b.top() << std::endl;
    b.pop();

    std::cout << b.top() << std::endl;
    b.pop();

    std::cout << b.top() << std::endl;
    b.pop();

    std::cout << b.top() << std::endl;
    b.pop();*/

    /*while (1)
    {
        std::cout << "$ ";

        std::string s;
        std::getline(std::cin, s);

        if (s.empty())
            continue;

        std::istringstream iss(s);

        std::istream_iterator<std::string> begin(iss);
        std::istream_iterator<std::string> end;

        std::vector<std::string> tokens(begin, end);

        if (tokens[0] == "sort")
        {
            std::sort(data.begin(), data.end(),
                [](const auto& c1, const auto& c2)
                {
                    return c1.x < c2.x || (c1.x == c2.x && c1.y < c2.y);
                });
        }

        else if (tokens[0] == "insert")
            data.insert(data.end(), { rand() % 50, rand() % 50 });

        else if (tokens[0] == "print")
        {
            if (tokens.size() > 1 && tokens[1] == "reverse")
            {
                for (auto it = data.rbegin(); it != data.rend(); it++)
                    std::cout << *it << std::endl;
            }
            else
            {
                for (auto it = data.begin(); it != data.end(); it++)
                    std::cout << *it << std::endl;
            }
        }

        else if (tokens[0] == "clear")
            data.clear();

        else if (tokens[0] == "cls")
        {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        }

        if (tokens[0] == "quit")
            break;
    }*/

    Container<double> s1;
    Container<double> s2;

    std::cout << "s1: ";

    for (int i = 0; i < 10; i++)
    {
        int n = rand() % 20;
        std::cout << n << ' ';
        s1.insert(s1.end(), n);
    }

    std::cout << std::endl;
    std::cout << "s2: ";

    for (int i = 0; i < 10; i++)
    {
        int n = rand() % 20;
        std::cout << n << ' ';
        s2.insert(s2.end(), n);
    }

    std::cout << std::endl;

    // uses insertion sort for small amount of data
    // uses quick sort for large amount of data

    // no sort on std::set
    std::sort(s1.begin(), s1.end());
    std::sort(s2.begin(), s2.end());

    //////////////////////////

    Container<int> s3;
    std::set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), std::inserter(s3, s3.begin()));

    std::cout << "Union: ";
    Print(s3);

    //////////////////////////

    Container<int> s4;
    std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), std::inserter(s4, s4.begin()));

    std::cout << "Intersection: ";
    Print(s4);

    //////////////////////////

    std::cout << "Sum s1: " << std::accumulate(s1.begin(), s1.begin() + 3, 0) << std::endl;

    //////////////////////////

    int n = rand() % 10;
    bool has = std::binary_search(s1.begin(), s1.end(), n);

    std::cout << "s1 " << (has ? "contains " : "doesn't contain ") << n << " in it" << std::endl;
}
