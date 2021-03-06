// Copyright 2016, Tobias Hermann.
// https://github.com/Dobiasd/frugally-deep
// Distributed under the MIT License.
// (See accompanying LICENSE file or at
//  https://opensource.org/licenses/MIT)

#pragma once

#include "fdeep/layers/layer.hpp"
#include "fdeep/recurrent_ops.hpp"

#include <string>
#include <functional>

namespace fdeep
{
namespace internal
{

class lstm_layer : public layer
{
  public:
    explicit lstm_layer(const std::string& name,
                        std::size_t n_units,
                        const std::string& activation,
                        const std::string& recurrent_activation,
                        const bool use_bias,
                        const bool return_sequences,
                        const bool return_state,
                        const float_vec& weights,
                        const float_vec& recurrent_weights,
                        const float_vec& bias)
        : layer(name),
          n_units_(n_units),
          activation_(activation),
          recurrent_activation_(recurrent_activation),
          use_bias_(use_bias),
          return_sequences_(return_sequences),
          return_state_(return_state),
          weights_(weights),
          recurrent_weights_(recurrent_weights),
          bias_(bias)
    {
    }

  protected:
    tensor5s apply_impl(const tensor5s &inputs) const override final
    {
        const auto input_shapes = fplus::transform(fplus_c_mem_fn_t(tensor5, shape, shape5), inputs);

        // ensure that tensor5 shape is (1, 1, 1, seq_len, n_features)
        assertion(inputs.front().shape().size_dim_5_ == 1
                  && inputs.front().shape().size_dim_4_ == 1
                  && inputs.front().shape().height_ == 1,
                  "size_dim_5, size_dim_4 and height dimension must be 1, but shape is '" + show_shape5s(input_shapes) + "'");

        const auto input = inputs.front();
        const fplus::maybe<tensor5> initial_state_h = inputs.size() > 1 ? inputs[1] : fplus::nothing<tensor5>();
        const fplus::maybe<tensor5> initial_state_c = inputs.size() > 2 ? inputs[2] : fplus::nothing<tensor5>();
        return lstm_impl(input, initial_state_h, initial_state_c,
            n_units_, use_bias_, return_sequences_, return_state_, weights_,
            recurrent_weights_, bias_, activation_, recurrent_activation_);
    }

    const std::size_t n_units_;
    const std::string activation_;
    const std::string recurrent_activation_;
    const bool use_bias_;
    const bool return_sequences_;
    const bool return_state_;
    const float_vec weights_;
    const float_vec recurrent_weights_;
    const float_vec bias_;
};

} // namespace internal
} // namespace fdeep
