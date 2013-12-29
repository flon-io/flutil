
//
// specifying flutil
//
// Sun Dec 29 09:32:51 JST 2013
//

#include "flutil.h"


context "sbuffer"
{
  describe "flu_sprintf()"
  {
    it "returns a formatted string"
    {
      char *s = flu_sprintf("%d/%d/%d", 2013, 12, 19);

      ensure(strcmp("2013/12/19", s) == 0);

      free(s);
    }
  }
}

