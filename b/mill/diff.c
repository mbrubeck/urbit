/* mill/diff.c
**
** This file is in the public domain.
*/
#include "u4/all.h"

/* _mill_diff(): like difference.
*/
u4_form
_mill_diff(u4_milr m,
           u4_axis axe,
           u4_type gan,
           u4_type tip)
{
  u4_type zug = _mill_flap(m, axe, gan);

  if ( _mill_orth(m, tip, zug) ) {
    return u4_k_cell(m->lane, u4_noun_1, u4_noun_1);
  }
  if ( _mill_cong(m, tip, zug) ) {
    return u4_k_cell(m->lane, u4_noun_1, u4_noun_0);
  }

  return _mill_fish(m, axe, gan);
}
