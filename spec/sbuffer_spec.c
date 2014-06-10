
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

      ensure(s ===f "2013/12/19");
    }
  }

  describe "flu_sbputc()"
  {
    it "prints a char to a flu_sbuffer"
    {
      flu_sbuffer *b = flu_sbuffer_malloc();

      int c = flu_sbputc(b, 'a');

      char *s = flu_sbuffer_to_string(b);

      ensure(s ===f "a");
      ensure(((char)c) == 'a');
    }
  }
}

