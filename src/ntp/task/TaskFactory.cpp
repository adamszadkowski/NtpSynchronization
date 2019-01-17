#include "ntp/task/TaskFactory.h"

#include "ntp/flow/task/AwaitNtpTimeResponse.h"
#include "ntp/flow/task/FindNtpHostname.h"
#include "ntp/flow/task/RequestNtpTime.h"
#include "ntp/flow/task/SynchronizeTime.h"

namespace ntp {
namespace task {

TaskFactory::TaskFactory(ntp::flow::state::SharedState* sharedState) : sharedState(sharedState) {
}

Runnable& TaskFactory::createFindNtpHostnameTask() {
  return *new ntp::flow::task::FindNtpHostname(sharedState, this);
}

Runnable& TaskFactory::createRequestNtpTimeTask() {
  return *new ntp::flow::task::RequestNtpTime(sharedState, this);
}

Runnable& TaskFactory::createAwaitNtpTimeResponseTask() {
  return *new ntp::flow::task::AwaitNtpTimeResponse(sharedState, this);
}

Runnable& TaskFactory::createSynchronizeTimeTask() {
  return *new ntp::flow::task::SynchronizeTime(sharedState, this);
}

}  // namespace task
}  // namespace ntp
