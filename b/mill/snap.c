/* mill/snap.c
**
** This file is in the public domain.
*/
#include "u4/all.h"

/* _snap_cell(): adjust [ger] for assignment into [%cell p_lom q_lom].
*/
static u4_type
_snap_cell(u4_milr m,
           u4_type p_lom,
           u4_type q_lom,
           u4_type ger)
{
  u4_lane lane = m->lane;
  u4_noun p_ger, q_ger;

  // [%cell p=type q=type]
  //
  if ( u4_b_pq(ger, u4_atom_cell, &p_ger, &q_ger) ) {
    return u4_k_trel
      (lane, u4_atom_cell, 
             _mill_snap(m, p_lom, p_ger),
             _mill_snap(m, q_lom, q_ger));
  }
  else if ( u4_b_pq(ger, u4_atom_fork, &p_ger, &q_ger) ) {
    // Not at all clear that this is necessary.  But it can't hurt.
    //
    return u4_k_trel
      (lane, u4_atom_fork,
             _snap_cell(m, p_lom, q_lom, p_ger),
             _snap_cell(m, p_lom, q_lom, q_ger));
  }
  // [%fuse p=type q=type]
  //
  else if ( u4_b_pq(ger, u4_atom_fuse, &p_ger, &q_ger) ) {
    // Not at all clear that this is necessary.  But it can't hurt.
    //
    return u4_k_trel
      (lane, u4_atom_fuse,
             _snap_cell(m, p_lom, q_lom, p_ger),
             _snap_cell(m, p_lom, q_lom, q_ger));
  }
  else return ger;
}

/* _snap_face(): adjust [ger] for assignment into [%face p_lom q_lom].
*/
static u4_type
_snap_face(u4_milr m,
           u4_mark p_lom,
           u4_type q_lom,
           u4_type ger)
{
  u4_lane lane = m->lane;
  u4_noun p_ger, q_ger;

  // [%face p=mark q=type]
  //
  if ( u4_b_pq(ger, u4_atom_face, &p_ger, &q_ger) ) {
    if ( u4_n_eq(p_lom, p_ger) ) {
      return u4_k_trel(lane, u4_atom_face, p_lom, _mill_snap(m, q_lom, q_ger));
    }
    else {
      return u4_k_trel(lane, u4_atom_face, p_lom, _mill_snap(m, q_lom, ger));
    }
  }

  // [%fork p=type q=type]
  //
  else if ( u4_b_pq(ger, u4_atom_fork, &p_ger, &q_ger) ) {
    // Not at all clear that this is necessary.  But it can't hurt.
    //
    return u4_k_trel
      (lane, u4_atom_fork,
             _snap_cell(m, p_lom, q_lom, p_ger),
             _snap_cell(m, p_lom, q_lom, q_ger));
  }

  // [%fuse p=type q=type]
  //
  else if ( u4_b_pq(ger, u4_atom_fuse, &p_ger, &q_ger) ) {
    // Not at all clear that this is necessary.  But it can't hurt.
    //
    return u4_k_trel
      (lane, u4_atom_fuse,
             _snap_face(m, p_lom, q_lom, p_ger),
             _snap_face(m, p_lom, q_lom, q_ger));
  }

  else {
    return u4_k_trel(lane, u4_atom_face, p_lom, _mill_snap(m, q_lom, ger));
  }
}

/* _mill_snap(): adjust [ger] for assignment into [lom].
*/
u4_type
_mill_snap(u4_milr m,
           u4_type lom,
           u4_type ger)
{
  u4_noun p_lom, q_lom;

  // [%cell p=type q=type]
  //
  if ( u4_b_pq(lom, u4_atom_cell, &p_lom, &q_lom) ) {
    return _snap_cell(m, p_lom, q_lom, ger);
  }

  // [%face p=mark q=type]
  //
  else if ( u4_b_pq(lom, u4_atom_face, &p_lom, &q_lom) ) {
    return _snap_face(m, p_lom, q_lom, ger);
  }

  // [%fuse p=type q=type]
  //
  else if ( u4_b_pq(lom, u4_atom_fuse, &p_lom, &q_lom) ) {
    return _mill_snap(m, q_lom, ger);
  }

  else return ger;
}
