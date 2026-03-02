#include <c10/util/ParallelGuard.h>

namespace c10 {

thread_local static bool in_at_parallel =
    false; // set in both serial and parallel paths
thread_local static bool in_parallel_path =
    false; // set only in the parallel path

bool ParallelGuard::is_enabled() {
  return in_at_parallel;
}

bool ParallelPathGuard::is_active() {
  return in_parallel_path;
}

ParallelGuard::ParallelGuard(bool state) : previous_state_(is_enabled()) {
  in_at_parallel = state;
}

ParallelGuard::~ParallelGuard() {
  in_at_parallel = previous_state_;
}

ParallelPathGuard::ParallelPathGuard() : previous_state_(in_parallel_path) {
  in_parallel_path = true;
}

ParallelPathGuard::~ParallelPathGuard() {
  in_parallel_path = previous_state_;
}

} // namespace c10
