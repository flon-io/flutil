
//
// specifying flutil
//
// Thu Jun 26 21:43:44 JST 2014
//

#include "flutil.h"


context "colls"
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
    }
  }

  describe "flu_list_and_items_free()"
  {
    it "frees the list and all its items"
    {
      l = flu_list_malloc();
      flu_list_add(l, strdup("hello"));
      flu_list_add(l, strdup("world"));

      ensure(l->size == 2);

      flu_list_and_items_free(l, free);

      l = NULL;

      // that spec depends on Valgrind ;-)
    }
  }
}

