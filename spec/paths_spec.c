
//
// specifying flutil
//
// Thu Oct  9 15:34:56 JST 2014
//

#include "flutil.h"


context "paths"
{
  describe "flu_fstat()"
  {
    it "returns 0 if the path points to nowhere"
    {
      expect(flu_fstat("../nada") == 0);
    }
    it "returns 'd' if the path points to a directory"
    {
      expect(flu_fstat("../src") == 'd');
    }
    it "returns 'f' if the path points to a non-directory"
    {
      expect(flu_fstat("../src/flutil.c") == 'f');
    }
  }

  describe "flu_basename()"
  {
    it "returns the basename given a path"
    {
      expect(flu_basename("/x/y/z.txt", NULL) ===f "z.txt");
    }

    it "accepts a .suffix for the returned basename"
    {
      expect(flu_basename("/x/y/z.json", ".txt") ===f "z.txt");
    }
  }

  describe "flu_move()"
  {
    before each
    {
      flu_writeall("a.txt", "alright");
      mkdir("_test0", 0755);
      mkdir("_test0/d0", 0755);
      flu_writeall("_test0/d0/b.txt", "blighty");
      mkdir("_test1", 0755);
    }
    after each
    {
      unlink("a.txt");
      system("rm -fR _test0");
      system("rm -fR _test1");
    }

    it "moves a file to a dir"
    {
      int r = flu_move("./a.txt", "_test0");

      expect(r == 0);

      expect(flu_readall("_test0/a.txt") ===f "alright");
    }

    it "moves a file to a dir/"
    {
      int r = flu_move("./a.txt", "_test0/");

      expect(r == 0);

      expect(flu_readall("_test0/a.txt") ===f "alright");
    }

    it "renames a file"
    {
      int r = flu_move("a.txt", "b.txt");

      expect(r == 0);

      expect(flu_readall("./b.txt") ===f "alright");
      expect(unlink("./b.txt") == 0);
    }

    it "moves a dir to another dir"
    {
      int r = flu_move("_test0/d0", "_test1");

      expect(r == 0);

      expect(flu_readall("_test1/d0/b.txt") ===f "blighty");
    }

    it "moves a dir to another dir with another filename"
    {
      int r = flu_move("_test0/d0", "_test1/d1");

      expect(r == 0);

      expect(flu_readall("_test1/d1/b.txt") ===f "blighty");
    }

    it "returns 1 if the source file doesn't exist"
    {
      int r = flu_move("_test9", "_test8");

      expect(r == 1);
    }
  }
}

