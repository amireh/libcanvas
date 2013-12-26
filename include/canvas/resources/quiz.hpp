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

#ifndef H_CANVAS_QUIZ_H
#define H_CANVAS_QUIZ_H

#include "canvas/canvas.hpp"
#include "canvas/resource.hpp"
#include <vector>

namespace Canvas {

  class Course;
  class Session;
  class QuizQuestion;
  class QuizSubmission;

  /**
   * \addtogroup Resources
   * @{
   * @class Quiz
   * @brief
   * A quiz with questions that students can take.
   */
  class Quiz : public Resource {
  public:
    using Resource::deserialize;
    typedef std::vector<QuizQuestion*> Questions;

    Quiz();
    Quiz(ID id, Course*);
    Quiz(const Quiz&) = delete;
    Quiz& operator=(Quiz const&) = delete;
    virtual ~Quiz();

    virtual void setCourse(Course*);

    /**
     * The Course this Quiz is for.
     */
    virtual Course const* course() const;

    /**
     * A not necessarily unique, but usually descriptive, title for the quiz.
     */
    virtual String const& title() const;

    /**
     * Free-form description of the Quiz to guide students.
     *
     * @note
     * This may contain HTML.
     */
    virtual String const& description() const;

    /**
     * An access code that must be provided by the student to participate in this
     * quiz.
     *
     * @note
     * Keep it secret!
     */
    virtual String const& accessCode() const;

    /**
     * The maximum number of points a student can score for this Quiz.
     */
    virtual uint pointsPossible() const;

    /**
     * How many times the student gets to take this quiz.
     *
     * A value of -1 denotes unlimited attempts.
     */
    virtual int allowedAttempts() const;

    /**
     * The number of questions this Quiz has, as recorded by Canvas.
     */
    virtual uint questionCount() const;

    /**
     * Number of minutes after which the student's quiz submission should be
     * automatically turned-in by the system.
     *
     * @warning
     * Answers recorded beyond this limit will be discarded by Canvas.
     */
    virtual int timeLimit() const;

    /**
     * Published quizzes are open for participation by students.
     */
    virtual bool isPublished() const;

    /**
     * Is it a One-Question-At-A-Time quiz?
     */
    virtual bool isOQAAT() const;

    /**
     * Whether correct answers should be displayed to students once they submit
     * the quiz.
     */
    virtual bool showCorrectAnswers() const;

    /**
     * Whether this Quiz has been explicitly locked for *this* student.
     */
    virtual bool locked() const;

    /**
     * Populate the Quiz from a JSON document.
     */
    virtual void deserialize(JSONValue&);

    virtual void loadQuestions(Session&, AsyncCallback);
    virtual void loadQuestions(String const&);

    /**
     * This Quiz's questions.
     */
    virtual Questions const& questions() const;

  protected:
    Questions mQuestions;
    Course* mCourse;
    String mTitle;
    String mAccessCode;
    String mDescription;
    bool mPublished;
    uint mPointsPossible;
    int mAllowedAttempts;
    uint mQuestionCount;
    int mTimeLimit;
    bool mOQAAT;
    bool mLocked;
    bool mShowCorrectAnswers;

    void buildUrl();
    void reset();
  };
  /** @} */
}

#endif
