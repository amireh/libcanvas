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

#include "canvas/resources/quiz_questions/calculated.hpp"
#include "canvas/resources/quiz_submission.hpp"

namespace Canvas {
namespace QuizQuestions {

  Calculated::Calculated()
  : QuizQuestion(), mAnswer(0)
  {
  }

  Calculated::Calculated(ID id)
  : QuizQuestion(id), mAnswer(0)
  {
  }

  Calculated::Calculated(ID id, Quiz const* quiz)
  : QuizQuestion(id, quiz), mAnswer(0)
  {
  }

  Calculated::~Calculated() {
  }

  void Calculated::deserialize(JSONValue &document) {
    QuizQuestion::deserialize(document);

    if (document.isMember("answers") && document["answers"].isArray()) {
      for (auto answerDocument : document["answers"]) {
        ID answerId = answerDocument["id"].asUInt();

        addAnswer(answerId, [&answerDocument](CalculatedAnswer *answer) {
          answer->deserialize(answerDocument);
        });
      }
    }

    if (document.isMember("variables") && document["variables"].isArray()) {
      for (auto vDocument : document["variables"]) {
        Variable variable;
        variable.name = vDocument["name"].asString();
        variable.min = vDocument["min"].asDouble();
        variable.max = vDocument["max"].asDouble();
        variable.precision = vDocument["scale"].asInt();

        mVariables.push_back(variable);
      }
    }
  }

  void Calculated::setAnswer(double value) {
    mAnswer = value;
  }

  double Calculated::answer() const {
    return mAnswer;
  }

  void Calculated::deserializeAnswer(JSONValue const &document) {
    QuizQuestion::deserializeAnswer(document);
    mAnswer = document["answer"].asDouble();
  }

  JSONValue Calculated::serializeAnswer() const {
    Json::Value document;
    document["answer"] = mAnswer;
    return document;
  }

  Calculated::Variable::Variable()
  : min(0), max(0), precision(0) {
  }

  Calculated::Variables const& Calculated::variables() const {
    return mVariables;
  }

  Calculated::Variable const& Calculated::variable(String const& name) const {
    for (Variable const& v : mVariables) {
      if (v.name == name) {
        return v;
      }
    }

    throw std::invalid_argument("Unknown variable " + name);
  }

  double Calculated::variableValue(QuizSubmission const& qs, Variable const& v) const {
    std::vector<double> values(variableValues(v));

    return values[ qs.id() % values.size() ];
  }

  std::vector<double> Calculated::variableValues(Variable const& v) const {
    std::vector<double> values;

    for (auto answer : mAnswers) {
      values.push_back(answer->variableValue(v.name));
    }

    return values;
  }

} // namespace QuizQuestions
} // namespace Canvas