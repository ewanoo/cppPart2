#include <iostream>
#include <string>
#include <vector>
/*
** January 2017
** week: 1 
** file: main.h ( demonstrates features developed during the course )
** use with: main.cpp
** 
** TYPES : Association Class
** =========================
** Association is storage data structure providing a mapping between a 'key' and 'value' pair.
** For example, where the first element is the lookup (key) and the second the answer (value)
** in an Opposites dictionary:  key:-> 'hot'  value:-> 'cold'. key:-> 'push' value:-> 'pull'.
** or in Partners dictionary: 'Tony' -> 'Cherie', 'Bill' -> 'Hillary', Donald -> ....
** or DaysInMonth dictionary 'February' -> 28
**
** Access is via the 'key' which returns the associated 'value'
** So on accces using key='Tony' the association structure returns value='Cherie'
** or key=February returns 28
**
*/

using std::cin;
using std::cerr;
using std::endl;
using std::istream;
using std::ostream;
using std::string;
using std::vector;

// #define DEBUG
// conflicts with MACOSX


/* Association class uses C++ Template class for key (as a generical type)
** e.g Integer or String, and Standard Template Library (STL) string as value
* EM - template for a class which associates two types
*/
template <typename K, typename V> class Association { // template class Association using K as key and V as value
 private:
  /*
  ** member data items
  * EM - standard is to give the private values names like this:  _name
  */
  K _key ;
  V _value ;
 public:
  /*
  ** build Association, with default constructor
  * EM - I think the ifdef DEBUG looks to see if we are in DEBUG mode
  */
  Association() { 
#ifdef DEBUG
    cerr << "Association::Association(DEFAULT)" << endl;
#endif
  }
  /*
  ** build Association, by providing both key and value
  */
 Association(K k, V v) : _key(k), _value(v) { // initialisation list, directly assign
#ifdef DEBUG
    cerr << "Association::Association(" << k << "," << v << ")" << endl;
#endif
  }
  /*
  ** class destructor
  */
  ~Association() {
#ifdef DEBUG
    cerr << "Association::~Association()" << endl;
#endif
  }

  /*
  ** overload operator for output
  * EM this class overloads << to enable an output that makes sense
  */
  friend ostream& operator<<(ostream& s,Association& a) {
    return s << "Association( K-> " << a.key() << ", V-> " << a.value() << ")" << endl;
  }
  /*
  ** access functions - to set
  * EM - these functions set the private variables
  * EM - K and V are the types (defined by the typenames used?)
  */
  void key(K key) { // set key 
    _key = key ; 
  }
  void value(V s) { // set value
    _value = s ; 
  }
  /*
  ** access functions - to get...(using constant functions)
  */
  V value() const { // get value
    return _value ; 
  }
  K key() const { 
    return _key ; // get key
  }
};


/*
** NotFoundException Class
** =======================
** A class used to flag a problem when a key is not in the dictionary
*/
class NotFoundException {
 public:
  NotFoundException(string t) { // constructor
    _data = t;
  }
  ~NotFoundException() {  } // empty destructor
  string data() const { return _data ; }
 private:
  string _data; 
};


/* make a new type, pointer to function, with no (void) return
** using Association<string> vector& parameter
*/
typedef void (*PTR_FUNC) (vector<Association<string,string> >&); // specialisation for k,v == string


/* *******************
** Function Prototypes
** *******************/

/* fill vector of Association<int> pointers using dynamic memory */
void addMonths(vector<Association <string, int> *>& );

/* cleanup dynamic vector data */
void cleanup(vector<Association <string, int> *>& );

/* fill vector of Association<string,string> */
void addMimeTypes(vector<Association<string,string> >& );

/* find value, given key using Association Dictionary provide */
int atKey(vector<Association<string,string> >&, string k="doc") ;
