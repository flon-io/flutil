
//
// specifying flutil
//
// Sat Nov  1 15:48:38 JST 2014
//

#include <time.h>
#include <errno.h>

#include "flutil.h"
#include "flutim.h"


context "time"
{
  describe "flu_now()"
  {
    it "returns the timespec for now"
    {
      struct timespec *ts = flu_now();

      expect(ts->tv_sec > 1409000000);

      free(ts);
    }
  }

  describe "flu_gets()"
  {
    describe "flu_gets('s')"
    {
      it "returns the count of seconds since the Epoch"
      {
        //printf("s: %lli\n", flu_gets('s'));

        ensure(flu_gets('s') > 1409000000);
      }
    }

    describe "flu_gets('m')"
    {
      it "returns the count of milliseconds (10-3) since the Epoch"
      {
        ensure(flu_gets('m') > 1409000000000);
      }
    }

    describe "flu_gets('u')"
    {
      it "returns the count of microseconds (10-3) since the Epoch"
      {
        ensure(flu_gets('u') > 1409000000000000);
      }
    }

    describe "flu_gets('n')"
    {
      it "returns the count of nanoseconds (10-6) since the Epoch"
      {
        ensure(flu_gets('n') > 1409000000000000000);
      }
    }
  }

  describe "flu_msleep()"
  {
    it "sleeps for some milliseconds"
    {
      long long r = flu_msleep(7);

      expect(r lli== 0); // vanilla
    }
  }

  describe "flu_do_msleep()"
  {
    it "sleeps for some milliseconds"
    {
      long long r = flu_do_msleep(7);

      expect(r > 6);
    }
  }

  //describe "flu_ts_to_tm()"
  //{
  //  it "turns ts into a local tm when utc=0"
  //  {
  //    struct timespec ts;
  //    ts.tv_sec = 1414791000;
  //    ts.tv_nsec = 0;
  //      //
  //      // 2014/11/01 06:30:00
  //    struct tm *t = flu_ts_to_tm(&ts, 0);
  //    char st[64];
  //    strftime(st, 64, "%Y%m%d.%H%M%S.", t);
  //    puts(st);
  //  }

  //  it "turns ts into an UTC tm when utc=1"
  //}

  context "tz dependents"
  {
    before each
    {
      //printf("0  tz: %s/%s\n", tzname[0], tzname[1]);
      char *tz = getenv("TZ");
      setenv("TZ", "JST-9", 1);
      tzset();
      //printf("0b tz: %s/%s\n", tzname[0], tzname[1]);
    }
    after each
    {
      //printf("1 pre: %s\n", tz);
      //printf("1  tz: %s/%s\n", tzname[0], tzname[1]);
      if (tz == NULL) unsetenv("TZ");
      else setenv("TZ", tz, 1);
      tzset();
      //printf("1b tz: %s/%s\n", tzname[0], tzname[1]);
    }

    describe "flu_tstamp()"
    {
      it "outputs a string timestamp"
      {
        struct timespec ts;
        ts.tv_sec = 1414791000;
        ts.tv_nsec = 123456789;
          //
          // 2014/11/01 06:30:00

        expect(flu_tstamp(&ts, 0, 'z') ===f "2014-10-31T21:30:00Z");
        expect(flu_tstamp(&ts, 1, 'z') ===f "2014-10-31T21:30:00Z");

        expect(flu_tstamp(&ts, 0, 'r') ===f "Fri, 31 Oct 2014 21:30:00 UTC");
        expect(flu_tstamp(&ts, 1, 'r') ===f "Fri, 31 Oct 2014 21:30:00 UTC");
        expect(flu_tstamp(&ts, 0, 'g') ===f "Fri, 31 Oct 2014 21:30:00 GMT");
        expect(flu_tstamp(&ts, 1, 'g') ===f "Fri, 31 Oct 2014 21:30:00 GMT");

        expect(flu_tstamp(&ts, 0, '2') ===f "Sat, 01 Nov 2014 06:30:00 +0900");
        expect(flu_tstamp(&ts, 1, '2') ===f "Fri, 31 Oct 2014 21:30:00 +0000");

        expect(flu_tstamp(&ts, 0, 'd') ===f "20141101");
        expect(flu_tstamp(&ts, 1, 'd') ===f "20141031");

        expect(flu_tstamp(&ts, 0, 'h') ===f "20141101.0630");
        expect(flu_tstamp(&ts, 1, 'h') ===f "20141031.2130");
        expect(flu_tstamp(&ts, 0, 's') ===f "20141101.063000");
        expect(flu_tstamp(&ts, 1, 's') ===f "20141031.213000");

        expect(flu_tstamp(&ts, 0, 'm') ===f "20141101.063000.123");
        expect(flu_tstamp(&ts, 1, 'm') ===f "20141031.213000.123");
        expect(flu_tstamp(&ts, 0, 'u') ===f "20141101.063000.123456");
        expect(flu_tstamp(&ts, 1, 'u') ===f "20141031.213000.123456");
        expect(flu_tstamp(&ts, 0, 'n') ===f "20141101.063000.123456789");
        expect(flu_tstamp(&ts, 1, 'n') ===f "20141031.213000.123456789");

        expect(flu_tstamp(&ts, 0, 'T') ===f "20141031T213000Z");
        expect(flu_tstamp(&ts, 1, 'T') ===f "20141031T213000Z");

        ts.tv_nsec = 1;

        expect(flu_tstamp(&ts, 0, 'm') ===f "20141101.063000.000");
        expect(flu_tstamp(&ts, 1, 'm') ===f "20141031.213000.000");
        expect(flu_tstamp(&ts, 0, 'u') ===f "20141101.063000.000000");
        expect(flu_tstamp(&ts, 1, 'u') ===f "20141031.213000.000000");
        expect(flu_tstamp(&ts, 0, 'n') ===f "20141101.063000.000000001");
        expect(flu_tstamp(&ts, 1, 'n') ===f "20141031.213000.000000001");
      }

      it "gets its time from clock_gettime(CLOCK_REALTIME, ...) if ts is NULL"
      {
        expect(flu_tstamp(NULL, 0, 'n') ^==f "20");
      }
    }

    describe "flu_sstamp()"
    {
      it "outputs a string timestamp"
      {
        long long s = 1414791000;

        expect(flu_sstamp(s, 0, 'z') ===f "2014-10-31T21:30:00Z");
      }

      it "computes now by itself if given 0"
      {
        char *a = flu_tstamp(NULL, 0, 'n');
        char *b = flu_sstamp(0, 0, 'n');

        expect(strcmp(a, b) <= 0);

        free(a); free(b);
      }
    }

    describe "flu_parse_tstamp()"
    {
      it "parses timestamps"
      {
        struct timespec *ts = NULL;

        ts = flu_parse_tstamp("2014-10-31T21:30:00Z", 0);
        expect(ts != NULL);
        expect(ts->tv_sec li== 1414791000);
        expect(ts->tv_nsec li== 0);
        free(ts);

        ts = flu_parse_tstamp("2014-10-31T21:30:00Z", 1);
        expect(ts != NULL);
        expect(ts->tv_sec li== 1414791000);
        expect(ts->tv_nsec li== 0);
        free(ts);

        ts = flu_parse_tstamp("20141031.2130", 1);
        expect(ts != NULL);
        expect(ts->tv_sec li== 1414791000);
        expect(ts->tv_nsec li== 0);
        free(ts);

        ts = flu_parse_tstamp("20141101.0630", 0);
        expect(ts != NULL);
        expect(ts->tv_sec li== 1414791000);
        expect(ts->tv_nsec li== 0);
        free(ts);

        ts = flu_parse_tstamp("20141101.063055", 0);
        expect(ts != NULL);
        expect(ts->tv_sec li== 1414791055);
        expect(ts->tv_nsec li== 0);
        free(ts);
      }

      it "parses timestamps with subseconds"
      {
        struct timespec *ts = NULL;

        ts = flu_parse_tstamp("20141101.063055.001", 0);
        expect(ts != NULL);
        expect(ts->tv_sec li== 1414791055);
        expect(ts->tv_nsec li== 1000000);
        free(ts);

        ts = flu_parse_tstamp("20141101.063055.001001", 0);
        expect(ts != NULL);
        expect(ts->tv_sec li== 1414791055);
        expect(ts->tv_nsec li== 1001000);
        free(ts);

        ts = flu_parse_tstamp("20141101.063055.001001009", 0);
        expect(ts != NULL);
        expect(ts->tv_sec li== 1414791055);
        expect(ts->tv_nsec li== 1001009);
        free(ts);
      }

      it "returns NULL when it cannot parse"
      {
        expect(flu_parse_tstamp("lore ipsum", 0) == NULL);
      }
    }
  }

  describe "flu_tdiff()"
  {
    it "substracts t0 from t1"
    {
      struct timespec t0 = { 10, 10 };
      struct timespec t1 = { 100, 100 };

      struct timespec *t2 = flu_tdiff(&t1, &t0);

      expect(t2->tv_sec li== 90);
      expect(t2->tv_nsec li== 90);

      free(t2);
    }

    it "carries from nanoseconds to seconds"
    {
      struct timespec t0 = { 10, 100 };
      struct timespec t1 = { 100, 0 };

      struct timespec *t2 = flu_tdiff(&t1, &t0);

      expect(t2->tv_sec li== 89);
      expect(t2->tv_nsec li== 999999900);

      free(t2);
    }

    it "uses flu_now() if t1 is not set"
    {
      struct timespec t0 = { 1414791055, 0 };

      struct timespec *t2 = flu_tdiff(NULL, &t0);

      expect(t2->tv_sec > 0);

      free(t2);
    }
  }

  describe "flu_ts_to_s()"
  {
    it "renders a timespec as a string"
    {
      struct timespec ts = { 10, 1200300 };

      expect(flu_ts_to_s(&ts, 's') ===f "10s");
      expect(flu_ts_to_s(&ts, 'm') ===f "10s001");
      expect(flu_ts_to_s(&ts, 'u') ===f "10s001200");
      expect(flu_ts_to_s(&ts, 'n') ===f "10s001200300");
    }
  }

  describe "flu_ts_to_hs()"
  {
    it "renders seconds (struct timespec) to a wdhms string"
    {
      struct timespec ts;

      ts = (struct timespec){ 10, 1200300 };
      expect(flu_ts_to_hs(&ts, 's') ===f "10s");
      expect(flu_ts_to_hs(&ts, 'm') ===f "10s001");
      expect(flu_ts_to_hs(&ts, 'u') ===f "10s001200");
      expect(flu_ts_to_hs(&ts, 'n') ===f "10s001200300");

      ts = (struct timespec){ 10, 200300 };
      expect(flu_ts_to_hs(&ts, 'm') ===f "10s000");

      ts = (struct timespec){ 52 * 7 * 24 * 3600, 201000000 };
      expect(flu_ts_to_hs(&ts, 'm') ===f "52w0s201");

      ts = (struct timespec){ 23456789, 201000000 };
      expect(flu_ts_to_hs(&ts, 'm') ===f "38w5d11h46m29s201");
    }
  }

  describe "flu_parse_ts()"
  {
    it "parses a time[spec] string"
    {
      struct timespec *ts = NULL;

      ts = flu_parse_ts("10s");
      expect(ts->tv_sec li== 10);
      expect(ts->tv_nsec li== 0);
      free(ts);

      ts = flu_parse_ts("7s001");
      expect(ts->tv_sec li== 7);
      expect(ts->tv_nsec li== 1000000);
      free(ts);

      ts = flu_parse_ts("7s001200");
      expect(ts->tv_sec li== 7);
      expect(ts->tv_nsec li== 1200000);
      free(ts);

      ts = flu_parse_ts("7s001200123");
      expect(ts->tv_sec li== 7);
      expect(ts->tv_nsec li== 1200123);
      free(ts);

      ts = flu_parse_ts("1s1m.001");
      expect(ts->tv_sec li== 61);
      expect(ts->tv_nsec li== 1000000);
      free(ts);

      ts = flu_parse_ts(".001s");
      expect(ts->tv_sec li== 0);
      expect(ts->tv_nsec li== 1000000);
      free(ts);

      ts = flu_parse_ts("-1");
      expect(ts->tv_sec li== -1);
      expect(ts->tv_nsec li== 0);
      free(ts);

      ts = flu_parse_ts("-1s");
      expect(ts->tv_sec li== -1);
      expect(ts->tv_nsec li== 0);
      free(ts);

      ts = flu_parse_ts("-.001s");
      expect(ts->tv_sec li== 0);
      expect(ts->tv_nsec li== -1000000);
      free(ts);

      ts = flu_parse_ts("-.001");
      expect(ts->tv_sec li== 0);
      expect(ts->tv_nsec li== -1000000);
      free(ts);
    }

    it "returns NULL when it cannot parse"
    {
      expect(flu_parse_ts("nada") == NULL);
    }

    it "accepts changes of sign"
    {
      struct timespec *ts = NULL;

      ts = flu_parse_ts("5s-1");
      expect(ts->tv_sec li== 4);
      expect(ts->tv_nsec li== 0);
      free(ts);

      ts = flu_parse_ts("5s-.001+1m");
      //puts(flu_ts_to_s(ts, 'n'));
      expect(ts->tv_sec li== 64);
      expect(ts->tv_nsec li== 999000000);
      free(ts);
    }

    it "doesn't mind white spaces"
    {
      // testing via flu_parse_d()

      expect(flu_parse_d(" 7s001") f== 7.001);
      expect(flu_parse_d("7s001 ") f== 7.001);
      expect(flu_parse_d("7s 001") f== 7.001);
    }
  }

  describe "flu_parse_t()"
  {
    it "parses a time string"
    {
      expect(flu_parse_t("10s") lli== 10);
      expect(flu_parse_t("2m10s") lli== 130);
      expect(flu_parse_t("-7s") lli== -7);
      expect(flu_parse_t("1h1s") lli== 3601);
      expect(flu_parse_t("-10m7s") lli== -607);

      expect(flu_parse_t("1") lli== 1);
      expect(flu_parse_t("1s") lli== 1);
      expect(flu_parse_t("1m") lli== 60);
      expect(flu_parse_t("1h") lli== 60 * 60);
      expect(flu_parse_t("1d") lli== 24 * 60 * 60);
      expect(flu_parse_t("1w") lli== 7 * 24 * 60 * 60);
      expect(flu_parse_t("1M") lli== 30 * 24 * 60 * 60);
      expect(flu_parse_t("1y") lli== 365 * 24 * 60 * 60);
    }

    it "sets errno to EINVAL when it cannot parse"
    {
      long long r = -1;

      r = flu_parse_t("nada");
      expect(r == 0);
      expect(errno == EINVAL);
      errno = 0;

      r = flu_parse_t("blah blah");
      expect(r == 0);
      expect(errno == EINVAL);
      errno = 0;
    }

    it "accepts changes of sign"
    {
      expect(flu_parse_t("1h-2m+3s") lli== 3600 - 2 * 60 + 3);
    }
  }

  describe "flu_parse_d()"
  {
    it "parses to a double"
    {
      expect(flu_parse_d("10s") f== 10.0);
      expect(flu_parse_d("7s001") f== 7.001);
      expect(flu_parse_d("7s001200") f== 7.0012);
      expect(flu_parse_d("7s001200123") f== 7.001200123);
      expect(flu_parse_d("1s1m.001") f== 61.001);
      expect(flu_parse_d(".001s") f== 0.001);
      expect(flu_parse_d("-1") f== -1.0);
      expect(flu_parse_d("-1s") f== -1.0);
      expect(flu_parse_d("-.001s") f== -0.001);
      expect(flu_parse_d("-.001") f== -0.001);
    }
  }
}

