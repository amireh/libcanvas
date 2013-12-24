## Subclass QuizQuestion

For example, adding a TrueFalse quiz question type:

```c++
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
```

- Header goes in `include/canvas/resources/quiz_questions`
- Source goes in `src/resources/quiz_questions`
- Write a generator in Quiz::loadQuestions()
- Define the custom type converters in QuizQuestion:
  - `MyType* QuizQuestion::asMyType();`
  - `MyType const* QuizQuestion::asMyType() const;`