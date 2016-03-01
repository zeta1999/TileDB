/**
 * @file   fragment.h
 * @author Stavros Papadopoulos <stavrosp@csail.mit.edu>
 *
 * @section LICENSE
 *
 * The MIT License
 *
 * @copyright Copyright (c) 2015 Stavros Papadopoulos <stavrosp@csail.mit.edu>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 * @section DESCRIPTION
 *
 * This file defines class Fragment. 
 */

#ifndef __FRAGMENT_H__
#define __FRAGMENT_H__

#include "array.h"
#include "array_schema.h"
#include "book_keeping.h"
#include "constants.h"
#include "read_state.h"
#include "write_state.h"
#include <vector>

/* ********************************* */
/*             CONSTANTS             */
/* ********************************* */

#define TILEDB_FG_OK     0
#define TILEDB_FG_ERR   -1

class Array;
class BookKeeping;
class ReadState;
class WriteState;

/** Contains information about an array fragment. */
class Fragment {
 public:
  // TYPE DEFINITIONS

  // TODO
  typedef std::pair<int64_t, int64_t> CellPosRange;
  // TODO
  typedef std::pair<int, CellPosRange> FragmentCellPosRange;
  // TODO
  typedef std::vector<FragmentCellPosRange> FragmentCellPosRanges;
  // TODO
  typedef std::pair<int, void*> FragmentCellRange;
  // TODO
  typedef std::vector<FragmentCellRange> FragmentCellRanges;

  // CONSTRUCTORS & DESTRUCTORS
  
  /** 
   * Constructor. 
   *
   * @param array The array the fragment belongs to.
   */
  Fragment(const Array* array);
  /** Destructor. */
  ~Fragment();

  // ACCESSORS
  
  /** Returns the array the fragment belongs to. */
  const Array* array() const;

  // TODO
  int64_t cell_num_per_tile() const;

  /** Returns true if the fragment is dense, and false if it is sparse. */
  bool dense() const;

  /** Returns the fragment name. */
  const std::string& fragment_name() const;

  // TODO
  template<class T>
  void compute_fragment_cell_ranges(
      int fragment_i,
      FragmentCellRanges& fragment_cell_ranges) const;

  // TODO
  const void* get_global_tile_coords() const;

  // TODO
  int read(void** buffers, size_t* buffer_sizes);

  // TODO
  bool overflow(int attribute_id) const;

  // TODO
  size_t tile_size(int attribute_id) const;

  // TODO
  ReadState* read_state() const;

  // TODO
  template<class T>
  bool max_overlap(const T* max_overlap_range) const;

  // TODO
  template<class T>
  int copy_cell_range(
      int attribute_id,
      void* buffer,
      size_t buffer_size,
      size_t& buffer_offset,
      const CellPosRange& cell_pos_range);

  //MUTATORS

  // TODO
  template<class T>
  bool coords_exist(const T* coords);

  // TODO
  void tile_done(int attribute_id);

  // TODO
  void reset_overflow();

  /**
   * Computes the next tile that overlaps with the range given in Array::init.
   * Applicable only when the read is applied on multipled fragments.
   *
   * @return void 
   */
  void get_next_overlapping_tile_mult();

// TODO
  template<class T>
  int get_cell_pos_ranges_sparse(
      int fragment_i,
      const T* tile_domain,
      const T* cell_range,
      FragmentCellPosRanges& fragment_cell_pos_ranges);

  // TODO
  template<class T>
  int get_first_two_coords(
      T* start_coords,
      T* first_coords,
      T* second_coords);

  // TODO
  int init(const std::string& fragment_name, const void* range);

  // TODO
  int write(const void** buffers, const size_t* buffer_sizes);

  // MISC
  
  // TODO
  int finalize();
 
 private:
  // PRIVATE ATTRIBUTES
  /** The array the fragment belongs to. */
  const Array* array_;
  /** A book-keeping structure. */
  BookKeeping* book_keeping_;
  // TODO
  bool dense_;
  /** The fragment name. */
  std::string fragment_name_;
  /** True if this fragment covers the full array domain. */
  bool full_domain_;
  /** A read state structure. */
  ReadState* read_state_;
  /** A write state structure. */
  WriteState* write_state_;

  // PRIVATE METHODS
  /** 
   * Changes the temporary fragment name into a stable one.
   *
   * @return TILEDB_FG_OK for success, and TILEDB_FG_ERR for error.
   */
  int rename_fragment();
};

#endif
