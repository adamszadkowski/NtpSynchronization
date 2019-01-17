#pragma once

#include <Runnable.h>
#include "ntp/flow/state/SharedState.h"
#include "ntp/task/TaskFactory.h"

namespace ntp {

class StartingTask : public Runnable {
 public:
  StartingTask(ntp::flow::state::SharedState* sharedState, ntp::task::TaskFactory* taskFactory)
      : sharedState(sharedState), taskFactory(taskFactory) {
  }

  ~StartingTask() override {
    delete taskFactory;
    delete sharedState;
  }

  void run() override {
    sharedState->clear();
    taskFactory->createFindNtpHostnameTask().run();
  }

 private:
  ntp::flow::state::SharedState* sharedState;
  ntp::task::TaskFactory* taskFactory;
};

}  // namespace ntp
