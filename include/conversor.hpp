//

#ifndef MUM_CONVERSOR_H_
#define MUM_CONVERSOR_H_

#include "MuMaterial.hpp"

#include <iostream>
#include <vector>

using namespace std;

class Conversor
{
  public:
  	Conversor();
	int chromatic2diatonic(int pitch);
  	int diatonic2chromatic(int pitch);
  
  private:

};

#endif  // MUM_CONVERSOR_H_