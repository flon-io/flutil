
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

  describe "flu_sbputs_n()"
  {
    it "prints part of a string to a flu_sbuffer"
    {
      flu_sbuffer *b = flu_sbuffer_malloc();

      flu_sbputs_n(b, "hello", 4);
      flu_sbputs_n(b, "  ", 1);
      flu_sbputs_n(b, "freeze ", 99);
      flu_sbputs_n(b, "will\0iam", 7);

      char *s = flu_sbuffer_to_string(b);

      ensure(s ===f "hell freeze will");
    }
  }

  describe "flu_sbwrite()"
  {
    it "writes part of a string to a flu_sbuffer"
    {
      flu_sbuffer *b = flu_sbuffer_malloc();

      size_t s0 = flu_sbwrite(b, "freeze ", 7);
      size_t s1 = flu_sbwrite(b, "will\0iam", 8);

      ensure(s0 == 7);
      ensure(s1 == 8);

      char *s = flu_sbuffer_to_string(b);

      ensure(s === "freeze will");
      ensure(s[11] == '\0');
      ensure(s + 12 === "iam");
      free(s);
    }
  }

  describe "flu_sbuffer_free()"
  {
    it "frees an open buffer"
    {
      flu_sbuffer *b = flu_sbuffer_malloc();

      flu_sbuffer_free(b);

      ensure(1 == 1); // Valgrind should tell
    }

    it "frees a read buffer"
    {
      flu_sbuffer *b = flu_sbuffer_malloc();
      char *s = flu_sbuffer_to_string(b);

      flu_sbuffer_free(b);

      ensure(s ===f "");
      //ensure(s === "");
    }

    it "frees a closed buffer"
    {
      flu_sbuffer *b = flu_sbuffer_malloc();
      flu_sbuffer_close(b);

      flu_sbuffer_free(b);

      ensure(1 == 1); // Valgrind should tell
    }
  }
}

