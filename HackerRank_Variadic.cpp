#include <iostream>
#include <vector>

using namespace std;

template <int... digits>
int reversed_binary_value()
{
    std::vector<int> vec = { digits... };
    int value = 0;
    for ( int i = 0; i < vec.size(); ++i )
    {        
        value |= vec[i] << i;
    }

    return value;
}

/*int main()
{
    cout << reversed_binary_value<0, 0, 1>() << endl;
    return 0;
}*/