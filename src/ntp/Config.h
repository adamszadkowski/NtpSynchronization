#pragma once

#include "Arduino.h"

#include <TimeUnit.h>

namespace ntp {

class Config {
 public:
  virtual ~Config() {
  }

  virtual String getHostname() = 0;

  virtual uint8_t getMaxResolveNameAttempts() {
    return 3;
  }
  virtual uint8_t getMaxAwaitResponseAttempts() {
    return 10;
  }

  virtual unsigned long getHostResolutionRetryDelay() {
    return 1;
  }
  virtual TimeUnit getHostResolutionRetryDelayTimeUnit() {
    return SECONDS;
  }

  virtual unsigned long getFirstResponseDelay() {
    return 1;
  }
  virtual TimeUnit getFirstResponseDelayTimeUnit() {
    return SECONDS;
  }

  virtual unsigned long getAwaitResponseRetryDelay() {
    return 1;
  }
  virtual TimeUnit getAwaitResponseRetryDelayTimeUnit() {
    return SECONDS;
  }
};

}  // namespace ntp
