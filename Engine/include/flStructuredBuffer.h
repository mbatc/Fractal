#pragma once

#include "flHardwareBuffer.h"
#include "flRef.h"

#include <vector>

namespace Fractal
{
  template<typename T>
  class StructuredBuffer : public T
  {
  public:
    template<typename... Args>
    StructuredBuffer(HardwareBuffer *pBuffer, int64_t count = 1)
      : m_pBuffer(MakeRef(pBuffer, true))
    {
      Resize(count);
    }

    void Upload() const {
      m_pBuffer->Set(m_data.data(), sizeof(T) * m_data.size());
    }

    void Download() {
      m_data.resize(m_pBuffer->GetSize() / sizeof(T));
      m_pBuffer->Get(m_data.data(), sizeof(T) * m_data.size());
    }

    void Resize(const int64_t &count) { m_data.resize(count); }
    void Resize(const int64_t &count, const T &initialValue) { m_data.resize(count, initialValue); }
    void PushBack(T item)  { m_data.push_back(std::move(item));  }
    void PushFront(T item) { m_data.push_front(std::move(item)); }
    void PopBack()  { m_data.pop_back();  }
    void PopFront() { m_data.pop_front(); }

    void Insert(const int64_t &index, const T &item) { m_data.insert(m_data.begin() + index, item); }
    void Erase(const int64_t &index) { m_data.erase(m_data.begin() + index); }

    T *operator->() { return m_data.data(); }
    T &operator* () { return *m_data.data(); }

    T const *operator->() const { return m_data.data(); }
    T const &operator* () const { return *m_data.data(); }

    T &operator[](const int64_t &index) { return m_data[index]; }
    T const &operator[](const int64_t &index) const { return m_data[index]; }

    T *begin() { return m_data.begin(); }
    T *end()   { return m_data.end(); }

    T const *begin() const { return m_data.begin(); }
    T const *end() const   { return m_data.end(); }

  private:
    Ref<HardwareBuffer> m_pBuffer;
    std::vector<T> m_data;
  };
}