#pragma once

#include <Runnable.h>
#include "ntp/flow/state/SharedState.h"

namespace ntp {
namespace task {

class TaskFactory {
 public:
  TaskFactory(ntp::flow::state::SharedState* sharedState);

  Runnable& createFindNtpHostnameTask();
  Runnable& createRequestNtpTimeTask();
  Runnable& createAwaitNtpTimeResponseTask();
  Runnable& createSynchronizeTimeTask();

 private:
  ntp::flow::state::SharedState* sharedState;
};

}  // namespace task
}  // namespace ntp
