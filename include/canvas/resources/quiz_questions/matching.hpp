/*
 *  Copyright (c) 2013 Algol Labs <ahmad@algollabs.com>
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

#ifndef H_CANVAS_MATCHING_QUIZ_QUESTION_H
#define H_CANVAS_MATCHING_QUIZ_QUESTION_H

#include "canvas/resources/quiz_question.hpp"
#include "canvas/resources/matching_answer.hpp"
#include "canvas/resources/quiz_question_prototypes/answerable.hpp"

namespace Canvas {
namespace QuizQuestions {
  using QuizQuestionPrototypes::Answerable;

  /**
   * \addtogroup Resources
   * @{
   * @class Matching
   * @brief
   * A question where the student gets to match pre-defined questions to answers.
   */
  class Matching : public QuizQuestion, public Answerable<MatchingAnswer> {
  public:
    using Resource::deserialize;
    using QuizQuestion::deserializeAnswer;

    struct Match {
      Match();
      bool operator==(const Match&) const;

      String text;
      ID id;
    };

    typedef std::vector<Match> Matches;
    typedef std::map<MatchingAnswer const*, Match> MatchPairs;

    Matching();
    Matching(ID);
    Matching(ID, Quiz const*);
    Matching(const Matching&) = delete;
    Matching& operator=(const Matching&) = delete;
    virtual ~Matching();

    virtual void deserialize(JSONValue&);
    virtual void deserializeAnswer(JSONValue&);

    /**
     * Supply a student's answer of a pairing between an answer and a match ID.
     */
    void matchPair(MatchingAnswer const*, ID);

    /**
     * Supply a student's answer of a pairing between an answer and a match.
     */
    void matchPair(MatchingAnswer const*, Match const&);

    /**
     * Supply a student's answer of a pairing between text to the left and right.
     */
    void matchPair(String const& left, String const& right);

    void clearMatching(MatchingAnswer const*);

    bool hasMatching(MatchingAnswer const*) const;
    Match const& matchedPair(MatchingAnswer const*) const;
    Match const& matchedPair(String const& left) const;
    MatchPairs const& matchedPairs() const;

    /**
     * Output looks like this:
     *
     *   { "answer": 10.5 }
     */
    virtual JSONValue serializeAnswer() const;

    Matches const& matches() const;
    Matches const& distractors() const;
    Match const& match(ID) const;
    Match const& match(String const&) const;
  protected:
    Matches mMatches;
    Matches mDistractors;

    MatchPairs mMatchedPairs;

    MatchingAnswer const* findAnswerByLeft(String const&) const;
  };
  /** @} */
}
}

#endif
