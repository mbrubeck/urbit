/* mill/hunt.c
**
** This file is in the public domain.
*/
#include "u4/all.h"

/* _is_lect()::
*/
static u4_t
_is_lect(u4_knot sod, 
         u4_tick *tik, 
         u4_term *cox)
{
  if ( u4_n_atom(sod) ) {
    if ( tik ) *tik = u4_noun_0;
    if ( cox ) *cox = sod;
    return 1;
  }
  else if ( u4_b_pq(sod, u4_atom_lect, tik, cox) ) {
    return 1;
  }
  else return 0;
}

/* _is_frag()::
*/
static u4_t
_is_frag(u4_knot sod,
         u4_axis *mar)
{
  return u4_b_p(sod, u4_atom_frag, mar);
}

/* _mill_hunt(): rope to tape.
*/
u4_tape
_mill_hunt(u4_milr m,
           u4_rope dap,
           u4_type fim,
           u4_axis *axe,
           u4_type *buv)
{
  u4_lane lane = m->lane;

  if ( u4_n_zero(dap) ) {
    if ( buv ) {
      *buv = fim;
    }
    return u4_noun_0;
  }
  else {
    u4_knot i_dap = u4_ch(dap);
    u4_rope t_dap = u4_ct(dap);
    u4_axis mar;
    u4_tick tik;
    u4_term cox;

    if ( _is_frag(i_dap, &mar) ) {
      u4_type gey = _mill_peek(m, mar, u4_noun_0, fim);

      *axe = u4_op_peg(lane, *axe, mar);

      return u4_k_cell
        (lane, u4_k_cell(lane, u4_atom_axis, mar),
               _mill_hunt(m, t_dap, gey, axe, buv));
    }
    else if ( _is_lect(i_dap, &tik, &cox) ) {
      u4_loaf zib = _mill_find(m, cox, u4_noun_0, fim);

      if ( u4_n_zero(zib) ) {
        u4_burp(lane, "mark", u4_prep_textual(lane, cox));
        u4_burp(lane, "type", _mill_dump(m, fim));

        return _mill_fail(m, "look: no port");
      }
      else {
        u4_type gey = u4_ch(zib);
   
        if ( !u4_b_p(u4_ct(zib), u4_noun_0, &mar) ) {
          return _mill_fail(m, "heavy rope");
        }
        else {
          u4_rope guz;

          guz = u4_n_zero(tik)
            ? t_dap
            : u4_k_cell
              (lane, u4_k_trel(lane, u4_atom_lect, u4_op_dec(lane, tik), cox),
                     t_dap);

          *axe = u4_op_peg(lane, *axe, mar);

          if ( u4_n_eq(u4_noun_1, mar) ) {
            return u4_k_cell
              (lane, u4_k_cell(lane, u4_atom_term, cox),
                     _mill_hunt(m, guz, gey, axe, buv));
          }
          else {
            return u4_k_trel
              (lane, u4_k_cell(lane, u4_atom_axis, mar),
                     u4_k_cell(lane, u4_atom_term, cox),
                     _mill_hunt(m, guz, gey, axe, buv));
          }
        }
      }
    }
    else return u4_trip;
  }
}
