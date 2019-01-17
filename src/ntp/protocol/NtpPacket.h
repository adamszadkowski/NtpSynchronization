#pragma once

#include "Arduino.h"

namespace ntp {
namespace protocol {

enum LeapIndicator { UNSYNCHRONIZED = 3 };
enum VersionNumber { VERSION_4 = 4 };
enum Mode { CLIENT = 3 };
enum Stratum { UNSPECIFIED = 0 };

struct NtpPacket {
  LeapIndicator leapIndicator : 2;
  VersionNumber versionNumber : 3;
  Mode mode : 3;

  uint8_t stratum;
  uint8_t poll;
  int8_t precision;

  uint32_t rootDelay;
  uint32_t rootDispersion;
  char referenceIdentifier[4];

  uint32_t referenceTimestampSeconds;
  uint32_t referenceTimestampFraction;

  uint32_t origiginTimestampSeconds;
  uint32_t origiginTimestampFraction;

  uint32_t receiveTimestampSeconds;
  uint32_t receiveTimestampFraction;

  uint32_t transmitTimestampSeconds;
  uint32_t transmitTimestampFraction;
};

}  // namespace protocol
}  // namespace ntp
