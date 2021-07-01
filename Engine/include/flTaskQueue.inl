
template<typename T, typename... Args>
inline bool Fractal::TaskQueue::Add(flIN Args&&... args)
{
  T *pTask = T::Create(std::forward<Args>(args)...);
  bool result = Add(pTask);
  pTask->DecRef();
  return result;
}
