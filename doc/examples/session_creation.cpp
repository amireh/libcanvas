#include <canvas/canvas.hpp>
#include <canvas/session.hpp>

int main(int, char**) {
  Canvas::init(argc, argv);

  Canvas::Session session;
  Canvas::String apiToken;

  apiToken = "ljZT290gJTrab9CCv50P8IeDUGob7NgsZktKy4ssqKaFKmIDLT5OCMPDhYzahMUQ";
  session.authenticate(apiToken);

  Canvas::free();

  return 0;
}