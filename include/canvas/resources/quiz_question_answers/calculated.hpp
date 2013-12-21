#include <vector>

namespace Canvas {
namespace QuizQuestionAnswers {
  class Calculated : public QuizQuestionAnswer {
  public:
    typedef struct {
      String    name;
      uint64_t  value;
    } Variable;

    typedef std::vector<Variable*> Variables;

  protected:
    Variables mVariables;
    uint64_t mAnswer;
  };
}
}