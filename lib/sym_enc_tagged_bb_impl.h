/* -*- c++ -*- */
/* 
 * Copyright 2016 Kristian Maier.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_CRYPTO_SYM_ENC_TAGGED_BB_IMPL_H
#define INCLUDED_CRYPTO_SYM_ENC_TAGGED_BB_IMPL_H

#include <crypto/sym_enc_tagged_bb.h>
#include <crypto/sym_ciph_desc.h>
#include <stdexcept>


namespace gr {
    namespace crypto {

        class sym_enc_tagged_bb_impl : public sym_enc_tagged_bb {
        private:
            const EVP_CIPHER *d_ciph;
            EVP_CIPHER_CTX *d_ciph_ctx;
            bool d_padding;
            unsigned long d_ctr;

            std::vector<uint8_t > d_key;
            std::vector<uint8_t> d_iv;

            pmt::pmt_t d_iv_tagkey;
            pmt::pmt_t d_final_tagkey;

            void init_ctx();

        protected:
            int calculate_output_stream_length(const gr_vector_int &ninput_items);

        public:
            sym_enc_tagged_bb_impl(sym_ciph_desc &ciph_desc, const std::string &packet_len_key);
            ~sym_enc_tagged_bb_impl();

            void get_iv(std::vector<uint8_t> &iv) { iv = d_iv; }

            int work(int noutput_items,
                     gr_vector_int &ninput_items,
                     gr_vector_const_void_star &input_items,
                     gr_vector_void_star &output_items);
        };

    } // namespace crypto
} // namespace gr

#endif /* INCLUDED_CRYPTO_SYM_ENC_TAGGED_BB_IMPL_H */

