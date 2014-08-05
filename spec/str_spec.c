
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

  describe "flu_strrtrim(char *s)"
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

    it "returns a new string"
    {
      char *s0 = rdz_strdup("");
      s = flu_strrtrim(s0);

      ensure(s != s0);

      free(s0);
    }
  }

  describe "flu_strtrim(char *s)"
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

  describe "flu_strends(char *s, char *ending)"
  {
    it "returns 1 if the s ends with ending"
    {
      ensure(flu_strends("toto", "to") == 1);
    }

    it "returns 0 else"
    {
      ensure(flu_strends("toto", "thenada") == 0);
    }
  }

  describe "flu_index(char *s, char c)"
  {
    it "returns -1 if it doesn't find the char"
    {
      ensure(flu_index("nada", 'z') == -1);
    }

    it "returns the index of the first occurence of the char"
    {
      ensure(flu_index("nada", 'a') == 1);
    }
  }

  describe "flu_rindex(char *s, char c)"
  {
    it "returns -1 if it doesn't find the char"
    {
      ensure(flu_rindex("nada", 'z') == -1);
    }

    it "returns the index of the last occurence of the char"
    {
      ensure(flu_rindex("nada", 'a') == 3);
    }
  }
}

