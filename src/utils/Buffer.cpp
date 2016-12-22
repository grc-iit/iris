/******************************************************************************
*include files
******************************************************************************/
#include "Buffer.h"
/******************************************************************************
*Constructors
******************************************************************************/
inline Buffer::Buffer(void *data)
{
  if(data != nullptr) data_ = (char *) data;
}

inline Buffer::Buffer(size_type s)
    :free_(true)
{
  if(s != 0) data_ = new char[s];
  else data_ = 0;
  size_ = capacity_ = s;
}

inline Buffer::Buffer(size_type s, size_type c)
    : free_(true)
{
  if(s > c)
    throw std::invalid_argument("size greater than capacity");

  if(s != 0) data_ = new char[s];
  else data_ = 0;
  size_ = s;
  capacity_ = c;
}

inline Buffer::Buffer(const void* d, size_type s)
    : free_(true)
{
  if(s != 0)
  {
    data_ = new char[s];
    std::memcpy (data_, d, s);
  }
  else data_ = 0;
  size_ = capacity_ = s;
}

inline Buffer::Buffer(const void* d, size_type s, size_type c)
    : free_(true)
{
  if(s > c)
    throw std::invalid_argument("size greater than capacity");

  if(c != 0)
  {
    data_ = new char[c];

    if(s != 0)
      std::memcpy(data_, d, s);
  }
  else data_ = 0;
  size_ = s;
  capacity_ = c;
}

inline Buffer::Buffer(void* d, size_type s, size_type c, bool own)
    : data_(static_cast<char*> (d)), size_(s), capacity_(c), free_(own)
{
  if(s > c)
    throw std::invalid_argument("size greater than capacity");
}

inline Buffer::Buffer(const Buffer& x)
    : free_(true)
{
  if(x.capacity_ != 0)
  {
    data_ = new char[x.capacity_];

    if(x.size_ != 0)
      std::memcpy (data_, x.data_, x.size_);
  }
  else data_ = 0;
  size_ = x.size_;
  capacity_ = x.capacity_;
}
/******************************************************************************
*Destructor
******************************************************************************/
inline Buffer::~Buffer()
{
  if(free_)
    delete[] data_;
}
/******************************************************************************
*Interface
******************************************************************************/
inline Buffer& Buffer::operator= (const Buffer& x)
{
  if(&x != this)
  {
    if(x.size_ > capacity_)
    {
      if(free_) delete[] data_;
      data_ = new char[x.capacity_];
      capacity_ = x.capacity_;
      free_ = true;
    }
    if(x.size_ != 0) std::memcpy (data_, x.data_, x.size_);
    size_ = x.size_;
  }
  return *this;
}

inline void Buffer::swap(Buffer& x)
{
  char* d(x.data_);
  size_type s(x.size_);
  size_type c(x.capacity_);
  bool f(x.free_);

  x.data_ = data_;
  x.size_ = size_;
  x.capacity_ = capacity_;
  x.free_ = free_;

  data_ = d;
  size_ = s;
  capacity_ = c;
  free_ = f;
}

inline char* Buffer::detach()
{
  char* r(data_);
  data_ = 0;
  size_ = 0;
  capacity_ = 0;

  return r;
}

inline void Buffer::assign(const void* d, size_type s)
{
  if(s > capacity_)
  {
    if(free_) delete[] data_;
    data_ = new char[s];
    capacity_ = s;
    free_ = true;
  }
  if(s != 0) std::memcpy (data_, d, s);
  size_ = s;
}

inline void Buffer::assign(void* d, size_type s, size_type c, bool own)
{
  if(free_) delete[] data_;
  data_ = static_cast<char*>(d);
  size_ = s;
  capacity_ = c;
  free_ = own;
}

inline void Buffer::append(const Buffer& b)
{
  append(b.data(), b.size());
}

inline void Buffer::append(const void* d, size_type s)
{
  if(s != 0)
  {
    size_type newsize(size_ + s);

    if(capacity_ < newsize) capacity (newsize);
    //TODO: replacement policies instead of resizing
    std::memcpy(data_ + size_, d, s);
    size_ = newsize;
  }
}

inline void Buffer::fill(char v)
{
  if(size_ > 0) std::memset(data_, v, size_);
}

inline Buffer::size_type Buffer::size() const
{
  return size_;
}

inline bool Buffer::size(size_type s)
{
  bool r(false);

  if (capacity_ < s) r = capacity(s);
  size_ = s;
  return r;
}

inline Buffer::size_type Buffer::capacity() const
{
  return capacity_;
}

inline bool Buffer::capacity(size_type c)
{
  // Ignore capacity decrease requests.
  //
  if(capacity_ >= c) return false;

  char* d(new char[c]);

  if(size_ != 0) std::memcpy (d, data_, size_);

  if(free_) delete[] data_;
  data_ = d;
  capacity_ = c;
  free_ = true;

  return true;
}

inline bool Buffer::empty () const
{
  return size_ == 0;
}

inline void Buffer::clear ()
{
  size_ = 0;
}

inline char* Buffer::data ()
{
  return data_;
}

inline const char* Buffer::data () const
{
  return data_;
}

inline char& Buffer::operator[] (size_type i)
{
  return data_[i];
}

inline char Buffer::operator[] (size_type i) const
{
  return data_[i];
}

inline char& Buffer::at (size_type i)
{
  if (i >= size_)
    throw std::out_of_range ("index out of range");

  return data_[i];
}

inline char Buffer::at (size_type i) const
{
  if (i >= size_)
    throw std::out_of_range ("index out of range");

  return data_[i];
}

inline Buffer::size_type Buffer::find (char v, size_type pos) const
{
  if (size_ == 0 || pos >= size_)
    return npos;

  char* p (static_cast<char*> (std::memchr (data_ + pos, v, size_ - pos)));
  return p != 0 ? static_cast<size_type> (p - data_) : npos;
}

inline Buffer::size_type Buffer::rfind (char v, size_type pos) const
{
  // memrchr() is not standard.
  //
  if (size_ != 0)
  {
    size_type n (size_);

    if (--n > pos)
      n = pos;

    for (++n; n-- != 0; )
      if (data_[n] == v)
        return n;
  }

  return npos;
}

/******************************************************************************
*Operators
******************************************************************************/
inline bool operator== (const Buffer& a, const Buffer& b)
{
  return a.size () == b.size () &&
         std::memcmp (a.data (), b.data (), a.size ()) == 0;
}

inline bool operator!= (const Buffer& a, const Buffer& b)
{
  return !(a == b);
}
