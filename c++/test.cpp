#include <iostream>


int main()
{
  char text[32] = "Call me Ishmael.";

  /* How many characters in the array? */
  /* How many characters in the c-string? */
  /* What is the smallest legal size for the text array? */

  int l = strlen(text);
  std::cout << l << " countable characters in '" << text << "'." << std::endl;

  char text_copy[32];
  strcpy(text_copy, text);
  std::cout << "Copy: " << text_copy << std::endl;

  char big_string[32];
  strcpy(big_string, "Big");
  strcat(big_string, "White");
  strcat(big_string, "Whale");
  std::cout << big_string << std::endl;

  char a[16] = "hello";
  char b[16] = "hello world";
  char c[16] = "goodb";
  char d[20] = "hello";

  std::cout << "strcmp(\""<<a<< "\",\""<<b<<"\") = " << strcmp(a, b) << std::endl;
  std::cout << "strcmp(\""<<a<< "\",\""<<c<<"\") = " << strcmp(a, c) << std::endl;
  std::cout << "strcmp(\""<<a<< "\",\""<<d<<"\") = " << strcmp(a, d) << std::endl;
  
  return 0;
}
