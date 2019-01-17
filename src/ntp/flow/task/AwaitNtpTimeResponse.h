#pragma once

#include "ntp/flow/state/SharedState.h"
#include "ntp/task/Task.h"

namespace ntp {
namespace flow {
namespace task {

class AwaitNtpTimeResponse : public ntp::task::Task {
 public:
  AwaitNtpTimeResponse(ntp::flow::state::SharedState* sharedState, ntp::task::TaskFactory* taskFactory);

  void executeStep() override;

 private:
  bool hasReceivedUdpPacket();
  bool shouldRetry();

  Config& config;
  WiFiUDP& udp;
};

}  // namespace task
}  // namespace flow
}  // namespace ntp
