
//
// specifying flutil
//
// Sun Aug 31 14:38:14 JST 2014
//

#include "flutil.h"


context "misc"
{
  describe "flu_getms()"
  {
    it "returns the count of milliseconds (10-3) since the Epoch"
    {
      //printf("ms: %li\n", flu_getms());

      ensure(flu_getms() > 1409000000000);
    }
  }

  describe "flu_getMs()"
  {
    it "returns the count of microseconds (10-6) since the Epoch"
    {
      //printf("Ms: %li\n", flu_getMs());

      ensure(flu_getMs() > 1409000000000000);
    }
  }
}

