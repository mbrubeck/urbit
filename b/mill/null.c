/* mill/null.c
**
** This file is in the public domain.
*/
#include "u4/all.h"

  /** Forward declarations.
  **/
    static u4_t _null_orth(u4_milr, u4_bag, u4_bag, u4_type, u4_type);
    static u4_t _null_main(u4_milr, u4_bag, u4_type);

/* _null_orth_plum(): as _null_orth(), for atomic cube.
*/
static u4_t
_null_orth_plum(u4_milr m,
                u4_bag  ham, 
                u4_bag  cal,
                u4_atom pp_typ,
                u4_type q_typ)
{
  u4_lane lane = m->lane;
  u4_noun pq_typ, qq_typ;

  if ( u4_n_eq(u4_atom_atom, q_typ) ) {
    return u4_false;
  }

  else if ( u4_n_eq(u4_atom_blur, q_typ) ) {
    return u4_false;
  }

  else if ( u4_b_pq(q_typ, u4_atom_cell, &pq_typ, &qq_typ) ) {
    return u4_true;
  }

  else if ( u4_b_p(q_typ, u4_atom_cube, &pq_typ) ) {
    if ( u4_n_atom(pq_typ) ) {
      return u4_false;
    } 
    else return u4_true;
  }

  else if ( u4_b_pq(q_typ, u4_atom_fork, &pq_typ, &qq_typ) ) {
    return ( _null_main(m, ham, pq_typ) ||
             _null_orth_plum(m, ham, cal, pp_typ, pq_typ) ) &&
           ( _null_main(m, ham, qq_typ) ||
             _null_orth_plum(m, ham, cal, pp_typ, qq_typ) );
  }

  else if ( u4_b_pq(q_typ, u4_atom_fuse, &pq_typ, &qq_typ) ) {
    return _null_orth_plum(m, ham, cal, pp_typ, pq_typ) ||
           _null_orth_plum(m, ham, cal, pp_typ, qq_typ);
  }

  else if ( u4_b_pq(q_typ, u4_atom_hold, &pq_typ, &qq_typ) ) {
    u4_noun p_typ = u4_k_cell(lane, u4_atom_cube, pp_typ);
    u4_noun fum   = u4_k_cell(lane, p_typ, q_typ);

    if ( u4_bag_in(fum, cal) ) {
      return 1;
    }
    else {
      return _null_orth_plum
        (m, ham, 
            u4_bag_add(lane, fum, cal), 
            pp_typ,
            _mill_repo(m, pq_typ, qq_typ));
    }
  }
  else return _null_orth_plum(m, ham, cal, pp_typ, _mill_reap(m, q_typ));
}

/* _null_orth_atom(): as _null_orth(), for bead.
*/
static u4_t
_null_orth_atom(u4_milr m,
                u4_bag  ham,
                u4_bag  cal,
                u4_type q_typ)
{
  u4_lane lane = m->lane;
  u4_noun pq_typ, qq_typ;

  if ( u4_n_eq(u4_atom_atom, q_typ) ) {
    return u4_false;
  }

  else if ( u4_n_eq(u4_atom_blur, q_typ) ) {
    return u4_false;
  }

  else if ( u4_b_pq(q_typ, u4_atom_cell, &pq_typ, &qq_typ) ) {
    return u4_true;
  }

  else if ( u4_b_p(q_typ, u4_atom_cube, &pq_typ) ) {
    if ( u4_n_atom(pq_typ) ) {
      return u4_false;
    } 
    else return u4_true;
  }

  else if ( u4_b_pq(q_typ, u4_atom_fork, &pq_typ, &qq_typ) ) {
    return ( _null_main(m, ham, pq_typ) ||
             _null_orth_atom(m, ham, cal, pq_typ) ) &&
           ( _null_main(m, ham, qq_typ) ||
             _null_orth_atom(m, ham, cal, qq_typ) );
  }

  else if ( u4_b_pq(q_typ, u4_atom_fuse, &pq_typ, &qq_typ) ) {
    return _null_orth_atom(m, ham, cal, pq_typ) ||
           _null_orth_atom(m, ham, cal, qq_typ);
  }

  else if ( u4_b_pq(q_typ, u4_atom_hold, &pq_typ, &qq_typ) ) {
    u4_noun fum   = u4_k_cell(lane, u4_atom_atom, q_typ);

    if ( u4_bag_in(fum, cal) ) {
      return 1;
    }
    else {
      return _null_orth_atom
        (m, ham, 
            u4_bag_add(lane, fum, cal), 
            _mill_repo(m, pq_typ, qq_typ));
    }
  }
  else return _null_orth_atom(m, ham, cal, _mill_reap(m, q_typ));
}

/* _null_orth_cell(): as _null_orth(), for cell.
*/
static u4_t
_null_orth_cell(u4_milr m,
                u4_bag  ham,
                u4_bag  cal,
                u4_type pp_typ,
                u4_type qp_typ,
                u4_type q_typ)
{
  u4_lane lane = m->lane;
  u4_noun pq_typ, qq_typ;

  if ( u4_n_eq(u4_atom_atom, q_typ) ) {
    return u4_true;
  }

  else if ( u4_n_eq(u4_atom_blur, q_typ) ) {
    return u4_false;
  }

  else if ( u4_b_pq(q_typ, u4_atom_cell, &pq_typ, &qq_typ) ) {
    return _null_orth(m, ham, cal, pp_typ, pq_typ) ||
           _null_orth(m, ham, cal, pq_typ, qq_typ);
  }

  else if ( u4_b_p(q_typ, u4_atom_cube, &pq_typ) ) {
    if ( u4_n_atom(pq_typ) ) {
      return u4_true;
    } 
    else {
      return _null_orth_cell
        (m, ham, cal, pp_typ, qp_typ, _mill_reap(m, q_typ));
    }
  }

  else if ( u4_b_pq(q_typ, u4_atom_fork, &pq_typ, &qq_typ) ) {
    return ( _null_main(m, ham, pq_typ) ||
             _null_orth_cell(m, ham, cal, pp_typ, qp_typ, pq_typ) ) &&
           ( _null_main(m, ham, qq_typ) ||
             _null_orth_cell(m, ham, cal, pp_typ, qp_typ, qq_typ) );
  }

  else if ( u4_b_pq(q_typ, u4_atom_fuse, &pq_typ, &qq_typ) ) {
    return _null_orth_cell(m, ham, cal, pp_typ, qp_typ, pq_typ) ||
           _null_orth_cell(m, ham, cal, pp_typ, qp_typ, qq_typ);
  }

  else if ( u4_b_pq(q_typ, u4_atom_hold, &pq_typ, &qq_typ) ) {
    u4_noun p_typ = u4_k_trel(lane, u4_atom_cell, pp_typ, qp_typ);
    u4_noun fum   = u4_k_cell(lane, p_typ, q_typ);

    if ( u4_bag_in(fum, cal) ) {
      return u4_true;
    }
    else {
      return _null_orth_cell
        (m, ham, 
            u4_bag_add(lane, fum, cal), 
            pp_typ,
            qp_typ,
            _mill_repo(m, pq_typ, qq_typ));
    }
  }
  else return _null_orth_cell
    (m, ham, cal, pp_typ, qp_typ, _mill_reap(m, q_typ));
}

/* _null_orth(): null, with double recursion control.
*/
static u4_t
_null_orth(u4_milr m,
           u4_bag  ham,
           u4_bag  cal,
           u4_type p_typ,
           u4_type q_typ)
{
  u4_lane lane = m->lane;
  u4_noun pp_typ, qp_typ;

  // u4_burp(lane, "no: p", _mill_dump(m, p_typ));
  // u4_burp(lane, "no: q", _mill_dump(m, q_typ));

  if ( u4_n_eq(u4_atom_atom, p_typ) ) {
    return _null_orth_atom(m, ham, cal, q_typ);
  }

  else if ( u4_n_eq(u4_atom_blur, p_typ) ) {
    return u4_false;
  }

  else if ( u4_b_pq(p_typ, u4_atom_cell, &pp_typ, &qp_typ) ) {
    return _null_orth_cell(m, ham, cal, pp_typ, qp_typ, q_typ);
  }

  else if ( u4_b_p(p_typ, u4_atom_cube, &pp_typ) ) {
    if ( u4_n_atom(pp_typ) ) {
      return _null_orth_plum(m, ham, cal, pp_typ, q_typ);
    }
    else return _null_orth(m, ham, cal, _mill_reap(m, p_typ), q_typ);
  }

  else if ( u4_b_pq(p_typ, u4_atom_fork, &pp_typ, &qp_typ) ) {
    return ( ( _null_main(m, ham, pp_typ) ||
               _null_orth(m, ham, cal, pp_typ, q_typ) ) &&
             ( _null_main(m, ham, qp_typ) ||
               _null_orth(m, ham, cal, qp_typ, q_typ) ) );
  }

  else if ( u4_b_pq(p_typ, u4_atom_fuse, &pp_typ, &qp_typ) ) {
    return _null_orth(m, ham, cal, pp_typ, q_typ) ||
           _null_orth(m, ham, cal, qp_typ, q_typ);
  }

  else if ( u4_b_pq(p_typ, u4_atom_hold, &pp_typ, &qp_typ) ) {
    u4_noun fum = u4_k_cell(lane, p_typ, q_typ);

    if ( u4_bag_in(fum, cal) ) {
      return u4_true;
    }
    else {
      return _null_orth
        (m, ham, 
            u4_bag_add(lane, fum, cal), 
            _mill_repo(m, pp_typ, qp_typ),
            q_typ);
    }
  }

  else return _null_orth(m, ham, cal, _mill_reap(m, p_typ), q_typ);
}

/* _null_main(): null, with recursion control.
*/
static u4_t
_null_main(u4_milr m,
           u4_bag  ham,
           u4_type typ)
{
  u4_lane lane = m->lane;
  u4_noun p_typ, q_typ;

  if ( u4_n_eq(u4_atom_atom, typ) ) {
    return u4_false;
  }
  else if ( u4_n_eq(u4_atom_blot, typ) ) {
    return u4_true;
  }
  else if ( u4_n_eq(u4_atom_blur, typ) ) {
    return u4_false;
  }
  else if ( u4_b_pq(typ, u4_atom_cell, &p_typ, &q_typ) ) {
    return _null_main(m, ham, p_typ) || _null_main(m, ham, q_typ);
  }
  else if ( u4_b_p(typ, u4_atom_cube, &p_typ) ) {
    return u4_false;
  }
  else if ( u4_b_pq(typ, u4_atom_fork, &p_typ, &q_typ) ) {
    return _null_main(m, ham, p_typ) && _null_main(m, ham, q_typ);
  }
  else if ( u4_b_pq(typ, u4_atom_fuse, &p_typ, &q_typ) ) {
    return _null_main(m, ham, p_typ) ||
           _null_main(m, ham, q_typ) ||
           _null_orth(m, ham, u4_noun_0, p_typ, q_typ);
  }
  else if ( u4_b_pq(typ, u4_atom_hold, &p_typ, &q_typ) ) {
    if ( u4_bag_in(typ, ham) ) {
      /* We can do this because we're searching conservatively.
      */
      return u4_true;
    }
    else {
      return _null_main
        (m, u4_bag_add(lane, typ, ham), _mill_repo(m, p_typ, q_typ));
    }
  }
  else return _null_main(m, ham, _mill_reap(m, typ));
}


/* _mill_null(): true if type is empty.
*/
u4_t
_mill_null(u4_milr m,
           u4_type typ)
{
  u4_nopt reb = u4_tab_get(typ, m->dam);

  if ( reb != u4_bull ) {
    return u4_n_zero(reb);
  }
  else {
    u4_t t_reb = _null_main(m, u4_noun_0, typ);

    m->dam = u4_tab_add(m->lane, typ, (t_reb ? u4_noun_0 : u4_noun_1), m->dam);
    return t_reb;
  }
}
