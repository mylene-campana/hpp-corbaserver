// Copyright (C) 2009, 2010 by Florent Lamiraux, Thomas Moulard, Joseph Mirabel, JRL.
//
// This file is part of the hpp-corbaserver.
//
// This software is provided "as is" without warranty of any kind,
// either expressed or implied, including but not limited to the
// implied warranties of fitness for a particular purpose.
//
// See the COPYING file for more information.

#ifndef HPP_CORBASERVER_SERVER_HH
# define HPP_CORBASERVER_SERVER_HH

# include <hpp/corbaserver/fwd.hh>
# include <hpp/corbaserver/config.hh>
# include <hpp/corbaserver/problem-solver-map.hh>

namespace hpp
{
  namespace corbaServer
  {
    /// Implementation of Hpp module Corba server.

    ///  This class initializes the Corba server and starts the following Corba interface implementations.
    ///  \li hpp::Robot: to build a model::Device and to insert it in a core::ProblemSolver object,
    ///  \li hpp::Obstacle: to build obstacles and insert them in a core::ProblemSolver object,
    ///  \li hpp::Problem: to define a path planning problem and solve it.

    ///  To use this object, call the constructor

    ///  \code
    ///  int argc=1;
    ///  char *argv[1] = {"program"};
    ///  core::ProblemSolverPtr_t problemSolver = new core::ProblemSolver;
    ///  Server server(problemSolver, argc, argv, isMultiThread);
    ///  \endcode
    ///  where \c isMultiThread specifies whether the server should process
    ///  requests using multi-thread policy of not.

    ///  After starting a name server and configuring your Corba implementation,
    ///  start the servers.
    ///  \code
    ///  server.startCorbaServer();
    ///  \endcode
    ///  Then, enter in the loop that handle the Corba requests
    ///  \code
    ///  server.processRequest(true);
    ///  \endcode
    ///  You can then send request to the servers.
    class HPP_CORBASERVER_DLLAPI Server
    {
    public:
      /// Constructor
      /// \param problemSolver the object that will handle Corba requests.
      /// \param argc, argv parameter to feed ORB initialization.
      /// \param multiThread whether the server may process request using
      ///        multithred policy.
      /// \note It is recommended to configure your Corba implementation
      ///       through environment variables and to set argc to 1 and argv to
      ///       any string.
      /// \note It is highly recommended not to enable multi-thread policy in
      ///       CORBA request processing if this library is run from an openGL
      ///       based GUI, since OpenGL does not support multithreading.
      Server (core::ProblemSolverPtr_t problemSolver, int argc,
	      const char* argv[], bool multiThread = false);

      /// Constructor
      /// \param problemSolverMap the object that will handle Corba requests.
      /// \param argc, argv parameter to feed ORB initialization.
      /// \param multiThread whether the server may process request using
      ///        multithred policy.
      /// \note It is recommended to configure your Corba implementation
      ///       through environment variables and to set argc to 1 and argv to
      ///       any string.
      /// \note It is highly recommended not to enable multi-thread policy in
      ///       CORBA request processing if this library is run from an openGL
      ///       based GUI, since OpenGL does not support multithreading.
      Server (ProblemSolverMapPtr_t problemSolverMap, int argc,
	      const char* argv[], bool multiThread = false);

      /// \brief Shutdown CORBA server
      ~Server ();

      /// \brief Initialize CORBA server to process requests from clients
      /// \return 0 if success, -1 if failure.
      void startCorbaServer ();

      /// \brief If ORB work is pending, process it
      /// \param loop if true, the function never returns,
      ///             if false, the function processes pending requests and
      ///             returns.
      int processRequest (bool loop);

      ProblemSolverMapPtr_t problemSolverMap ();

      core::ProblemSolverPtr_t problemSolver ();

    private:

      ///\name CORBA server initialization
      /// \{
      /// Initialize ORB and CORBA servers.

      /// \param argc, argv parameter to feed ORB initialization.
      /// \param multiThread whether the server may process request using
      ///        multithred policy.
      void initORBandServers (int argc, const char* argv[], bool multiThread);

      /// \}

      impl::Server* private_;

      /// pointer to core::ProblemSolver Object.
      ///
      /// At initialization, the constructor creates a core::ProblemSolver
      /// object and keeps a pointer to this object. All Corba requests are
      /// processed by this object. Notice that this pointer is passed
      /// to each constructor of implementation classes of the server
      /// Corba interface.
      ProblemSolverMapPtr_t problemSolverMap_;
    };

  } // end of namespace corbaServer.
} // end of namespace hpp.
#endif
