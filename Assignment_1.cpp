#include <iostream>
#include <vector>
#include <unordered_map>

int main()
{
    int n;
    int target;
    int num1, num2 = 0;
    std::unordered_map<int, int> map;

    std::cout << "Enter the input array size: " << std::endl;
    std::cin >> n;

    std::vector<int> array(n);
    std::cout << "Enter input array elements: ";
    for (int i = 0; i < n; i++)
    {
        std::cin >> array[i];
    }

    std::cout << "Enter Target to find: ";
    std::cin >> target;
    int i = 0;
    while (i < n)
    {
        int num = target - array[i];
        if (map.find(num) != map.end())
        {
            num1 = map[num];
            num2 = i;
            break;
        }
        map[array[i]] = i;
        i++;
    }
    if (num1 | num2 != 0)
    {
        std::cout << "[" << num1 << ',' << num2 << ']';
    }
    else
    {
        std::cout << "Not found any pair";
    }

    return 0;
}