// Copyright 2017 Wu Tao
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "pb_utils.h"
#include "logging.h"

#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>

namespace yaraft {

pb::MessageType GetResponseType(pb::MessageType type) {
  switch (type) {
    case pb::MsgApp:
      return pb::MsgAppResp;
    case pb::MsgVote:
      return pb::MsgVoteResp;
    case pb::MsgPreVote:
      return pb::MsgPreVoteResp;
    case pb::MsgHeartbeat:
      return pb::MsgHeartbeatResp;
    default:
      D_FMT_LOG(FATAL, "{} is not a request type", pb::MessageType_Name(type));
      return pb::MessageType(0);
  }
}

// Print the message in a single line, useful for logging or other purposes.
std::string DumpPB(const google::protobuf::Message& msg) {
  std::string msgstr = msg.DebugString();
  boost::trim(msgstr);

  std::vector<std::string> tmp;
  boost::split(tmp, msgstr, [](char c) { return c == '\n'; });
  msgstr = boost::join(tmp, ", ");
  return std::string("{") + msgstr + '}';
}

}  // namespace yaraft
