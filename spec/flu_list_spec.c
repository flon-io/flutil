
//
// specifying flutil
//
// Thu Jun 26 21:43:44 JST 2014
//

#include "flutil.h"


context "flu_list"
{
  before each
  {
    flu_list *l = NULL;
  }
  after each
  {
    if (l != NULL) flu_list_free(l);
  }

  describe "flu_list_malloc()"
  {
    it "creates and empty list"
    {
      l = flu_list_malloc();

      ensure(l->size == 0);
      ensure(l->first == NULL);
      ensure(l->last == NULL);
    }
  }

  describe "flu_list_add()"
  {
    it "adds an item to the list"
    {
      l = flu_list_malloc();
      flu_list_add(l, "equord");

      ensure(l->size == 1);
      ensure(l->first == l->last);

      flu_list_add(l, "freiherr");

      ensure(l->size == 2);
      ensure(l->first->item === "equord");
      ensure(l->last->item === "freiherr");
    }
  }

  describe "flu_list_add_unique()"
  {
    it "adds if the item isn't part of the list"
    {
      int r;
      l = flu_list_malloc();

      r = flu_list_add_unique(l, "one");

      ensure(r == 1); // added
      ensure(l->size == 1);
      ensure(l->first == l->last);

      r = flu_list_add_unique(l, "two");

      ensure(r == 1); // added
      ensure(l->size == 2);
      ensure(l->first->item === "one");
      ensure(l->last->item === "two");
    }

    it "doesn't add if the item is already part of the list"
    {
      int r;
      char *one = flu_strdup("one");

      l = flu_list_malloc();
      r = flu_list_add_unique(l, one);

      ensure(r == 1); // added
      ensure(l->size == 1);

      r = flu_list_add_unique(l, one);

      ensure(r == 0); // not added
      ensure(l->size == 1);

      free(one);
    }
  }

  describe "flu_list_at()"
  {
    it "returns NULL if pointed outside of the list"
    {
      l = flu_list_malloc();

      flu_list_add(l, "one");

      ensure(flu_list_at(l, 1) == NULL);
    }

    it "returns the item at the given index"
    {
      l = flu_list_malloc();

      flu_list_add(l, "un");
      flu_list_add(l, "deux");

      ensure(flu_list_at(l, 0) === "un");
      ensure(flu_list_at(l, 1) === "deux");
    }
  }

  describe "flu_list_and_items_free()"
  {
    it "frees the list and all its items"
    {
      l = flu_list_malloc();
      flu_list_add(l, flu_strdup("hello"));
      flu_list_add(l, flu_strdup("world"));

      ensure(l->size == 2);

      flu_list_and_items_free(l, free);

      l = NULL;

      // that spec depends on Valgrind ;-)
    }
  }

  describe "flu_list_free_all()"
  {
    it "frees the list and all its items"
    {
      l = flu_list_malloc();
      flu_list_add(l, flu_strdup("hello"));
      flu_list_add(l, flu_strdup("world"));

      ensure(l->size == 2);

      flu_list_free_all(l);

      l = NULL;

      // that spec depends on Valgrind ;-)
    }
  }

  describe "flu_list_to_array(l, 0)"
  {
    it "creates an array out of the list"
    {
      l = flu_list_malloc();
      flu_list_add(l, flu_strdup("hello"));
      flu_list_add(l, flu_strdup("world"));

      char **a = (char **)flu_list_to_array(l, 0);

      ensure(a[0] ===f "hello");
      ensure(a[1] ===f "world");

      free(a);
    }
  }

  describe "flu_list_to_array(l, FLU_F_EXTRA_NULL)"
  {
    it "creates a NULL terminated array out of the list"
    {
      l = flu_list_malloc();
      flu_list_add(l, flu_strdup("hello"));
      flu_list_add(l, flu_strdup("world"));

      char **a = (char **)flu_list_to_array(l, FLU_F_EXTRA_NULL);

      ensure(a[0] ===f "hello");
      ensure(a[1] ===f "world");
      ensure(a[2] == NULL);

      free(a);
    }
  }

  describe "flu_list_to_array(l, FLU_F_REVERSE)"
  {
    it "creates a reversed array out of the list"
    {
      l = flu_list_malloc();
      flu_list_add(l, flu_strdup("hello"));
      flu_list_add(l, flu_strdup("world"));

      char **a = (char **)flu_list_to_array(l, FLU_F_REVERSE);

      ensure(a[0] ===f "world");
      ensure(a[1] ===f "hello");
      //ensure(a[2] == NULL);

      free(a);
    }

    it "returns the reversed array with a final NULL"
    {
      l = flu_list_malloc();
      flu_list_add(l, flu_strdup("hello"));
      flu_list_add(l, flu_strdup("world"));

      char **a = (char **)flu_list_to_array(l, FLU_F_REVERSE | FLU_F_EXTRA_NULL);

      ensure(a[0] ===f "world");
      ensure(a[1] ===f "hello");
      ensure(a[2] == NULL);

      free(a);
    }
  }

  describe "flu_list_unshift()"
  {
    it "places an item at the first place in the list"
    {
      l = flu_list_malloc();
      flu_list_unshift(l, "eins");
      flu_list_unshift(l, "zwei");

      ensure(l->size == 2);
      ensure(flu_list_at(l, 0) === "zwei");
      ensure(flu_list_at(l, 1) === "eins");
      ensure(l->last->item === "eins");
    }
  }

  describe "flu_list_shift()"
  {
    it "removes and returns the first item in the list"
    {
      l = flu_list_malloc();
      flu_list_add(l, "hitotsu");
      flu_list_add(l, "futatsu");

      ensure(l->size == 2);

      ensure(flu_list_shift(l) === "hitotsu");
      ensure(l->first == l->last);
      ensure(l->size == 1);

      ensure(flu_list_shift(l) === "futatsu");
      ensure(l->first == NULL);
      ensure(l->last == NULL);
      ensure(l->size == 0);

      ensure(flu_list_shift(l) == NULL);
      ensure(l->first == NULL);
      ensure(l->last == NULL);
      ensure(l->size == 0);
    }
  }

  describe "flu_list_isort()"
  {
    int _strcmp(const void *a, const void *b)
    {
      //return strcmp(*(char * const *)s0, *(char * const *)s1);
      return strcmp((char *)a, (char *)b);
    }

    it "sorts (2 items)"
    {
      l = flu_list_malloc();
      flu_list_add(l, "zebulon");
      flu_list_add(l, "yamatoko");

      flu_list_isort(l, _strcmp);

      ensure(l->size == 2);
      ensure(l->first->item === "yamatoko");
      ensure(l->last->item === "zebulon");
    }

    it "sorts (3 items)"
    {
      l = flu_list_malloc();
      flu_list_add(l, "zebulon");
      flu_list_add(l, "yamatoko");
      flu_list_add(l, "xerxes");

      flu_list_isort(l, _strcmp);

      ensure(l->size == 3);
      ensure(l->first->item === "xerxes");
      ensure(l->last->item === "zebulon");
    }

    it "doesn't shuffle"
    {
      l = flu_list_malloc();
      flu_list_add(l, "xerxes");
      flu_list_add(l, "yamatoko");
      flu_list_add(l, "zebulon");

      flu_list_isort(l, _strcmp);

      ensure(l->size == 3);
      ensure(l->first->item === "xerxes");
      ensure(l->last->item === "zebulon");
    }
  }
}

