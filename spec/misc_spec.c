
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

  describe "flu_system()"
  {
    it "behaves like system + printf"
    {
      expect(flu_system("%s > /dev/null", "pwd") == 0);
    }
  }
}

