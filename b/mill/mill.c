/* mill/mill.c
**
** This file is in the public domain.
*/
#include "u4/all.h"

/* u4_mill(): 
**
**   Convert [gene type] to [type form].
*/
u4_loaf
u4_mill(u4_lane lane,
        u4_lump nes,
        u4_lump zyl)
{
  struct _u4_mill milr;

  u4_mill_init(&milr, lane);

  {
    u4_milr m   = &milr;
    u4_loaf lof = _mill_make(m, nes, zyl);

    return lof;
  }
}
