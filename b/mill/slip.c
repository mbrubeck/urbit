/* mill/bink.c
**
** This file is in the public domain.
*/
#include "u4/all.h"

/* _mill_slip(): peek bar.
*/
u4_type
_mill_slip(u4_milr m,
           u4_axis axe,
           u4_rail bar)
{
  if ( u4_n_zero(bar) ) {
    return u4_noun_0;
  }
  else {
    u4_type caf = _mill_peek(m, axe, u4_noun_0, u4_ch(bar));

    if ( u4_n_eq(u4_atom_blur, caf) ) {
      return _mill_slip(m, axe, u4_ct(bar));
    } else {
      return u4_k_cell(m->lane, caf, _mill_slip(m, axe, u4_ct(bar)));
    }
  }
}
