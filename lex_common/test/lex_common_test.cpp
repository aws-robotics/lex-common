/*
 * Copyright 2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */


#include <lex_common/lex_common.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <aws/core/utils/Outcome.h>
#include <aws/lex/LexRuntimeServiceClient.h>
#include <aws/core/utils/memory/AWSMemory.h>
#include <aws/lex/model/PostContentResult.h>

#include <memory>
#include <string>
#include <utility>


namespace Aws
{
namespace Lex
{
using Aws::LexRuntimeService::Model::PostContentResult;
class TestData
{
  PostContentResult example_result;
public:

  std::string content_type = "content_type";
  LexRuntimeService::Model::DialogState dialog_state =
    LexRuntimeService::Model::DialogState::ElicitSlot;
  std::string intent_name = "intent_name";
  std::string message = "message";
  std::string slot_to_elicit = "slot_to_elicit";
  LexRuntimeService::Model::MessageFormatType message_format =
    LexRuntimeService::Model::MessageFormatType::PlainText;
  std::string session_attributes = "session_attributes";

  TestData()
  {
    example_result.SetContentType(content_type.c_str());
    example_result.SetDialogState(dialog_state);
    example_result.SetIntentName(intent_name.c_str());
    example_result.SetMessage(message.c_str());
    example_result.SetSlots("");
    example_result.SetSlotToElicit(slot_to_elicit.c_str());
    example_result.SetMessageFormat(message_format);
    example_result.SetSessionAttributes(session_attributes.c_str());
  }

  PostContentResult&& GetExampleResultR() {
    return std::forward<PostContentResult>(example_result);
  }
  PostContentResult& GetExampleResult() {
    return example_result;
  }
};

TEST(TestLexCommon, CopyResultFailureInvalidJson) {
  TestData test_data;
  auto & result = test_data.GetExampleResult();
  {
    auto io_stream = new Aws::StringStream();
    *io_stream << "test_text";
    result.ReplaceBody(io_stream);
  }
  result.SetSlots("This Causes Failure, not valid json");
  LexResponse response;
  ASSERT_EQ(ErrorCode::INVALID_RESULT, CopyResult(result, response));
}

TEST(TestLexCommon, CopyResultSuccessValidJson) {
  TestData test_data;
  auto & result = test_data.GetExampleResult();
  {
    auto io_stream = new Aws::StringStream();
    *io_stream << "test_text";
    result.ReplaceBody(io_stream);
  }
  Aws::Utils::Json::JsonValue value;
  value.WithString("key", "value");
  auto value_str = value.View().WriteReadable();
  const unsigned char * json = reinterpret_cast<const unsigned char *>(
    value_str.c_str());
  Aws::Utils::ByteBuffer bb(json,
    value_str.size());
  result.SetSlots(Aws::Utils::HashingUtils::Base64Encode(bb));
  LexResponse response;
  ASSERT_EQ(ErrorCode::SUCCESS, CopyResult(result, response));
  EXPECT_EQ(1, response.slots.size());
  EXPECT_EQ("value", response.slots["key"]);
}

TEST(TestLexCommon, CopyResultSuccessNoSlots) {
  TestData test_data;
  auto & result = test_data.GetExampleResult();
  {
    auto io_stream = new Aws::StringStream();
    *io_stream << "test_text";
    result.ReplaceBody(io_stream);
  }
  LexResponse response;
  ASSERT_EQ(ErrorCode::SUCCESS, CopyResult(result, response));
  EXPECT_EQ(test_data.message, response.text_response);
  EXPECT_EQ(test_data.intent_name, response.intent_name);
  using Aws::LexRuntimeService::Model::DialogStateMapper::GetNameForDialogState;
  std::string dialog_state_name =
    GetNameForDialogState(test_data.dialog_state).c_str();
  EXPECT_EQ(dialog_state_name, response.dialog_state);
  using Aws::LexRuntimeService::Model::MessageFormatTypeMapper::GetNameForMessageFormatType;
  std::string message_format_name =
    GetNameForMessageFormatType(test_data.message_format).c_str();
  EXPECT_EQ(message_format_name, response.message_format_type);
  EXPECT_EQ(test_data.session_attributes, response.session_attributes);
  EXPECT_TRUE(response.slots.empty());
}

TEST(TestLexInteractor, TestLexInteractorFailedConfiguration) {
  LexInteractor lex_interactor;
  auto lex_configuration = std::make_shared<LexConfiguration>();
  auto lex_runtime_client =
    std::make_shared<Aws::LexRuntimeService::LexRuntimeServiceClient>();
  EXPECT_EQ(ErrorCode::INVALID_LEX_CONFIGURATION,
    lex_interactor.ConfigureAwsLex(nullptr, nullptr));
  EXPECT_EQ(ErrorCode::INVALID_LEX_CONFIGURATION,
    lex_interactor.ConfigureAwsLex(lex_configuration, nullptr));
  EXPECT_EQ(ErrorCode::INVALID_LEX_CONFIGURATION,
    lex_interactor.ConfigureAwsLex(nullptr, lex_runtime_client));
}

}  // namespace Lex
}  // namespace Aws
