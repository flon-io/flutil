
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

    it "removes a final /"
    {
      expect(flu_dirname("/x/") ===f "/x");
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

  describe "flu_mkdir_p()"
  {
    after each
    {
      system("rm -fR __mkdir_test_dir");
    }

    it "creates a single dir"
    {
      int r = flu_mkdir_p("__mkdir_test_dir", 0755);

      expect(r == 0);

      expect(flu_fstat("__mkdir_test_dir") == 'd');
    }

    it "creates a tree of dirs"
    {
      int r = flu_mkdir_p("__mkdir_test_dir/a/b/c", 0755);

      expect(r == 0);

      expect(flu_fstat("__mkdir_test_dir") == 'd');
      expect(flu_fstat("__mkdir_test_dir/a") == 'd');
      expect(flu_fstat("__mkdir_test_dir/a/b") == 'd');
      expect(flu_fstat("__mkdir_test_dir/a/b/c") == 'd');
    }

    it "returns 0 (success) if the path already exists"
    {
      int r = flu_mkdir_p("__mkdir_test_dir/a/b/c", 0755);
      expect(r == 0);

      r = flu_mkdir_p("__mkdir_test_dir/a/b/c", 0755);
      expect(r == 0);
    }

    it "composes its path"
    {
      int r = flu_mkdir_p("__mkdir_test_dir/%s/b/c", "a", 0755);

      expect(r == 0);

      expect(flu_fstat("__mkdir_test_dir") == 'd');
      expect(flu_fstat("__mkdir_test_dir/a") == 'd');
      expect(flu_fstat("__mkdir_test_dir/a/b") == 'd');
      expect(flu_fstat("__mkdir_test_dir/a/b/c") == 'd');
    }
  }

  describe "flu_rm_files()"
  {
    before each
    {
      system("mkdir __rm_files_test_dir");
      system("touch __rm_files_test_dir/a.json");
      system("touch __rm_files_test_dir/b.json");
      system("touch __rm_files_test_dir/.nada");
      system("touch __rm_files_test_dir/c.txt");
    }
    after each
    {
      system("rm -fR __rm_files_test_dir");
    }

    it "unlinks the files with the given suffix"
    {
      expect(flu_pline("ls __rm_files_test_dir | wc -w") ===f "3");

      ssize_t r = flu_rm_files("__rm_files_test_%s/*.json", "dir");

      expect(r lli== 2);
      expect(flu_pline("ls __rm_files_test_dir | wc -w") ===f "1");
    }
  }

  describe "flu_empty_dir()"
  {
    before each
    {
      system("mkdir -p __empty_test_dir/x/y/z");
      system("touch __empty_test_dir/x/y/z/a.json");
      system("touch __empty_test_dir/x/y/z/b.json");
      system("touch __empty_test_dir/x/y/z/c.txt");
      system("touch __empty_test_dir/x/a.json");
      system("touch __empty_test_dir/x/b.json");
    }
    after each
    {
      system("rm -fR __empty_test_dir");
    }

    it "empties a dir"
    {
      //flu_system("ls -R __empty_test_dir | grep \"^[^_]\"");

      expect(
        flu_pline("ls -R __empty_test_dir | grep \"^[^_]\" | wc -l") ===f "8");

      int r = flu_empty_dir("__empty_test_%s", "dir");

      //flu_system("ls -R __empty_test_dir | grep \"^[^_]\"");
      expect(r i== 0);

      expect(
        flu_pline("ls -R __empty_test_dir | grep \"^[^_]\" | wc -l") ===f "0");
    }
  }

  describe "flu_prune_empty_dirs()"
  {
    before each
    {
      system("mkdir -p __empty_test_dir/a/x");
      system("mkdir -p __empty_test_dir/a/y");
      system("mkdir -p __empty_test_dir/b/z");
      system("touch __empty_test_dir/a/x/a.json");
    }
    after each
    {
      system("rm -fR __empty_test_dir");
    }

    it "recursively prunes empty dirs"
    {
      //flu_system("tree __empty_test_dir/");
      expect(flu_pline("tree __empty_test_dir/ | wc -l") ===f "9");

      flu_prune_empty_dirs("__%s_test_dir", "empty");

      //flu_system("tree __empty_test_dir/");
      expect(flu_pline("tree __empty_test_dir/ | wc -l") ===f "6");
    }
  }
}

