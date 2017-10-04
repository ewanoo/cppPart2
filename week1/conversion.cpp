#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[])
{/*
  * using moves these to this namespace
  */
  using std::cin;
  using std::cerr;
  using std::cout;
  using std::endl;

  double fac{ 2.54 }; // or use auto conversion factor
  // prompt user
  cout << "Input number followed by i for inch input, c for centimetres input\n";
  cout << "Enter length: ";

  char conv{'i'}; //set the conv char to have value 'i' we will overwrite it later
  double x;
  char inp[32];//char array

  cin.get(inp,32,'\n'); // read off array, terminated by newline

  if(cin) {//checks that something has been read to guard against an error
    int count=cin.gcount();
    cerr << "READ: " << count << " CHARS: " << inp << "\n";//noddy print out what we got
    for(int i=0; i < count ; i++ ) {
      if(isalpha(inp[i])) {// found alpha char
	if(inp[i] == 'c' || inp[i] == 'C')
	  conv = 'c';
	else if(inp[i] == 'i' || inp[i] == 'I')
	  conv = 'i';
	else
	  return(EXIT_FAILURE); //return -1;
	
	// terminate string
	inp[i]='\0';
	x = atof(inp); // convert string to double
	      
      }else{ // ignore
	; 
      }
          
    }// for loop
  }else{ // error on cin
    cerr << "Error reading input\n";
    return(EXIT_FAILURE);
  }

  //by now we've got x which is a double value and we know if we've got inches or centimetres
  // do calculations
  double in{ 0.0 }, cm{ 0.0 }; // closest to point of use
  switch (conv) { // try for upper case, try with an if
  case('i') :  // inch, convert to centimetres
    in = x;
    cm = x * fac;
    cout << in << " inches = " << cm << " centimetres\n";
    break;
  case('c') :  // centimetres, convert to inch
    in = x / fac;
    cm = x;
    cout << cm << " centimetres = " << in << " inches\n";
    break;
  }
  return(EXIT_SUCCESS);
}
