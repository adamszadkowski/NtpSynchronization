#include "ntp/flow/task/SynchronizeTime.h"

#include <ESP8266WiFi.h>
#include <TimeLib.h>
#include "ntp/protocol/NtpPacket.h"

namespace ntp {
namespace flow {
namespace task {

SynchronizeTime::SynchronizeTime(ntp::flow::state::SharedState* sharedState, ntp::task::TaskFactory* taskFactory)
    : Task(sharedState, taskFactory) {
}

void SynchronizeTime::executeStep() {
  WiFiUDP& udp = sharedState->getUDP();
  ntp::protocol::NtpPacket packet;
  udp.read(reinterpret_cast<uint8_t*>(&packet), sizeof(packet));

  unsigned long secsSince1900 = ntohl(packet.transmitTimestampSeconds);
  const unsigned long seventyYears = 2208988800UL;
  time_t epoch = secsSince1900 - seventyYears;

  setTime(epoch);

  udp.stop();
  Executor& executor = sharedState->getExecutor();
  executor.execute(sharedState->getSuccessTask());
}

}  // namespace task
}  // namespace flow
}  // namespace ntp
