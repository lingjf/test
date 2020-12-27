#include "h2_macro.hpp"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "assert.h"


bool test_cat()
{
#define CAT1 1
#define CAT13 -13
   int m12 = _H2PP_CAT2(1, 2);
   if (m12 != 12) return false;

   int m13 = _H2PP_CAT2(CAT1, 3);
   if (m13 != -13) return false;

   int n12 = H2PP_CAT2(1, 2);
   if (n12 != 12) return false;

   int n13 = H2PP_CAT2(CAT1, 3);
   if (n13 != 13) return false;

    return true;
#undef CAT1
#undef CAT13
}

int main()
{
    assert(test_cat());
    return 0;
}