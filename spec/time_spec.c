
//
// specifying flutil
//
// Sat Nov  1 15:48:38 JST 2014
//

#include "flutil.h"


context "time"
{
  describe "flu_gets('s')"
  {
    it "returns the count of seconds since the Epoch"
    {
      //printf("s: %lli\n", flu_gets('s'));

      ensure(flu_gets('s') > 1409000000);
    }
  }

  describe "flu_gets('m')"
  {
    it "returns the count of milliseconds (10-3) since the Epoch"
    {
      ensure(flu_gets('m') > 1409000000000);
    }
  }

  describe "flu_gets('M')"
  {
    it "returns the count of milliseconds (10-3) since the Epoch"
    {
      ensure(flu_gets('M') > 1409000000000000);
    }
  }

  describe "flu_gets('n')"
  {
    it "returns the count of microseconds (10-6) since the Epoch"
    {
      ensure(flu_gets('n') > 1409000000000000000);
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

