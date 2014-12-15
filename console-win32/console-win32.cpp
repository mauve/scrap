
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

int main()
{
  for (int i = 0; i < 5; i++)
    std::cout << i << " ";

  for (auto i : {0, 1, 2, 3, 4})
    std::cout << i << " ";

  auto v = { 0, 1, 2, 3, 4 };
  std::copy(std::begin(v), std::end(v),
    std::ostream_iterator<int>(std::cout, " "));

  std::vector<int> a{ 0, 1, 2, 3, 4 };
  std::for_each(std::begin(a), std::end(a), [](int i){
    std::cout << i << " ";
  });

  return 0;
}