
//
// specifying flutil
//
// Wed Nov 12 21:24:54 JST 2014
//

#include "flu64.h"


context "flu64"
{
  describe "flu64_do_encode()"
  {
    it "encodes"
    {
      char *in = "Man is";
      char *out = calloc(strlen(in) * 2, sizeof(char));

      flu64_do_encode(in, strlen(in), out);

      expect(out ===f "TWFuIGlz");
    }

    it "encodes and pads (=)"
    {
      char *in = "Man is d";
      char *out = calloc(strlen(in) * 2, sizeof(char));

      flu64_do_encode(in, strlen(in), out);

      expect(out ===f "TWFuIGlzIGQ=");
    }

    it "encodes and pads (==)"
    {
      char *in = "Man is ";
      char *out = calloc(strlen(in) * 2, sizeof(char));

      flu64_do_encode(in, strlen(in), out);

      expect(out ===f "TWFuIGlzIA==");
    }

    it "encodes it all"
    {
      char *in =
        "Man is distinguished, not only by his reason, but by this singular "
        "passion from other animals, which is a lust of the mind, that by a "
        "perseverance of delight in the continued and indefatigable "
        "generation of knowledge, exceeds the short vehemence of any carnal "
        "pleasure.";
      char *out = calloc(strlen(in) * 2, sizeof(char));

      flu64_do_encode(in, strlen(in), out);

      expect(out ===f ""
        "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1d"
        "CBieSB0aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aG"
        "ljaCBpcyBhIGx1c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2U"
        "gb2YgZGVsaWdodCBpbiB0aGUgY29udGludWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdl"
        "bmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRoZSBzaG9ydCB2ZWhlbWVuY"
        "2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=");
    }
  }

  describe "flu64_encode()"
  {
    it "encodes"
  }

  describe "flu64_decode()"
  {
    it "decodes"
  }
}

