
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
    it "encodes and pads (==)"
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

//  char *lev =
//    "Man is distinguished, not only by his reason, but by this singular "
//    "passion from other animals, which is a lust of the mind, that by a "
//    "perseverance of delight in the continued and indefatigable generation "
//    "of knowledge, exceeds the short vehemence of any carnal pleasure.";
//  //char *lev = "Man is";
//
//  char *out =
//    "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0"
//    "aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx1"
//    "c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0"
//    "aGUgY29udGludWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdl"
//    "LCBleGNlZWRzIHRoZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=";
//  //char *out = "TWFuIGlz";

