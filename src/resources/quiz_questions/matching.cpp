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

#include "canvas/resources/quiz_questions/matching.hpp"
#include "canvas/resources/quiz_submission.hpp"
#include "canvas/logger.hpp"
#include "canvas/utility.hpp"

namespace Canvas {
namespace QuizQuestions {

  Matching::Matching()
  : QuizQuestion()
  {
  }

  Matching::Matching(ID id)
  : QuizQuestion(id)
  {
  }

  Matching::Matching(ID id, Quiz const* quiz)
  : QuizQuestion(id, quiz)
  {
  }

  Matching::~Matching() {
    mMatchedPairs.clear();
  }

  void Matching::deserialize(JSONValue &document) {
    QuizQuestion::deserialize(document);

    if (document.isMember("answers") && document["answers"].isArray()) {
      for (auto answerDocument : document["answers"]) {
        ID answerId = answerDocument["id"].asUInt();

        addAnswer(answerId, [&answerDocument](MatchingAnswer *answer) {
          answer->deserialize(answerDocument);
        });
      }
    }

    if (document.isMember("matches") && document["matches"].isArray()) {
      for (auto mDocument : document["matches"]) {
        Match match;
        match.text = mDocument["text"].asString();
        match.id = mDocument["match_id"].asUInt();

        mMatches.push_back(match);
      }
    }
    if (document.isMember("matching_answer_incorrect_matches") &&
        document["matching_answer_incorrect_matches"].isString()) {
      String distractors = document["matching_answer_incorrect_matches"].asString();
      for (auto distractor : Utility::split(distractors, '\n')) {
        Match match;
        match.text = distractor;
        match.id = 0;

        mDistractors.push_back(match);
      }
    }
  }

  void Matching::matchPair(MatchingAnswer const* answer, ID matchId) {
    matchPair(answer, this->match(matchId));
  }

  void Matching::matchPair(MatchingAnswer const* answer, Match const& match) {
    MatchPairs::iterator locator = mMatchedPairs.find(answer);

    if (!answer) {
      throw std::invalid_argument("A valid answer must be provided to the matching pair.");
    }

    if (locator != mMatchedPairs.end()) {
      mMatchedPairs.erase(answer);
    }

    mMatchedPairs.insert(std::make_pair(answer, match));
  }

  void Matching::matchPair(String const& left, String const& right) {
    MatchingAnswer const* answer = findAnswerByLeft(left);

    if (!answer) {
      throw std::invalid_argument("Unknown answer with text " + left);
    }

    matchPair(answer, match(right));
  }

  void Matching::clearMatching(MatchingAnswer const* answer) {
    mMatchedPairs.erase(answer);
  }

  bool Matching::hasMatching(MatchingAnswer const* answer) const {
    return mMatchedPairs.find(answer) != mMatchedPairs.end();
  }

  Matching::Match const& Matching::matchedPair(MatchingAnswer const* answer) const {
    MatchPairs::const_iterator locator = mMatchedPairs.find(answer);

    if (!answer) {
      throw std::invalid_argument("An answer must provided to look up its match pair.");
    }

    if (locator == mMatchedPairs.end()) {
      throw std::invalid_argument("No matching pair given for that answer.");
    }

    return locator->second;
  }

  Matching::Match const& Matching::matchedPair(String const& left) const {
    MatchingAnswer const* answer = findAnswerByLeft(left);

    if (!answer) {
      throw std::invalid_argument("Unknown answer with text " + left);
    }

    return matchedPair(answer);
  }
  Matching::MatchPairs const& Matching::matchedPairs() const {
    return mMatchedPairs;
  }

  void Matching::deserializeAnswer(JSONValue const &document) {
    QuizQuestion::deserializeAnswer(document);

    if (document.isMember("answer") && document["answer"].isArray()) {
      for (auto pairDocument : document["answer"]) {
        if (!pairDocument["match_id"].isInt()) {
          Logger::defaultLogger().error()
            << "bad match_id in document: " << pairDocument.toStyledString();
          continue;
        }
        else if (!pairDocument["answer_id"].isInt()) {
          Logger::defaultLogger().error()
            << "bad answer_id in document: " << pairDocument.toStyledString();

          continue;
        }

        ID matchId = pairDocument.get("match_id", "0").asUInt();
        ID answerId = pairDocument.get("answer_id", "0").asUInt();

        if (matchId && answerId) {
          Logger::defaultLogger().info() <<
            "match " << answerId << " <> " << matchId;
          matchPair(findAnswer(answerId), matchId);
        }
      }
    }
  }

  JSONValue Matching::serializeAnswer() const {
    Json::Value document;

    for (auto matchPair : mMatchedPairs) {
      JSONValue pairDocument;
      pairDocument["answer_id"] = matchPair.first->id();
      pairDocument["match_id"] = matchPair.second.id;

      document["answer"].append( pairDocument );
    }

    return document;
  }

  Matching::Match::Match()
  : id(0) {
  }

  bool Matching::Match::operator==(const Match& rhs) const {
    return rhs.id == id && rhs.text == text;
  }


  Matching::Matches const& Matching::matches() const {
    return mMatches;
  }
  Matching::Matches const& Matching::distractors() const {
    return mDistractors;
  }

  Matching::Match const& Matching::match(ID id) const {
    for (Match const& match : mMatches) {
      if (match.id == id) {
        return match;
      }
    }

    throw std::invalid_argument("Unknown match " + id);
  }

  Matching::Match const& Matching::match(String const& text) const {
    for (Match const& match : mMatches) {
      if (match.text == text) {
        return match;
      }
    }

    throw std::invalid_argument("Unknown match with text " + text);
  }

  MatchingAnswer const* Matching::findAnswerByLeft(String const& left) const {
    for (auto answer : mAnswers) {
      if (answer->left() == left) {
        return answer;
      }
    }

    return nullptr;
  }

} // namespace QuizQuestions
} // namespace Canvas