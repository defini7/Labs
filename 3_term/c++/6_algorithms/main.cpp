#if 0

#include <iostream>

#include <stack>
#include <vector>
#include <list>

using namespace std;

template <class T>
void PushElements(T& stack)
{
    for (int i = 0; i < 10; i++)
    {
        stack.push(i);
        cout << stack.top() << ' ';
    }
}

template <class T>
void PopElements(T& stack)
{
    while (!stack.empty())
    {
        cout << stack.top() << ' ';
        stack.pop();
    }
}

int main()
{
    stack<int> stkDeque;
    stack<int, list<int>> stkList;
    stack<int, vector<int>> stkVec;

    cout << "pushing onto deque stack: ";
    PushElements(stkDeque);

    cout << "\npushing onto list stack: ";
    PushElements(stkList);

    cout << "\npushing onto vec stack: ";
    PushElements(stkVec);

    cout << endl;

    cout << "\npopping from deque stack: ";
    PopElements(stkDeque);

    cout << "\npopping from list stack: ";
    PopElements(stkList);

    cout << "\npopping from vec stack: ";
    PopElements(stkVec);

    cout << endl;
}

#endif

#if 0

#include <iostream>
#include <queue>

using namespace std;

int main()
{
    std::queue<double> values;

    values.push(3.2);
    values.push(9.8);
    values.push(5.4);

    while (!values.empty())
    {
        cout << values.front() << ' ';
        values.pop();
    }

    cout << endl;
}

#endif

#if 0

#include <iostream>
#include <queue>

using namespace std;

int main()
{
    std::priority_queue<double> values;

    values.push(3.2);
    values.push(9.8);
    values.push(5.4);

    while (!values.empty())
    {
        cout << values.top() << ' ';
        values.pop();
    }

    cout << endl;
}

#endif

#if 0

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    vector<int> v = { 5, 3, 9, 10, 4, 2 };

    make_heap(v.begin(), v.end()); // создание кучи

    for (int n : v)
        cout << n << ' ';

    cout << endl;

    for (int i = 0; i < 10; i++)
    {
        v.push_back(rand() % 100);
        push_heap(v.begin(), v.end()); // поддержка в кучевом состоянии
    }

    sort_heap(v.begin(), v.end()); // сортировка

    for (int n : v)
        cout << n << ' ';

    cout << endl;
}

#endif

// Haven't discussed before

#if 0

#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int main()
{
    vector<int> v = { 1, 2, 3, 4 };

    while (next_permutation(v.begin(), v.end()))
    {
        for (int n : v)
            cout << n << ' ';

        cout << endl;
    }

    cout << endl;

    for (int n : v)
        cout << n << ' ';

    cout << endl;

    rotate(v.begin(), v.begin() + 2, v.end());

    for (int n : v)
        cout << n << ' ';
}

#endif

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    vector<int> v = { 3, 3, 4, 5, 10, 20, 21, 31, 31, 36, 42, 43, 55 };

    auto [left, right] = equal_range(v.begin(), v.end(), 21);

    cout << distance(v.begin(), left) << ':' << *left << ' ' << distance(v.begin(), right) << ':' << *right << endl;

    v.insert(left, 21);
    //v.insert(right, 21);

    for (int n : v)
        cout << n << endl;

    cout << endl;

    cout << *min_element(v.begin(), v.end()) << endl;
    cout << *max_element(v.begin(), v.end()) << endl;
}
