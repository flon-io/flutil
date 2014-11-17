
//
// specifying flutil
//
// Sun Aug 31 14:38:14 JST 2014
//

#include "flutil.h"


context "misc"
{
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

  describe "flu_path()"
  {
    it "composes a path"
    {
      expect(flu_path("a/%s", "x") ===f "a/x");
      expect(flu_path("./%s", "/x") ===f "x");
      expect(flu_path("/%s", "/x") ===f "/x");
    }
  }

  describe "flu_system()"
  {
    it "behaves like system + printf"
    {
      expect(flu_system("%s > /dev/null", "pwd") == 0);
    }
  }

  describe "flu_stoll()"
  {
    it "extracts strings"
    {
      expect(flu_stoll("a123b", 3, 10) lli== 0);
      expect(flu_stoll("a123b" + 1, 3, 10) lli== 123);
      expect(flu_stoll("123" + 1, 100, 10) lli== 23);
      expect(flu_stoll("123" + 5, 100, 10) lli== 0);
    }
  }

  describe "flu_putf()"
  {
    it "puts and then frees its argument"
    {
      char *s = strdup("");
      flu_putf(s);
    }
  }
}

