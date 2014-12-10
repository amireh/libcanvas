#include <canvas/canvas.hpp>
#include <canvas/session.hpp>
#include <canvas/settings.hpp>

int main(int argc, char** argv) {
  Canvas::init(argc, argv);

  Canvas::Settings::set("canvas_host", "http://localhost");
  Canvas::Settings::set("canvas_port", "3000");
  Canvas::Settings::set("canvas_api_prefix", "/api/v1");

  // All endpoints requested by the session now will be prefixed by:
  // http://localhost:3000/api/v1
  Canvas::Session session;

  // For example, the following GET request will be made to
  // http://localhost:3000/api/v1/courses
  session.get("/courses");

  Canvas::free();

  return 0;
}