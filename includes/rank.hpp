#ifndef RANK_BV
#define RANK_BV

#include <sdsl/bit_vectors.hpp>
#include <sdsl/int_vector_buffer.hpp>

using namespace sdsl;
using namespace std;


class rank_bv_64
{
    uint32_t* block;
    uint64_t u;  //bit vector length
    uint64_t n; // # ones
    uint64_t nw; // number of 64-bit words in array seq

public:
    rank_bv_64() = default;
    uint64_t* seq;

    rank_bv_64(bit_vector &bv)
    {
        uint64_t i;
        uint8_t byte_mask;
        uint32_t cur_word = 0, count = 0;

        u = bv.size();

        seq = new uint64_t[(u+63)/64]();
        block = new uint32_t[(u+63)/64]();
        nw = (u+63)/64;

        for (i = 0; i < u; ++i) {

            if (i%64 == 0)
                block[cur_word++] = count;

            if (bv[i]) {
                count++;
                seq[i/64] |= (1L<<(i%64));
            }
            else
                seq[i/64] &= ~(1L<<(i%64));

        }
        n = count;
    }

    rank_bv_64(vector<uint64_t> _bv)
    {
        u = _bv[_bv.size() - 1] + 1; //last element
        n = _bv.size(); // each element  is a position with a 1
        nw = (u+63)/64;

        bit_vector bv = bit_vector(u, 0);
        // for each 1 in _bv, we mark it in bv
        for (int i = 0;  i < n; i++) {
            bv[_bv[i]] = 1;
        }

        uint64_t i;
        uint8_t byte_mask;
        uint32_t cur_word = 0, count = 0;

        seq = new uint64_t[(u+63)/64]();
        block = new uint32_t[(u+63)/64]();

        for (i = 0; i < u; ++i) {

            if (i%64 == 0)
                block[cur_word++] = count;

            if (bv[i]) {
                count++;
                seq[i/64] |= (1L<<(i%64));
            }
            else
                seq[i/64] &= ~(1L<<(i%64));
        }
    }

    inline uint64_t rank(uint64_t i)
    {
        return block[i>>6] + bits::cnt(seq[i>>6] & ~(0xffffffffffffffff << (i&0x3f)));
    }

    // Given a position i, returns the position of the next 1 in the bit vector
    // returns u if there is no next 1
    uint64_t select_next(uint64_t i)
    {
        uint64_t t = seq[i/64] & (0xffffffffffffffff << ((i%64)));

        if (t) {
            return bits::lo(t) + i - (i%64);
        } else {
            uint64_t j = i/64;
            while (++j < nw && !seq[j]);
            if (j == nw) return u; // there is no next 1
            cout << "el bit siguiente  " << bits::lo(seq[j]) + j*64 << endl;
            return bits::lo(seq[j]) + j*64;
        }
    }

    uint64_t select_next_active(uint64_t i, rank_bv_64 active)
    {

        uint64_t t = (seq[i/64] & active.seq[i/64]) & (0xffffffffffffffff << (i%64));

        if (t) {
            return bits::lo(t) + i - (i%64);
        } else {
            uint64_t j = i/64;
            while (++j < nw && !(seq[j] & active.seq[j]));
            if (j == nw) return u; // there is no next 1
            return bits::lo(seq[j] & active.seq[j]) + j*64;
        }
    }

    inline uint8_t get_4_bits(uint64_t start_pos)
    {
        return ((seq[start_pos >> 6] >>(start_pos & 0x3f) ) & 0x0f);
    }

    inline uint8_t get_2_bits(uint64_t start_pos)
    {
        return ((seq[start_pos >> 6] >>(start_pos & 0x3f) ) & 0x03);
    }

    // number of bits in the bv
    inline uint64_t size()
    {
        return u;
    }

    inline uint64_t n_ones()
    {
        return n;
    }

    inline uint64_t size_in_bytes()
    {
        return sizeof(uint64_t)*((u+63)/64) + sizeof(uint32_t)*(u+63)/64
               + sizeof(uint64_t*) + sizeof(uint32_t*)
               + 2*sizeof(uint64_t);
    }


    uint32_t get_bits(uint64_t start_pos, k2_tree_ns::size_type dim)
    {

        switch (dim){
            case 2:
                return ((seq[start_pos >> 6] >>(start_pos & 0x3f) ) & 0x03);
                break;
            case 4:
                return ((seq[start_pos >> 6] >>(start_pos & 0x3f) ) & 0x0f);
                break;
            case 8:
                return ((seq[start_pos >> 6] >>(start_pos & 0x3f) ) & 0xff);
                break;
            case 16:
                return ((seq[start_pos >> 6] >>(start_pos & 0x3f) ) & 0xffff);
                break;
            case 32:

                return((seq[start_pos >> 6] >>(start_pos & 0x3f) ) & 0xffffffff);
                break;

        }
        /*for (int l = 0; l < dim; l++)
        {
            cout << ((x & (1 << l)) ? "1" : "0");
        }
        cout << " ";*/
    }

    void bv_and(rank_bv_64 bv){
        seq[0] &= *bv.seq;
    }

};

#endif
