
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

  describe "flu_rtrim()"
  {
    it "returns NULL when passed NULL"
    {
      expect(flu_rtrim(NULL) == NULL);
    }

    it "is OK with empty strings"
    {
      s = strdup("");
      char *s1 = flu_rtrim(s);

      expect(s1 === "");
    }

    it "trims a string in place"
    {
      s = strdup("abc ");
      char *s1 = flu_rtrim(s);

      expect(s == s1);
      expect(strlen(s1) zu== 3);
    }
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

  describe "flu_index(char *s, size_t off, char c)"
  {
    it "returns -1 if it doesn't find the char"
    {
      ensure(flu_index("nada", 0, 'z') == -1);
    }

    it "returns the index of the first occurence of the char"
    {
      ensure(flu_index("nada", 0, 'a') == 1);
    }

    it "returns the index of the 1st occurence of the char, starting at off"
    {
      ensure(flu_index("nada", 2, 'a') == 3);
    }
  }

  describe "flu_rindex(char *s, ssize_t off, char c)"
  {
    it "returns -1 if it doesn't find the char"
    {
      ensure(flu_rindex("nada", -1, 'z') == -1);
    }

    it "returns the index of the last occurence of the char"
    {
      ensure(flu_rindex("nada", -1, 'a') == 3);
    }

    it "returns the index of the last occurence of the char, starting at off"
    {
      ensure(flu_rindex("nada", 2, 'a') == 1);
    }
  }

  describe "flu_split()"
  {
    before each
    {
      flu_list *l = NULL;
    }
    after each
    {
      if (l) flu_list_free_all(l);
    }

    it "splits a string"
    {
      l = flu_split("a,b,c", ",");

      expect(l != NULL);
      expect(l->size zu== 3);
      expect(l->first->item === "a");
      expect(l->first->next->item === "b");
      expect(l->last->item === "c");
    }

    it "splits a one item list"
    {
      l = flu_split("abc", ".");

      expect(l != NULL);
      expect(l->size zu== 1);
      expect(l->first->item === "abc");
    }

    it "splits an empty list"
    {
      l = flu_split("", ".");

      expect(l != NULL);
      expect(l->size zu== 1);
      expect(l->first->item === "");
    }

    it "splits with longer delimiters"
    {
      l = flu_split("a/,/b/,/b/,/c", "/,/");

      expect(l != NULL);
      expect(l->size zu== 4);
      expect(l->first->item === "a");
      expect(l->first->next->item === "b");
      expect(l->first->next->next->item === "b");
      expect(l->last->item === "c");
    }
  }
}

