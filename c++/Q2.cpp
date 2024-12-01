/*
Q2: Write a c++ script that performs the following task:

Write a program that prompts the user to input two integers and outputs the largest.
*/
void Q2(){

  int number1, number2;
    std::cout<< "Enter the number1 integer: ";
  std::cin>> number1;
   std::cout<< "Enter the number2 integer: ";
  std::cin>> number2;
  if (number1 > number2){
    std::cout<<number1<<" is the largest"<<endl;
    }

  else{
      std::cout<<number2<<" is the largest"<<endl;
}
}
