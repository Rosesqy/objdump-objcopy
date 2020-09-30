#ifndef OBJSYM_H
#define OBJSYM_H

#include <stdbool.h>
#include "bfd.h"

char *long_to_string(unsigned long val, char *temp);
void print_nm(bfd *abfd, asection *sect, void *obj);
bool enter_objsym(char *inputf);

#endif
