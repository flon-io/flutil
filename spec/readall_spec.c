
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

      ensure(s != NULL);
      ensure(strstr(s, "flu_readall(path)") != NULL);
      free(s);
    }

    it "reads from a sprintf'ed path"
    {
      char *s = flu_readall("./%s", "s.c");

      ensure(s != NULL);
      ensure(strstr(s, "sprintf'ed") != NULL);
      free(s);
    }
  }
}

context "writeall"
{
  describe "flu_writeall(path, ...)"
  {
    it "writes a file"
    {
      int r = flu_writeall(
        "./test%i.txt", 0,
        "hello %s\n", "world");

      expect(r == 1);
      expect(flu_readall("./test0.txt") ===f "hello world\n");

      expect(unlink("./test0.txt") == 0);
    }
  }
}

context "unlink"
{
  describe "flu_unlink(path, ...)"
  {
    it "returns 0 in case of success (like unlink)"
    {
      flu_writeall("./test_unlink.txt", "unlink me!");

      int r = flu_unlink("./test_unlink.txt");

      expect(r == 0);
      expect(flu_readall("./test_unlink.txt") == NULL);
    }

    it "composes its path"
    {
      flu_writeall("./test_unlink_1.txt", "unlink me!!");

      int r = flu_unlink("./test_unlink_%i.txt", 1);

      expect(r == 0);
      expect(flu_readall("./test_unlink.txt") == NULL);
    }
  }
}

