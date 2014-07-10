
//
// specifying flutil
//
// Thu Jul 10 06:48:00 JST 2014
//

#include "flutil.h"


context "readall"
{

  describe "flu_readall(path)"
  {
    it "reads the entirety of a file in a string"
    {
      char *s = flu_readall("s.c");
      ensure(strstr(s, "flu_readall(path)") != NULL);
      free(s);
    }
  }

  //describe "flu_freadall(file)"
  //{
  //  pending "implementation"
  //}
}

