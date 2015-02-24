#include <iostream>
bool test(char x, char y)
{
      int i;
      bool same = false;
      for(i = 0; i < x.size(); i++)
      {
	int j;
	for(j =0; i <y.size(); j++)
	{
	  if (x[i] == y[j])
	    {
	      same = true;
	    }    
	}
      }
      return same;
}
int main()
{
  char x[30];
  char y[30];
  bool test1;
  bool test2;
  std::cout << "Enter words to be checked" << std::endl;
  while ( x != "last" && y != "pair" )
    {
      std::cout << "Enter 2 words";
      std::cin >> x >> y;
      test1 = test(x, y);
      test2 = test(y, x);
      if (!test1 || !test2)
	{
	  std::cout <<"not same" <<std::endl;
	}
      else{
	std::cout << "same" << std::endl;
      }
      }
  return 0;
}
