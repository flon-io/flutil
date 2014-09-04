
//
// specifying flutil
//
// Fri Sep  5 06:21:05 JST 2014
//

#include "flutil.h"


context "flu_list as dict"
{
  before each
  {
    flu_list *l = flu_list_malloc();
  }
  after each
  {
    if (l != NULL) flu_list_free(l);
  }

  describe "flu_list_set()"
  {
    it "sets a node with a key at the beginning of the list"
    {
      flu_list_set(l, "red", "aka");

      ensure(l->size == 1);
      ensure(l->first->key === "red");
      ensure(l->first->item === "aka");

      flu_list_set(l, "red", "rodzo");

      ensure(l->size == 2);
      ensure(l->first->key === "red");
      ensure(l->first->item === "rodzo");
    }
  }

  describe "flu_list_get()"
  {
    it "returns the item for the first node with the given key"
    {
      flu_list_set(l, "red", "rot");

      ensure(flu_list_get(l, "red") === "rot");

      flu_list_set(l, "red", "rouge");

      ensure(flu_list_get(l, "red") === "rouge");
    }
  }

  describe "flu_list_keys()"
  {
    it "returns an array of the keys in the flu_list"
    {
      flu_list_set(l, "red", "aka");
      flu_list_set(l, "blue", "ao");

      char **keys = flu_list_keys(l);

      ensure(keys[0] === "red");
      ensure(keys[1] === "blue");
      ensure(keys[2] == NULL);
    }

    it "returns an array of the keys in the flu_list (2)"
    {
      flu_list_set(l, "red", "aka");
      flu_list_set(l, "blue", "ao");
      flu_list_set(l, "red", "rosso");
      flu_list_set(l, "orange", "orange");
      flu_list_set(l, "white", "bianco");

      char **keys = flu_list_keys(l);

      ensure(keys[0] === "blue");
      ensure(keys[1] === "red");
      ensure(keys[2] === "orange");
      ensure(keys[3] === "white");
      ensure(keys[4] == NULL);

      free(keys);
    }
  }
}

