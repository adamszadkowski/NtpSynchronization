#pragma once

#include <Runnable.h>
#include "ntp/flow/state/SharedState.h"
#include "ntp/task/TaskFactory.h"

namespace ntp {
namespace task {

class Task : public Runnable {
 public:
  Task(ntp::flow::state::SharedState* sharedState, TaskFactory* taskFactory) : sharedState(sharedState), taskFactory(taskFactory) {
  }

  void run() final {
    executeStep();
    delete this;
  }

  virtual void executeStep() = 0;

 protected:
  ntp::flow::state::SharedState* sharedState;
  TaskFactory* taskFactory;
};

}  // namespace task
}  // namespace ntp
