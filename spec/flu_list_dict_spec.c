
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

  describe "flu_list_set_last()"
  {
    it "sets a 'default'"
    {
      flu_list_set(l, "red", "aka");
      flu_list_set_last(l, "red", "murakami");

      ensure(l->size == 2);
      ensure(flu_list_get(l, "red") === "aka");
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
      flu_list_set(l, "white", NULL);
      flu_list_set(l, "red", "rojo");

      flu_list *tl = flu_list_dtrim(l);

      //size_t i = 0;
      //for (flu_node *n = tl->first; n != NULL; n = n->next)
      //{
      //  printf("%zu: %s: \"%s\"\n", i++, n->key, (char *)n->item);
      //}

      ensure(tl->size == 3);
      ensure(flu_list_at(tl, 0) === "rojo");
      ensure(flu_list_at(tl, 1) === NULL);
      ensure(flu_list_at(tl, 2) === "blau");
      ensure(tl->first->key === "red");
      ensure(tl->last->key === "blue");

      flu_list_free(tl);
    }
  }

  describe "flu_d()"
  {
    it "builds a flu_list dict"
    {
      flu_list *d =
        flu_d("name", "Hans", "age", "30", "balance", "1000", NULL);

      ensure(d->size == 3);
      ensure(flu_list_get(d, "name") === "Hans");
      ensure(flu_list_get(d, "age") === "30");
      ensure(flu_list_get(d, "balance") === "1000");

      flu_list_free(d);
    }
  }

  describe "flu_vsd()"
  {
    it "returns NULL when fed a key without a value"
  }

  describe "flu_sd()"
  {
    it "composes string -> string dictionaries"
    {
      flu_list *d =
        flu_sd(
          "name", "Hans %s", "Rothenmeyer",
          "age", "%X", 15 + 1 + 11,
          "balance", "10%s", "05",
          "x_%s", "special", "nothing",
          NULL);

      ensure(d->size zu== 4);
      ensure(flu_list_get(d, "name") === "Hans Rothenmeyer");
      ensure(flu_list_get(d, "age") === "1B");
      ensure(flu_list_get(d, "balance") === "1005");
      ensure(flu_list_get(d, "x_special") === "nothing");

      flu_list_free_all(d);
        //
        // Contrast with flu_d() above. Here, all the strings are
        // malloc'ed so _free_all is "de rigueur".
    }

    it "returns NULL when fed a key without a value"
  }
}

