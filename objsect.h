#ifndef OBJSECT_H
#define OBJSECT_H

#include <stdbool.h>
#include "bfd.h"

static char *long_to_string(unsigned long val, char *temp);
void print_objdump(bfd *abfd, asection *sect, void *obj);
bool enter_objsect(char *inputf);

#endif
