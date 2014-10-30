
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

  describe "flu_msleep()"
  {
    it "sleeps for some milliseconds"
    {
      long long start = flu_getms();

      long long r = flu_msleep(7);

      expect(flu_getms() > start + 6);
      expect(r > 6);
      expect(r < 10);
    }
  }

  describe "flu_canopath()"
  {
    it "canonicalizes /x"
    {
      expect(flu_canopath("/x") ===f "/x");
    }
    it "canonicalizes ./x"
    {
      expect(flu_canopath("./x") $==f "/tmp/x");
    }
    it "canonicalizes ../x"
    {
      expect(flu_canopath("../x") $==f "/flutil/x");
    }
    it "canonicalizes .."
    {
      expect(flu_canopath("..") $==f "/flutil/");
    }
    it "canonicalizes /.."
    {
      expect(flu_canopath("/..") ===f "/");
    }
    it "canonicalizes .//x"
    {
      expect(flu_canopath(".//x") $==f "/tmp/x");
    }
    it "canonicalizes ."
    {
      expect(flu_canopath(".") $==f "/tmp/");
    }

    it "composes its original path"
    {
      expect(flu_canopath("/x/%s", "y") ===f "/x/y");
    }
  }

  describe "flu_system()"
  {
    it "behaves like system + printf"
    {
      expect(flu_system("%s > /dev/null", "pwd") == 0);
    }
  }
}

