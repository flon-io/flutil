
//
// specifying flutil
//
// Sat Nov  1 15:48:38 JST 2014
//

#include "flutil.h"


context "time"
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

  describe "flu_msleep()"
  {
    it "sleeps for some milliseconds"
    {
      long long r = flu_msleep(7);

      expect(r lli== 0); // vanilla
    }
  }

  describe "flu_do_msleep()"
  {
    it "sleeps for some milliseconds"
    {
      long long r = flu_do_msleep(7);

      expect(r > 6);
    }
  }
}

