#include <iostream>
using namespace std;
enum class Fruit { apple, orange, pear };
enum class Color { red, green, orange };

#include <string>
#include <unordered_map>
#include <type_traits>

struct EnumClassHasher
{
    template <typename T>
    int operator()(const T& t) const
    {
        return static_cast<int>(t);
    }
};

using FuitsMap = unordered_map<Fruit, string, EnumClassHasher>;
using ColorMap = unordered_map<Color, string, EnumClassHasher>;


FuitsMap fruitTraits({  { Fruit::apple,"apple" },
                        { Fruit::orange,"orange" },
                        { Fruit::pear, "pear" } });
ColorMap colorTraits({  { Color::red,"red" },
                        { Color::green,"green" },
                        { Color::orange, "orange" } });
    


template <typename T>
struct Traits
{
    static string name(int index)
    {
        if (std::is_same<Fruit,T>::value)
        {
            auto found = fruitTraits.find((Fruit)index);
            if (found != fruitTraits.end())
                return found->second;
        }
        else if (std::is_same<Color, T>::value)
        {
            auto found = colorTraits.find((Color)index);
            if (found != colorTraits.end())
                return found->second;
        }

        return "unknown";
    }
};

/*int main()
{    
    
    int t = 0; std::cin >> t;

    for (int i = 0; i != t; ++i) {
        int index1; std::cin >> index1;
        int index2; std::cin >> index2;
        cout << Traits<Color>::name(index1) << " ";
        cout << Traits<Fruit>::name(index2) << "\n";
    }
    return 0;
}*/