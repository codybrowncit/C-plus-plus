#include <iostream>
int main()
{
  int l;
  int p;
  int v;
  while(std::cin >> l >> p >> v)
    {
      int div = v/p;
      int mod = v%p;
      int days = div*l;
      days +=mod;
      std::cout<< days <<std::endl;
    }
}
