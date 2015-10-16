// This file is part of the DerpVision Project.
// Licensing information can be found in the LICENSE file.
// (C) 2015 Group 13. All rights reserved.

#include <cstdlib>
#include <iostream>
#include <string>

#include <boost/program_options.hpp>

#include "core/Master.h"
#include "core/ProCam.h"
#include "slave/ProCamApplication.h"

using namespace dv::slave;


int main(int argc, char **argv) {
  try {
    namespace po = boost::program_options;

    // Set up the description of all command line options.
    po::options_description description("DerpVision Procam Server");
    description.add_options()
        ( "help"
        , "Print this message."
        )
        ( "--ip"
        , po::value<std::string>()->default_value("localhost")
        , "Set the IP of the master node."
        )
        ( "--port"
        , po::value<uint16_t>()->default_value(11630)
        , "Set the port on which Procam messages master node."
        );


    // Parse options.
    po::variables_map options;
    po::store(po::parse_command_line(argc, argv, description), options);
    po::notify(options);

    // Print help if requested.
    if (options.count("help")) {
      std::cout << description << std::endl;
      return EXIT_SUCCESS;
    }

    // Create & run the app.
    return ProCamApplication(
        options["--ip"].as<std::string>(),
        options["--port"].as<uint16_t>()
    ).run();
  } catch (const std::exception &ex) {
    std::cerr << "[Exception] " << ex.what() << std::endl;
    return EXIT_FAILURE;
  } catch (...) {
    std::cerr << "[Exception] Unknown exception." << std::endl;
    return EXIT_FAILURE;
  }
}

