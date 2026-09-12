
#include <stddef.h>

// this header is to detected parts of the syntax
// like var names, or quotes
// every function in here expectes the string to start with what is searched
// if it does not start with what we are searching every function here returns 0

size_t	ms_parsing_varname(char *str);
