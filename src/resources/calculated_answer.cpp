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

#include "canvas/resources/calculated_answer.hpp"

namespace Canvas {
  CalculatedAnswer::CalculatedAnswer()
  : QuizQuestionAnswer()
  {
  }

  CalculatedAnswer::CalculatedAnswer(ID id)
  : QuizQuestionAnswer(id)
  {
  }

  CalculatedAnswer::CalculatedAnswer(ID id, QuizQuestion const* question)
  : QuizQuestionAnswer(id, question)
  {
  }

  CalculatedAnswer::~CalculatedAnswer() {
  }

  void CalculatedAnswer::deserialize(JSONValue& document) {
    mId = document.get("id", 0).asUInt();
    mWeight = document.get("weight", 0).asUInt();
    mValue = document.get("answer", 0).asDouble();

    if (document.isMember("variables") && document["variables"].isArray()) {
      for (auto variableDocument : document["variables"]) {
        Variable v;
        v.name = variableDocument["name"].asString();
        v.value = variableDocument["value"].asDouble();
        mVariables.push_back(v);
      }
    }
  }

  double CalculatedAnswer::correctValue() const {
    return mValue;
  }

  double CalculatedAnswer::variableValue(String const& name) const {
    return variable(name).value;
  }

  CalculatedAnswer::Variables const& CalculatedAnswer::variables() const {
    return mVariables;
  }

  CalculatedAnswer::Variable const& CalculatedAnswer::variable(String const& name) const {
    for (Variable const &v : mVariables) {
      if (v.name == name) {
        return v;
      }
    }

    throw std::invalid_argument("Unknown variable " + name);
  }
}