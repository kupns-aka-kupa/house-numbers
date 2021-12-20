#include <boost/program_options.hpp>
#include <sysexits.h>
#include <torch/script.h>

namespace po = boost::program_options;

int main(int argc, const char *argv[]) {
  po::options_description desc("Allowed options");
  desc.add_options()("help,h", "produce help message")("version,v",
                                                       "print version string");

  po::options_description config("Configuration");
  config.add_options()("model,m", po::value<std::string>(), "Model file");

  desc.add(config);

  po::variables_map map;
  try {
    po::store(po::parse_command_line(argc, argv, desc), map);
  } catch (const std::exception &e) {
    std::cerr << e.what();
    return EX_USAGE;
  }
  po::notify(map);

  if (map.count("version")) {
    std::cout << PROJECT_NAME << ':' << PROJECT_VERSION;
    return EX_OK;
  }

  if (map.count("help")) {
    std::cout << desc;
    return EX_OK;
  }

  torch::jit::script::Module module;

  if (map.count("model")) {
    try {
      module = torch::jit::load(map["model"].as<std::string>());
    } catch (const c10::Error &e) {
      std::cerr << "error loading model\n" << e.what();
      return EXIT_FAILURE;
    }
  } else {
    std::cerr << "error loading file";
  }

  return EX_OK;
}