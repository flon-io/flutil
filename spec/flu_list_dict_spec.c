
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
    it "returns NULL if there is no item for the key"
    {
      ensure(flu_list_get(l, "red") == NULL);

      flu_list_set(l, "red", "rot");
      flu_list_set(l, "red", NULL);

      ensure(flu_list_get(l, "red") == NULL);

      flu_list_set(l, "red", "rouge");

      ensure(flu_list_get(l, "red") === "rouge");
    }

    it "returns the item for the first node with the given key"
    {
      flu_list_set(l, "red", "rot");

      ensure(flu_list_get(l, "red") === "rot");

      flu_list_set(l, "red", "rouge");

      ensure(flu_list_get(l, "red") === "rouge");
    }

    it "skips non-keyed nodes"
    {
      flu_list_set(l, "blue", "bleu");
      flu_list_unshift(l, "black");

      ensure(flu_list_get(l, "blue") === "bleu");
    }
  }

  describe "flu_list_dtrim()"
  {
    it "returns a new, trimmed, flu_list"
    {
      flu_list_set(l, "red", "aka");
      flu_list_set(l, "blue", "ao");

      flu_list *tl = flu_list_dtrim(l);

      ensure(tl->size == 2);
      ensure(flu_list_at(tl, 0) === "ao");
      ensure(flu_list_at(tl, 1) === "aka");
      ensure(tl->first->key === "blue");
      ensure(tl->last->key === "red");

      flu_list_free(tl);
    }

    it "returns a new, trimmed, flu_list (2)"
    {
      flu_list_set(l, "blue", "bleu");
      flu_list_unshift(l, "black");
      flu_list_set(l, "white", "blanc");
      flu_list_set(l, "blue", "blau");

      flu_list *tl = flu_list_dtrim(l);

      ensure(tl->size == 2);
      ensure(flu_list_at(tl, 0) === "blau");
      ensure(flu_list_at(tl, 1) === "blanc");
      ensure(tl->first->key === "blue");
      ensure(tl->last->key === "white");

      flu_list_free(tl);
    }
  }
}

