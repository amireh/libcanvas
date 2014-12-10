# Usage

@tableofcontents

@section getting-started Getting started

There are two routines that must be called before and after you're working with
`libcanvas`: @ref Canvas::init(int, char**) and @ref Canvas::free(). The former
will perform any allocations required by library resources, while the other will
take care of cleaning up after the resources to avoid any leaks.

@include basic_integration.cpp

@section session-usage Using the session

The session is the interface for interacting with the Canvas API.
It is primarily concerned with:

  - authenticating with the Canvas API (as a student)
  - performing HTTP requests

Evidently, you will always need an instance of a Canvas::Session to carry out
requests through the available resources. Having a single session instance
throughout your application scope (ie, a singleton) is usually fine.

@warning
`libcanvas` is not inherently thread-safe. However, it allows for integration
within a threaded environment through use of callbacks in blocking operations.
However, it is not safe to manipulate resources from different threads
concurrently, and as such it is left to the caller to synchronize access.

For a session to be valid, an API token must be passed to it that belongs to an
authentic Canvas user. The generation of an API token must be done via @canvas.

Creating a session is very simple, here's an example of creating one and
providing an authentication token to use for requests:

@include session_creation.cpp

Now that we have an authentic session, we should configure `libcanvas` to know
the host and port of the @canvas instance we plan to
interact with. This is done by modifying the two setting keys `canvas_host`
and `canvas_port` respectively.

@include connection_settings.cpp

@section taking-quizzes Taking quizzes

With `libcanvas` integrated, and the session set up, we are now ready to get
right down to the fun stuff. In this section, I'll walk you through loading
the courses a student is enrolled in, their available quizzes, and how to manage
the student's submissions for these quizzes.

@subsection using-student The Canvas::Student resource

The first @ref Canvas::Resource "resource" we'll deal with is the Canvas::Student.
The student provides us with the ability to:

  - load her identity (which is identified by the API token)
  - load the courses she's enrolled in
  - manage her submissions to course quizzes

To take a quiz, we must first get the list of available courses the student is
enrolled in:

@include loading_courses.cpp

> **A note on callbacks**
>
> As is evident in the `loadCourses` method call above, it accepts a _functor_ with
> the status of the operation provided as a parameter. This approach is taken
> by all methods in `libcanvas` that perform any kind of network I/O. While, as
> noted earlier in this guide, the library in itself does not provide any concurrency
> or background-threading of its blocking operations (mainly, the HTTP requests),
> it still adopts the callback design to make it possible for the integrating
> application to provide true asynchronous behaviour.

With the courses loaded, we now proceed to load the @ref Canvas::Quiz "*quizzes*"
available for each course.

@subsection loading-courses Loading courses
