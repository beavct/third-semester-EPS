CC     = gcc
CFLAGS = -Wall -pedantic -O2 -std=c11
CC_OMP = -fopenmp
CC_PTH = -pthread

all: check time_test grid_gen

check: check.o lga_base.o lga_seq.o lga_omp.o lga_pth.o
	$(CC) $(CFLAGS) $(CC_OMP) $(CC_PTH) -o $@ $^

check.o: check.c lga_base.o
	$(CC) $(CFLAGS) -c $<

time_test: time_test.o lga_base.o lga_seq.o lga_omp.o lga_pth.o time_extra.o
	$(CC) $(CFLAGS) $(CC_OMP) $(CC_PTH) -o $@ $^

time_test.o: time_test.c lga_base.o
	$(CC) $(CFLAGS) -c $<

lga_seq.o: lga_seq.c lga_seq.h lga_base.o
	$(CC) $(CFLAGS) -c $<

lga_omp.o: lga_omp.c lga_omp.h lga_base.o
	$(CC) $(CFLAGS) $(CC_OMP) -c $<

lga_pth.o: lga_pth.c lga_pth.h lga_base.o
	$(CC) $(CFLAGS) $(CC_PTH) -c $<

grid_gen: grid_gen.o lga_base.o
	$(CC) $(CFLAGS) -o $@ $^

grid_gen.o: grid_gen.c lga_base.o
	$(CC) $(CFLAGS) -c $<

lga_base.o: lga_base.c lga_base.h
	$(CC) $(CFLAGS) -c $<

time_extra.o: time_extra.c time_extra.h
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm *.o check time_test grid_gen
