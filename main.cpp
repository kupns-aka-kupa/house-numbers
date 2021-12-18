#include "net.hpp"
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <pqxx/pqxx>

void init() {
  boost::log::core::get()->set_filter(boost::log::trivial::severity >=
                                      boost::log::trivial::trace);
}

const std::string schema = "mnist_d2a23ca6";

int main() {
  init();

  pqxx::connection connection{std::getenv("CONNECTION_STRING")};
  pqxx::work transaction{connection, PROJECT_NAME};

  if (connection.is_open()) {
    BOOST_LOG_TRIVIAL(info)
        << "Opened database successfully: " << connection.dbname()
        << " Backend version: " << connection.server_version()
        << " Protocol version: " << connection.protocol_version();

  } else {
    BOOST_LOG_TRIVIAL(fatal) << "Can't open database";
    return EXIT_FAILURE;
  }

  auto net = std::make_shared<Net>();

  auto data_loader = torch::data::make_data_loader(
      torch::data::datasets::MNIST(DATASET_PATH)
          .map(torch::data::transforms::Stack<>()),
      /*batch_size=*/64);

  // Instantiate an SGD optimization algorithm to update our Net's parameters.
  torch::optim::SGD optimizer(net->parameters(), /*lr=*/0.01);

  for (size_t epoch = 1; epoch <= 10; ++epoch) {
    size_t batch_index = 0;
    // Iterate the data loader to yield batches from the dataset.
    for (auto &batch : *data_loader) {
      // Reset gradients.
      optimizer.zero_grad();
      // Execute the model on the input data.
      torch::Tensor prediction = net->forward(batch.data);
      // Compute a loss value to judge the prediction of our model.
      torch::Tensor loss = torch::nll_loss(prediction, batch.target);
      // Compute gradients of the loss w.r.t. the parameters of our model.
      loss.backward();
      // Update the parameters based on the calculated gradients.
      optimizer.step();
      // Output the loss and checkpoint every 100 batches.
      if (++batch_index % 100 == 0) {
        BOOST_LOG_TRIVIAL(debug)
            << "Epoch: " << epoch << " | Batch: " << batch_index
            << " | Loss: " << loss.item<float>() << std::endl;

        transaction.exec_params("insert into mnist_d2a23ca6.loss (batch, epoch, loss) values ($1, $2, $3)", batch_index, epoch, loss.item<float>());
        transaction.commit();
        torch::save(net, "net.pt");
      }
    }
  }
  return EXIT_SUCCESS;
}
