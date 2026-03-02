#pragma once

#include <c10/macros/Macros.h>

namespace c10 {

// RAII thread local guard that tracks whether code is being executed in
// `at::parallel_for` or `at::parallel_reduce` loop function.
class C10_API ParallelGuard {
 public:
  static bool is_enabled();

  ParallelGuard(bool state);
  ~ParallelGuard();

 private:
  bool previous_state_;
};

// RAII guard that marks the calling thread as executing the parallel path of
// parallel_for/parallel_reduce. Unlike ParallelGuard (set in both serial and
// parallel paths for COW checks), this is set ONLY in the parallel path so
// that at::in_parallel_region() correctly returns false in serial fallbacks.
class C10_API ParallelPathGuard {
 public:
  static bool is_active();
  ParallelPathGuard();
  ~ParallelPathGuard();

 private:
  bool previous_state_;
};

} // namespace c10
