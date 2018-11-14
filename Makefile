TARGETS=test1
targets:$(TARGETS)

test1:test1.cpp cwt1d.hpp  cwt1d_wavelets.hpp  filter_cwt1d.hpp
	g++ test1.cpp -o test1 -I ../fftw_blitz/ ../fftw_blitz/fftw_blitz.o -I ../opt_utilities -lfftw3_threads -lfftw3f_threads -lfftw3 -lfftw3f -lfio -lcfitsio -O3

clean:
	rm -f *.o $(TARGETS)
