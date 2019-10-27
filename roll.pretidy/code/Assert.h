/* Assert.h for GNU C/C++ */

#pragma interface

#ifdef ASSERT

void AssertionFailure(char *exp, char *file, char *baseFile, int line);

#define Assert(exp)  if (exp) ; \
        else AssertionFailure( #exp, __FILE__, __BASE_FILE__, __LINE__ )

#else

#define Assert(exp)

#endif

