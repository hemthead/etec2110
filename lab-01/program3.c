// Name: John Reed
// Class: Systems Programming Section: 01
// Assignment: Lab 1 - Simple 'C' Programs & The Preprocessor - Program III

#include <stdio.h>

#define main int main
#define begin {
#define end }

#define write printf

// I've never bothered much with the CPP outside of includes and basic defines,
// so I guess we can have a little fun here

// Force-enable printf support for writeln
// #define PROGRAM3_FORCE_WRITELN_PRINTF

// Allow use of ##__VA_ARGS__ syntax
#define PROGRAM3_ALLOW_WRITELN_EMPTY_VARIADIC

#if __STDC_VERSION__ >= 202311L
// __VA_OPT__ was officially added in C23, though GCC had support before that
#define writeln(format_string, ...)                                            \
  printf(format_string "\n" __VA_OPT__(, ) __VA_ARGS__)
#elif defined(__GNUC__) && defined(PROGRAM3_ALLOW_WRITELN_EMPTY_VARIADIC)
// Everyone's impersonating GCC, so ##__VA_ARGS__ is decently likely to work,
// but it's not standard, just a GNUC extension
#define writeln(s, ...) printf(s "\n", ##__VA_ARGS__)
#elif defined(PROGRAM3_FORCE_WRITELN_PRINTF)
// __VA_ARGS__ has been around since C99
// If you really wanna put writeln(format_string, NULL); everywhere just for
// printf, be my guest
#define writeln(format_string, ...) printf(format_string "\n", __VA_ARGS__)
#else
// I guess this is really the easiest solution, puts even adds a newline for
// you...
#define writeln puts
#endif

// I /would/ put checks for C99 (and __VA_ARGS__ support), but that's when
// single-line comments were added, so there's not much use in pretending to
// support anything prior

main() begin write("first");
write("line");
writeln(" ");
writeln("John Reed");
writeln("\"'Portability is for people who cannot write new programs' "
        "-me, right now (with tounge in cheek)\"");
writeln("    -Linus Torvalds");
end
