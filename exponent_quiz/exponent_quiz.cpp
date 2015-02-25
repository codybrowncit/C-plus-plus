#include <iostream>
#include <ctime>
#include <cstdlib>
#include "exponent_quiz.h"

void generate_exponents(const int min, const int max, int *exponents)
{
  int i;
  int x= 0;
  for (i=min; i <=max; i++, x++)
    {
      exponents[x] = i;
    }
  int r;
    x = 0;
    for (i=min; i <= max; i++, x++)
      {
	r = (std::rand() % (max-min+1));
	int hold = exponents[x];
	exponents[x] = exponents[r];
	exponents[r] = hold;
      }
}

long long power_2(const int exponent)
{
  long long answer = 1;
  int i;
  for (i=0; i < exponent; i++)
    {
      answer = answer * 2;
    }
  return answer;
}

long long string_to_number(const char *str)
{
  long long number = 0;
  for(;*str>='0' && *str<='9'; str++)
    {
      number = number*10+*str-'0';
    }
  if (*str == 'k')
    {
      number = number * 1024;
    }
  else if (*str == 'm')
    {
	  number = number * 1048576;
    }
  else if (*str == 'b')
    {
      number = number * 1073741824;
    }
  else if (*str == 't')
    {
      number = number * 1099511627776;
    }
  return number;
}
int main()
{
  std::cout << "This program quizzes you on the powers of 2. There will be 50 questions. Namely 2^0 through 2^49. You are required to answer each question correctly and will be scored by the length of time it takes you to complete the quiz, so try to answer each question as quickly as possible. If you answer a question incorrectly, 5 seconds will be added to your score. Lets Begin!" << std::endl; 
  int min = 1;
  int max = 49;
  int size = max-min+1;
  int exponents[size];
  char answer[14];
  std::srand(time(0));
  int error_time = 0;
  int errors = 0;
  time_t start;
  time_t end;
  generate_exponents(min, max, &exponents[0]);
  int i;
  bool ended = false;
  start=time(0);
  for (i=0; i <= size; i++)
    {
      if (ended == true)
	{
	  break;
	}
      bool correct = false;
      long long correct_answer = power_2(exponents[i]);
      while (!correct)
	{
	  std::cout << "What is 2^" << exponents[i] << "? ";
	  std::cin >> answer;
	  if (*answer == 'q')
	    {
	      ended = true;
	      break;
	    }
	  long long converted_answer =  string_to_number(answer);
	   if (converted_answer == correct_answer)
	     {
	       correct = true;
	       std::cout << "Correct!" << std::endl;
	     }
	   else
	     {
	       error_time = error_time +5;
	       errors++;
	       std::cout << "Nope! Guess again." << std::endl;
	     }
	}
    }
  end = time(0);
  int timer = end - start;
  int score = timer + error_time;
  std::cout << "That took " << timer << " seconds." << std::endl;
  std::cout << "You missed " << errors << " questions." << std::endl;
  std::cout << "Score:" << score << std::endl;
  return 0;
}
