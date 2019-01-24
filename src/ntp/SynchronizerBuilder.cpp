#include "ntp/SynchronizerBuilder.h"

#include <NullTask.h>
#include "ntp/StartingTask.h"
#include "ntp/flow/state/SharedState.h"
#include "ntp/task/TaskFactory.h"

namespace ntp {

SynchronizerBuilder::SynchronizerBuilder() {
  executor = &::executor;
  successTask = []() {};
  failTask = []() {};
}

SynchronizerBuilder& SynchronizerBuilder::withExecutor(Executor& executor) {
  SynchronizerBuilder::executor = &executor;
  return *this;
}

SynchronizerBuilder& SynchronizerBuilder::withConfig(Config& config) {
  SynchronizerBuilder::config = &config;
  return *this;
}

SynchronizerBuilder& SynchronizerBuilder::withSuccessTask(Command successTask) {
  SynchronizerBuilder::successTask = successTask;
  return *this;
}

SynchronizerBuilder& SynchronizerBuilder::withFailTask(Command failTask) {
  SynchronizerBuilder::failTask = failTask;
  return *this;
}

Runnable* SynchronizerBuilder::build() {
  ntp::flow::state::SharedState* state = new ntp::flow::state::SharedState(*executor, *config, successTask, failTask);
  ntp::task::TaskFactory* taskFactory = new ntp::task::TaskFactory(state);

  return new ntp::StartingTask(state, taskFactory);
}

}  // namespace ntp
