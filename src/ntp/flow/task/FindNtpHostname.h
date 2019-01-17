#pragma once

#include "Arduino.h"

#include "ntp/flow/state/SharedState.h"
#include "ntp/task/Task.h"

namespace ntp {
namespace flow {
namespace task {

class FindNtpHostname : public ntp::task::Task {
 public:
  FindNtpHostname(ntp::flow::state::SharedState* sharedState, ntp::task::TaskFactory* taskFactory);

  void executeStep() override;

 private:
  bool shouldRetry();

  Config& config;
};

}  // namespace task
}  // namespace flow
}  // namespace ntp
