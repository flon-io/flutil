
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

    it "encodes UTF-8 over chars"
  }

  describe "flu64_encode()"
  {
    it "encodes"
    {
      char *in =
        "Man is distinguished, not only by his reason, but by this singular "
        "passion from other animals, which is a lust of the mind, that by a "
        "perseverance of delight in the continued and indefatigable "
        "generation of knowledge, exceeds the short vehemence of any carnal "
        "pleasure.";

      expect(flu64_encode(in, -1) ===f ""
        "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1d"
        "CBieSB0aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aG"
        "ljaCBpcyBhIGx1c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2U"
        "gb2YgZGVsaWdodCBpbiB0aGUgY29udGludWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdl"
        "bmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRoZSBzaG9ydCB2ZWhlbWVuY"
        "2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=");
    }
  }

  describe "flu64_do_decode()"
  {
    it "decodes"
    {
      char *in = "TWFuIGlz";
      char *out = calloc(strlen(in), sizeof(char));

      flu64_do_decode(in, strlen(in), out);

      expect(out ===f "Man is");
    }

    it "decodes when padding (=)"
    {
      char *in = "TWFuIGlzIGQ=";
      char *out = calloc(strlen(in), sizeof(char));

      flu64_do_decode(in, strlen(in), out);

      expect(out ===f "Man is d");
    }

    it "decodes when padding (==)"
    {
      char *in = "TWFuIGlzIA==";
      char *out = calloc(strlen(in), sizeof(char));

      flu64_do_decode(in, strlen(in), out);

      expect(out ===f "Man is ");
    }
  }

  describe "flu64_decode()"
  {
    it "decodes"
    {
      char *in =
        "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1d"
        "CBieSB0aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aG"
        "ljaCBpcyBhIGx1c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2U"
        "gb2YgZGVsaWdodCBpbiB0aGUgY29udGludWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdl"
        "bmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRoZSBzaG9ydCB2ZWhlbWVuY"
        "2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=";

      expect(flu64_decode(in, -1) ===f ""
        "Man is distinguished, not only by his reason, but by this singular "
        "passion from other animals, which is a lust of the mind, that by a "
        "perseverance of delight in the continued and indefatigable "
        "generation of knowledge, exceeds the short vehemence of any carnal "
        "pleasure.");
    }
  }
}

