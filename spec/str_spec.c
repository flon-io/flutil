
//
// specifying flutil
//
// Sun Dec 29 08:35:42 JST 2013
//

#include "flutil.h"


describe "flu_strrtrim()"
{
  before each
  {
    char *s = NULL;
  }
  after each
  {
    if (s != NULL) free(s);
  }

  it "trims on the right"
  {
    s = flu_strrtrim("brown fox \n\t");

    ensure(strcmp("brown fox", s) == 0);
  }
}

