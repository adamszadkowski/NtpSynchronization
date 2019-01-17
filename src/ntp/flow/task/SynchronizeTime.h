#pragma once

#include "ntp/flow/state/SharedState.h"
#include "ntp/task/Task.h"

namespace ntp {
namespace flow {
namespace task {

class SynchronizeTime : public ntp::task::Task {
 public:
  SynchronizeTime(ntp::flow::state::SharedState* sharedState, ntp::task::TaskFactory* taskFactory);

  void executeStep() override;
};

}  // namespace task
}  // namespace flow
}  // namespace ntp
