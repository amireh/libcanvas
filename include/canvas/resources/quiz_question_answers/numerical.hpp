namespace Canvas {
namespace QuizQuestionAnswers {
  class Numerical : public QuizQuestionAnswer {
  protected:
    String mAnswerType;
    uint64_t exact;
    uint64_t margin;
  };
}
}