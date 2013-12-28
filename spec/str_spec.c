
//
// specifying flutil
//
// Sun Dec 29 08:35:42 JST 2013
//

#include "flutil.h"


context "str functions"
{
  before each
  {
    char *s = NULL;
  }
  after each
  {
    if (s != NULL) free(s);
  }

  describe "flu_strrtrim()"
  {
    it "trims on the right"
    {
      s = flu_strrtrim("brown fox \n\t");

      ensure(strcmp("brown fox", s) == 0);
    }

    it "doesn't trim when not necessary"
    {
      s = flu_strrtrim("");

      ensure(strcmp("", s) == 0);
    }
  }

  describe "flu_strtrim()"
  {
    it "trims on the left and on the right"
    {
      s = flu_strtrim("  \tbrown fox \n\t");

      ensure(strcmp("brown fox", s) == 0);
    }

    it "doesn't trim when not necessary"
    {
      s = flu_strtrim("");

      ensure(strcmp("", s) == 0);
    }
  }
}

