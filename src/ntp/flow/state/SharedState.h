#pragma once

#include "Arduino.h"

#include <Executor.h>
#include <IPAddress.h>
#include <Runnable.h>
#include <WiFiUdp.h>
#include "ntp/Config.h"

namespace ntp {
namespace flow {
namespace state {

class SharedState {
 public:
  SharedState(Executor &executor, Config &config, Runnable &successTask, Runnable &failTask)
      : executor(executor), config(config), successTask(successTask), failTask(failTask) {
    clear();
  }

  void clear() {
    resolveNameAttempt = 0;
    awaitResponseAttempt = 0;
    timeServerIP = IPAddress();
    udp = WiFiUDP();
  }

  Executor &getExecutor() {
    return executor;
  }
  Config &getConfig() {
    return config;
  }
  Runnable &getSuccessTask() {
    return successTask;
  }
  Runnable &getFailTask() {
    return failTask;
  }

  uint8_t getResolveNameAttempt() {
    return resolveNameAttempt;
  }
  void incrementResolveNameAttempt() {
    ++resolveNameAttempt;
  }
  uint8_t getAwaitResponseAttempt() {
    return awaitResponseAttempt;
  }
  void incrementAwaitResponseAttempt() {
    ++awaitResponseAttempt;
  }
  WiFiUDP &getUDP() {
    return udp;
  }
  IPAddress &getTimeServerIP() {
    return timeServerIP;
  }

 private:
  Executor &executor;
  Config &config;
  Runnable &successTask;
  Runnable &failTask;

  uint8_t resolveNameAttempt;
  uint8_t awaitResponseAttempt;
  WiFiUDP udp;
  IPAddress timeServerIP;
};

}  // namespace state
}  // namespace flow
}  // namespace ntp
