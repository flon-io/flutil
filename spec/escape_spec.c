
//
// specifying flutil
//
// Sat Jun  7 09:41:22 JST 2014
//

#include "flutil.h"


context "escapes"
{
  describe "flu_escape()"
  {
    it "escapes newlines"
    {
      ensure(flu_escape("new\nline") ===f "new\\nline");
    }
    it "escapes double quotes"
    {
      ensure(flu_escape("double \" quotes") ===f "double \\\" quotes");
    }
    it "doesn't escape if not necessary"
    {
      ensure(flu_escape("fuji山") ===f "fuji山");
    }
  }

  describe "flu_unescape()"
  {
    it "unescapes back slashes"
    {
      ensure(flu_unescape("back\\\\slash") ===f "back\\slash");
    }
    it "unescapes double quotes"
    {
      ensure(flu_unescape("double\\\"quote") ===f "double\"quote");
    }
    it "unescapes tabs"
    {
      ensure(flu_unescape("a\\ttab") ===f "a\ttab");
    }
    it "unescapes \\uxxxx sequences"
    {
      ensure(flu_unescape("fuji\\u5c71") ===f "fuji山");
    }
    it "unescapes low \\uxxxx sequences"
    {
      ensure(flu_unescape("old \\u0066ool") ===f "old fool");
    }
    it "leaves unknown escapes as is"
    {
      ensure(flu_unescape("that's \\zorro") ===f "that's \\zorro");
    }
  }

  describe "flu_urlencode()"
  {
    it "encodes reserved characters"
    {
      expect(flu_urlencode("a b c", -1) ===f "a%20b%20c");
    }
  }

  describe "flu_urldecode()"
  {
    it "decodes percent encoded characters"
    {
      expect(flu_urldecode("a%20b%20c", -1) ===f "a b c");
    }
  }
}

