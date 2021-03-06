/* mill/make.c
**
** This file is in the public domain.
*/
#include "u4/all.h"

#define _make_p(flot) \
  if ( u4_b_p(gen, u4_atom_##flot, &p_gen) ) { \
    u4_wire _mill_x_##flot(u4_milr, u4_noun, u4_type); \
    return _mill_x_##flot(m, p_gen, tip); \
  }

#define _make_pq(flot) \
  if ( u4_b_pq(gen, u4_atom_##flot, &p_gen, &q_gen) ) { \
    u4_wire _mill_x_##flot(u4_milr, u4_noun, u4_noun, u4_type); \
    return _mill_x_##flot(m, p_gen, q_gen, tip); \
  }

#define _make_pqr(flot) \
  if ( u4_b_pqr(gen, u4_atom_##flot, &p_gen, &q_gen, &r_gen) ) {\
    u4_wire _mill_x_##flot(u4_milr, u4_noun, u4_noun, u4_noun, u4_type); \
    return _mill_x_##flot(m, p_gen, q_gen, r_gen, tip); \
  }

/* _mill_make_main(): internal of _mill_make().
*/
u4_wire
_mill_make_main(u4_milr m,
                u4_gene gen,
                u4_type tip)
{
  u4_noun p_gen, q_gen, r_gen;

  if ( u4_b_fork(gen, &p_gen, &q_gen) ) {
    return _mill_make_main
      (m, u4_k_qual(m->lane, u4_atom_cage, p_gen, q_gen, u4_noun_0), tip);
  }
  else {
    _make_pq (link);    // ~>
    _make_pq (kick);    // :=
    _make_pq (cast);    // ^+
    _make_p  (dbug);
    _make_p  (rock);
    _make_p  (load);
    _make_pqr(sure);    // ^=
    _make_p  (bail);    // !!
    _make_p  (dbug);    // !?
    _make_pq (nock);
    _make_pqr(quiz);    // ?:
    _make_pq (name);    // :`
    _make_p  (cage);    // :.
    _make_pq (spot);
    _make_pq (home);
    _make_pq (like);    // ?= 

    {
      u4_noun rex = _mill_open(m, gen);

      if ( u4_n_eq(rex, gen) ) {
        u4_err(m->lane, "rex", rex);
        return u4_trip;
      }
      else {
        return _mill_make(m, rex, tip);
      }
    }
  }
}

/* _mill_make(): type inference, top level.
*/
u4_wire
_mill_make(u4_milr m,
           u4_gene gen,
           u4_type tip)
{
  u4_lane lane = m->lane;
  u4_noun fid  = u4_k_cell(lane, gen, tip);
  u4_nopt raz  = u4_tab_get(fid, m->niq);

  if ( raz ) {
    return raz;
  }
  else {
    /* Memoize.
    */
    raz = _mill_make_main(m, gen, tip);

    m->niq = u4_tab_add(lane, fid, raz, m->niq);
    return raz;
  }
}
