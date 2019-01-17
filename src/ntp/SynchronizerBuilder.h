#pragma once

#include <Executor.h>
#include <Runnable.h>
#include "ntp/Config.h"

namespace ntp {

class SynchronizerBuilder {
 public:
  SynchronizerBuilder();

  SynchronizerBuilder& withExecutor(Executor& executor);
  SynchronizerBuilder& withConfig(Config& config);
  SynchronizerBuilder& withSuccessTask(Runnable& successTask);
  SynchronizerBuilder& withFailTask(Runnable& failTask);
  Runnable* build();

 private:
  Executor* executor;
  Config* config;
  Runnable* successTask;
  Runnable* failTask;
};

}  // namespace ntp
