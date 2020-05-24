
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEQIO_DEFINE
#include "seqio.h"

/*
 * This example is a simple version of `fgrep' for biological sequences.
 * It searches each sequence of the input, and for each sequence that
 * contains the keyword, it outputs the sequence's entry.
 */

int main(int argc, char *argv[])
{
  int i, len;
  char *seq, *entry;
  SEQFILE *sfp;

  if (argc < 3) {
    fprintf(stderr, "Usage:  ex3 keyword files...\n");
    exit(1);
  }

  for (i=2; i < argc; i++) {
    if ((sfp = seqfopen2(argv[i])) == NULL)
      continue;

    while ((seq = seqfgetseq(sfp, &len, 0)) != NULL) {
      /*
       * Search the sequence for the keyword.
       */
      if (len > 0 && strstr(seq, argv[1]) != NULL) {
        entry = seqfentry(sfp, &len, 0);
        fwrite(entry, len, 1, stdout);
      }
    }
    seqfclose(sfp);
  }

  return 0;
}


