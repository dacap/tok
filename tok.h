// tok
// Copyright (c) 2020 David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#ifndef TOK_H_INCLUDED
#define TOK_H_INCLUDED

#include <iterator>
#include <string>

namespace tok {

struct ignore_empties { enum { allow_empty = false }; };
struct include_empties { enum { allow_empty = true }; };

template<typename T, typename EmptyPolicy>
class token_iterator {
public:
  using iterator_category = std::forward_iterator_tag;
  using internal_iterator = typename T::const_iterator;
  using char_type = typename T::value_type;
  using value_type = typename std::remove_const<T>::type;
  using difference_type = typename T::difference_type;
  using pointer = T*;
  using reference = T&;
  using const_reference = const T&;

  token_iterator() = delete;
  token_iterator(const token_iterator&) = default;
  token_iterator(const internal_iterator& begin,
                 const internal_iterator& end,
                 char_type chr) :
    begin_(begin),
    inter_(begin),
    end_(end),
    chr_(chr) {
    operator++(); // Find first word to fill "str_" field
  }

  token_iterator& operator++() {
    if (EmptyPolicy::allow_empty) {
      if (inter_ != end_ && *inter_ == chr_) {
        ++inter_;
      }
    }
    else {
      while (inter_ != end_ && *inter_ == chr_) {
        ++inter_;
      }
    }
    begin_ = inter_;
    while (inter_ != end_ && *inter_ != chr_) {
      ++inter_;
    }
    str_ = T(begin_, inter_);
    return *this;
  }

  const_reference operator*() {
    return str_;
  }

  bool operator!=(const token_iterator& that) const {
    return (begin_ != that.end_);
  }

private:
  internal_iterator begin_, inter_, end_;
  char_type chr_;
  value_type str_;
};

template<typename T, typename Empties>
class token_range {
public:
  using char_type = typename T::value_type;
  using iterator = token_iterator<T, Empties>;

  token_range(const T& str, char_type chr) : str_(str), chr_(chr) { }

  iterator begin() const { return iterator(str_.begin(), str_.end(), chr_); }
  iterator end() const { return iterator(str_.end(), str_.end(), chr_); }

private:
  const T& str_;
  char_type chr_;
};

template<typename T>
token_range<T, ignore_empties>
split_tokens(const T& str,
             typename T::value_type chr) {
  return token_range<T, ignore_empties>(str, chr);
}

template<typename T>
token_range<T, include_empties>
csv(const T& str,
    typename T::value_type chr = ',') {
  return token_range<T, include_empties>(str, chr);
}

} // namespace tok

#endif
