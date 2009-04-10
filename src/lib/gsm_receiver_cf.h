/* -*- c++ -*- */
/*
 * Copyright 2004 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */
#ifndef INCLUDED_GSM_RECEIVER_CF_H
#define INCLUDED_GSM_RECEIVER_CF_H

#include <gr_block.h>
#include <gr_complex.h>

#define BUFFER_SIZE 4096

class gsm_receiver_cf;

/*
 * We use boost::shared_ptr's instead of raw pointers for all access
 * to gr_blocks (and many other data structures).  The shared_ptr gets
 * us transparent reference counting, which greatly simplifies storage
 * management issues.  This is especially helpful in our hybrid
 * C++ / Python system.
 *
 * See http://www.boost.org/libs/smart_ptr/smart_ptr.htm
 *
 * As a convention, the _sptr suffix indicates a boost::shared_ptr
 */
typedef boost::shared_ptr<gsm_receiver_cf> gsm_receiver_cf_sptr;

/*!
 * \brief Return a shared_ptr to a new instance of gsm_receiver_cf.
 *
 * To avoid accidental use of raw pointers, gsm_receiver_cf's
 * constructor is private.  howto_make_square_ff is the public
 * interface for creating new instances.
 */
gsm_receiver_cf_sptr gsm_make_receiver_cf( int osr );

/*!
 * \brief Receives fcch
 * \ingroup block
 * \sa
 */

class gsm_receiver_cf : public gr_block
{

  private:
    int d_counter;
    int d_return;
    float d_phase_diff_buffer[BUFFER_SIZE];
    
    friend gsm_receiver_cf_sptr gsm_make_receiver_cf( int osr );
    gsm_receiver_cf( int osr );
    int find_fcch_burst( const gr_complex *in, const int items );

  public:
    ~gsm_receiver_cf();
    void forecast( int noutput_items, gr_vector_int &ninput_items_required );
    int general_work( int noutput_items,
                      gr_vector_int &ninput_items,
                      gr_vector_const_void_star &input_items,
                      gr_vector_void_star &output_items );
};

#endif /* INCLUDED_GSM_RECEIVER_CF_H */
