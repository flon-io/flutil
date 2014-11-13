
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

  context "roundtrip"
  {
    before each
    {
      char *s1 = NULL; char *s2 = NULL;
    }
    after each
    {
      free(s1); free(s2);
    }

    it "deals with UTF-8"
    {
      char *s =
        "株式会社spicelifeはRubyWorldConferenceのスポンサーになっております。";

      s1 = flu64_encode(s, -1);
      expect(s1 === ""
        "5qCq5byP5Lya56S+c3BpY2VsaWZl44GvUnVieVdvcmxkQ29uZmVyZW5jZeOBru"
        "OCueODneODs+OCteODvOOBq+OBquOBo+OBpuOBiuOCiuOBvuOBmeOAgg==");

      s2 = flu64_decode(s1, -1);

      expect(s2 === s);
    }

    it "deals with binary data (not just \\0 terminated strings)"
    {
      char s[5] = { 0, 'a', 'b', 0, 'e' };
      //printf("%0x, %0x, %0x, %0x\n", s[0], s[1], s[2], s[3]);

      s1 = calloc(5 * 2, sizeof(char));
      flu64_do_encode(s, 5, s1);
      //puts(s1);

      expect(s1 === "AGFiAGU=");

      s2 = calloc(5, sizeof(char));
      flu64_do_decode(s1, strlen(s1), s2);
      //printf("%0x, %0x, %0x, %0x\n", s2[0], s2[1], s2[2], s2[3]);

      expect(strncmp(s, s2, 5) == 0);
    }
  }
}

