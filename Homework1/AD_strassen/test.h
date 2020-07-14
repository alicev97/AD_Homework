#ifndef __TEST__


double test(void (*f)(float **,
	                  float const *const *const,
	                  float const *const *const,
	                  size_t, size_t, size_t), 
	        float **C, float** A, float **B, size_t n, size_t m, size_t p);
#endif // __TEST__
