CFLAGS = -Wall -pedantic -O2 -std=c11
MCC = mpicc
NAME = broadcast

$(NAME): $(NAME).c
	$(MCC) $(DEBUG) $(CFLAGS) -o $(NAME) $<

debug: DEBUG = -DDEBUG

debug: $(NAME)

.PHONY: clean
clean:
	rm $(NAME)
	