// libcanvas integration and session setup ommitted for brevity
// ...

#include <canvas/resources/student.hpp>

static void loadStudentCourses() {
  Canvas::Student student;

  student.loadCourses(session, [&](bool success) {
    if (success) {
      // courses have been loaded successfully
    }
  });
}