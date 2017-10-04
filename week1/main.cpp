/*
** January 2017
** week: 1 
** file: main.cpp ( demonstrates features developed during the course )
** use with: main.h
**
** linux compile with: 
** g++ -Wnarrowing -std=c++11 main.cpp -o main
** 
** win32 compile with: cl main.cpp
** 
** demonstrates: Programming Constructions:-
**               Sequencing, Selection (if), Iterations (while/for) 
** demonstrates: Pre-processing directives
** demonstrates: Arrays
** demonstrates: Classes - (constructors,destructors) 
** demonstrates: Overloaded functions, friends
** demonstrates: Template classes, 
** demonstrates: STL vectors,strings
** demonstrates: STL Iterators
** demonstrates: Exceptions - classes; throwing and catching
** demonstrates: Functions, function parameters, references
** demonstrates: Function pointers
** demonstrates: Enumeration type definitions
** demonstrates: Typedefs
** demonstrates: Dynamic memory allocation/deletion (using new and delete)
*/
#include "main.h"
/*
would like to know what argc and argv are all about
*/
int main(int argc, char* argv[])
{
  /* *************************************************
  ** define base data types: vector of class templates
  ** *************************************************/
  vector<Association<string,int>*> daysInMonth;// vector of pointers -EM - to string int associations
  // this is on the Heap since we are not in a function
  vector<Association<string,string> > mimeDictionary(10);// fixed vector

  /* *****************************************************************
  ** populate class template vectors using two different function call
  ** methods - standard call, and pointer to function call.......
  ** ****************************************************************/
  PTR_FUNC fillDictionary = &addMimeTypes ; // assign function pointer

  (*fillDictionary)(mimeDictionary); // declare mimeDictionary
  // populate mime dictionary invoking function via function pointer
  // EM -the relevant addmonths is defined below from the prototype in the header
  addMonths( daysInMonth ); // populate months using normal function
  
  
  /* ************************************************************
  ** using iterator to identify all element with VALUE of 30 days
  ** ************************************************************/
  cerr << "Using Days In Month dictionary, identify months with 30 days" << endl;
  vector<Association<string, int> *>::iterator iter2 = daysInMonth.begin();
  while( iter2 != daysInMonth.end() ) { 
    Association<string,int> *p = *iter2; // extract element from vector
    //note that the pointer p is different to the iterator
    // importantly can use the -> with a pointer which this iterator can't (some can)
    // in other ways *iter2 looks like a pointer
    if( p->value() == 30 ) {
      cerr << "Found month with thirty days\n";
      cerr << *p; // print, using output operator
    }
    iter2++;
  }
  // EM - defined below
  cleanup(daysInMonth); // cleanup heap memory

  /* *******************************************************************
  ** using function 'atKey' identify value elements with specified keys
  ** *******************************************************************/
  cerr << "\n\nUsing Mime Types dictionary, identify any with specified key" << endl;
  cerr << "Identify any mime value with key taken as default parameter" << endl;
  try{
    int idx = atKey(mimeDictionary); // use default parameter
    cerr << "FOUND KEY: " << mimeDictionary[idx].key() << " AT VALUE: " << mimeDictionary[idx].value() << endl;
  }catch (const NotFoundException& E) { // if not found
    cerr << "NOT FOUND EXCEPTION CAUGHT\n";
    cerr << "Exception Data: " << E.data() << endl;
  }

  try{
    string not_found_key="abc"; // this is not in the mime-dictionary types
    int idx = atKey(mimeDictionary, not_found_key) ;
    cerr << "FOUND KEY: " <<  mimeDictionary[idx].key()  <<  " AT VALUE: " << mimeDictionary[idx].value() << endl;
  }catch(const NotFoundException& E) {
    cerr << "NOT FOUND EXCEPTION CAUGHT\n";
    cerr << "Exception Data: " << E.data() << endl; // now do something sensible - like adding key/value pair
  }

  // if running within IDE
  // char c = cin.get(); 
}

/*
** fill a vector with 10 elements 
*/
void addMimeTypes(vector<Association<string,string> >& dict)
{
  dict[0].key("doc")  ; dict[0].value("application/msword");
  dict[1].key("dot")  ; dict[1].value("application/msword");
  dict[2].key("bmp")  ; dict[2].value("image/bmp");
  dict[3].key("c")    ; dict[3].value("text/plain");
  dict[4].key("html") ; dict[4].value("text/html");
  dict[5].key("jpeg") ; dict[5].value("image/jpeg");
  dict[6].key("mov")  ; dict[6].value("video/quicktime");
  dict[7].key("pdf")  ; dict[7].value("application/pdf");
  dict[8].key("txt")  ; dict[8].value("text/plain");
  dict[9].key("xls")  ; dict[9].value("application/vnd.ms-excel");
}

/*
** fill dynamic vector using heap memory
*/
void addMonths(vector<Association <string, int> *>& months)
{
  // use enum type, with array for days in month data
  enum mon { jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec };
  int days[13] = { -1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
  months.push_back(new Association <string, int>("January", days[jan]));
  months.push_back(new Association <string, int>("February",days[feb]));
  months.push_back(new Association <string, int>("March",days[mar]));
  months.push_back(new Association <string, int>("April",days[apr]));
  months.push_back(new Association <string, int>("May",days[may]));
  months.push_back(new Association <string, int>("June",days[jun]));
  months.push_back(new Association <string, int>("July",days[jul]));
  months.push_back(new Association <string, int>("August",days[aug]));
  months.push_back(new Association <string, int>("September", days[sep]));
  months.push_back(new Association <string, int>("October",days[oct]));
  months.push_back(new Association <string, int>("November", days[nov]));
  months.push_back(new Association <string, int>("December", days[dec]));
}

// delete dynamic memory allocated in 'addMonths'
void cleanup(vector<Association <string, int> *>& months) 
{
  // cleanup heap
  for(unsigned int i = 0 ; i < months.size() ; ++i) {
    delete months[i];
  }
  months.clear();
}

/*
** using vector iterator search in dictionary for key, return
** index for found value,
** otherwise throw Exception
*/
int atKey(vector<Association<string,string> >& dict, string k)
{
  // create vector iterator
  vector<Association<string,string> >::const_iterator iter1 = dict.begin();
  int idx=0; // indexer
  while( iter1 != dict.end() ) {
    string the_key = (*iter1).key();
    if( the_key == k ) {
      return idx; //return index into vector for found key
    }
    idx++; // increase index
    iter1++; // next element
  }
  // if arrives here then key has not been found, return exception
  throw( NotFoundException(k) );
}








