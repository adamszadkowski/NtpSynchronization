#include "ntp/flow/task/RequestNtpTime.h"

#include <DelayedTask.h>
#include "ntp/protocol/NtpPacket.h"

namespace ntp {
namespace flow {
namespace task {

RequestNtpTime::RequestNtpTime(ntp::flow::state::SharedState* sharedState, ntp::task::TaskFactory* taskFactory)
    : Task(sharedState, taskFactory), udp(sharedState->getUDP()) {
}

void RequestNtpTime::executeStep() {
  Executor& executor = sharedState->getExecutor();
  Config& config = sharedState->getConfig();

  udp.begin(2390);
  sendNtpPacket(sharedState->getTimeServerIP());
  executor.execute(*new DelayedTask(executor, taskFactory->createAwaitNtpTimeResponseTask(), config.getFirstResponseDelay(),
                                    config.getFirstResponseDelayTimeUnit()));
}

void RequestNtpTime::sendNtpPacket(IPAddress& address) {
  ntp::protocol::NtpPacket packet = {};

  packet.leapIndicator = ntp::protocol::LeapIndicator::UNSYNCHRONIZED;
  packet.versionNumber = ntp::protocol::VersionNumber::VERSION_4;
  packet.mode = ntp::protocol::Mode::CLIENT;
  packet.poll = 6;
  packet.stratum = ntp::protocol::Stratum::UNSPECIFIED;
  packet.precision = -2;
  packet.referenceIdentifier[0] = 'L';
  packet.referenceIdentifier[1] = 'O';
  packet.referenceIdentifier[2] = 'C';
  packet.referenceIdentifier[3] = 'L';

  udp.beginPacket(address, 123);
  udp.write(reinterpret_cast<uint8_t*>(&packet), sizeof(packet));
  udp.endPacket();
}

}  // namespace task
}  // namespace flow
}  // namespace ntp
