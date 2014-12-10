# Extending libcanvas

## Adding support for new question types

### Subclass QuizQuestion

For example, adding a `TrueFalse` quiz question type:

~~~{.cpp}
#ifndef H_CANVAS_TRUE_FALSE_QUIZ_QUESTION_H
#define H_CANVAS_TRUE_FALSE_QUIZ_QUESTION_H

#include "canvas/resources/quiz_questions/multiple_choice.hpp"

namespace Canvas {
namespace QuizQuestions {
  class TrueFalse : public QuizQuestion {
  };
}
}

#endif
~~~

- Header goes in `include/canvas/resources/quiz_questions`
- Source goes in `src/resources/quiz_questions`
- Write a generator in the Quiz::loadQuestions() factory
- Define the custom type converters in QuizQuestion:
  - `MyType* QuizQuestion::asMyType();`
  - `MyType const* QuizQuestion::asMyType() const;`
- Add header and source to `src/CMakeLists.txt`