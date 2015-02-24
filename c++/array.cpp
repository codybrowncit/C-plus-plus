#include <iostream>
void sort_int_asc(char a[], const int size)
{
    bool switched = true;
    int i;
    char hold;
    int j;
    int k;
    while (switched)
    {
        switched = false;
	j++;
	k=0;
        for (i=0; i < size-1; i++)
        {
            if (a[i] > a[i+1])
            {
	      k++;
	        std::cout<< j << k <<"a[i]"<< a[i] << std::endl;
                hold = a[i];
	        std::cout<< j << k <<"hold"<< hold << std::endl;
                a[i] = a[i+1];
		std::cout<< j << k <<"a[i]"<< a[i] << std::endl;
                a[i+1] = hold;
		std::cout<< j << k <<"a[i+1]"<< a[i+1] << std::endl;
                switched = true;
            }
        }
    }
}


int main()
{
  char test[5] = { 'x', 'a', 'A', '0', ' ' };
  sort_int_asc(test, 5);
  for (int i; i<5; i++)
    {
      std::cout<< test[i] << std::endl;
    }
}
