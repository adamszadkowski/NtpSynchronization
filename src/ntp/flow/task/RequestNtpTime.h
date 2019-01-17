#pragma once

#include <IPAddress.h>
#include <WiFiUdp.h>
#include "ntp/flow/state/SharedState.h"
#include "ntp/task/Task.h"

namespace ntp {
namespace flow {
namespace task {

class RequestNtpTime : public ntp::task::Task {
 public:
  RequestNtpTime(ntp::flow::state::SharedState* sharedState, ntp::task::TaskFactory* taskFactory);

  void executeStep() override;

 private:
  void sendNtpPacket(IPAddress& address);

 private:
  WiFiUDP& udp;
};

}  // namespace task
}  // namespace flow
}  // namespace ntp
