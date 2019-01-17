#include "ntp/flow/task/AwaitNtpTimeResponse.h"

#include <DelayedTask.h>

namespace ntp {
namespace flow {
namespace task {

AwaitNtpTimeResponse::AwaitNtpTimeResponse(ntp::flow::state::SharedState* sharedState, ntp::task::TaskFactory* taskFactory)
    : Task(sharedState, taskFactory), config(sharedState->getConfig()), udp(sharedState->getUDP()) {
}

void AwaitNtpTimeResponse::executeStep() {
  Executor& executor = sharedState->getExecutor();

  if (hasReceivedUdpPacket()) {
    executor.execute(taskFactory->createSynchronizeTimeTask());
  } else if (shouldRetry()) {
    executor.execute(*new DelayedTask(executor, taskFactory->createAwaitNtpTimeResponseTask(), config.getAwaitResponseRetryDelay(),
                                      config.getAwaitResponseRetryDelayTimeUnit()));
  } else {
    udp.stop();
    executor.execute(sharedState->getFailTask());
  }

  sharedState->incrementAwaitResponseAttempt();
}

bool AwaitNtpTimeResponse::hasReceivedUdpPacket() {
  return 0 != udp.parsePacket();
}

bool AwaitNtpTimeResponse::shouldRetry() {
  return sharedState->getAwaitResponseAttempt() < config.getMaxAwaitResponseAttempts();
}

}  // namespace task
}  // namespace flow
}  // namespace ntp
