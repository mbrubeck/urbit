/* mill/seal.c
**
** This file is in the public domain.
*/
#include "u4/all.h"

    /** Forward declarations.
    **/
      static u4_bag
      _seal_main(u4_milr, u4_bag, u4_type);


/* _seal_main(): as _mill_seal(), with gil.
*/
static u4_loaf
_seal_main(u4_milr m,
           u4_bag  gil,
           u4_type typ)
{
  u4_lane lane = m->lane;
  u4_noun p_typ, q_typ;

  // %atom
  // %blur
  //
  if ( u4_n_eq(u4_atom_atom, typ) ||
       u4_n_eq(u4_atom_blur, typ) ||
       u4_n_eq(u4_atom_blot, typ) ) 
  {
    return u4_noun_0;
  }

  // [%cell p=type q=type]
  //
  else if ( u4_b_pq(typ, u4_atom_cell, &p_typ, &q_typ) ) {
    return u4_bag_cat(lane, _seal_main(m, gil, p_typ),
                            _seal_main(m, gil, q_typ));
  }

  // [%cone p=type q=bush+[mark type]]
  //
  else if ( u4_b_pq(typ, u4_atom_cone, &p_typ, &q_typ) ) {
    return _seal_main(m, gil, p_typ);
  }

  // [%cube p=noun]
  // 
  else if ( u4_b_p(typ, u4_atom_cube, &p_typ) ) {
    return u4_noun_0;
  }

  // [%face p=mark q=type]
  //
  else if ( u4_b_pq(typ, u4_atom_face, &p_typ, &q_typ) ) {
    return _seal_main(m, gil, q_typ);
  }

  // [%fork p=type q=type]
  //
  else if ( u4_b_pq(typ, u4_atom_fork, &p_typ, &q_typ) ) {
    return u4_bag_cat(lane, _seal_main(m, gil, p_typ),
                            _seal_main(m, gil, q_typ));
  }

  // [%fuse p=type q=type]
  //
  else if ( u4_b_pq(typ, u4_atom_fuse, &p_typ, &q_typ) ) {
    return u4_bag_cat(lane, _seal_main(m, gil, p_typ),
                            _seal_main(m, gil, q_typ));
  }

  // [%hold p=type q=gene]
  //
  else if ( u4_b_pq(typ, u4_atom_hold, &p_typ, &q_typ) ) {
    if ( u4_bag_in(typ, gil) ) {
      return u4_k_trel(lane, typ, u4_noun_0, u4_noun_0);
    } 
    else {
      return _seal_main
        (m, u4_bag_add(lane, typ, gil),
            _mill_repo(m, p_typ, q_typ));
    }
  }

  else {
    u4_bug("strange type", typ);
    return u4_trip;
  }
}

/* _mill_seal(): produce set of holds sealing [typ].
*/
u4_bag
_mill_seal(u4_milr m,
           u4_type typ)
{
  return _seal_main(m, u4_noun_0, typ);
}
