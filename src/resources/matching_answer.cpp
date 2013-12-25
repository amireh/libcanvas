/*
 *  Copyright (C) 2013 Algol Labs <ahmad@algollabs.com>
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a
 *  copy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation
 *  the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 *  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 */

#include "canvas/resources/matching_answer.hpp"
#include "canvas/resources/quiz_questions/matching.hpp"

namespace Canvas {
  MatchingAnswer::MatchingAnswer()
  : QuizQuestionAnswer(), mMatchId(0)
  {
  }

  MatchingAnswer::MatchingAnswer(ID id)
  : QuizQuestionAnswer(id), mMatchId(0)
  {
  }

  MatchingAnswer::MatchingAnswer(ID id, QuizQuestion const* question)
  : QuizQuestionAnswer(id, question), mMatchId(0)
  {
  }

  MatchingAnswer::~MatchingAnswer() {
  }

  void MatchingAnswer::deserialize(JSONValue& document) {
    QuizQuestionAnswer::deserialize(document);

    mText = mLeft = document.get("left", "").asString();
    mRight = document.get("right", "").asString();
    mMatchId = document.get("match_id", 0).asUInt();
  }

  String const& MatchingAnswer::left() const {
    return mLeft;
  }

  String const& MatchingAnswer::right() const {
    return mRight;
  }

  ID MatchingAnswer::matchId() const {
    return mMatchId;
  }
}