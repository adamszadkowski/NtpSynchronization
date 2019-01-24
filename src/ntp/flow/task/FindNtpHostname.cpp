#include "ntp/flow/task/FindNtpHostname.h"

#include <DelayedTask.h>
#include <ESP8266WiFi.h>

namespace ntp {
namespace flow {
namespace task {

FindNtpHostname::FindNtpHostname(ntp::flow::state::SharedState* sharedState, ntp::task::TaskFactory* taskFactory)
    : Task(sharedState, taskFactory), config(sharedState->getConfig()) {
}

void FindNtpHostname::executeStep() {
  Executor& executor = sharedState->getExecutor();

  int result = WiFi.hostByName(config.getHostname().c_str(), sharedState->getTimeServerIP());
  if (result == 1) {
    executor.execute(taskFactory->createRequestNtpTimeTask());
  } else if (shouldRetry()) {
    executor.executeWithDelay(taskFactory->createFindNtpHostnameTask(), config.getHostResolutionRetryDelay(),
                              config.getHostResolutionRetryDelayTimeUnit());
  } else {
    executor.execute(sharedState->getFailTask());
  }

  sharedState->incrementResolveNameAttempt();
}

bool FindNtpHostname::shouldRetry() {
  return sharedState->getResolveNameAttempt() < config.getMaxResolveNameAttempts();
}

}  // namespace task
}  // namespace flow
}  // namespace ntp
