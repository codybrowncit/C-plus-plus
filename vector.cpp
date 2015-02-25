#include <iostream>
#include <vector>

int main(){

  std::vector<int> nums;
  int x;
  bool done = false;
    std::cout << "This Program Averages A List Of Numbers. "<< std::endl;
  while (!done){
      std::cout << "Enter a Number or Enter 0 to Return Results. ";
    std::cin >> x;
    if (x == 0){
      done = true;
    }
    else{
      nums.push_back(x);
    }
  }
  int total = 0;
  unsigned int i;
  for (i = 0; i < nums.size(); i++){
    total += nums[i];
  }
  std::cout << "Average: " << (total/nums.size()) << std::endl;
  std::cout << 5/2 << std::endl;
  return 0;
}
