#include <gtest/gtest.h>
#include "../utils.h"
#include "common.h"

extern protocol_type SearchRtsp(rte_mbuf *);

using namespace packet_modifier;

TEST(RTSP, BadLength) {
  uint8_t data[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x08, 0x00,

    0x05, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x40, 0x11, // (ttl, proto)
    0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,

    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    0x52, 0x54, 0x53, 0x50, // RTSP without anything else
  };
  auto m = InitPacket(data, sizeof(data));
  ASSERT_EQ(PreparePacket(m), true);
  ASSERT_EQ(SearchRtsp(m), UNKNOWN);
  rte_pktmbuf_free(m);
}

TEST(RTSP, Response) {
  uint8_t data[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x08, 0x00,

    0x05, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x40, 0x11, // (ttl, proto)
    0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,

    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    0x52, 0x54, 0x53, 0x50, // RTSP
    0x2f, // /
    0x31, 0x2e, 0x30, // 1.0
    0x20, // space
    0x32, 0x30, 0x30, // 200
    0x20, // space
    0x4f, 0x4b, // OK
  };
  auto m = InitPacket(data, sizeof(data));
  ASSERT_EQ(PreparePacket(m), true);
  ASSERT_EQ(SearchRtsp(m), RTSP);
  rte_pktmbuf_free(m);
}

TEST(RTSP, Describe) {
  uint8_t data[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x08, 0x00,

    0x05, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x40, 0x11, // (ttl, proto)
    0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,

    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    0x44, 0x45, 0x53, 0x43, 0x52, 0x49, 0x42, 0x45, // DESCRIBE
    0x20, // space
    0x72, 0x74, 0x73, 0x70, 0x3a, 0x2f, 0x2f, // rtsp://
    0x00, 0x00, 0x00, // other data
  };
  auto m = InitPacket(data, sizeof(data));
  ASSERT_EQ(PreparePacket(m), true);
  ASSERT_EQ(SearchRtsp(m), RTSP);
  rte_pktmbuf_free(m);
}

TEST(RTSP, Options) {
  uint8_t data[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x08, 0x00,

    0x05, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x40, 0x11, // (ttl, proto)
    0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,

    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    0x4f, 0x50, 0x54, 0x49, 0x4f, 0x4e, 0x53, //OPTIONS
    0x20, // space
    0x72, 0x74, 0x73, 0x70, 0x3a, 0x2f, 0x2f, // rtsp://
    0x00, 0x00, 0x00, // other data
  };
  auto m = InitPacket(data, sizeof(data));
  ASSERT_EQ(PreparePacket(m), true);
  ASSERT_EQ(SearchRtsp(m), RTSP);
  rte_pktmbuf_free(m);
}

TEST(RTSP, Play) {
  uint8_t data[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x08, 0x00,

    0x05, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x40, 0x11, // (ttl, proto)
    0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,

    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    0x50, 0x4c, 0x41, 0x59, // PLAY
    0x20, // space
    0x72, 0x74, 0x73, 0x70, 0x3a, 0x2f, 0x2f, // rtsp://
    0x00, 0x00, 0x00, // other data
  };
  auto m = InitPacket(data, sizeof(data));
  ASSERT_EQ(PreparePacket(m), true);
  ASSERT_EQ(SearchRtsp(m), RTSP);
  rte_pktmbuf_free(m);
}

TEST(RTSP, Pause) {
  uint8_t data[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x08, 0x00,

    0x05, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x40, 0x11, // (ttl, proto)
    0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,

    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    0x50, 0x41, 0x55, 0x53, 0x45, // PAUSE
    0x20, // space
    0x72, 0x74, 0x73, 0x70, 0x3a, 0x2f, 0x2f, // rtsp://
    0x00, 0x00, 0x00, // other data
  };
  auto m = InitPacket(data, sizeof(data));
  ASSERT_EQ(PreparePacket(m), true);
  ASSERT_EQ(SearchRtsp(m), RTSP);
  rte_pktmbuf_free(m);
}

TEST(RTSP, Record) {
  uint8_t data[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x08, 0x00,

    0x05, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x40, 0x11, // (ttl, proto)
    0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,

    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    0x52, 0x45, 0x43, 0x4f, 0x52, 0x44, // RECORD
    0x20, // space
    0x72, 0x74, 0x73, 0x70, 0x3a, 0x2f, 0x2f, // rtsp://
    0x00, 0x00, 0x00, // other data
  };
  auto m = InitPacket(data, sizeof(data));
  ASSERT_EQ(PreparePacket(m), true);
  ASSERT_EQ(SearchRtsp(m), RTSP);
  rte_pktmbuf_free(m);
}

TEST(RTSP, Redirect) {
  uint8_t data[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x08, 0x00,

    0x05, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x40, 0x11, // (ttl, proto)
    0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,

    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    0x52, 0x45, 0x44, 0x49, 0x52, 0x45, 0x43, 0x54, // REDIRECT
    0x20, // space
    0x72, 0x74, 0x73, 0x70, 0x3a, 0x2f, 0x2f, // rtsp://
    0x00, 0x00, 0x00, // other data
  };
  auto m = InitPacket(data, sizeof(data));
  ASSERT_EQ(PreparePacket(m), true);
  ASSERT_EQ(SearchRtsp(m), RTSP);
  rte_pktmbuf_free(m);
}

TEST(RTSP, Setup) {
  uint8_t data[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x08, 0x00,

    0x05, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x40, 0x11, // (ttl, proto)
    0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,

    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    0x53, 0x45, 0x54, 0x55, 0x50, // SETUP
    0x20, // space
    0x72, 0x74, 0x73, 0x70, 0x3a, 0x2f, 0x2f, // rtsp://
    0x00, 0x00, 0x00, // other data
  };
  auto m = InitPacket(data, sizeof(data));
  ASSERT_EQ(PreparePacket(m), true);
  ASSERT_EQ(SearchRtsp(m), RTSP);
  rte_pktmbuf_free(m);
}

TEST(RTSP, Announce) {
  uint8_t data[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x08, 0x00,

    0x05, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x40, 0x11, // (ttl, proto)
    0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,

    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    0x41, 0x4e, 0x4e, 0x4f, 0x55, 0x4e, 0x43, 0x45, // ANNOUNCE
    0x20, // space
    0x72, 0x74, 0x73, 0x70, 0x3a, 0x2f, 0x2f, // rtsp://
    0x00, 0x00, 0x00, // other data
  };
  auto m = InitPacket(data, sizeof(data));
  ASSERT_EQ(PreparePacket(m), true);
  ASSERT_EQ(SearchRtsp(m), RTSP);
  rte_pktmbuf_free(m);
}

TEST(RTSP, GetParameter) {
  uint8_t data[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x08, 0x00,

    0x05, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x40, 0x11, // (ttl, proto)
    0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,

    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    0x47, 0x45, 0x54, 0x5f, 0x50, 0x41, 0x52, 0x41, 0x4d, 0x45, 0x54, 0x45, 0x52, // GET_PARAMETER
    0x20, // space
    0x72, 0x74, 0x73, 0x70, 0x3a, 0x2f, 0x2f, // rtsp://
    0x00, 0x00, 0x00, // other data
  };
  auto m = InitPacket(data, sizeof(data));
  ASSERT_EQ(PreparePacket(m), true);
  ASSERT_EQ(SearchRtsp(m), RTSP);
  rte_pktmbuf_free(m);
}

TEST(RTSP, SetParameter) {
  uint8_t data[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x08, 0x00,

    0x05, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x40, 0x11, // (ttl, proto)
    0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,

    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    0x53, 0x45, 0x54, 0x5f, 0x50, 0x41, 0x52, 0x41, 0x4d, 0x45, 0x54, 0x45, 0x52, // SET_PARAMETER
    0x20, // space
    0x72, 0x74, 0x73, 0x70, 0x3a, 0x2f, 0x2f, // rtsp://
    0x00, 0x00, 0x00, // other data
  };
  auto m = InitPacket(data, sizeof(data));
  ASSERT_EQ(PreparePacket(m), true);
  ASSERT_EQ(SearchRtsp(m), RTSP);
  rte_pktmbuf_free(m);
}

TEST(RTSP, TearDown) {
  uint8_t data[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x08, 0x00,

    0x05, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x40, 0x11, // (ttl, proto)
    0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,

    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,

    0x54, 0x45, 0x41, 0x52, 0x44, 0x4f, 0x57, 0x4e, // TEARDOWN
    0x20, // space
    0x72, 0x74, 0x73, 0x70, 0x3a, 0x2f, 0x2f, // rtsp://
    0x00, 0x00, 0x00, // other data
  };
  auto m = InitPacket(data, sizeof(data));
  ASSERT_EQ(PreparePacket(m), true);
  ASSERT_EQ(SearchRtsp(m), RTSP);
  rte_pktmbuf_free(m);
}
