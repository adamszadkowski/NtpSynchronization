#pragma once

#include <Command.h>
#include <Executor.h>
#include <Runnable.h>
#include "ntp/Config.h"

namespace ntp {

class SynchronizerBuilder {
 public:
  SynchronizerBuilder();

  SynchronizerBuilder& withExecutor(Executor& executor);
  SynchronizerBuilder& withConfig(Config& config);
  SynchronizerBuilder& withSuccessTask(Command successTask);
  SynchronizerBuilder& withFailTask(Command failTask);
  Runnable* build();

 private:
  Executor* executor;
  Config* config;
  Command successTask;
  Command failTask;
};

}  // namespace ntp
