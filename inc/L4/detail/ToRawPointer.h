#pragma once


namespace L4 {
namespace Detail {

// #include <boost/interprocess/detail/utilities.hpp>
// using boost::interprocess::ipcdetail::to_raw_pointer;

// The following subset of functions are copied over from the above header file
// (or further includes) and are the minimum required ones to get L4 working
// without pulling boost sources in entirety.

#define L4_MAYBE_INLINE 

template<class RawPointer>
class pointer_uintptr_caster;

template<class T>
class pointer_uintptr_caster<T*>
{
   public:
   L4_MAYBE_INLINE explicit pointer_uintptr_caster(uintptr_t sz)
      : m_uintptr(sz)
   {}

   L4_MAYBE_INLINE explicit pointer_uintptr_caster(const volatile T *p)
      : m_uintptr(reinterpret_cast<uintptr_t>(p))
   {}

   L4_MAYBE_INLINE uintptr_t uintptr() const
   {   return m_uintptr;   }

   L4_MAYBE_INLINE T* pointer() const
   {   return reinterpret_cast<T*>(m_uintptr);   }

   private:
   uintptr_t m_uintptr;
};

template<class RawPointer>
class pointer_size_t_caster
{
   public:
   explicit pointer_size_t_caster(std::size_t sz)
      : m_ptr(reinterpret_cast<RawPointer>(sz))
   {}

   explicit pointer_size_t_caster(RawPointer p)
      : m_ptr(p)
   {}

   std::size_t size() const
   {   return reinterpret_cast<std::size_t>(m_ptr);   }

   RawPointer pointer() const
   {   return m_ptr;   }

   private:
   RawPointer m_ptr;
};


template<class RawPointer, class OffsetType>
class pointer_offset_caster;

template<class T, class OffsetType>
class pointer_offset_caster<T*, OffsetType>
{
   public:
   L4_MAYBE_INLINE explicit pointer_offset_caster(OffsetType offset)
      : m_offset(offset)
   {}

   L4_MAYBE_INLINE explicit pointer_offset_caster(const volatile T *p)
      : m_offset(reinterpret_cast<OffsetType>(p))
   {}

   L4_MAYBE_INLINE OffsetType offset() const
   {   return m_offset;   }

   L4_MAYBE_INLINE T* pointer() const
   {   return reinterpret_cast<T*>(m_offset);   }

   private:
   OffsetType m_offset;
};



#define BOOST_INTERPROCESS_OFFSET_PTR_BRANCHLESS_TO_PTR
template <class OffsetType>
L4_MAYBE_INLINE void *offset_ptr_to_raw_pointer(const volatile void *this_ptr, OffsetType offset) {
  typedef pointer_offset_caster<void *, OffsetType> caster_t;
#ifndef BOOST_INTERPROCESS_OFFSET_PTR_BRANCHLESS_TO_PTR
  if (offset == 1) {
    return 0;
  } else {
    return caster_t(caster_t(this_ptr).offset() + offset).pointer();
  }
#else
  OffsetType mask = offset == 1;
  --mask;
  OffsetType target_offset = caster_t(this_ptr).offset() + offset;
  target_offset &= mask;
  return caster_t(target_offset).pointer();
#endif
}


template <class T>
L4_MAYBE_INLINE T* to_raw_pointer(T* p)
{  return p; }

template<class T>
L4_MAYBE_INLINE std::size_t offset_ptr_to_offset(const volatile void *ptr, const volatile void *this_ptr)
{
   typedef pointer_size_t_caster<void*> caster_t;
   #ifndef BOOST_INTERPROCESS_OFFSET_PTR_BRANCHLESS_TO_OFF
      //offset == 1 && ptr != 0 is not legal for this pointer
      if(!ptr){
         return 1;
      }
      else{
         caster_t this_caster((void*)this_ptr);
         caster_t ptr_caster((void*)ptr);
         std::size_t offset = ptr_caster.size() - this_caster.size();
         assert(offset != 1);
         return offset;
      }
   #else
      caster_t this_caster((void*)this_ptr);
      caster_t ptr_caster((void*)ptr);
      std::size_t offset = (ptr_caster.size() - this_caster.size() - 1) & -std::size_t(ptr != 0);
      ++offset;
      return offset;
   #endif
}




}  // namespace Detail
}  // namespace L4
