#include <torch/torch.h>

struct Net : torch::nn::Module {
  Net();

  torch::Tensor forward(torch::Tensor x);

  torch::nn::Linear fc1{nullptr}, fc2{nullptr}, fc3{nullptr};
};
