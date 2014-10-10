
//
// specifying flutil
//
// Thu Oct  9 15:34:56 JST 2014
//

#include <sys/stat.h>
#include <sys/types.h>

#include "flutil.h"


context "path functions"
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

    it "composes paths"
    {
      expect(flu_fstat("../%s/flutil.c", "src") == 'f');
    }
  }

  describe "flu_dirname()"
  {
    it "returns the dirname of a path"
    {
      expect(flu_dirname("/x/y/z.txt") ===f "/x/y");
    }

    it "returns the dirname of a path (2)"
    {
      expect(flu_dirname("z.txt") ===f ".");
    }

    it "composes paths"
    {
      expect(flu_dirname("/x/%s/z.txt", "y") ===f "/x/y");
    }
  }

  describe "flu_basename()"
  {
    it "returns the basename of a path"
    {
      expect(flu_basename("/x/y/z.txt", NULL) ===f "z.txt");
    }

    it "accepts a .suffix for the returned basename"
    {
      expect(flu_basename("/x/y/z.json", ".txt") ===f "z.txt");
    }

    it "composes its path"
    {
      expect(flu_basename("/x/y/%s.txt", "z", NULL) ===f "z.txt");
      expect(flu_basename("/x/y/%s.json", "z", ".txt") ===f "z.txt");
    }

    it "returns NULL if there is a new suffix and it doesn't begin with '.'"
    {
      expect(flu_basename("/x/y/z.json", "txt") == NULL);
      expect(flu_basename("/x/y/%s.json", "z", "txt") == NULL);
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

    it "composes its paths"
    {
      int r = flu_move("_test0/d%i", 0, "_test1/d%i", 1);

      expect(r == 0);

      expect(flu_readall("_test1/d1/b.txt") ===f "blighty");
    }
  }
}

