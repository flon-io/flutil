
NAME=flutil

default: $(NAME).o

.DEFAULT:
	$(MAKE) -C tmp/ $@ NAME=$(NAME)

spec:
	$(MAKE) -C tmp/ spec NAME=$(NAME)

clean:
	$(MAKE) -C tmp/ clean NAME=$(NAME)

.PHONY: spec clean

