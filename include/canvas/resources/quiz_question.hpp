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

#ifndef H_CANVAS_QUIZ_QUESTION_H
#define H_CANVAS_QUIZ_QUESTION_H

#include "canvas/canvas.hpp"
#include "canvas/resource.hpp"

namespace Canvas {

  class Quiz;
  class QuizSubmission;
  class QuizQuestion;

  namespace QuizQuestions {
    class MultipleChoice;
  }

  /**
   * \addtogroup Resources
   * @{
   * @class QuizQuestion
   * @brief
   * A base question interface for Quiz questions. Must be cast to one of the
   * 10 question types for handling.
   */
  class QuizQuestion : public Resource {
  public:
    using Resource::deserialize;

    QuizQuestion();
    QuizQuestion(ID);
    QuizQuestion(ID, Quiz const*);
    QuizQuestion(const QuizQuestion&) = delete;
    QuizQuestion& operator=(QuizQuestion const&) = delete;
    virtual ~QuizQuestion();

    /**
     * The Quiz this QQ is in.
     */
    virtual Quiz const* quiz() const;

    /**
     * A (non-unique) question name, defaults to "Question X" where X is the
     * position of the question.
     */
    virtual String const& name() const;

    /**
     * Stringified type of the question.
     */
    virtual String const& type() const;

    /**
     * The question body of text to present to the student.
     */
    virtual String const& text() const;

    /**
     * A comment to show when the student chooses a correct answer.
     */
    virtual String const& correctComments() const;

    /**
     * A comment to show when the student chooses an incorrect answer.
     */
    virtual String const& incorrectComments() const;

    /**
     * A comment to show when the student chooses any answer.
     */
    virtual String const& neutralComments() const;

    /**
     * The maximum number of points a student could score for this question.
     */
    virtual int pointsPossible() const;

    /**
     * The question group ID this question belongs to, if any.
     */
    virtual ID groupId() const;

    /**
     * The position of this question inside its group (or the default group.)
     */
    virtual int position() const;

    /**
     * Whether the question is marked.
     */
    virtual bool isMarked() const;

    /**
     * Populate QuizQuestion from a JSON document.
     */
    virtual void deserialize(JSONValue&);

    /**
     * Load the student's answer for this question from a JSON document.
     */
    virtual void deserializeAnswer(String const&);
    virtual void deserializeAnswer(JSONValue&) = 0;

    /**
     * Generate a JSON document representing the student's answer for this
     * question.
     */
    virtual JSONValue serializeAnswer() const = 0;

    virtual void setQuiz(Quiz const*);

    /**
     * The URL at which the question can be answered while taking a quiz.
     */
    virtual URI answerUrl(QuizSubmission const&) const;

    QuizQuestions::MultipleChoice* asMultipleChoice();

    template<typename T>
    T* toActualType(String const& type) {
      if (this->type() != type) {
        throw std::runtime_error("Invalid target question type: " + type +
          ", actual is:" + this->type());
      } else {
        return reinterpret_cast<T*>(this);
      }
    }

    virtual void mark(bool marked);

  protected:
    friend class Quiz;

    void reset();
    virtual void buildUrl();

    Quiz const* mQuiz;
    int mPosition;
    int mPointsPossible;
    ID mGroupId;
    String mName;
    String mType;
    String mText;
    String mCorrectComments;
    String mIncorrectComments;
    String mNeutralComments;
    bool mMarked;
  };
  /** @} */
}

#endif
